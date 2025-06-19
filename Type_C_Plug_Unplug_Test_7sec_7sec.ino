#define Vbus A0
// === Vbus Voltage Threshold ===
// ADC讀值100 約為5.78V，判斷標準
#define VBUS_THRESHOLD 100
int Vbus_Voltage;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  // Relay pin 2,3,4,5
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  // LED pin 6,7,8
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  //Buzzer pin.
  pinMode(13, OUTPUT);
  //Voltage sense pin.
  pinMode(Vbus, INPUT);
  Serial.begin(9600);
  initialSetup();
}

// the loop function runs over and over again forever
void loop() {
  //Relay off 5 sec
  Relay_OFF();
  delay(10000);
  Vbus_Voltage = analogRead(Vbus);
  VoltagePrint();
  //check Vbus pin is non Voltage.
  //5V分壓後，IC analog讀到的值大約120.
  //分壓電阻130k,12k
  if(Vbus_Voltage>VBUS_THRESHOLD){
    //Buzzer_Alarm();
    while(1){
      Buzzer_Alarm();
      LED_Fail_2();
    }
  }
  LED_OK();
  //delay(5000);
  //Relay on 5sec
  Relay_ON();
  delay(700);
  delay(10000);
  Vbus_Voltage = analogRead(Vbus);
  VoltagePrint();
  //check voltage > 5V
  if(Vbus_Voltage<VBUS_THRESHOLD){
    //Buzzer_Alarm();
    while(1){
      Buzzer_Alarm();
      LED_Fail_1();
    }
  }
  LED_OK();
}

void LED_OK(){
  digitalWrite(8, LOW);//OK
  digitalWrite(7, HIGH);//Fail 1
  digitalWrite(6, HIGH);//Fail 2
}
void LED_Fail_1(){
  digitalWrite(8, HIGH);//OK
  digitalWrite(7, LOW);//Fail 1
  digitalWrite(6, HIGH);//Fail 2
}
void LED_Fail_2(){
  digitalWrite(8, HIGH);//OK
  digitalWrite(7, HIGH);//Fail 1
  digitalWrite(6, LOW);//Fail 2
}
void Buzzer_Alarm(){
  digitalWrite(13,LOW);
  //delay(1000);
  //digitalWrite(13,HIGH);
  //delay(1000);
}
void initialSetup(){
  // Relay 全部 off
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  // LED 全部Off
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  // Buzzer Off
  digitalWrite(13,HIGH);
  // 全域變數 設定初始狀態
  Vbus_Voltage=0;
  // 開機 點亮LED測試一下會不會亮
  // Optional: blink LED 8 three times
  for(int i=0; i<3; i++){
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    delay(200);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    delay(200);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    delay(200);
  }
  //測試完畢關閉LED燈
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  // 開機 測試Buzzer會不會叫，叫兩聲來聽聽
  for(int i=0; i<2; i++){
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(100);
  }
}
void Relay_ON(){
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  delay(50);
  digitalWrite(3, LOW);
}
void Relay_OFF(){
  digitalWrite(3, HIGH);
  delay(50);
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
}
void VoltagePrint(){
  Serial.print("Vbus=");
  Serial.print(Vbus_Voltage*42);
  Serial.println("mV");
}