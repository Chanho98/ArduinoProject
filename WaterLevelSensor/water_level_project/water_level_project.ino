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
