#include <string.h>
#include "str2send.h"
#include <mbed.h>

Serial s(USBTX, USBRX);

StringToSend::StringToSend(int _xI, int _yI,char _x[], char _y[], bool _buttonPressed){
    
    char f[10];
    
    if(!determinarSigneNombre(_xI)) 
        f[0]='+';
    sprintf(x, "%s%d\0",f, _x);
    if(!determinarSigneNombre(_yI))   
        f[0]='+';
    sprintf(y, "%s%d\0",f, _y);

    
    xI=_xI;
    yI=_yI;
    processarReal(x);
    processarReal(y);
    bButtonPressed = _buttonPressed;
    
}


void StringToSend::iniResultatToSend(){
   strcpy(resultat, "DATA,");
}

bool StringToSend::determinarSigneNombre(int n){//esNegatiu
        return n<0;
}


void StringToSend::processarReal(char val[]){
    int i= 0;
    int numReal=0;
    for(i=0;i<10;i++){
        if(val[i]=='\0') break;
        else if (val[i]!='-' || val[i]!='+') numReal++;
        
    }
    
    if(numReal == 1){
        xReal[1]='0';
        xReal[2]='0';
        xReal[3]=val[1];
    }else if (numReal == 2){
        xReal[1] ='0';
        xReal[2]= val[1];
        xReal[3]=val[2];
    }else if (numReal == 3){
        xReal[1]=val[1];
        xReal[2]=val[2];
        xReal[3]=val[3];
    }
    xReal[4]=',';
    xReal[5]='\0';
}


void StringToSend::generateString(){
    strcat(resultat, xReal);
    strcat(resultat,yReal);
    if(bButtonPressed) //boto apretat
        strcat(resultat, ",1");
    else
        strcat(resultat, ",0");

    //enviarho al earth!
    s.printf(resultat);
}

