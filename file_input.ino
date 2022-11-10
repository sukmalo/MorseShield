#define DATA_PIN 2
#define DATA_LEVEL LOW
#define SPACE_LEVEL HIGH
#define DATA true
#define SPACE false
#define DASH_DURATION 3
#define DOT_DURATION 1
#define DURATION 7
#define TU 100

long start_data, start_space;
long duration[100];
bool color[100];
int index = 0;
int previous = SPACE;
String CODES[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};
int NLETTERS = 27;

void setup() {
  Serial.begin(9600);
  pinMode(DATA_PIN, INPUT);
}

void loop() {
  fill_arays();
  decode_letter();
}

void decode_letter(){
  for(int i = 0; i<index; i++){
    if (duration[i] >= DASH_DURATION && color[i] == SPACE){
      String code = "";
      for(int j=0; j<i; j++){
        if(duration[j] == DASH_DURATION && color[j] == DATA){
         code+='-';
        }
        if(duration[j] == DOT_DURATION && color[j] == DATA){
         code+='.';
        }
        duration[j] = 0;
      }
      for(int iletter=0; iletter<NLETTERS; iletter++){
        if (code==CODES[iletter]){
          Serial.println(LETTERS[iletter]);
        }
      }
    }
    if (duration[i]==DURATION && color[i] == SPACE){
      Serial.println(' ');
    }
  }
}

void fill_arays() {
  int current = digitalRead(DATA_PIN);
  if (current == DATA_LEVEL && previous == SPACE_LEVEL){
    start_data = millis();
    duration[index] = (millis() - start_space + 0.5 * TU) / TU;
    color[index]=SPACE;
    index++;
  }
  if (current == SPACE_LEVEL && previous == DATA_LEVEL){
    start_space = millis();
    duration[index] = (millis() - start_data + 0.5 * TU) / TU;
    color[index]=DATA;
    index++;
  }
  previous = current; 
}
