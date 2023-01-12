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
    noTone(11); // 다음음 재생까지 잠시 멈춤,
    
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
