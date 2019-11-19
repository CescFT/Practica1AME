#include <mbed.h>

//Centre
#define CENTERMIN 0.70
#define CENTERMAX 0.80
/*
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
*/

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

char calibration(double x, double y){
  char value = 0;
  if(x>CENTERMAX) value = value | (1 << 2); //Max x
  else value = value | (1 << 0); //Min x
  if(y>CENTERMAX) value = value | (1 << 3); //Max y
  else value = value | (1 << 1); //Min y
  
  return value;
}

void punt_cardinal_led_on(char value){
        
        
    led_nord.write((value & (1 << 3)));
    led_sud.write((value & (1 << 1)));
    led_est.write((value & (1 << 2)));
    led_oest.write((value & (1 << 0)));
  
    wait_ms(1500);
}


int main() {

  // put your setup code here, to run once:
  char posX[10];
  char posY[10];
  char sortida[10];
  

  while(1) {
    // put your main code here, to run repeatedly:
    double x = posX_joystick.read(); 
    
    sprintf(posX, "x:%lf", x);
    serial1.printf(posX);
    double y = posY_joystick.read();
    sprintf(posY, "y: %lf\n", y);
    serial1.printf(posY);

    ini_leds();
    char val =calibration(x, y);
    sprintf(sortida, "res: %c\n", val);
    serial1.printf(sortida);
      
      punt_cardinal_led_on(val);
    //punt_cardinal_led_on(calibration(x, y));
    /*
    double num = position(x);
    sprintf(sortida, "res: %lf\n", num);
    serial1.printf(sortida);
    */

  }
}