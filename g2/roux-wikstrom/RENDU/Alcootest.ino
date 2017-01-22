#include <rgb_lcd.h>
#include <Wire.h>

rgb_lcd lcd;

#define blueLEDPin 3
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

const int mq3AnalogPin = A0;
const int button = A1;
bool button_status = false;
String messagePrincipal = "Appuyez sur le bouton pour commencer";
String msg1 = "Vous pouvez continuer de consommer sans risque";
String msg2 = "Si vous souhaitez prendre la voiture, il ne faut plus rien boire";
String msg3 = "Ne pas conduire. Si vous continuez, vous risquez de mal finir.";
String msg4 = "Ne pas conduire!Pour se souvenir demain, il vous faudra des photos.";
String msg5 = "Ne pas conduire!Vous risauez de chuter. Boire de l'eau.";
String msg6 = "Ne pas conduire!Recommande de se mettre en PLS.";
String msg7 = "Danger de mort! Il est recommande d'appeler le  18.";

void setup() 
{
    // set up the LCD's number of columns and rows:
    lcd.begin(47, 2);
    pinMode(blueLEDPin, OUTPUT);
    Serial.begin(9600); // open serial at 9600 bps
    
    lcd.setRGB(colorR, colorG, colorB);
    lcd.setRGB(colorR, colorG, colorB);

    delay(1000);
}
  
void printLong(String msg){
  lcd.clear();
  lcd.setCursor(0,0);
  int len = msg.length();
  if(len<=16) {
    lcd.print(msg);
  } else if(len > 16 && len<= 32){
    lcd.print(msg.substring(0,16));
    lcd.setCursor(0,1);
    if (msg[16] == ' ') {
      lcd.print(msg.substring(17, 32));
    } else {
    lcd.print(msg.substring(16,32));
    }
    delay(3500);
    lcd.clear();
  }else if(len>32) {
    lcd.print(msg.substring(0,16));
    lcd.setCursor(0,1);
    if (msg[16] == ' ') {
      lcd.print(msg.substring(17, 32));
    } else {
    lcd.print(msg.substring(16,32));
    }
    delay(3500);
    lcd.clear();
    printLong(msg.substring(32));
  }
}

void loop() 
{
      button_status = false;
      lcd.setCursor(4, 0);
      lcd.print(messagePrincipal);
      
      while (!button_status) {
        button_status = digitalRead(button);
        lcd.scrollDisplayLeft();
        delay(200);
      }
      
      lcd.clear();
      int j;
      
      for (j=5; j>0; j--){
        lcd.setCursor(0, 0);
        lcd.print("Soufflez dans :");
        delay(250);
        lcd.setCursor(0,1);
        lcd.print(j);
        delay(750);
        lcd.clear();
      }
      
      lcd.print("Soufflez !");
      delay(250);
      digitalWrite(blueLEDPin, HIGH);
      float avAlcValue = 0.0;
      int temp;
      int i= 0;
      float mq3ValueTot = 0.0;
      
      for (i=0; i<300; i++) {
        float sensorValue = analogRead(A0);
        float sensor_volt=sensorValue/1024.0*5.0;
        float RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL
        float ratio = RS_gas/6.407;  // ratio = RS/R0
        mq3ValueTot = mq3ValueTot + ratio;
        delay(10);
       }
       
      lcd.clear();
      digitalWrite(blueLEDPin, LOW);
      lcd.print("C'est bon !");
      delay(1000);
      lcd.clear();
      avAlcValue = mq3ValueTot / 300.0;
      lcd.setCursor(0,0);
      
      if (avAlcValue > 2.2) { 
        lcd.print("Alcoolemie");
        lcd.setCursor(0,1);
        lcd.print("estimee:<0,1mg/L");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0,0);
        printLong(msg1);
       }else if(avAlcValue > 1.2 && avAlcValue <= 2.2) { //First degree, Behavior nearly normal by ordinary observation
        lcd.print("Alcoolemie estimee :");
        lcd.setCursor(0,1);
        lcd.print("0,1 mg/L");
        delay(2000);
        printLong(msg2);
       }else if(avAlcValue > 0.9 && avAlcValue <= 1.2) { //second degree, mild euphoria, sociability, talkitiveness etc
        lcd.print("Alcoolemie estimee : ");
        lcd.setCursor(0,1);
        lcd.print("0,3 mg/L");
        delay(2000);
        printLong(msg3);
       } else if (avAlcValue > 0.55 && avAlcValue <= 0.9) {
        /*Emotional instability; loss of critical judgment
          Impairment of perception, memory and comprehension
          Decreased sensitory response; increased reaction time
          Reduced visual acuity; peripheral vision and glare recovery
          Sensory-motor incoordination; impaired balance
          Drowsiness
         */
        lcd.print("Alcoolemie estimee : ");
        lcd.setCursor(0,1);
        lcd.print("0,8 mg/L");
        printLong(msg4);
       } else if(avAlcValue > 0.5 && avAlcValue <= 0.55) {
        /*Disorientation, mental confusion; dizziness
          Exaggerated emotional states
          Disturbances of vision and of perception of color, form, motion and dimensions
          Increased pain threshold
          Increased muscular incoordination; staggering gait; slurred speech
          Apathy, lethargy
         */
        lcd.print("Alcoolemie estimee : ");
        lcd.setCursor(0,1);
        lcd.print("1,0 mg/L");
        printLong(msg5);
       } else if (avAlcValue > 0.35 && avAlcValue <= 0.5) {
        /*General inertia; approaching loss of motor functions
          Markedly decreased response to stimuli
          Marked muscular incoordination; inability to stand or walk
          Vomiting; incontinence
          Impaired consciousness; sleep or stupor
         */
        lcd.print("Alcoolemie estimee : ");
        lcd.setCursor(0,1);
        lcd.print("1,5 mg/L");
       } else if (avAlcValue > 0.3 && avAlcValue <= 0.35) {
        // DONT DRINK ANYTHING ELSE (than water)
        lcd.print("Alcoolemie estimee : ");
        lcd.print("2,2 mg/L");
       } else {
        lcd.print("Danger de mort !.");
       }
       
      delay(3000);
      lcd.clear();
}
