#define DATA_PIN 9
#define DATA_LEVEL LOW
#define SPACE_LEVEL HIGH
#define DASH_DURATION 3
#define DOT_DURATION 1
#define DURATION 7
#define TU 100


String CODES[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..", " "};
char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};
int NLETTERS = 27;
String last_code=" ";


void setup() {
  Serial.begin(9600);
  pinMode(DATA_PIN, OUTPUT);
}

void loop() {
  if(Serial.available()>=1){
    char letter = Serial.read();
    for (int iletter; iletter < NLETTERS; iletter++){
      if(letter == LETTERS[iletter]){
        String code = CODES[iletter];
        send_letter(code);
      }
    }
  }

}
void send_letter(String code){
  if (code==" "){
    last_code=" ";
    digitalWrite(DATA_PIN, SPACE_LEVEL);
    delay((DASH_DURATION+1)*TU);
  }else{
    int code_len = code.length();
    for(int i = 0; i < code_len; i++){
      char symbol = code[i];
      if(last_code!=" "){
        digitalWrite(DATA_PIN, SPACE_LEVEL);
        delay(TU);
      }
      if (symbol=='.'){
        digitalWrite(DATA_PIN, DATA_LEVEL);
        delay(DOT_DURATION*TU);
      }
      if (symbol=='-'){
        digitalWrite(DATA_PIN, DATA_LEVEL);
        delay(DASH_DURATION*TU);
      }
      last_code=symbol;
    }
    last_code=" ";
    delay(DASH_DURATION*TU);
  }
}
