#include <Arduino.h>
#include  <WiFi.h> //libery need to run the program 
#include <AsyncUDP.h> //libery need to run the program 
 
const int pinX = 34; //the pin for the x
const int pinY = 35; //the pin for the y
const int buttonPres = 14; // the pin for the button
unsigned long currentMillis; // assign a value for the timer  
unsigned long previousMillis = 0; // to store the last time/millls form the last interval
int tollance = 20;   
const int LED_Pin = 19 ;

  
  const char * ssid = ""; //input name of network
  const char * password = ""; //input the password for the network
  AsyncUDP UDP; // creates an AsyncUDP object 
  int port = 7000; // assign a port to broadcast yo
  int listenport = 7007; // assign a port to listen to
 
void setup() {
 Serial.begin(9600); // the program begins
 WiFi.mode(WIFI_STA); // to connects to the Wifi
 WiFi.begin(ssid, password); // checks if the WiFi name and password  
 pinMode(pinX,INPUT); // the x-axis or right and left
 pinMode(pinY,INPUT); // the y-axis or up and down
 pinMode(buttonPres,INPUT_PULLUP); // used to initializing the pixel bye buttonpres 
 pinMode(EXTRENAL_LED,OUTPUT); 
 pinMode(LED_BUILTIN,OUTPUT);
}

void LEDBlinkON(int LCD_Pin){
  digitalWrite(LED_BUILTIN,HIGH);
  digitalWrite(EXTRENAL_LED,HIGH);
}

void LEDBlinkOFF (){
  digitalWrite(LED_BUILTIN,LOW);   
  digitalWrite(EXTRENAL_LED,LOW);
}

void Initialize_Pixel(){
if(digitalRead(buttonPres) == LOW){ // LOW == pressed
     UDP.broadcastTo("init 6 6",port); // initialise the pixel by presing the button
}
 
void Broadcasts_Movement(String Movement, String print){ //broadcasts the movement of the pixels on the pixelserver
  UDP.broadcastTo(Movement.c_str(),port); //c.str() is needed to broadcast the direction to the chararry for the funtion to work 
  Serial.print(print); //prints the way the pixel moves in the serial moniter 
}
void Pixel_Movement(int horizontal, int vertical){
  if(horizontal >= 2000 - tollance && horizontal <= 0 + tollance ){ // by pushing the joystick all the way to the right the pixel move right
    Broadcasts_Movement("moveright ","moveright ");
    LEDBlinkON;
  } else if (horizontal <= 2100+tollance && horizontal >= 4000 - tollance ) // by pushing the joystick all the way to the left the pixel move right
  {Broadcasts_Movement("moveleft  ","moveleft ");
    LEDBlinkOFF
  } else if (vertical >=  2000 - tollance && vertical <= 0 + tollance){ // by pushing the joystick all the way to the up the pixel move right
     Broadcasts_Movement("moveup ","moveup ");
     LEDBlinkON;
  } else if(vertical <= 2100 + tollance && vertical >= 4000 - tollance){ // by pushing the joystick all the way to the down the pixel move right the down does not work you need to pres the joystick down and left to make it print/move down
   Broadcasts_Movement("movedown  ","movedown "); 
   LEDBlinkOFF
  }else{
    UDP.broadcastTo("not moveing",port);  // when the joystick is not moveing the pixel will stop
    LEDBlinkOFF;
  }    
}

 
void loop() {
  currentMillis = millis(); // set currentMillis to Millis 
   Initialize_Pixel;
  }
  
  if(currentMillis-previousMillis >interval){ // will only read commands at the interval 
    Pixel_Movement(analogRead(pinX),analogRead(pinY)); // is used to read the input from the joystick 
    previousMillis=currentMillis; // the interval will be repeated 
    UDP.listen(listenport); // listening on the listenport 
  }  
}