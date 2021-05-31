// leds
const int redPin = 12;
const int greenPin = 11;
const int bluePin = 10;
const int whitePin = 9;

// buttons
const int redButton = 8;
const int greenButton = 7;
const int blueButton = 6;
const int whiteButton = 5;

// buzzer
const int buzzer = 4;

// level of game
const int num_level = 10;

int active_led[10];

bool is_true[10] = {false};

int delayTime = 2000;

bool success = false;

// check if button is pressed
int redB;
int greenB;
int blueB;
int whiteB;

// notes
int C = 262;
int D = 294;
int E = 330;
int F = 349;
int G = 392;
int A = 440;
int B = 494;
int C_ = 523;
int notes[8] = {C, D, E, F, G, A, B, C_};

void setup()
{
  // leds
  pinMode(redPin, OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(whitePin, OUTPUT);
  
  // buzzer
  pinMode(buzzer, OUTPUT);
  
  //buttons
  pinMode(redButton, INPUT);
  pinMode(greenButton, INPUT);
  pinMode(blueButton, INPUT);
  pinMode(whiteButton, INPUT);
  
  Serial.begin(9600);
}

void loop()
{ 
	for(int i = 0; i < num_level; i++)
    {	
      	// if success is false, return to level 1
      	if(!success)
          i = 0;
      
      	Serial.print("Level: ");
      	Serial.println(i + 1);
      
        success = game(i + 1);
    }
  
  	// if game finished restart game
  	reset();
}

void lightLed(int pin, int d)
{
 	digitalWrite(pin, HIGH);
  	lightSpeaker(pin, d / 10);
  	delay(d);
  	digitalWrite(pin, LOW);
}

void lightSpeaker(int pin, int d)
{
	 if(pin == 12)
       tone(buzzer, G, d);
  	 if(pin == 11)
       tone(buzzer, D, d);
  	 if(pin == 10)
       tone(buzzer, B, d);
  	 if(pin == 9)
       tone(buzzer, A, d);
}

// take input
bool input(int level)
{
  	// return true if player pass round
  	bool flag = false;
  	
  	// if pressed false button return false
  	bool quit = false;
    int count = 0,j,pressed=0;
  
  	for(int i = 0; !quit && i < level; i++)
    {   
      	// switching between button's delay 
        delay(500);
      
      // look for if button pressed for 5s
      for(j=0;pressed==0 && j<5000;j++){ // so it breaks if a button is pushed or when time(5s) runs out
      	
        redB = digitalRead(redButton);
        greenB = digitalRead(greenButton);
  		blueB = digitalRead(blueButton);
  		whiteB = digitalRead(whiteButton);
        
        if(redB==1){
          pressed=1;
        }
        else if(greenB==1){
          pressed=1;
        }
        else if(blueB==1){
          pressed=1;
        }
        else if(whiteB==1){
          pressed=1;
        }
        
        delay(1);
      }
      	Serial.println(redB);
        Serial.println(greenB);
      	Serial.println(blueB);
      	Serial.println(whiteB);
    	
      	// check if buttons and lights matched
      
      	if(active_led[i] == 12 && redB == 1)
        {
          Serial.println("RED");
          lightLed(redPin, delayTime);
          is_true[i] = true;
        }
      	if(active_led[i] == 11 && greenB == 1)
        {
          Serial.println("GREEN");
          lightLed(greenPin, delayTime);
          is_true[i] = true;
        }
        if(active_led[i] == 10 && blueB == 1)
        {
          Serial.println("BLUE");
          lightLed(bluePin, delayTime);
          is_true[i] = true;
        }
        if(active_led[i] == 9 && whiteB == 1)
        {
          Serial.println("WHITE");
          lightLed(whitePin, delayTime);
          is_true[i] = true;
        }
      
      // if false break loop
      if(!is_true[i])
        quit = true;
       
      pressed = 0;
    }
  
  for(int i = 0; i < level; i++)
  {
    if(is_true[i])
      count++;
  }
  
  if(count == level)
    flag = true;
  
  return flag;
}

// main game code
bool game(int level)
{
  bool flag = false;
  
  // make level design
  for(int i = 0; i < level; i++)
  {
  	int randomNum = random(9, 13);
    lightLed(randomNum, delayTime);
    active_led[i] = randomNum;
  }
  
  // delay for waiting player
  Serial.println("Wait!!!");
  delay(1000);
  Serial.println("Your Turn!!!");
  flag = input(level);
  Serial.println("Exit' input");
  
  if(flag)
  	allright();
  else
   	reset();
  
  return flag;
}

// if game finished or round lost reset
void reset()
{
  	Serial.println("Reset | Restarting...");
  
 	delayTime = 2000;
  	
  	for(int i = 12; i != 8; i--)
    {
    	lightLed(i, 500);
      	tone(buzzer, notes[i - 6], 200);
    }
  	for(int i = 9; i < 12; i++)
    {
      	lightLed(i, 500);
      	tone(buzzer, notes[i - 9], 200);
    }
  
  	for(int i = 0; i < 10; i++)
      is_true[i] = false;
  
  	delay(500);
}

// if player win round give him prize
void allright()
{  
  	 // prepare for other round
  	 for(int i = 0; i < 10; i++)
      is_true[i] = false;
  	
  	 for(int i = 12; i != 8; i--)
     {
      	digitalWrite(i, HIGH);
     }
  	 
  	 delay(500);
  
  	 // play song
  	 tone(buzzer, A, 200);
  	 delay(200);
  	 tone(buzzer, C, 200);
  	 delay(200);
  	 tone(buzzer, D, 200);
  	 delay(200);
     tone(buzzer, D, 200);
  	 delay(200);
     tone(buzzer, D, 200);
  	 delay(300);
  	 tone(buzzer, E, 200);
  	 delay(200);
     tone(buzzer, F, 200);
  	 delay(200);
  	 tone(buzzer, F, 200);
  	 delay(300);
  	 tone(buzzer, F, 200);
  	 delay(200);
     tone(buzzer, G, 200);
  	 delay(200);
  	 tone(buzzer, E, 200);
  	 delay(200);
     tone(buzzer, E, 200);
  	 delay(200);
  	 tone(buzzer, D, 200);
  	 delay(200);
     tone(buzzer, C, 200);
  	 delay(200);
     tone(buzzer, D, 200);
  	 delay(300);
  	 
  	 for(int i = 12; i != 8; i--)
     {
      	digitalWrite(i, LOW);
     }
  
  	 delay(500);
  
  	 // make game harder with low delay time
  	 delayTime -= 150;
}





