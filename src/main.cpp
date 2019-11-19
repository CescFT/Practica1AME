#include <mbed.h>

//Centre
#define CENTERX 0.80
#define CENTERY 0.818559 

//NORD
#define NORTHX 0.731624
#define NORTHY 0.863492

//SOUTH
#define SOUTHX 0.8424
#define SOUTHY 0.0166

//EAST
#define EASTX 0.807545
#define EASTY 0.79758


//WEST
#define WESTX 0.81319
#define WESTY 0.01782

AnalogIn posX_joystick (A1); //IO
AnalogIn posY_joystick (A0); //I1

DigitalOut led_nord(D9); //O3
DigitalOut led_sud(D5); //O4
DigitalOut led_est(D10); //O1
DigitalOut led_oest(D6); //O2

Serial serial1(USBTX, USBRX);


void ini_leds(){
    led_nord.write(0);
    led_sud.write(0);
    led_est.write(0);
    led_oest.write(0);
    //wait_ms(1500);
}

void punt_cardinal_led_on(double x, double y){
  if(y>CENTERY)
    {
        //nord
        led_nord.write(1);
        led_sud.write(0);
        led_est.write(0);
        led_oest.write(0);
    }else {
        //sud
        led_nord.write(0);
        led_sud.write(1);
        led_est.write(0);
        led_oest.write(0);
    }
    if(x>CENTERX){
          //Est
        led_nord.write(0);
        led_sud.write(0);
        led_est.write(1);
        led_oest.write(0);
    }else{
          //Oest
        led_nord.write(0);
        led_sud.write(0);
        led_est.write(0);
        led_oest.write(1);
    }
    
    if(y>CENTERY)
    {
      if(x>CENTERX){
        //nord est
        led_nord.write(1);
        led_sud.write(0);
        led_est.write(1);
        led_oest.write(0);
      }else{
        //nord oest
        led_nord.write(1);
        led_sud.write(0);
        led_est.write(0);
        led_oest.write(1);
      }
    }else{
      if(x>CENTERX){
        //sud est
        led_nord.write(0);
        led_sud.write(1);
        led_est.write(1);
        led_oest.write(0);
      }else{
        //sud oest
        led_nord.write(0);
        led_sud.write(1);
        led_est.write(0);
        led_oest.write(1);
      }
    }
    wait_ms(1500);
}


float position(float pos){
    //Being:
    //MAX_Y and MIN_Y, S and N
    //MAX_X and MIN_Y, E and W
    //CENTER_X and CENTER_Y, point zero
    //defined as global
    if(between(pos,NORTHY,CENTERY)) return equivalentScale(pos,NORTHY,CENTERY,'N');
    if(between(pos,EASTX,CENTERX)) return equivalentScale(pos,EASTX,CENTERX,'E');
    if(between(pos,SOUTHY,CENTERY)) return equivalentScale(pos,SOUTHY,CENTERY,'S');
    if(between(pos,WESTX,CENTERX)) return equivalentScale(pos,WESTX,CENTERX,'W');
    else return 0;
}

bool between(float val, float val_1, float val_2){
    if(val_1 > val_2) return (val<val_1 && val>val_2);
    if(val_2 > val_1) return (val>val_1 && val<val_2);
    else return false;
}

float equivalentScale(float val, float val_1, float val_2, char orientation){
    float proportion;
    float final_pos;
    proportion = abs(val_2)/abs(val_1);
    final_pos = final_pos + 127 * proportion;
    switch(orientation){
        case 'N':
            return final_pos;
        case 'E':
            return final_pos;
        case 'S':
            return -final_pos;
        case 'W':
            return -final_pos;
    }
}



int main() {

  // put your setup code here, to run once:
  char posX[10];
  char posY[10];
  

  while(1) {
    // put your main code here, to run repeatedly:
    double x = posX_joystick.read(); 
    
    sprintf(posX, "x:%lf", x);
    serial1.printf(posX);
    double y = posY_joystick.read();
    sprintf(posY, "y: %lf\n", y);
    serial1.printf(posY);

    ini_leds();
        
    punt_cardinal_led_on(x, y);

  }
}