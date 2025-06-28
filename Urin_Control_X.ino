// Urin Control - Automation System
// 2015 - Dr. L. Gorczyca
// REV 1.0.0 8/23/2015
// REV 1.0.1 8/26/2015
// REV 1.0.2 10/10/2015 Stuck Loop & Arc FIX

#include <SerialLCD.h>
#include <SoftwareSerial.h> //this is a must
#include <avr/EEPROM.h>

int debug = false;

SerialLCD slcd(11,12);
char stringOne[10];
  
int LED1=11;
int LED2=12;

int Time_Delay1;
int Time_Delay2;
int D_Time;
int T_Fact=3; // MS/Step for PISS delay 
int W_Time=600; // MS Wait time for shot delays and other timings


int Temp_Sensor1;
int Temp_Sensor2;

int Trigger1=10;
int Trigger2=19;

int SCR_STATUS;

// Buss Bar Sensor ( Future )
float MAX_TEMP = 38.0; // F 102.2 Shutdowm point in C.
float COOL_TEMP = 34.0; // F 96.8 Min Temp to Re-enable Circuit

// AC Relays
int RLY1 = 0;
int RLY2 = 1;
int RLY3 = 2;
int RLY4 = 3;
int RLY5 = 4;
// MOSFET Switches
int SW1 = 5;
int SW2 = 6;
int SW3 = 7;
int SW4 = 8;
int SW5 = 8;

void setup() {  

pinMode(Trigger1, INPUT); 
pinMode(Trigger2, INPUT);

pinMode(RLY1, INPUT);
pinMode(RLY2, OUTPUT);
pinMode(RLY3, OUTPUT);
pinMode(RLY4, OUTPUT);
pinMode(RLY5, OUTPUT);

pinMode(SW1, OUTPUT); 
pinMode(SW2, OUTPUT);
pinMode(SW3, OUTPUT);
pinMode(SW4, OUTPUT);
pinMode(SW5, OUTPUT);
delay(100);
SCR_OFF();  // Make sure that we assume that it is overheated at power up!

digitalWrite(RLY1, LOW); // Un-Used
digitalWrite(RLY2, LOW); // Head Clamp
digitalWrite(RLY3, LOW); // Water Solenoid 1
digitalWrite(RLY4, LOW); // Water Solenoid 2
digitalWrite(RLY5, LOW); // Piss Solenoid

digitalWrite(SW1, LOW); // Mag Shot
digitalWrite(SW2, LOW); // Over Temp Light
digitalWrite(SW3, LOW); // Un-Used
digitalWrite(SW4, LOW); // Un-Used
digitalWrite(SW5, LOW); // Un-Used

digitalWrite(A0, LOW);
digitalWrite(A1, LOW);
digitalWrite(A2, LOW);
digitalWrite(A3, LOW);

Water_Off();

 if(debug==true){
    slcd.begin();
    slcd.backlight();
    slcd.print("Pisser V1.0");
    delay(600);
  }
  else{
    pinMode(LED1, OUTPUT); 
    pinMode(LED2, OUTPUT); 

    digitalWrite(LED1, LOW); 
    digitalWrite(LED2, HIGH);  
  }
}

void loop()
{
  Time_Delay1 = analogRead(A0);
  D_Time=(Time_Delay1*T_Fact);
  
  Temp_Check();
  if(SCR_STATUS!=0){
    if((digitalRead(Trigger1)==LOW)&&(Time_Delay1>0)){
      AutoMag(); // Magnatize
    }
    if((digitalRead(Trigger2)==LOW)&&(Time_Delay1>0)){
      Demag(); // De-Magnatize
    }
    if((digitalRead(Trigger1)==LOW)&&(Time_Delay1==0)){
      Std_Mag(); // Magnatize
    }
    
  }
  if(digitalRead(RLY1)==HIGH){
    PGM_MODE();
  } 
  if((debug==false)&&(SCR_STATUS==0)){
    digitalWrite(LED1, LOW); // Green LED off
    digitalWrite(LED2, HIGH); // Red LED on 
  }
  if((debug==false)&&(SCR_STATUS==1)){
    digitalWrite(LED1, HIGH); // Green LED on
    digitalWrite(LED2, LOW); // Red LED off 
  }
  if(debug==true){
    D_Bug();
  }
}

void Std_Mag()
{
  if(debug==true){
    slcd.setCursor(0, 0);
    slcd.print("DRY MAG    ");
  }
 Clamp(); 
 delay(1000);
 Mag_Shot();
 delay(600);
 Mag_Shot();
 delay(600);
 UnClamp();
}

void AutoMag()
{
  Clamp();
  delay(W_Time); // Delay to get hand out of the way.
  Mag_Shot();
  delay(W_Time); // Delay to prevent arcing.
  Water_On();
  delay(500);
    if(debug==true){
      slcd.setCursor(0, 0);
      slcd.print("PISS ON    ");
    }
  Piss();
      if(debug==true){
      slcd.setCursor(0, 0);
      slcd.print("PISS OFF   ");
    }
    
  Water_Off();
  Mag_Shot();
  delay(W_Time); 
  Mag_Shot();
  delay(W_Time); 
  delay(W_Time);
  UnClamp();
  
}

void Mag_Shot()
{
  digitalWrite(SW1, HIGH); // Mag Shot
  delay(100); // Delay Time
  digitalWrite(SW1, LOW); // Mag Shot
}

void Demag()
{
  if(debug==true){
      slcd.setCursor(0, 0);
      slcd.print("DEMAG ON   ");
    }
   Clamp();
  delay(1000);
  digitalWrite(SW3, HIGH); // DE-Mag Shot
  delay(100); // Delay Time
  digitalWrite(SW3, LOW); // De-Mag Shot
  delay(25000);
  if(debug==true){
      slcd.setCursor(0, 0);
      slcd.print("DEMAG OFF  ");
  }
  UnClamp();
}

void Water_On()
{
  digitalWrite(RLY3, LOW); // Water Solenoid 1
  digitalWrite(RLY4, HIGH); // Water Solenoid 2
}

void Water_Off()
{
  digitalWrite(RLY3, HIGH); // Water Solenoid 1
  digitalWrite(RLY4, LOW); // Water Solenoid 2
}

void Clamp()
{
  digitalWrite(RLY2, HIGH); // Clamp Head
}

void UnClamp()
{
  digitalWrite(RLY2, LOW); // UnClamp Head
}

void Piss()
{
  digitalWrite(RLY5, HIGH); // Piss On
  delay(D_Time); // Delay Time
  digitalWrite(RLY5, LOW); // Piss Off  
}

void Temp_Check()
{
  Temp_Sensor1 = (analogRead(A2)* 0.48828125);
  Temp_Sensor2 = (analogRead(A3)* 0.48828125);
  if((Temp_Sensor1>=MAX_TEMP)||(Temp_Sensor2>=MAX_TEMP)){
    SCR_OFF();
  }
  if((Temp_Sensor1<=COOL_TEMP)&&(Temp_Sensor2<=COOL_TEMP)){
    SCR_ON();
  }
}

void SCR_ON(){
  digitalWrite(SW2, LOW);
  SCR_STATUS=1;
}

void SCR_OFF(){
  digitalWrite(SW2, HIGH);
  SCR_STATUS=0;
}

void D_Bug()
{
  slcd.setCursor(0, 0);
  slcd.print("T1=");
  slcd.setCursor(3, 0);
  sprintf(stringOne,"     ");
  slcd.print(stringOne);
  slcd.setCursor(3, 0);
  sprintf(stringOne,"%d",Temp_Sensor1);
  slcd.print(stringOne);
      
  slcd.setCursor(8, 0);
  slcd.print("T2=");
  slcd.setCursor(11, 0);
  sprintf(stringOne,"     ");
  slcd.print(stringOne);
  slcd.setCursor(11, 0);
  sprintf(stringOne,"%d",Temp_Sensor2);
  slcd.print(stringOne);

  slcd.setCursor(0, 1);
  slcd.print("P1=");
  slcd.setCursor(3, 1);
  sprintf(stringOne,"     ");
  slcd.print(stringOne);
  slcd.setCursor(3, 1);
  sprintf(stringOne,"%d",Time_Delay1);
  slcd.print(stringOne);
      
  slcd.setCursor(8, 1);
  slcd.print("P2=");
  slcd.setCursor(11, 1);
  sprintf(stringOne,"     ");
  slcd.print(stringOne);
  slcd.setCursor(11, 1);
  sprintf(stringOne,"%d",Time_Delay2);
  slcd.print(stringOne);
}

void PGM_MODE()
{
  if(debug==true){
    slcd.setCursor(0, 0);
    slcd.print("PGM_MODE ON ");
  }
 while(digitalRead(RLY1)==HIGH){
   
  Time_Delay1 = analogRead(A0);
  D_Time=(Time_Delay1*T_Fact);
  
  Temp_Check();
  if(SCR_STATUS!=0){
    if((digitalRead(Trigger2)==LOW)&&(Time_Delay1>0)){
      Piss(); // Magnatize
      delay(D_Time); // Return Delay Time
    }
    if(digitalRead(Trigger1)==LOW){
      Clamp();
      MAG_SETUP(); // De-Magnatize
      UnClamp();
    }
   }
 }
}

void MAG_SETUP()
{
   while(digitalRead(RLY1)==HIGH){
     if(digitalRead(Trigger2)==LOW){
       break;
     }
     if(digitalRead(Trigger1)==LOW){
       Temp_Check();
       if(SCR_STATUS!=0){
         Mag_Shot();
       }
     }
   }
}


