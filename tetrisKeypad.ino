#include"pitches.h"
#include "U8glib.h"
#include "RTClib.h"
#define NX 18
#define NY 9
// !!!!!!!!
#define ROZMIAR_F 4 
#define ILOSC_F 6
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST);
RTC_DS1307 rtc;

#include <Keypad.h>

const byte numRows= 4;

const byte numCols= 4;

char keymap[numRows][numCols]= { {'A', '3', '1', '2'},

{'B', '6', '4', '5'},

{'C', '9', '7', '8'},

{'D', '#', '0', '9'} };

byte rowPins[numRows] = {9,8,7,6}; //Rows 0 to 3

byte colPins[numCols]= {5,4,3,2}; //Columns 0 to 3

//initializes an instance of the Keypad class

Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);



char* rok(int r)
{
  switch (r){
     case(2021):
  return "21";
  break; 
    case(2022):
  return "22";
  break;
    case(2023):
  return "23";
    case(2024):
  return "24";
  break;
    case(2025):
  return "25";
  break;
  }
  
}


char *liczba[60]{"00", "01","02","03","04","05","06","07","08","09","10","11","12",
"13","14","15","16","17","18","19","20","21","22","23","24",
"25","26","27","28","29","30","31","32","33","34","35","36",
"37","38","39","40","41","42","43","44","45","46","47","48",
"49","50","51","52","53","54","55","56","57","58","59"};

void Int6NaString(int wyn,char (&tablica)[6]){
  for(int i=5;i>=0;i--)
  {    
    tablica[i]=wyn%10+48;    
    wyn=(wyn/10); 
  }
}
void cls(){
  u8g.firstPage();
  do{
  
  }while(u8g.nextPage());

  
}

 struct pixel
{
   int x=7;
   int y=0;
  }; 
struct figura
{
  struct pixel a,b,c,d;
  }; 
  
void generuj(bool (&ttab)[ROZMIAR_F], bool (&tlos)[ILOSC_F][ROZMIAR_F],int &r)
{
    r=random(ILOSC_F);
    for(int i=0;i<ROZMIAR_F;i++){
    ttab[i]=tlos[r][i];  
    }
    
}



bool czywejdzie(bool (&tXY)[18][9], figura &F,bool(&ttab)[ROZMIAR_F])
{
  if(ttab[0]){
  if(tXY[F.a.x][F.a.y] ){return false;}
  }
  if(ttab[1]){
  if(tXY[F.b.x][F.b.y] ){return false;}
  }
  if(ttab[2]){
  if(tXY[F.c.x][F.c.y] ){return false;}
  }
  if(ttab[3]){
  if(tXY[F.d.x][F.d.y] ){return false;}
  }
  return true;
}

void setup() { 
  //u8g.setFont(u8g_font_fur11);
  randomSeed(analogRead(0));
  pinMode(5,OUTPUT);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  Serial.begin(9600);
   if (! rtc.begin()) {
   Serial.println("Couldn't find RTC");
   while (1);
 }
 if (! rtc.isrunning()) {
   Serial.println("RTC is NOT running!");
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 }

}

void loop() { 

while(1)
{
  char keypressed = myKeypad.getKey();

if (keypressed != NO_KEY)

{

Serial.print(keypressed);

}
  }



    
int im=0;
int melodia[] = {
NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_C5, NOTE_E5,
NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4,
NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, 
NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4}; 

int czas[] = {
2,4,4,2,4,4,2,4,4,2,4,4,2,4,4,2,2,2,2,1, 
2,4,2,4,4,2,2,2,4,4,2,4,4,2,2,2,2,1};


unsigned long ty=0;
unsigned long tx=0;
unsigned long tm=0;
unsigned long tp=0;
unsigned long to=0;
int tc=0;

bool tab[ROZMIAR_F]={1,0,1,1};
bool XY[NX][NY]={{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
bool halt=0;
int wynik=0;
bool tetris=0;
//granice ekranu;
for(int i=0;i<NY-2;i++)
{
  XY[0][i]=true;
  XY[NX-1][i]=true;
  }
for(int i=0;i<NX;i++)
XY[i][NY-1]=1;
//dodając do tej tablicy dodajesz ksztalty
bool los[ILOSC_F][ROZMIAR_F]={{1,1,0,0},{0,1,0,1},{0,1,1,1},{1,0,1,1},{1,1,1,0},{1,1,0,1}};
int stan;
 figura blok ;
 blok.a.x=7;blok.a.y=0;
 blok.b.x=8;blok.b.y=0;
 blok.c.x=7;blok.c.y=1;
 blok.d.x=8;blok.d.y=1;
 generuj(tab, los, stan); 
 cls();
 int b=0;
 while(!tetris){ 
 DateTime now = rtc.now();
// if(now.second()-tc>0){ 
//  tc=now.second();  
    u8g.firstPage();
   do{
   
    u8g.setFont(u8g_font_fur17);
    u8g.drawStr( 10, 22, liczba[now.hour()]);
    u8g.drawStr( 40, 22, ":");
    u8g.drawStr( 50, 22, liczba[now.minute()]);
    u8g.drawStr( 80, 22, ":");
    u8g.drawStr( 90, 22, liczba[now.second()]);
    u8g.drawStr( 10, 48, liczba[now.day()]);
    u8g.drawStr( 40, 48, "/");
    u8g.drawStr( 50, 48, liczba[now.month()]);
    u8g.drawStr( 80, 48, "/");
    u8g.drawStr( 90, 48, rok(now.year()));   
    if(digitalRead(3)==LOW) tetris=!tetris;
   }while( u8g.nextPage() );
 //}
 }

 do{ 
int muz=800/czas[im];
   u8g.firstPage();  
    do{     
    unsigned long t=millis();
    tone(5,melodia[im]);
    if(t-tm>=muz){
    if(melodia[im]==melodia[im+1])noTone(5);
    im++;
    tm=t;      
   }
    
      bool niespad=true;
      if(im==38)im=0;
       if(t-ty>=300)
        {
          ty=t;
          blok.a.y += 1;
          blok.b.y += 1;
          blok.c.y += 1;
          blok.d.y += 1;
          niespad =czywejdzie(XY, blok, tab);
          Serial.println(niespad);
          if(!niespad)
          {
            XY[blok.a.x][blok.a.y-1] += tab[0];
            XY[blok.b.x][blok.b.y-1] += tab[1];
            XY[blok.c.x][blok.c.y-1] += tab[2];
            XY[blok.d.x][blok.d.y-1] += tab[3];
            for(int i=1;i<17;i++)
            {
              if(XY[i][0]) halt=true;
              
            }
            wynik++;
            blok.a.y = 0;
            blok.b.y = 0;
            blok.c.y = 1;
            blok.d.y = 1;
            blok.a.x=7;
            blok.b.x=8;
            blok.c.x=7;
            blok.d.x=8;
            generuj(tab, los, stan);
            tone(5,NOTE_E3);
            delay(40);
            }
         
         }
         
        int zwrot = 0;
        bool brakzderzenia = true;
        if(digitalRead(3)==LOW && t-to>=200){         
          to=t;
          switch (stan){
            case 0:
            stan=1;
            break;
            case 1:
            stan=0;
            break;
            default:
            stan++;            
            if(stan==6)stan=2;
            break;
          };
          for(int i=0;i<ROZMIAR_F;i++){
          tab[i]=los[stan][i];  
          }
        }
        if(digitalRead(2)==LOW && t-tx>=100){         
          tx=t;
          zwrot=1;
        }
        if(digitalRead(4)==LOW  && t-tx>=100){
           tx=t; 
           zwrot=-1;
            }
        if(zwrot != 0)
        {
          blok.a.x += zwrot;
          blok.b.x += zwrot;
          blok.c.x += zwrot;
          blok.d.x += zwrot;
          
          brakzderzenia = czywejdzie(XY , blok, tab);
        Serial.println(brakzderzenia);
          if(!brakzderzenia)
          {
            blok.a.x -= zwrot;
            blok.b.x -= zwrot;
            blok.c.x -= zwrot;
            blok.d.x -= zwrot;
            }
         }
        if(tab[0])u8g.drawBox(8*blok.a.x-8,8*blok.a.y,6,6);
        if(tab[1])u8g.drawBox(8*blok.b.x-8,8*blok.b.y,6,6);
        if(tab[2])u8g.drawBox(8*blok.c.x-8,8*blok.c.y,6,6);
        if(tab[3])u8g.drawBox(8*blok.d.x-8,8*blok.d.y,6,6);
        
        
        for(int j=NY-2;j>=0;j--){
          bool gap=false;
          // wykrycie braku dziury
          for(int i=1;i<NX-1;i++){
            if(!gap){ 
              if(!XY[i][j]){         
                gap=true;
              }
            }
          }
          // usuniecie lini przez zastapienie powyzszymi
          if(!gap){  
            for(int i=j;i>0;i--){
             for(int k=1;k<17;k++){  
               XY[k][i]=XY[k][i-1];
                }
             }
             wynik+=10;
           }
        // wypisanie na ekran
            for(int i=1;i<17;i++){                             
              if(XY[i][j]) u8g.drawBox(8*(i-1),8*j,6,6);
           }         
        }
            if(halt) break; 
      }while( u8g.nextPage() );
       
       
      if(halt) break;
     
      
 }while(1); 
 while(digitalRead(3)==HIGH){
   u8g.firstPage();
   do{
    u8g.setFont(u8g_font_fur17);
    u8g.drawStr(8,24,"YOU LOSE");
    char tmp[6];
    Int6NaString(wynik, tmp);
    u8g.drawStr(24,48, tmp);
    noTone(5);  
   }while( u8g.nextPage() );
    
   }

 
} 
