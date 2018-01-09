#include <Adafruit_NeoPixel.h>


#define PIN            6
#define NUMPIXELS      54

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

int distance = 0;
int dotDelay = 1000;
int dashDelay = 3000;
int startLoopDelay = 7000;

struct {
  char letter,
  *code;} Map[] =
{
  { 'A', ".-" },
  { 'B', "-..." },
  { 'C', "-.-." },
  { 'D', "-.." },
  { 'E', "." },
  { 'F', "..-." },
  { 'G', "--." },
  { 'H', "...." },
  { 'I', ".." },
  { 'J', ".---" },
  { 'K', ".-.-" },
  { 'L', ".-.." },
  { 'M', "--" },
  { 'N', "-." },
  { 'O', "---" },
  { 'P', ".--." },
  { 'Q', "--.-" },
  { 'R', ".-." },
  { 'S', "..." },
  { 'T', "-" },
  { 'U', "..-" },
  { 'V', "...-" },
  { 'W', ".--" },
  { 'X', "-..-" },
  { 'Y', "-.--" },
  { 'Z', "--.." },
  { ' ', "     " }, //Gap between word, five units 
    
  { '1', ".----" },
  { '2', "..---" },
  { '3', "...--" },
  { '4', "....-" },
  { '5', "....." },
  { '6', "-...." },
  { '7', "--..." },
  { '8', "---.." },
  { '9', "----." },
  { '0', "-----" },
    
  { '.', "·–·–·–" },
  { ',', "--..--" },
  { '?', "..--.." },
  { '!', "-.-.--" },
  { ':', "---..." },
  { ';', "-.-.-." },
  { '(', "-.--." },
  { ')', "-.--.-" },
  { '"', ".-..-." },
  { '@', ".--.-." },
  { '&', ".-..." },
};


void setup() {
  pixels.begin();
  Serial.begin(9600);
}

void loop() {

  distance = analogRead(A0);
  Serial.print("distance:");
  Serial.println(distance);
  if (distance < 100) {
    ledOff();

  } else {
    ledDelay();

    // read input from console
    String msg = readInput() ;

    if (msg.length() > 0) {
        distance  = map(distance, 60, 500, 0, 255);
        
        Serial.println("starting:");
        char *myMorse;
      
        for (int i = 0; i < sizeof(msg) - 1; i++) {
          char l = msg[i];
          l = toupper(l);
          myMorse = getMorse(l);
          Serial.print("morse: ");
          Serial.print(l);
          Serial.print(" : ");
          Serial.println(myMorse);
    
          displayMessage(myMorse) ;
        }
    }
  }
}

void ledOn() {
  for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // off color.;
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
}

void ledOff() {
   for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // off color.;
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
}

void ledDelay() {
  for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 255)); // off color.;
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval);
   }
}

void dash() {
  ledOn();
  delay(dashDelay);
  ledOff();
  delay(dashDelay);
}

void dot() {
  ledOn();
  delay(dotDelay);
  ledOff();
  delay(dotDelay);
}

void startLoopPause() {
  ledOff();
  delay(startLoopDelay);
}

void spacePause(){
  ledOff();
  delay(dashDelay);
}

char * getMorse(char l){
    for (int i = 0; i < 47; i++) {
      if(l == Map[i].letter) {
        return Map[i].code;
      }
    }
}

void displayMessage(char *letter) {
   int i = 0;
   while (letter[i] != '\0') {
      distance = analogRead(A0);
   
      if (distance > 100) {
        Serial.print("display x : ");
        Serial.println(letter[i]);
        switch(letter[i]) {
          case '.':
            Serial.println("dot");
            dot();
            break;
          case '-':
            Serial.println("dash");
            dash();
            break;
          case ' ':
            startLoopPause();
            break;
        }
      } else {
        break ;  
      }

      i++;
    }
}

String readInput() {
  String readString;
  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the String readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }

  if (readString.length() >0) {
    Serial.print("Mirror is giving : ");
    Serial.println(readString);  //so you can see the captured String 
    
    //readString="";
  }

   return readString;
}  
