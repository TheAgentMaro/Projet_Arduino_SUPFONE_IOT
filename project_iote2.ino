#include <LiquidCrystal.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#define nokia_2 2
#define menu_max 7


// lcd
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// buzzer
int buzz = A3;

// keypad
char customKey;
const byte ROWS = 4;
const byte COLS = 4;


char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'+','0','=','>'}
};
byte rowPins[ROWS] = {7,6,5,4};
byte colPins[COLS] = {3,2,A1,A2};

Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// write send receive message variables
int r,c,x,s;
char cr = Wire.read();
char action[17];
int val = 999 ;
int milli0 = 0;
int milli1 = 0;
int count =0;
char mystr[15];
char allMessage[15];
int countMessage = 0;


// contact variables
struct Contact {
  String name;
  String number;
};

const int MAX_CONTACTS = 4;
Contact contacts[MAX_CONTACTS];
int num_contacts = 0;


// menu function
void keyboard();
void menu1();		//Message
void menu6();		//Receiver
void menu5();		//Contact
void contact();		
void menu4();       //modifyContact
void menu7(); 		//deleteContact

int menu_num = 1, sub_menu = 1, submenu1 = 1;

void setup() {
  // Messge denu me
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
    case 2: menu6(); break;
    case 3: menu5(); break;
    case 4: menu4(); break;
  }
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




void menu6()
{
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("<  Message-Inbox  >");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print("  Message-Inbox  ");
       lcd.setCursor(0,1);
       Wire.begin(nokia_2);
  	   Wire.onReceive(receiveEvents);
       break;
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

void menu1() {
  switch (sub_menu) {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("   Message     >");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("   Message    ");
      lcd.setCursor(0, 1);
      writeMessage();
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



void contact() {
  static const int MAX_CONTACTS = 10; // Maximum number of contacts
  static struct {
    String name;
    String number;
  } contacts[MAX_CONTACTS]; // Array to store contacts
  static int num_contacts = 0; // Number of contacts currently stored
  
  customKey = myKeypad.getKey();
  lcd.setCursor(0, 0);
  lcd.print("    Contacts    ");
  
  if (customKey == '+') { // Add new contact
    if (num_contacts >= MAX_CONTACTS) {
      lcd.setCursor(0, 1);
      lcd.print("Max contacts reached");
      delay(1000);
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Entrer le nom:");
      delay(100);
      String name = readStringFromKeypad(); // Read name from keypad input
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Entrer le numéro:");
      delay(100);
      String number = readStringFromKeypad(); // Read number from keypad input
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Contact ajouté");
      delay(1000);
      contacts[num_contacts].name = name;
      contacts[num_contacts].number = number;
      num_contacts++;
    }
  } else { // Display existing contacts
    for (int i = 0; i < num_contacts; i++) {
      lcd.setCursor(0, 1 + i);
      lcd.print(contacts[i].name);
      lcd.setCursor(10, 1 + i);
      lcd.print(contacts[i].number);
    }
  }
}

void menu4()
{
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("<Modifier Contacts>");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print(" Modifier Contacts ");
       lcd.setCursor(0,1);
  	   modifyContact();
       break;
  } 
}


void modifyContact() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Entrer le nom à modifier :");
  delay(100);
  String nameToEdit = readStringFromKeypad(); // Read name of contact to edit from keypad input
  
  int contactIndex = -1;
  for (int i = 0; i < num_contacts; i++) {
    if (contacts[i].name == nameToEdit) { // Check if the contact name matches
      contactIndex = i;
      break;
    }
  }
  
  if (contactIndex == -1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Contact introuvable");
    delay(1000);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Saisir le nouveau nom :");
    delay(100);
    String newName = readStringFromKeypad(); // Read new name from keypad input
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Saisir un nouveau numéro :");
    delay(100);
    String newNumber = readStringFromKeypad(); // Read new number from keypad input
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Contact mis à jour");
    delay(1000);
    contacts[contactIndex].name = newName;
    contacts[contactIndex].number = newNumber;
  }
}

void menu7()
{
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("<Supprimer Contacts>");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print(" Supprimer Contacts ");
       lcd.setCursor(0,1);
  	   suppContact();
       break;
  } 
}

void suppContact() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Supprimer un contact:");
  delay(100);

  String nameToDelete = readStringFromKeypad();

  int contactIndexToDelete = -1;

  // Search for contact with matching name and get its index
  for (int i = 0; i < num_contacts; i++) {
    if (contacts[i].name == nameToDelete) {
      contactIndexToDelete = i;
      break;
    }
  }

  if (contactIndexToDelete >= 0) { // If contact found
    // Shift all elements after contactIndexToDelete by one index to the left
    for (int i = contactIndexToDelete; i < num_contacts - 1; i++) {
      contacts[i].name = contacts[i + 1].name;
      contacts[i].number = contacts[i + 1].number;
    }

    // Clear last element in the array
    contacts[num_contacts - 1].name = "";
    contacts[num_contacts - 1].number = "";

    num_contacts--;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Contact supprimé");
    delay(1000);
  } else { // If contact not found
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Contact introuvable");
    delay(1000);
  }
}

String readStringFromKeypad() {
  String str = "";
  while (true) {
    customKey = myKeypad.getKey();
    if (customKey == '=') {
      return str;
    } else if (customKey != NO_KEY) {
      str += customKey;
      lcd.setCursor(str.length() - 1, 1);
      lcd.print(customKey);
      delay(100);
    }
  }
}
void receiveEvents(int numBytes) {
  char c = Wire.read();
  if(c=='@'){lcd.write("@");}
  Serial.print(c);
  lcd.write(c);
  tone(buzz, 392 , 50);
}