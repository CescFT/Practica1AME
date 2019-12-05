#include <string.h>
#include "str2send.h"
#include <mbed.h>

Serial s(USBTX, USBRX);

StringToSend::StringToSend(int _xI, int _yI,char _x[], char _y[], bool _buttonPressed){
    
    int aux;
    char signe='a';
    
    strcpy(resultat, "DATA,");
    if (!determinarSigneNombre(_xI)){
        strcat(resultat, "+");
    }else{
        strcat(resultat, "-");
        _xI = _xI * (-1);
    }
    aux = fillZerosCounter(_xI);
    for (int i = 0; i < aux; i = i + 1){
        strcat(resultat, "0");
    }
    sprintf(x, "%d,", _xI);
    strcat(resultat, x);

    if (!determinarSigneNombre(_yI)){
        strcat(resultat, "+");
    }else{
        strcat(resultat, "-");
        _yI = _yI * (-1);
    }
    aux = fillZerosCounter(_yI);
    for (int i = 0; i < aux; i = i + 1){
        strcat(resultat, "0");
    }
    sprintf(y, "%d,%d", _yI, _buttonPressed);
    strcat(resultat, y);
    
    /*xI=_xI;
    yI=_yI;
    
    processarReal(x, true);
    processarReal(y, false);
    bButtonPressed = _buttonPressed;*/
    
}


void StringToSend::iniResultatToSend(){
   strcpy(resultat, "DATA,");
}

bool StringToSend::determinarSigneNombre(int n){//esNegatiu
        return n<0;
}

/*
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
    
}*/

int StringToSend::fillZerosCounter(int val){
    int cont = 2;
    while (val > 10)
    {
        cont = cont - 1;
        val = val / 10;
    }
    return cont;
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

