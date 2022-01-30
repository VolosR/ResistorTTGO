#include <TFT_eSPI.h> 
#include "res.h"

const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;

TFT_eSPI tft = TFT_eSPI(); 
int tt[4]={1,2,5,10};
int cT[4]={TFT_BROWN,TFT_RED,TFT_GOLD,TFT_SILVER};
int colors[12]={TFT_BLACK,TFT_BROWN,TFT_RED,TFT_ORANGE,TFT_YELLOW,TFT_GREEN,TFT_BLUE,TFT_VIOLET,TFT_LIGHTGREY, TFT_WHITE, TFT_GOLD,TFT_SILVER };
double multis[12]={1,10,100,1000,10000,100000,1000000,10000000,100000000,100000000,0.1,0.01};
String mm[12]={"x1","x10","x100","x1K","x10K","x100K","x1M","x10M","x100M","x1G","x0.1","x0.01"};
int band=0;
int color=0;

int first=1;
int secon=2;
int multiplier=1;
int tolerance=2;
int deb1=0;
int deb2=0;

int x=56;
int y=24;
int w=126;
int h=20;

int bPos[4]={86,98,110,138};

void setup() {

  pinMode(0,INPUT_PULLUP);
  pinMode(35,INPUT_PULLUP);

    ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(TFT_BL, pwmLedChannelTFT);
  ledcWrite(pwmLedChannelTFT, 100);
  
  tft.init();
  tft.setSwapBytes(true);
  tft.setRotation(1);
  
  tft.fillScreen(TFT_BLACK);
  tft.drawString("Resistor CALC",x,0,2);
  tft.pushImage(x,y,120,26,resistor);

 
   tft.fillRect(x+30,y,6,26,colors[first]);
  tft.fillRect(x+42,y+3,6,20,colors[secon]);
  tft.fillRect(x+54,y+3,6,20,colors[multiplier]);
  tft.fillRect(x+82,y,6,26,cT[tolerance]);

  tft.fillCircle(bPos[band]+2,58,2,TFT_WHITE);
   for(int i=0;i<12;i++)
   {
    
    
    if(i<10  ){
    tft.fillRect(0,i*13,11,13,colors[i]);
    tft.fillRect(22,i*13,11,13,colors[i]);
    if(i==0)
    tft.setTextColor(TFT_WHITE,colors[i]);
    else
    tft.setTextColor(TFT_BLACK,colors[i]);
    
    tft.drawString(String(i),3,(i*13)+2);
    tft.drawString(String(i),25,(i*13)+2);

    tft.setTextColor(TFT_WHITE,TFT_BLACK);
    }
    if(i==0)
    tft.drawCircle(235,(i*11)+5,4,TFT_WHITE);
    else
    tft.fillCircle(235,(i*11)+5,4,colors[i]);

    tft.drawString(mm[i],194,(i*11)+1);
    
   }

    /*
    tft.drawString("<",14,(first*13)+2);
    tft.drawString("<",36,(secon*13)+2);
     */

     tft.fillCircle(16,(first*13)+5,2,TFT_WHITE);
     tft.fillCircle(38,(secon*13)+5,2,TFT_WHITE);
     tft.fillCircle(188,(multiplier*11)+5,2,TFT_WHITE);
    

    for(int i=0;i<4;i++){
    tft.fillRect(44+(i*34),117,34,11,cT[i]);
    tft.setTextColor(TFT_BLACK,cT[i]);
    tft.drawString(String(tt[i])+"%",54+(i*34),119);
    }
    tft.fillCircle(61+(tolerance*34),133,2,TFT_WHITE);
   tft.setTextColor(TFT_WHITE,TFT_BLACK); 
}

void loop() {

  if(digitalRead(0)==0)
  {
    if(deb1==0)
    {
      tft.fillCircle(bPos[band]+2,58,2,TFT_BLACK);
     deb1=1;
     band++;
     if(band>3)
     band=0; 
     tft.fillCircle(bPos[band]+2,58,2,TFT_WHITE);
    }
    }else deb1=0;

     if(digitalRead(35)==0)
  {
    if(deb2==0)
    {
     
     deb2=1;
     if(band==0)
      {
         tft.fillCircle(16,(first*13)+5,2,TFT_BLACK);
      first++;
      if(first>9)
      first=0;
      tft.fillRect(x+30,y,6,26,colors[first]);
       tft.fillCircle(16,(first*13)+5,2,TFT_WHITE);
      }
          if(band==1)
            {
              tft.fillCircle(38,(secon*13)+5,2,TFT_BLACK);
         secon++;
         if(secon>9)
         secon=0;
         tft.fillCircle(38,(secon*13)+5,2,TFT_WHITE);
         tft.fillRect(x+42,y+3,6,20,colors[secon]);
            }

             if(band==2)
            {
              tft.fillCircle(188,(multiplier*11)+5,2,TFT_BLACK);
          multiplier++;
          if(multiplier>11)
          multiplier=0;
          tft.fillCircle(188,(multiplier*11)+5,2,TFT_WHITE);
          tft.fillRect(x+54,y+3,6,20,colors[multiplier]);
            }

                if(band==3)
            {
              tft.fillCircle(61+(tolerance*34),133,2,TFT_BLACK);
          tolerance++;
          if(tolerance>3)
          tolerance=0;
          tft.fillCircle(61+(tolerance*34),133,2,TFT_WHITE);
          tft.fillRect(x+82,y,6,26,cT[tolerance]);
            }

     double res=((first*10)+secon)*multis[multiplier];
     tft.fillRect(44,70,136,46,0x00A5);
     double maxx=res+(res*(tt[tolerance]/100.00));
     double minn=res-(res*(tt[tolerance]/100.00));
     tft.setTextColor(TFT_WHITE,0x00A5); 

     if(res>=1000 && res<1000000){
     tft.drawString(String(first)+String(secon)+"x10 ="+String(res/1000)+" K",48,76,2);
     tft.drawString(String(multiplier),85,72);
     tft.drawString("MAX:"+String(maxx),48,94);
     tft.drawString("MIN:"+String(minn),48,106);
     }
     
      else if(res>=1000000)
     {
     tft.drawString(String(first)+String(secon)+"x10 ="+String(res/100000)+" M",48,76,2);
     tft.drawString(String(multiplier),85,72);
     tft.drawString("MAX:"+String(maxx),48,94);
     tft.drawString("MIN:"+String(minn),48,106);
     }
     
     else
     {
     tft.drawString(String(first)+String(secon)+"x10 ="+String(res)+" ohm",48,76,2);
     tft.drawString(String(multiplier),85,72);
     tft.drawString("MAX:"+String(maxx),48,94);
     tft.drawString("MIN:"+String(minn),48,106);
     }

     tft.setTextColor(TFT_WHITE,TFT_BLACK); 
     
    }
    }else deb2=0;
 
}
