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

    //enviarho al earth!
    s.printf(resultat);
    
}


void StringToSend::iniResultatToSend(){
   strcpy(resultat, "DATA,");
}

bool StringToSend::determinarSigneNombre(int n){//esNegatiu
        return n<0;
}

int StringToSend::fillZerosCounter(int val){
    int cont = 2;
    while (val > 10){
        cont = cont - 1;
        val = val / 10;
    }
    return cont;
}


