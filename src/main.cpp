#include <mbed.h>

//Centre
#define CENTERMIN 0.60
#define CENTERMAX 0.85


AnalogIn posX_joystick (A1); //IO
AnalogIn posY_joystick (A0); //I1

DigitalOut led_nord(D11); //O0
DigitalOut led_sud(D10); //O1
DigitalOut led_est(D9); //O2
DigitalOut led_oest(D6); //O3
DigitalOut led_boto(D5); //O4
DigitalIn button(A2); //boto

Serial serial1(USBTX, USBRX);


void calculValor(double x, double y, char value){
    int equivY = 0;
    int equivX = 0;
    char xequiv[100];
    char yequiv[100];
    for(int i = 0; i<100; i++)
        xequiv[i]='b';
    for(int i=0; i<100; i++)
        yequiv[i]='b';
    if((value & (1 << 3))){
      equivY=(y - CENTERMAX)*127/(1 - CENTERMAX);
    }
    if((value & (1 << 1))){
      equivY=y*127/(1-CENTERMIN);
      equivY=-(127 - equivY);
    }
    if((value & (1 << 2))){
      equivX=(x - CENTERMAX)*127/(1 - CENTERMAX);
    }
    if((value & (1 << 0))){
      equivX=x*127/(1-CENTERMIN);
      equivX=-(127 - equivX);
    }

    sprintf(xequiv, "\nx bona: %d", equivX);
    sprintf(yequiv, "\ny bona: %d\n", equivY);
    serial1.printf(xequiv);
    serial1.printf(yequiv);


}





void ini_leds(){
    led_nord.write(0);
    led_sud.write(0);
    led_est.write(0);
    led_oest.write(0);
    //wait_ms(1500);
}

char calibration(double x, double y){
  char value = 0;
  if(x>CENTERMAX) value = value | (1 << 2); //est
  if(x<CENTERMIN) value = value | (1 << 0); //oest
  
  if(y>CENTERMAX) value = value | (1 << 3); //nord
  if(y<CENTERMIN) value = value | (1 << 1); //sud
  
  return value;
}

void punt_cardinal_led_on(char value){
        
        
    led_nord.write((value & (1 << 3)));
    led_sud.write((value & (1 << 1)));
    led_est.write((value & (1 << 2)));
    led_oest.write((value & (1 << 0)));
  
    wait_ms(1500);
}


int main(){

  // put your setup code here, to run once:
  char posX[10];
  char posY[10];
  char sortidaN[10];
  char sortidaS[10];
  char sortidaE[10];
  char sortidaO[10];
  char equivY[10];
  char equivX[10];
 

  while(1) {
    // put your main code here, to run repeatedly:
    double x = posX_joystick.read(); 
    
    sprintf(posX, "x:%lf", x);
    serial1.printf(posX);
    double y = posY_joystick.read();
    sprintf(posY, "y: %lf\n", y);
    serial1.printf(posY);
    int nord;
    nord = 0;
    int sud=0;
    int est=0;
    int oest=0;
    
    
    ini_leds();
    if(button.read()==0){
      char value = calibration(x, y);
      if (value & (1 << 3)) nord=1;
      if(value & (1 << 1)) sud=1;
      if(value & (1 << 2)) est=1;
      if(value & (1 << 0)) oest=1;
      


      sprintf(sortidaN, "Nord: %d ", nord);
      serial1.printf(sortidaN);
      sprintf(sortidaS, "Sud: %d ", sud);
      serial1.printf(sortidaS);
      sprintf(sortidaE, "Est: %d ", est);
      serial1.printf(sortidaE);
      sprintf(sortidaO, "Oest: %d ", oest);
      serial1.printf(sortidaO);
      
      punt_cardinal_led_on(value);
      


      calculValor(x, y, value);


    }
      led_boto.write(button.read());

  }
}