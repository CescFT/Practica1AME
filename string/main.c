#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool determinarSigneNombre(int numero){
    return numero<0;
}

void processarReal(char val[], bool esX)
{

}

int main()
{
    int xLlegida=-20;
    int yLlegida=1;
    char xReal[10];
    char yReal[10];
    char x[10];
    char y[10];
    char resultat[100];
    char signe='a';

    if(!determinarSigneNombre(xLlegida))
        signe='+';


    if(signe == '+')
        sprintf(x, "%c%d\0", signe,xLlegida);
    else
        sprintf(x, "%d\0", xLlegida);


    signe='a';
    if(!determinarSigneNombre(yLlegida))
        signe='+';


    if(signe=='+')
        sprintf(y, "%c%d\0", signe, yLlegida);
    else
        sprintf(y, "%d\0", yLlegida);

    printf("%s\n", x);
    printf("%s\n", y);

    strcpy(resultat, "DATA,");

    int numReal=0;
    char *val= &x;
    char elem=*val;
    while(elem!='\0')
    {
        if(elem!='-' || elem!='+'){ /*fet aixi no agafa els signes pero bueno ho podem mirar*/
            numReal++;
        }
        val+=1;
        elem=*(val);
    }



    printf("Elements dins de la x: %d", numReal);

    if(numReal == 1){
        xReal[1]='0';
        xReal[2]='0';

        *val=&x;
        val=val+1;
        elem=*val;

        xReal[3]=elem;
    }else if (numReal == 2){
        xReal[1] ='0';

        *val=&x;
        val=val+1;
        elem=*val;

        xReal[2]= elem;

        *val=&x;
        val=val+2;
        elem=*val;

        xReal[3]=elem;
    }else if (numReal == 3){

        *val=&x;
        val=val+1;
        elem=*val;

        xReal[1]=elem;

        *val=&x;
        val=val+2;
        elem=*val;

        xReal[2]=val;

        *val=&x;
        val=val+3;
        elem=*val;

        xReal[3]=elem;
    }
    xReal[4]=',';
    xReal[5]='\0';

    printf("%s", xReal);

    numReal=0;
    *val= &y;
    elem=*val;
    while(elem!='\0')
    {
        if(elem!='-' || elem!='+'){ /*fet aixi no agafa els signes pero bueno ho podem mirar*/
            numReal++;
        }
        val+=1;
        elem=*(val);
    }



    printf("Elements dins de la y: %d", numReal);

    if(numReal == 1){
        yReal[1]='0';
        yReal[2]='0';
        yReal[3]=y[1];
    }else if (numReal == 2){
        yReal[1] ='0';
        yReal[2]= y[1];
        yReal[3]=y[2];
    }else if (numReal == 3){
        yReal[1]=y[1];
        yReal[2]=y[2];
        yReal[3]=y[3];
    }
    yReal[4]=',';
    yReal[5]='\0';


    /*printf("%s, %s", xReal, yReal);*/

    return 0;
}
