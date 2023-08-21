#include <DS3231.h>
#include "pitches.h"
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 

DS3231  rtc(SDA, SCL);
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
int sw1=6,sw2=7,sw3=8,sw4=9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int swstate1=0;
bool stopwatchstate=false;
bool countdownstate=false;
int btncnt=0;
const int buzzer=13;
int valsw1,valsw2,valsw3,valsw4;
bool setupscreen = false;
int h,h1,h2=0;
//String strh="";
int m,m1,m2=0;
int s,s1,s2=0;

String alarmtimeh,alarmtimeh1,alarmtimeh2="";
String alarmtimem,alarmtimem1,alarmtimem2="";
String alarmtimes,alarmtimes1,alarmtimes2="";
String alarmtime1="";
String alarmtime="";
String alarmtime2="";
bool alarmtimestate=false;

int melody[] = {
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, REST,
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, REST,
  NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, REST,
  
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_D5, NOTE_E5, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, REST,
  NOTE_C5, NOTE_A4, NOTE_B4, REST,
  
  NOTE_A4, NOTE_A4,
  //Repeat of first part
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, REST,
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, REST,
  NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, REST,
  
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_D5, NOTE_E5, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, REST,
  NOTE_C5, NOTE_A4, NOTE_B4, REST,
  //End of Repeat
  
  NOTE_E5, REST, REST, NOTE_F5, REST, REST,
  NOTE_E5, NOTE_E5, REST, NOTE_G5, REST, NOTE_E5, NOTE_D5, REST, REST,
  NOTE_D5, REST, REST, NOTE_C5, REST, REST,
  NOTE_B4, NOTE_C5, REST, NOTE_B4, REST, NOTE_A4,
  
  NOTE_E5, REST, REST, NOTE_F5, REST, REST,
  NOTE_E5, NOTE_E5, REST, NOTE_G5, REST, NOTE_E5, NOTE_D5, REST, REST,
  NOTE_D5, REST, REST, NOTE_C5, REST, REST,
  NOTE_B4, NOTE_C5, REST, NOTE_B4, REST, NOTE_A4
};

int durations[] = {
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  4, 8, 4, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 4,
  
  4, 8,
  //Repeat of First Part
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  4, 8, 4, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 4,
  //End of Repeat
  
  4, 8, 4, 4, 8, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 4,
  4, 8, 4, 4, 8, 4,
  8, 8, 8, 8, 8, 2,
  
  4, 8, 4, 4, 8, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 4,
  4, 8, 4, 4, 8, 4,
  8, 8, 8, 8, 8, 2
};

void setup() { 
 rtc.begin(); // Initialize the rtc object
 lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
 Serial.begin(9600);
 pinMode(sw1,INPUT);
 pinMode(sw2,INPUT);
 pinMode(sw3,INPUT);
 pinMode(sw4,INPUT);
 pinMode(buzzer,OUTPUT);
//  rtc.setTime(12,23,50);
//  rtc.setDate(23,2,2023);
}

void loop() { 

  valsw1=digitalRead(sw1);
  valsw2=digitalRead(sw2);
  valsw3=digitalRead(sw3);
  valsw4=digitalRead(sw4);
  alarmtime= alarmtimeh+alarmtimem+alarmtimes;
  alarmtime1= alarmtimeh1+alarmtimem1+alarmtimes1;
  alarmtime2= alarmtimeh2+alarmtimem2+alarmtimes2;
  Serial.print(btncnt);
  Serial.print("\n");
  Serial.print(s1);
  Serial.print("\n");

  Serial.print("\n");
  Serial.print(rtc.getTimeStr());
  Serial.print("\n");

 if(alarmtimestate==true)
  {
    int size = sizeof(durations) / sizeof(int);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Press Any Key");       
    for (int note = 0; note < size; note++) 
    {
   
      //to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int duration = 1000 / durations[note];
      tone(buzzer, melody[note], duration);
  
      //to distinguish the notes, set a minimum time between them.
      //the note's duration + 30% seems to work well:
      int pauseBetweenNotes = duration * 1.30;
      delay(pauseBetweenNotes);
      noTone(buzzer);
      if(digitalRead(sw1)==0||digitalRead(sw2)==0||digitalRead(sw3)==0||digitalRead(sw4)==0)
      {
      noTone(buzzer);
      btncnt=0;
      alarmtimestate=false;   
      countdownstate=false;
      break;
      }  
    }

  }



  if(valsw1==0 && alarmtimestate==false&&countdownstate==false&&stopwatchstate==false)
  {
    setupscreen=true;
    btncnt++;
  }
  if(valsw4==0)
  {
    btncnt--;
  }
   
  if(btncnt==0)
  {
    setupscreen=false;
  }

 if(!setupscreen)
 {
   telltime();
 }
 else if(setupscreen==true && alarmtimestate==false&&btncnt<5&&countdownstate==false&&stopwatchstate==false)
 {
  setalarm(); 
 }
//   else if (setupscreen==true && alarmtimestate==false&&btncnt>=5&&countdownstate==false&&stopwatchstate==false)
//  {
//    songselect();
//  }
//  else if(setupscreen==true && alarmtimestate==false&&btncnt>=5&&btncnt<9&&countdownstate==false&&stopwatchstate==false)
//  {
//   settimer(); 
//  }
//  else if(setupscreen==true && alarmtimestate==false&&btncnt>=9&&countdownstate==false&&stopwatchstate==false)
//  {
//    stopwatch();
//  }
 if(alarmtime==rtc.getTimeStr()) //check if time is equals to alarmtime
 {
  alarmtimestate=true;
 }
 if(btncnt>=5)
 {
   btncnt=0;
   setupscreen=false;
 }
 if(btncnt<0)
 {
   btncnt==4;
 }
}
 




void telltime(){
 lcd.setCursor(0,0);
 lcd.print("Time:  ");
 lcd.print(rtc.getTimeStr());
 
 lcd.setCursor(0,1);
 lcd.print("Date: ");
 lcd.print(rtc.getDateStr());
 
 delay(1000); 
}

void setalarm()
{

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set Your Alarm:");
  lcd.setCursor(0,1);

  if (btncnt==2)
  {

    if(valsw2==0)
    {

      if(h<23)
      {
        h++;
        
      }
      else
      {
        h=0;
      }
    }
    if(valsw3==0)
    {
      if(h>0)
      {
        h--;
      }
      else
      {
        h=23;
      }
    }

  }
  if(h<10){
    lcd.print("0");
    lcd.print(h);
    lcd.print(":");
    alarmtimeh="0"+String(h)+":";

  }
  else if(h>=10){
    lcd.print(h);
    lcd.print(":");
    alarmtimeh=String(h)+":";

  }

  if(btncnt==3)
  {
    if(valsw2==0)
    {
      if(m<59)
      {
        m++;
        
      }
      else
      {
        m=0;
      }
    }
    if(valsw3==0)
    {
      if(m>0)
      {
        m--;
       
      }
      else
      {
        m=59;
      }
    }    
  }
   if(m<10){
    lcd.print("0");
    lcd.print(m);
    lcd.print(":");
    alarmtimem="0"+String(m)+":";
  }
  else if(m>=10){
    lcd.print(m);
    lcd.print(":");
    alarmtimem=String(m)+":";
  }

  if(btncnt==4)
  {
    if(valsw2==0)
    {
      if(s<59)
      {
        s++;
    
      }
      else
      {
        s=0;
      }
    }    
    if(valsw3==0)
    {
      if(s>0)
      {
        s--;
        
      }
      else
      {
        s=59;
      }
    }
  }
    if(s<10)
    {
    lcd.print("0");
    lcd.print(s);
    alarmtimes="0"+String(s);
  }
  else if(s>=10){
    lcd.print(s);
    alarmtimes=String(s);
  }
  
   
  //if(btncnt==0)
 // {
  //  setupscreen=false;
 // }
  delay(100);
}

// void songselect(){
//   if(btncnt==5){
//   lcd.clear();
//   lcd.setCursor(0,0);
//   lcd.print("Select Song");

//   }
//   if(btncnt==6)
//   {
//     lcd.setCursor(0,1);
//     lcd.print("Starwar");
//     if(valsw2==0)
//     {
//        
//     }
//   delay(200);
// }  
