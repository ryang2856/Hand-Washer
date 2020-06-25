/*
   An open source project showing people how to wash their hands with a colour display
   Please refer to the project inorder to get more details
   REQUIRED LIBRARIES:
    Adafruit GFX
    Adafruit ST7735
*/

#include <Adafruit_GFX.h>    // include the Adafruit GFX Library
#include <Adafruit_ST7735.h> // include the Adafruit Library for driving this specific SPI display
#include <SPI.h> // include the SPI library as we communicate with the display using SPI

#define TFT_CS D4
#define TFT_RST D3 //Declaring pins
#define TFT_DC  D2

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST); // init. the object tft 

int triggerDistance = 40;  //CHANGE THIS FOR HOW CLOSE A HAND MUST BE TO START THE PROGRAM

const int trigPin = D0; //Declaring pins for the sensor
const int echoPin = D1;

bool triggered = false; //check if the sensors value has got smaller than the trigger distance

long duration; // measure how long it took for both the signal to be sent and then come back
int distanceCm; //the current distance being measurement 

int runonce = 0;

extern  unsigned char  menuPage[];
extern  unsigned char  picture1[];
extern  unsigned char  picture2[];
extern  unsigned char  picture3[];
extern  unsigned char  picture4[];   //all the images
extern  unsigned char  picture5[];
extern  unsigned char  picture6[];
extern  unsigned char  picture7[];
extern  unsigned char  picture8[];

void setup()
{
  startup(); //setting up the display and sensor
  menu(); //displays menu
}

void loop()
{
  if (triggered == false) //if it isn't triggered
  {
    checkformovement(); //keep checking whether the sensor has detected someone
  }
  else
  {
    runSteps(); //if it did get triggered run the steps 
  }

}

void runSteps()
{
  step1(); //step1
  step2(); //step2
  step3(); //step3
  step4(); //step4
  step5(); //step5
  step6(); //step6
  step7(); //step7
  step8(); //step8
  clearscreen(8); //clear the screen
  menu(); //display the menu
  resetvariables(); //reset the variable
}

void startup()
{
  Serial.begin(9600);
  tft.initR(INITR_BLACKTAB); //start display
  tft.fillScreen(ST77XX_BLACK); //make it black
  tft.setTextWrap(false);
  tft.setRotation(2);
  pinMode(trigPin, OUTPUT); //init. inputs / outputs
  pinMode(echoPin, INPUT);
}

void menu()
{
  tft.drawBitmap(00, 00, menuPage, 128, 160, ST77XX_WHITE); //waiting for motion to be detected
  tft.drawLine(0, 40, 128, 40, ST77XX_BLUE); //draw the menu
}

void checkformovement()
{
  digitalWrite(trigPin, LOW); //turns off the wave
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // turns on the wave
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  //turns off the wave to be read
  duration = pulseIn(echoPin, HIGH); //measure the time it took to bounce back
  distanceCm = duration * 0.034 / 2; // works out the cm by taking the duration multiplying it by 0.034
  // which gives the length of both the wave going towards and coming
  //back so we divide it by 2
  if (triggerDistance > distanceCm)
  {
    triggered = true;
  }
}

void clearscreen(int i)
{
  if (runonce == i)
  {
    tft.fillScreen(ST77XX_BLACK);
    runonce += 1;
  }
}

void resetvariables()
{
  triggered = false;
  runonce = 0;
}

void counter(int time_start, int x, int y)
{
  for (int i = time_start; i != 0; i = i - 1)
  {
    tft.setCursor(x, y);
    tft.setTextSize(2);
    tft.println(i);
    delay(1000);
    tft.fillRect(x, y, 20, 15, ST77XX_BLACK);
  }
}


void step1()
{
  tft.setTextColor(ST77XX_GREEN);
  clearscreen(0);
  tft.fillRect(0, 45, 128, 3, ST77XX_BLUE);
  tft.drawBitmap(00, 00, picture1, 128, 160, ST77XX_WHITE);
  counter(5, 80, 25);
}

void step2()
{
  clearscreen(1);
  tft.fillRect(0, 40, 128, 3, ST77XX_BLUE);
  tft.drawBitmap(00, 00, picture2, 128, 160, ST77XX_WHITE);
  counter(5, 80, 20);
}

void step3()
{
  clearscreen(2);
  tft.fillRect(0, 37, 128, 3, ST77XX_BLUE);
  tft.drawBitmap(00, 00, picture3, 128, 160, ST77XX_WHITE);
  counter(5, 85, 18);
}

void step4()
{
  clearscreen(3);
  tft.fillRect(0, 45, 128, 3, ST77XX_BLUE);
  tft.drawBitmap(00, 00, picture4, 128, 160, ST77XX_WHITE);
  counter(5, 95, 22);
}

void step5()
{
  clearscreen(4);
  tft.fillRect(0, 63, 128, 3, ST77XX_BLUE);
  tft.drawBitmap(00, 00, picture5, 128, 160, ST77XX_WHITE);
  counter(5, 105, 33);
}

void step6()
{
  clearscreen(5);
  tft.fillRect(0, 40, 128, 1, ST77XX_BLUE);
  tft.drawBitmap(00, 00, picture6, 128, 160, ST77XX_WHITE);
  counter(5, 90, 19);
}

void step7()
{
  clearscreen(6);
  tft.fillRect(0, 59, 128, 3, ST77XX_BLUE);
  tft.drawBitmap(00, 00, picture7, 128, 160, ST77XX_WHITE);
  counter(5, 85, 27);
}

void step8()
{
  clearscreen(7);
  tft.fillRect(0, 65, 128, 3, ST77XX_BLUE);
  tft.drawBitmap(00, 00, picture8, 128, 160, ST77XX_WHITE);
  counter(5, 90, 12);
}
