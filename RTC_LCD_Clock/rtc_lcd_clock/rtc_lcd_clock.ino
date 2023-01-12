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
