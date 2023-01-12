# ArduinoProject
Uno 보드를 이용한 프로젝트 [물 수위 센서, RealTimeClock & LCD, 피에조 부저 플레이어]

## 1.1. Water Sensor Project
물 높이 센서를 이용하여 물 높이를 측정하는 실험
## 1.2. 실험 회로도
<p align="center"><img src="https://user-images.githubusercontent.com/78125194/211792463-a21147e8-cfd0-46ee-b98a-fe471179842a.png" width="600" height="400"/></p>
브레드 보드를 이용하여 회로망 구성, 센서의GND, VCC를 Arduino Uno에 연결하여 전원을 인가, 센서가 읽어오는 Analog CT 신호를 데이터 입력핀 A1에 할당 이후 실험 진행

## 1.3. 실험 코드
```
/********************************
Project Name : Water Level Sensor with Arduino Uno-Board
********************************/
// include libraries
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
/********************************/
int sensorPin = A1;  // 물 수위 센서 데이터 라인과 연결된 A1핀을 sensorpin으로  변수 설정
int ledPin = 8;      // LED핀 8번으로 연결, 정상적으로 연결되어 있는지 확인하는 용도
int sensorValue = 0; // 초기 센서값에 Trash value가 있을 수 있기에 0으로 변수 값 초기화
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);// LCD 사용을 위해 주소값 설정
/********************************/
void setup() {
  Serial.begin(9600); // 아두이노 우노의 통신 baudrate를 9800으로 설정, 통신시작
  pinMode(ledPin, OUTPUT);  // pinmode를  이용하여 아웃풋으로 설정
  lcd.begin (16, 2);    // 보유한 LCD는 2줄, 16칸의 데이터를 표시할 수 있으므로 이에 맞추어 설정
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH); // switch on the backlight
}

void loop() {

  sensorValue = analogRead(sensorPin); // 센서로부터 데이터 받아오기
 // 데이터 LCD로 출력
 // 먼저 센서의 민감도를 확인하기 위해 cm별 센서가 읽어오는 값을 확인
 // 센서의 민감도를 조정하기 위해서 600부터 뜨기 시작해서 범위를 [0, 600] = 1cm, [600, 660] = 2cm, [660, 670] = 3cm, [그 이상] = 4cm  로 조정함
 // if와 else if 문을 사용하여 구현함
 if (sensorValue <= 0) {
    lcd.setCursor(0, 0);
    lcd.print("Water lvl: 0mm");
    Serial.println("Water level: 0mm - Empty!");
  }
  else if (sensorValue > 0 && sensorValue <= 600) {
    lcd.setCursor(0, 0);
    lcd.print("Water lv:0-10mm");
    lcd.setCursor(0, 1);
    //lcd.print("Alarm! Alarm!");
    Serial.println("Water lv:0-10mm");
    digitalWrite(ledPin, HIGH);  // 물이 감지되기 시작하면 LED에 불이 들어와 정상 작동을 확인
  }
  else if (sensorValue > 600 && sensorValue <= 660) {
    lcd.setCursor(0, 0);
    lcd.print("Water lv:10-20mm");
    Serial.println("Water lv: 10-20mm");
  }
  else if (sensorValue > 660 && sensorValue <= 670) {
    lcd.setCursor(0, 0);
    lcd.print("Water lv:20-30mm");
    Serial.println("Water lv: 20-30mm");
  }
  else if (sensorValue > 670) {
    lcd.setCursor(0, 0);
    lcd.print("Water lv:30-40mm");
    Serial.println("Water lv: 30-40mm");
  }
  delay(100); // delay 1 second
  lcd.clear(); // LCD를 초기화해주지 않으면 Trash 값으로 인하여 정상적으로 LCD 출력이 이루어지지 않기에 결과 출력 후 초기화 해줌
  digitalWrite(ledPin, LOW);  // 한번의 루프 후 LED를 다시 점멸해줌으로서 LED가 계속 켜짐을 밤지
}
```
## 1.4. 실험 결과
https://user-images.githubusercontent.com/78125194/211794336-50ab645e-f1ed-47a2-a3b9-6139e5019d31.mp4

![KakaoTalk_20230111_202233662](https://user-images.githubusercontent.com/78125194/211793983-df9a25fe-a607-4fef-b9ac-e730afe5f303.png)

## ○ 참고 문서
* [Arduino Water Sensor tool](https://arduinogetstarted.com/tutorials/arduino-water-sensor) 참고
* [Arduino LCD tool](https://www.thegeekpub.com/236571/arduino-water-level-sensor-tutorial/) 참고
* [LiquidCrystal Library](https://codedragon.tistory.com/7098) 참고
****

## 2.1 Real Time Clock with LCD
DS1302 RTC 모듈을 이용하여 LCD 패널에 출력되는 시계 제작
## 2.2. 실험 회로도
<p align="center"><img src="https://user-images.githubusercontent.com/78125194/211796065-2dc61d14-0591-4ca7-8c0e-03fd64de5786.png" width="600" height="400"/></p>
RTC 모듈 VCC, GND, CLK, DAT, RST 핀으로 구성 이를 Uno 보드에 인가

## 2.3. 실험 코드
```
//---------------------------------
//           헤더 선언
//---------------------------------
#include <virtuabotixRTC.h>       // RTC 모듈 사용을 위한 헤더파일
#include <Wire.h>                 // I2C 통신을 위한 헤더파일
#include <LiquidCrystal_I2C.h>    // LCD 사용을 위한 헤더파일
//---------------------------------
//           변수 선언
//---------------------------------
virtuabotixRTC myRTC(6, 7, 8);    // CLK 6번핀, DAT 7번핀, RST 8번핀 
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD 사용을 위해 주소값 설정
//---------------------------------
//           셋업 함수
//---------------------------------
void setup()  {
  Serial.begin(9600);       // 시리얼 통신 시작
  // LCD 초기화
  lcd.init();
  lcd.backlight();          // LCD 초기화
  myRTC.setDS1302Time(00, 48, 8, 7, 1, 1, 2022);  // (초, 분, 시, 요일, 일, 월, 년)
}
//---------------------------------
//           루프 함수
//---------------------------------
// 기본적인 시간 데이터는 모두 DS1302로 부터 받아옴
void loop()  {
  myRTC.updateTime();     // 시간 업데이트
  lcd.setCursor(1,0);     // LCD 커서 위치를 1줄 1칸으로 설정
  lcd.print(myRTC.year);  // 년도 출력
  lcd.print("/");
  lcd.print(myRTC.month); // 월 출력
  lcd.print("/");
  lcd.print(myRTC.dayofmonth);  // 일 출력
  lcd.print("/");
  // 요일 정보에 따라서 요일 정보를 출력해주는 switch 구문
  // case 1 ~ case 7까지 각각 월 화 수 목 금 토 일을 출력하도록 함
  switch (myRTC.dayofweek) {    // 요일 출력
    case 1: 
      lcd.print("Sun");
      break;
    case 2: 
      Serial.print("MON");
      break;
    case 3: 
      lcd.print("TUE");
      break;
    case 4:   
      lcd.print("WED");
      break;
    case 5:  
      lcd.print("THU");
      break;
    case 6:   
      lcd.print("FRI");
      break;
    case 7:    
      lcd.print("SAT");
      break;
  }     
  lcd.setCursor(5,1);   // LCD 커서 위치를 2둘 5칸으로 설정
  lcd.print(myRTC.hours);   // 시간 출력
  lcd.print(":");
  lcd.print(myRTC.minutes);   // 분 출력
  lcd.print(":");
  lcd.print(myRTC.seconds);   // 초 출력

  delay(1000);      // 1초 딜레이
  lcd.clear();      // LCD 초기화
}

```
## 2.4. 실험 결과
https://user-images.githubusercontent.com/78125194/211798310-cc4b3e5a-3962-4559-86bc-81dd44485a6b.mp4

![KakaoTalk_20230111_202233662](https://user-images.githubusercontent.com/78125194/211798430-c16eb8dc-3ddf-465c-a5ce-2231bf98b6e2.png)

## ○ 참고 문서
* [Arduino Water Sensor tool](https://arduinogetstarted.com/tutorials/arduino-water-sensor) 참고
* [Arduino LCD tool](https://www.thegeekpub.com/236571/arduino-water-level-sensor-tutorial/) 참고
* [LiquidCrystal Library](https://codedragon.tistory.com/7098) 참고
****

## 3.1. Piezo Buzzer
 피에조 효과를 이용한 부저를 이용하여 음악 플레이어를 제작 하였다. 이 때 능동부저는 주파수에 따라 다양한 음을 낼 수 있는데, 아래의 주파수 영역에 따른 음역을 참고하였다.
## 3.2. 회로도 및 주파수 영역에 따른 음역대
<p align="center"><img src="https://user-images.githubusercontent.com/78125194/211968523-3a4370ae-bd4b-4e1e-a6e6-4363d15569f7.png" width="700" height="300"/></p>

## 3.3. 실험 코드
```
//-------------------------------------
//               Variables
//          음 높이 선언(공식 참고)
//-------------------------------------
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define MUSICPIN 8 //입력핀 번호

//-------------------------------------
//               Variables
//-------------------------------------
unsigned long preTime = 0;
unsigned long Duration = 0;
int currentnote = 0;

//-------------------------------------
//                 Music
//-------------------------------------
//고향의 봄 계이름 및 음표 정리
int melodySize = 58; //음 개수
int melody[] = {
  NOTE_G4,NOTE_G4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_A4,NOTE_G4,NOTE_G4,NOTE_C5,NOTE_E5,NOTE_D5,NOTE_C5,NOTE_D5,
  NOTE_E5,NOTE_E5,NOTE_D5,NOTE_D5,NOTE_C5,NOTE_D5,NOTE_C5,NOTE_A4,NOTE_A4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_E4,NOTE_D4,NOTE_C4,
  NOTE_D4,NOTE_D4,NOTE_E4,NOTE_C4,NOTE_D4,NOTE_D4,NOTE_E4,NOTE_G4,NOTE_A4,NOTE_C5,NOTE_E5,NOTE_D5,NOTE_C5,NOTE_D5,
  NOTE_E5,NOTE_E5,NOTE_D5,NOTE_D5,NOTE_C5,NOTE_D5,NOTE_C5,NOTE_A4,NOTE_A4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_E4,NOTE_D4,NOTE_C4,

  //솔솔미파솔라라솔솔도미레도레
  //미미레레도레도라라솔솔솔미레도
  //레레미도레레미솔라도미레도레
  //미미레레도레도라라솔솔솔미레도

};
//Mario main them tempo
int tempo[] = {
  88,88,176,176,88,88,88,44,88,88,88,176,176,66,
  88, 88,88,88,88,176,176,88,88,88,88,88,176,176,66,
  88,88,88,88,88,88,88,88,88,88,88,176,176,66,
  88,88,88,88,88,176,176,88,88,88,88,88,88,176,176,66,

  //4분음표 : 88 341ms
  //8분음표 : 176 682ms
  //2분음표 : 44 1364ms
  //점 2분음표 : 66 2046ms
};

//-------------------------------------
//            setup & loop
//-------------------------------------
void setup() {
  pinMode(MUSICPIN, OUTPUT); //8번핀 출력으로 설정
}

void loop() {
    if(millis() < preTime + Duration) { //속도 조절용 함수 너무 빨리 나오면 소리가 망가짐
        return;
    }
    noTone(11); // 다음음 재생까지 잠시 멈춤
    
    if(currentnote >= melodySize) //음표 조절
        currentnote = 0;
    int noteDuration = 60000/tempo[currentnote]; // 정상속도시에 1분에 88개의 4분음표 재생
                                                   // 60*1000MS/TEMPO
    
    tone(MUSICPIN, melody[currentnote], noteDuration); // tone(pin, frequency, duration)
                                                         // pin : tone을 발생시킬 핀, frequency : tone의 주파수, duration : tone의 지속시간
    
    preTime = millis();
    Duration = noteDuration * 1.3;
    
    currentnote++;
}
```
## 3.4. 실험 결과
<p align="center"><img src="https://user-images.githubusercontent.com/78125194/211969106-52ffdc3a-238e-441e-8632-ebf6848dc408.png" width="700" height="300"/></p>

## ○ 참고 문서
* [Piezo Buzzer Tutorial](https://www.instructables.com/How-to-use-a-Buzzer-Arduino-Tutorial/) 참고
* [Piezo Buzzer Info](https://www.makerguides.com/interface-piezo-buzzer-with-arduino/) 참고
****
