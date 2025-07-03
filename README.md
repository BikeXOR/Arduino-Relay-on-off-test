使用Arduino nano單晶片，控制繼電器模組，以模擬USB-C插拔的現象

功能簡單說明：
1. 可單獨調整繼電器on與off的時間，單位為ms。
2. 使用Arduino ADC pin偵測USB Vbus上的電壓。
3. 程式會判斷電壓是否正常，例如USB-C接上後無輸出電壓，或是USB-C拔掉後還有電壓存在。
4. 新增LED燈號顯示異常狀態。
5. 新增蜂鳴器在異常狀態時啟動。

Arduino Pin腳定義

Vbus ADC 偵測腳位 (分壓電阻110kΩ and 13kΩ)
#define Vbus A0

繼電器模組腳位 (低電位觸發)
pin 2 (Vbus)
pin 3 (CC pin)
pin 4 (GND)
pin 5 (NA)

蜂鳴器腳位 (低電位觸發)
pin 13

LED腳位 (低電位觸發)
pin 6 (正常)
pin 7 (Error1 紅色)
pin 8 (Error2 藍色)
