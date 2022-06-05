
#include"pitches.h"
#include "U8glib.h"

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST);


  //bool blok[2][2]={{},{}};
  //int x=7,y=0; 
 int melodia[] = {
  NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_C5, NOTE_E5,
  NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4,
  NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4,
}; 

int czas[] = {
  2,4,4,2,4,4,2,4,4,2,4,4,2,4,4,2,2,2,2,1, 
  2,4,2,4,4,2,2,2,4,4,2,4,4,2,2,2,2,1,
};


void setup() {
  pinMode(5,OUTPUT);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  Serial.begin(9600);
  // put your setup code here, to run once:
  
  
}

bool blok[2][2]={{0,1},{0,1}};

int x=7,y=0;
 
bool XY[16][8]={{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};

unsigned long ty=0;
unsigned long tx=0;
unsigned long tm=0;
unsigned long tp=0;
int i=0;


void loop() {
    unsigned long t=millis();
    int muz=1000/czas[i];
  
    tone(5,melodia[i]);
    if(t-tm>=muz){
      if(melodia[i]==melodia[i+1])noTone(5);
      i++;
      tm=t;      
    }
     

     

    if(i==38)i=0;
    u8g.firstPage();
    
      do {
        
        if(t-ty>=200)
        {
          ty=t;
          if(!XY[x][y+1]&& y+1<=7)y++;
          else {
            XY[x][y]=true;
            tone(5,NOTE_E3);//x=7;
            
            
            y=0;            
          }
        }
        if(digitalRead(4)==LOW && x-1>=0 && t-tx>=100){         
          tx=t;
          if(!XY[x-1][y]) x--;
           
        }
        if(digitalRead(2)==LOW && x+1<16 && t-tx>=100){
           tx=t;
           if(!XY[x+1][y]) x++;
          
        }
        u8g.drawBox(8*x,8*y,6,6);
        
        
        
        for(int j=7;j>=0;j--){
        bool gap=false;
           
        for(int i=0;i<16;i++){
        if(!gap){ 
        if(!XY[i][j]){         
          gap=true;
        }
        }
        }
          
        if(!gap){  
          for(int i=j;i>0;i--){
          for(int k=0;k<16;k++){  
             XY[k][i]=XY[k][i-1];
          }
          }
        }
        
        for(int i=0;i<16;i++){                             
        if(XY[i][j]) u8g.drawBox(8*i,8*j,6,6);
        }      
        }
              
      }while( u8g.nextPage() );
      
} 
