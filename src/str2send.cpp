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
    processarReal(x, true);
    processarReal(y, false);
    bButtonPressed = _buttonPressed;
    
}


void StringToSend::iniResultatToSend(){
   strcpy(resultat, "DATA,");
}

bool StringToSend::determinarSigneNombre(int n){//esNegatiu
        return n<0;
}


void StringToSend::processarReal(char val[], bool esX){
    int i= 0;
    int numReal=0;
    for(i=0;i<10;i++){
        if(val[i]=='\0') break;
        else if (val[i]!='-' || val[i]!='+') numReal++;
        
    }
    
    if(esX){
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
    }else{
        if(numReal == 1){
            yReal[1]='0';
            yReal[2]='0';
            yReal[3]=val[1];
        }else if (numReal == 2){
            yReal[1] ='0';
            yReal[2]= val[1];
            yReal[3]=val[2];
        }else if (numReal == 3){
            yReal[1]=val[1];
            yReal[2]=val[2];
            yReal[3]=val[3];
        }
        yReal[4]=',';
        yReal[5]='\0';
    }
    
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

