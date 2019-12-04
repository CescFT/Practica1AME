#define MBED_STR2SEND_H
#include <string.h>
#include <mbed.h>

class StringToSend{
    public:
        StringToSend(int xI, int yI,char x[], char y[], bool bButtonPressed);
        void generateString(); //enviarho directament al earth
        void iniResultatToSend();
        bool determinarSigneNombre(int n);
        void processarReal(char val[], bool esX);
        void processarYReal();
        
    private:
        char resultat[100];
        char x[10];
        char y[10];
        char xReal[10];
        char yReal[10];
        bool bButtonPressed;
        int xI;
        int yI;
};

