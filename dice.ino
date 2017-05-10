
/*
 * FILE          : diceGame.ino
 * PROJECT       : Final Project
 * PROGRAMMER    : SAGAR PATEL
 * FIRST VERSION : 17th April 2016
 * DESCRIPTION   : This code works when pushbutton is pressed it generates a random
 *                 numbers on LEDs between 1 to 6 and diplay it on 16 X 2 LCD.Then 
 *                 it comapares that number with 7 or 11 and according to that it
 *                 displays congrats and good luck message on LCD.After that it st-
 *                 ores the values on EEPROM memory of teensy and when second push-
 *                 button is pressed it displays last 10 results from EEPROM memory
 *                 on serial port.
 */

//----------- header files ----------//
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

//-------------- globals ------------//
LiquidCrystal lcd(18, 19, 20, 21, 22, 23);
//liquidCrystal   lcd(RS, E,  D4, D5, D6, D7);
const int8_t  pinLeds1   = 9;
const int8_t  pinLeds2   = 8;
const int8_t  pinLeds3   = 7;
const int8_t  pinLeds4   = 6;
const int8_t  pinLeds5   = 17;
const int8_t  pinLeds6   = 16;
const int8_t  pinLeds7   = 15;
const int8_t  pinLeds8   = 14;
const int8_t  buttonPin  = 5;
const int8_t  pbPin      = 10;
const int8_t  speakerPin = 1;
int8_t        flag       = 0;
int8_t        pbState;
int8_t        buttonState;

//-------------- prototypes -----------//
void greetingDisplay();
void readPushbuttonsStatus();
void ledStatsWhenPbNotPressed();
void storeTheDiceNumbersInMemory(int8_t totalDiceNumber);
void compareDiceNumberWithWinningNumbers(int8_t totalDiceNumber);
void diceGame();

//--------------- function definations --------------//
//
// FUNCTION      : greetingDisplay()
// DESCRIPTION   : Displays the Welcome Info only on startup.
// PARAMETERS    : No Parameters.
// RETURNS       : Does not return anything
//
void greetingDisplay()
{
  lcd.setCursor(5, 0);
  lcd.printf("WelCome");
  lcd.setCursor(2, 1);
  lcd.printf("To Dice Game");
  delay(5000);
  lcd.clear();
  lcd.printf("Press Button to");
  lcd.setCursor(0, 1);
  lcd.printf("Roll the dice ");
  delay(5000);
  lcd.clear();
}

//
// FUNCTION      : readPushbuttonsStatus()
// DESCRIPTION   : Read the status of pushbuttons if they are pressed
//                 or not.
// PARAMETERS    : No Parameters.
// RETURNS       : Does not return anything
//
void readPushbuttonsStatus()
{
  buttonState = digitalRead(buttonPin);
  pbState     = digitalRead(pbPin);
}

//
// FUNCTION      : displayTheLast10Values()
// DESCRIPTION   : Read the 10 values from EEPROM memory and
//                 display it on serial port.
// PARAMETERS    : No Parameters.
// RETURNS       : Does not return anything
//
void displayTheLast10Values()
{
  if (flag == 0)
  {
    int8_t address = 0;
    Serial.printf("Last 10 Results :\n");
    for (int8_t i = 0; i < 10; i++)       // read the 10 values from EEPROM
    {
      int8_t value = EEPROM.read(address);
      Serial.printf("value = %d \n", value);
      address = address + 1;
    }
    flag = 1;
  }
}

//
// FUNCTION      : storeTheDiceNumbersInMemory()
// DESCRIPTION   : Store the dice numbers from the first address in
//                 EEPROM memory of teensy.
// PARAMETERS    : totalDiceNumber : the value of dice number.
// RETURNS       : Does not return anything
//
void storeTheDiceNumbersInMemory(int8_t totalDiceNumber)
{
  int8_t addr = 0;
  EEPROM.write(addr, totalDiceNumber);
  addr = addr + 1;
}

//
// FUNCTION      : compareDiceNumberWithWinningNumbers()
// DESCRIPTION   : Compare the dice value with 7 and 11 if it
//                 happens it shows congrats message otherwise
//                 it shows good luck message.
// PARAMETERS    : totalDiceNumber : the value of dice number.
// RETURNS       : Does not return anything
//
void compareDiceNumberWithWinningNumbers(int8_t totalDiceNumber)
{
  if (totalDiceNumber == 7 || totalDiceNumber == 11)        // compare dice number with 7 and 11
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printf("congrats!");
    tone(speakerPin, 570, 400);                             // play a note for 400 ms duration
    delay(750);
    tone(speakerPin, 430, 400);
    delay(750);
    lcd.setCursor(0, 1);
    lcd.printf("You won jackpot");
    delay(2000);
    lcd.clear();
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printf("Better luck");
    tone(speakerPin, 100, 900);                            // play a note for 900 ms duration
    delay(750);
    lcd.setCursor(0, 1);
    lcd.printf("next time");
    delay(2000);
    lcd.clear();
  }
}

//
// FUNCTION      : ledStatsWhenPbNotPressed()
// DESCRIPTION   : if pb not pressed turns off all LEDs.
// PARAMETERS    : No Parameters.
// RETURNS       : Does not return anything
//
void ledStatsWhenPbNotPressed()
{
  digitalWrite (pinLeds1, LOW);
  digitalWrite (pinLeds2, LOW);
  digitalWrite (pinLeds3, LOW);
  digitalWrite (pinLeds4, LOW);
  digitalWrite (pinLeds5, LOW);
  digitalWrite (pinLeds6, LOW);
  digitalWrite (pinLeds7, LOW);
  digitalWrite (pinLeds8, LOW);
}

//
// FUNCTION      : diceGame()
// DESCRIPTION   : Generates random numbers if pushbutton is pressed
//                 and display the results on LCD.
// PARAMETERS    : No Parameters.
// RETURNS       : Does not return anything
//
void diceGame()
{
  int8_t ran;
  int8_t ran2;

  readPushbuttonsStatus();            //function call

  //-------------------- if --------------------//
  if (pbState == LOW )
  {
    displayTheLast10Values();
  }

  //------------------- else if ----------------//
  else if (buttonState == LOW)
  {
    ran  = random (1, 6);            //generates random number between 1 & 6
    ran2 = random (1, 6);

    //-------------- No. 1 ------------//
    if (ran == 1 )
    {
      digitalWrite (pinLeds4, HIGH);
      delay (500);
    }
    else if (ran2 == 1)
    {
      digitalWrite (pinLeds8, HIGH);
      delay (500);
    }

    //-------------- No. 2 ------------//
    if (ran == 2)
    {
      digitalWrite (pinLeds1, HIGH);
      delay (1000);
    }
    else if  (ran2 == 2)
    {
      digitalWrite (pinLeds5, HIGH);
      delay (1000);
    }

    //-------------- No. 3 ------------//
    if (ran == 3)
    {
      digitalWrite (pinLeds3, HIGH);
      digitalWrite (pinLeds4, HIGH);
      delay (1200);
    }
    else if ( ran2 == 3)
    {
      digitalWrite (pinLeds7, HIGH);
      digitalWrite (pinLeds8, HIGH);
      delay (1200);
    }

    //-------------- No. 4 ------------//
    if (ran == 4)
    {
      digitalWrite (pinLeds1, HIGH);
      digitalWrite (pinLeds3, HIGH);
      delay (1400);
    }
    else if (ran2 == 4)
    {
      digitalWrite (pinLeds5, HIGH);
      digitalWrite (pinLeds7, HIGH);
      delay (1400);
    }

    //-------------- No. 5 ------------//
    if (ran == 5)
    {
      digitalWrite (pinLeds1, HIGH);
      digitalWrite (pinLeds3, HIGH);
      digitalWrite (pinLeds4, HIGH);
      delay (800);
    }
    else   if (ran2 == 5)
    {
      digitalWrite (pinLeds5, HIGH);
      digitalWrite (pinLeds7, HIGH);
      digitalWrite (pinLeds8, HIGH);
      delay (800);
    }

    //-------------- No. 6 ------------//
    if (ran == 6 )
    {
      digitalWrite (pinLeds1, HIGH);
      digitalWrite (pinLeds2, HIGH);
      digitalWrite (pinLeds3, HIGH);
      delay (1100);
    }
    else if (ran2 == 6)
    {
      digitalWrite (pinLeds5, HIGH);
      digitalWrite (pinLeds6, HIGH);
      digitalWrite (pinLeds7, HIGH);
      delay (1100);
    }

    //------------------------------------------------------------//
    int8_t totalDiceNumber = ran + ran2;                    //total of two dice number
    lcd.setCursor(0, 0);
    lcd.printf("Your no is %i", totalDiceNumber);           //display the dice number on LCD
    delay(3000);
    lcd.clear();
    storeTheDiceNumbersInMemory(totalDiceNumber);
    compareDiceNumberWithWinningNumbers(totalDiceNumber);
    //------------------------------------------------------------//
  }
  //--------------------------------- else --------------------------------------//
  else
  {
    ledStatsWhenPbNotPressed();
  }
}

//***************************** SETUP *****************************//
void setup ()
{
  lcd.begin   (16, 2);              //initializes the LCD to 2 X 16
  Serial.begin(9600);
  pinMode     (pinLeds1,   OUTPUT);
  pinMode     (pinLeds2,   OUTPUT);
  pinMode     (pinLeds3,   OUTPUT);
  pinMode     (pinLeds4,   OUTPUT);
  pinMode     (pinLeds5,   OUTPUT);
  pinMode     (pinLeds6,   OUTPUT);
  pinMode     (pinLeds7,   OUTPUT);
  pinMode     (pinLeds8,   OUTPUT);
  pinMode     (speakerPin, OUTPUT);
  pinMode     (buttonPin,  INPUT_PULLUP);
  pinMode     (pbPin,      INPUT_PULLUP);
  randomSeed  (analogRead(0));
  greetingDisplay();                //welcome info
}

//***************************** LOOP ******************************//
void loop()
{
  diceGame();
}
