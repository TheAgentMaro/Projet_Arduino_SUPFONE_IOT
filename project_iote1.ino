#include <LiquidCrystal.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#define nokia_2 2
#define menu_max 7

// define variables
// emojis
byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};

byte heart_empty[8] = {
B00000,
B00000,
B01010,
B10101,
B10001,
B01010,
B00100,
};

byte heart_full[8] = {
B00000,
B00000,
B01010,
B11111,
B11111,
B01110,
B00100,
};

byte man_1[8] = {
B00100,
B01110,
B00101,
B11111,
B10100,
B00100,
B01010,
B11011,
};

byte man_2[8] = {
B00100,
B01110,
B10100,
B11111,
B00101,
B00100,
B01010,
B11011,
};

byte smile[8] = {
B00000,
B01010,
B01010,
B00000,
B10001,
B01110,
B00000,
B00000,
};

byte arrow_1[8] = {
B01110,
B01110,
B00100,
B00100,
B00100,
B11111,
B01110,
B00100,
};

byte arrow_2[8] = {
B00100,
B01110,
B11111,
B00100,
B00100,
B00100,
B01110,
B01110,
};

byte smile_sin[8] = {
B00000,
B01001,
B01010,
B00000,
B10001,
B01110,
B00000,
B00000,
};

// lcd
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// buzzer
int buzz = A3;

// keypad
char customKey;
const byte ROWS = 4;
const byte COLS = 4;

// variables calculator
long first = 0;
long second = 0;
double total = 0;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'+','0','=','>'}
};
byte rowPins[ROWS] = {7,6,5,4};
byte colPins[COLS] = {3,2,A1,A2};

Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// write and send message variables
int r,c,x,s;
char cr = Wire.read();
char action[17];
int val = 999 ;
int milli0 = 0;
int milli1 = 0;
int count =0;

// composer variables
int note = 0;
int dure = 100;

// menu function
void keyboard();
void menu1();		//Message
void menu2();		//Calculator
void menu3();		//Music
void menu5();		//Contact
void menu6();		//Composer
void menu4();		//Volume
void menu7();		//display all emojis
void contact();		//name+num
void composer();	//manage composer ( musique composer)

int menu_num = 1, sub_menu = 1, submenu1 = 1;

// playMusic function ( des fonctions pour jouer de la musique)

void playMusic1() {
  lcd.setCursor(0,0);
    lcd.print("Musique 1  ");
    lcd.setCursor(0,1);
    tone(buzz, 392 , 500);
    delay(250);
    tone(buzz, 587.23 , 500);
    delay(300);
    tone(buzz, 587.23 , 500);
    delay(350);
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void playMusic2() {
  lcd.setCursor(0,0);
    lcd.print("Musique 2");
    lcd.setCursor(0,1);
    tone(buzz, 410 , 200);
    delay(300);
    tone(buzz, 359.23 , 200);
    delay(350);
    tone(buzz, 523.25 , 200);
    delay(400);
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void playMusic3() {
  lcd.setCursor(0,0);
    lcd.print("Musique 3");
    lcd.setCursor(0,1);
    tone(buzz, 523.25 , 200);
    delay(300);
    tone(buzz, 587.23 , 200);
    delay(350);
    tone(buzz, 523.25 , 200);
    delay(400);
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void playMusic4() {
  lcd.setCursor(0,0);
    lcd.print("Musique 4");
    lcd.setCursor(0,1);
    tone(buzz, 320.25 , 200);
    delay(300);
    tone(buzz, 320.23 , 200);
    delay(350);
    tone(buzz, 418.25 , 200);
    delay(400);
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void playMusic5() {
  lcd.setCursor(0,0);
    lcd.print("Musique 5");
    lcd.setCursor(0,1);
    tone(buzz, 523.25 , 200);
    delay(300);
    tone(buzz, 110.23 , 200);
    delay(350);
    tone(buzz, 720 , 200);
    delay(400);
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void setup() {
  // Message de menu
  lcd.createChar(0, smiley);
  lcd.begin(16, 2);  
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(0,0);
    lcd.print("SUPFONE");
    lcd.setCursor(0,1);
    lcd.print("SUPINFO-PROJECT");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  
  // write_message_initialize
  r=1,c=-1,x=-1,s=1;
  
}

void loop() 
{
  keyboard();
  
  switch(menu_num)
  {
    case 1: menu1(); break;
    case 2: menu2(); break;
    case 3: menu3(); break;
    case 4: menu6(); break;
    case 5: menu5(); break;
    case 6: menu4(); break;
    case 7: menu7(); break;
  }
}

// Fonction de calculator opération entre deux nombre (first / second) 
void doCalcul() {
  customKey = myKeypad.getKey();
  switch(customKey) 
  {
  case '0' ... '9':
    lcd.setCursor(0,1);
    first = first * 10 + (customKey - '0');
    lcd.print(first);
    break;

  case '+':
    first = (total != 0 ? total : first);
    lcd.setCursor(0,1);
    lcd.print("+");
    second = SecondNumber(); 
    total = first + second;
    lcd.setCursor(0,3);
    lcd.print(total);
    first = 0, second = 0;
    break;

  case 'A':
    first = (total != 0 ? total : first);
    lcd.setCursor(0,1);
    lcd.print("-");
    second = SecondNumber();
    total = first - second;
    lcd.setCursor(0,3);
    lcd.print(total);
    first = 0, second = 0;
    break;

  case 'B':
    first = (total != 0 ? total : first);
    lcd.setCursor(0,1);
    lcd.print("*");
    second = SecondNumber();
    total = first * second;
    lcd.setCursor(0,3);
    lcd.print(total);
    first = 0, second = 0;
    break;

  case '>':
    first = (total != 0 ? total : first);
    lcd.setCursor(0,1);
    lcd.print("/");
    second = SecondNumber();
    lcd.setCursor(0,3);

    second == 0 ? lcd.print("Invalid") : total = (float)first / (float)second;

    lcd.print(total);
    first = 0, second = 0;
    break;
  case 'C':
    menu_num = 2;
    sub_menu = 1;
   break;
  }

}

long SecondNumber()
{
  while( 1 )
  {
    customKey = myKeypad.getKey();
    if(customKey >= '0' && customKey <= '9')
    {
      second = second * 10 + (customKey - '0');
      lcd.setCursor(0,2);
      lcd.print(second);
    }

    if(customKey == '=') break;  //return second;
  }
 return second; 
}

void keyWrite(){
	if (customKey == '1')
      {val = customKey;
       count = ++count;
       if (count == 1)
       {customKey = 'a';}
       if (count == 2)
       {customKey = 'b';}
       if (count == 3)
       {customKey = 'c';}
       if (count == 4)
       {customKey = '1';
       count = 0;}
       if (count>4)
       {count = 0;}
       action[x] = customKey;} 

      if (customKey == '2')
      {count = ++count;
       if (count == 1)
       {customKey = 'd';}
       if (count == 2)
       {customKey = 'e';}
       if (count == 3)
       {customKey = 'f';}
       if (count == 4)
       {customKey = '2';
       count = 0;}
       if (count>4)
       {count = 0;}
      action[x] = customKey;}
      
      if (customKey == '3')
      {count = ++count;
       if (count == 1)
       {customKey = 'g';}
       if (count == 2)
       {customKey = 'h';}
       if (count == 3)
       {customKey = 'i';}
       if (count == 4)
       {customKey = '3';
       count = 0;}
       if (count>4)
       {count = 0;}
      action[x] = customKey;}
      
      if (customKey == '4')
      {count = ++count;
       if (count == 1)
       {customKey = 'j';}
       if (count == 2)
       {customKey = 'k';}
       if (count == 3)
       {customKey = 'l';}
       if (count == 4)
       {customKey = '4';
       count = 0;}
       if (count>4)
       {count = 0;}
      action[x] = customKey;}
      
      if (customKey == '5')
      {count = ++count;
       if (count == 1)
       {customKey = 'm';}
       if (count == 2)
       {customKey = 'n';}
       if (count == 3)
       {customKey = 'o';}
       if (count == 4)
       {customKey = '5';
       count = 0;}
       if (count>4)
       {count = 0;}
      action[x] = customKey;}
      
      if (customKey == '6')
      {count = ++count;
       if (count == 1)
       {customKey = 'p';}
       if (count == 2)
       {customKey = 'q';}
       if (count == 3)
       {customKey = 'r';}
       if (count == 4)
       {customKey = '6';
       count = 0;}
       if (count>4)
       {count = 0;}
      action[x] = customKey;}
      
      if (customKey == '7')
      {count = ++count;
       if (count == 1)
       {customKey = 's';}
       if (count == 2)
       {customKey = 't';}
       if (count == 3)
       {customKey = 'u';}
       if (count == 4)
       {customKey = '7';
       count = 0;}
       if (count>4)
       {count = 0;}
      action[x] = customKey;}
      if (customKey == '8')
      {count = ++count;
       if (count == 1)
       {customKey = 'v';}
       if (count == 2)
       {customKey = 'w';}
       if (count == 3)
       {customKey = 'x';}
       if (count == 4)
       {customKey = '8';
       count = 0;}
       if (count>4)
       {count = 0;}
      action[x] = customKey;}
      if (customKey == '9')
      {count = ++count;
       if (count == 1)
       {customKey = 'y';}
       if (count == 2)
       {customKey = 'z';}
       if (count == 3)
       {customKey = '9';
       count = 0;}
       if (count>3)
       {count = 0;}
      action[x] = customKey;}
      if (customKey == '+')
      {count = ++count;
       if (count == 1)
       {customKey = '+';}
       if (count == 2)
       {customKey = '-';}
       if (count == 3)
       {customKey = '/';}
       if (count == 4)
       {customKey = '*';
       count = 0;}
       if (count>4)
       {count = 0;}
      action[x] = customKey;}
      if (customKey == 'B')
      {count = ++count;
       if (count == 1)
       {lcd.createChar (1, heart_empty);
        customKey = lcd.write(byte(1));}
       if (count == 2)
       {lcd.createChar (2, heart_full);
        customKey = lcd.write(byte(2));}
       if (count == 3)
       {lcd.createChar (3, man_1);
        customKey = lcd.write(byte(3));}
       if (count == 4)
       {lcd.createChar (4, man_2);
        customKey = lcd.write(byte(4));}
       if (count == 5)
       {lcd.createChar (5, smile);
        customKey = lcd.write(byte(5));
        count = 0;}
       if (count>5)
       {count = 0;}
       action[x] = customKey;
      }
  	 if (customKey == '0'){customKey = '@';action[x] = customKey;}
}

void writeMessage(){
 if(customKey)  
  	{ 
      milli1 = millis();
      
      if (val != customKey)  
      {count=0;
       c = ++c;
      val = customKey;
       x = ++x;
      }
      if ((milli1-milli0)>800)
      {
        count=0;
        milli0=milli1;
        }
 
      
    	
       	
    if (customKey == 'A')
      {
      
      	
       	lcd.setCursor(0, 0);
      		while(s<c)
      		{
      		lcd.print(action[s]);
            Wire.begin();
            Serial.begin(9600);
            Serial.print(action[s]);
            Wire.beginTransmission(nokia_2);
            Wire.write(action[s]);
            Wire.endTransmission();
            s = ++s;

      		}
         
    }
      
     keyWrite();
  lcd.setCursor(c, r);        
  lcd.print(customKey);
    if (c==15)
    {
     lcd.setCursor(0, 0);
     lcd.print("max char: 16");}	
    }
}

void keyboard()
{
  customKey = myKeypad.getKey();
  if(customKey != 'A' && sub_menu == 1)
   {
      delay(25);
      if(menu_num <= menu_max) menu_num += 1; 
   }

   if(customKey != 'B' && sub_menu == 1)
   {
      delay(25);
      if(menu_num > 0) menu_num -= 1;
   }

   if(customKey != 'C')
   {
      delay(25);
      if(sub_menu <= 2) sub_menu += 1;
   }
  
   if(customKey != '>')
   {
      delay(25);
      if(sub_menu > 0) sub_menu -= 1;
   }
}

void menu1()
{
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("   Message     >");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print("   Message    ");
       lcd.setCursor(0,1);
  	   writeMessage();
       break;
  } 
}

void menu2()
{
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("< Calculatrice >");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print(" Calculatrice ");
       lcd.setCursor(0,1);
       doCalcul();
       break;
  } 
}

void menu3()
{
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("<   Musique    >");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print("   Musique   ");
       lcd.setCursor(0,1);
       playMusic1();
       playMusic2();
       playMusic3();
       playMusic4();
       playMusic5();
       menu_num = 3;
       sub_menu = 1;
       break;
  } 
}

void menu4()
{
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("<   Volume  .    ");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print("  Volume    .");
       lcd.setCursor(0,1);
       lcd.print("Turn Potentiometer");
       break;
  }
}

void menu5()
{
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("<   Contacts   >");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print("   Contacts    ");
       lcd.setCursor(0,1);
  	   contact();
       break;
  } 
}

void menu6()
{
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("<   Composer   >");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print("   Composer   ");
       lcd.setCursor(0,1);
       composer();
       break;
  } 
}

void menu7()
{
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("<   Emojis   >");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print("   Emojis   ");
       lcd.setCursor(0,1);
       allEmojis();
       break;
  }
}

void allEmojis()
{
    lcd.createChar (1, heart_empty);
    lcd.createChar (2, heart_full);
    lcd.createChar (3, man_1);
  	lcd.createChar (4, man_2);
  	lcd.createChar (5, smile);
  	lcd.createChar (6, smile_sin);
    lcd.createChar (7, arrow_1);
  	lcd.createChar (8, arrow_2);
  
  	lcd.setCursor(0,1);
  
    lcd.print (char(1));
    lcd.print (char(2));
    lcd.print (char(3));
    lcd.print (char(4));
    lcd.print (char(5));
    lcd.print (char(6));
    lcd.print (char(7));
    lcd.print (char(8));
}

void contact()
{
   customKey = myKeypad.getKey();
   lcd.setCursor(0,0);
   lcd.print("    Contacts    ");
   switch(submenu1)
   {
     case 1:
     lcd.setCursor(0,1);
     lcd.print("Marwen  07221242");
     if(customKey != 'A'){delay(50);submenu1 ++;}
     break;
     case 2:
     lcd.setCursor(0,1);
     lcd.print("Jack  07221242"); 
     if(customKey != 'A'){delay(50);submenu1 ++;}
     if(customKey != 'B'){delay(50);submenu1 --;}
     break;
   }
}

void composer(){
  
  customKey = myKeypad.getKey();

  if(customKey=='1'){note=262;lcd.print("Do       ");tone(buzz, note , dure);}
  if(customKey=='2'){note=294;lcd.print("Re       ");tone(buzz, note , dure);}
  if(customKey=='3'){note=330;lcd.print("Mi       ");tone(buzz, note , dure);}
  if(customKey=='4'){note=349;lcd.print("Fa       ");tone(buzz, note , dure);}
  if(customKey=='5'){note=392;lcd.print("Sol      ");tone(buzz, note , dure);}
  if(customKey=='6'){note=440;lcd.print("La		  ");tone(buzz, note , dure);}  
  if(customKey=='7'){note=494;lcd.print("Si		  ");tone(buzz, note , dure);}
  
  if(customKey=='8'){note=277;lcd.print("Do#	  ");tone(buzz, note , dure);}
  if(customKey=='9'){note=311;lcd.print("Re#	  ");tone(buzz, note , dure);}
  if(customKey=='+'){note=370;lcd.print("Fa#	  ");tone(buzz, note , dure);}
  if(customKey=='0'){note=415;lcd.print("Sol#	  ");tone(buzz, note , dure);}
  if(customKey=='='){note=466;lcd.print("La#	  ");tone(buzz, note , dure);}
  
  if(customKey=='A'){
    count = ++count;
    if(count == 1){
      dure = 100;
      lcd.print("Noire    ");
    }
    if(count == 2){
      dure = 200;
      lcd.print("Blanche  ");
    }
    if(count == 3){
      dure = 400;
      lcd.print("Ronde    ");
    }
    if(count == 4){
      dure = 50;
      lcd.print("Croche   ");
    }
    if(count>4){
      {count = 0;}
    }
  }
  if(customKey=='C'){menu_num = 5;sub_menu = 1;}

}