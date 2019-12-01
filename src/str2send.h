#define MBED_STR2SEND_H
#include <string.h>

class StringToSend{
    public:
        StringToSend(int xI, int yI,char x[], char y[], bool bButtonPressed);
        void generateString(); //enviarho directament al earth
        void iniResultatToSend();
        void determinarSigneNombreX();
        void determinarSigneNombreY();
        void processarXReal();
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

