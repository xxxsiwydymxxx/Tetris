#include"pitches.h"
#include "U8glib.h"
#include "RTClib.h"
#define NX 16
#define NY 8

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST);
#include <Keypad.h>

const u8int_t jablko[36]=
{
0, 1, 1, 0, 0, 0,
0, 0, 0, 1, 0, 0,
0, 1, 1, 1, 1, 0,
0, 1, 1, 1, 1, 0,
0, 1, 1, 1, 1, 0,
0, 0, 1, 1, 0, 0,
}

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

struct snakehead
{
	int x,y;
};

void setup() { 
  pinMode(5,OUTPUT);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() { 
snakehead snek={1,0};
snakehead body={8,4};
snakehead jabco;
jabco.x = random()%NX;
jabco.y = random()%NY;
unsigned long ty=0;
unsigned long tx=0;
unsigned long tm=0;
unsigned long tp=0;
unsigned long to=0;

unsigned int ekran[NX][NY];

//granice ekranu;

 do{ 
 
//start gry
bool kolizja = false;
signed int dlugosc = 4;
signed int dlugoscjabca=30;


   u8g.firstPage();  
    do{   
	 unsigned long t=millis();
       if(t-ty>=300)
        {
			//kolizje if ekran[x][y] !=0 i czy kolizja z jablkiem;
          ty=t;
		  
		  if(body.x+snek.x>=0){
			  body.x = (body.x+snek.x)%(NX-1);
		  }else
		  {
			  body.x = (NX-1);
		  }
		  if(body.y+snek.y>=0){
			  body.y = (body.y+snek.y)%(NY-1);
		  }else{
			  body.y = (NY-1);
		  }
		  if(ekran[body.x][body.y]!=0)
		  {
			  if(body.x == jabco.x && body.y == jabco.y)
			  {
				  dlugosc++;
				  jabco.x = random()%NX;
				  jabco.y = random()%NY;
				  ekran[jabco.x][jabco.y]=dlugoscjabca;
			  }else
			  {
				  kolizja = true;
				  
			  }
		  }
		  //wpisanie dlugosci czesci ogona sneka do ekran[][]
		  if(!kolizja)
		  {
			 ekran[body.x][body.y]=dlugosc;
			 //mija czas 1 klatki czyli t - ty czesci ogona starzeja sie
			 for(int i=0;i<NX;i++)
			 {
				 for(int j=0;j<NY;j++)
				 {
					 if(ekran[i][j]!=0)
					 {
						 ekran[i][j]-=1;
					 }
				 }
			 }
		  }
		  
		  
         }
        if(digitalRead(3)==LOW && t-to>=200){         
          to=t; 
		  if(snek.x==0){snek.y = -snek.y;swap(snek.x,snek.y);}
		   else{swap(snek.x,snek.y);}
          }
          
        
        if(digitalRead(2)==LOW && t-tx>=100){         
          tx=t;
          if()
        }
        if(digitalRead(4)==LOW  && t-tx>=100){
           tx=t; 
           if(snek.y==0){snek.x = -snek.x;swap(snek.x,snek.y);}
		   else{swap(snek.x,snek.y);}
		}
		// if kolizja koniec gry i reset przy low na '3'
		if(kolizja)
		{
			while(1){}
		}
		
			//wyswietlanie
			for(int i=0;i<NX;i++)
			 {
				 for(int j=0;j<NY;j++)
				 {
					 if(ekran[i][j]!=0 && i!=jabco.x && j!=jabco.y)
					 {
						u8g.drawbox(i*8,j*8,6,6); 
					 }
				 }
			 }
			 if(ekran[jabco.x][jabco.y] > 0)u8g.drawbitmap(jabco.x,jabco.y,6,6,jablko);
		 
      }while( u8g.nextPage() );
     
 }while(1); 

} 
