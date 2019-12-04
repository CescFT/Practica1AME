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
    int xLlegida=127;
    int yLlegida=-1;
    char xReal[10];
    char yReal[10];
    char x[10];
    char y[10];
    char resultat[100];
    char signe='-';

    if(!determinarSigneNombre(xLlegida))
        signe='+';


    if(signe == '+'){
        xReal[0]='+';
        sprintf(x, "%c%d\0", signe,xLlegida);
    }else{
        xReal[0]='-';
        sprintf(x, "%d\0", xLlegida);
    }

    signe='-';
    if(!determinarSigneNombre(yLlegida))
        signe='+';


    if(signe=='+'){
        sprintf(y, "%c%d\0", signe, yLlegida);
        yReal[0]='+';
    }else{
        yReal[0]='-';
        sprintf(y, "%d\0", yLlegida);
    }


    strcpy(resultat, "DATA,");

    int numReal=0;

    if(xLlegida>0)
    {
        if(xLlegida<=9)
            numReal=1;
        else if(xLlegida > 9 && xLlegida<=99)
            numReal=2;
        else if(xLlegida>99)
            numReal=3;
    }else{
        if(xLlegida>=-9)
            numReal=1;
        else if(xLlegida>=-99 && xLlegida<-9)
            numReal=2;
        else if(xLlegida<-99)
            numReal=3;
    }


    char *val= &x;
    char elem=*val;



    if(numReal == 1){
        xReal[1]='0';
        xReal[2]='0';

        val=val+1;
        elem=*val;

        xReal[3]=elem;
    }else if (numReal == 2){
        xReal[1] ='0';


        val=val+1;
        elem=*val;

        xReal[2]= elem;


        val=val+1;
        elem=*val;

        xReal[3]=elem;
    }else if (numReal == 3){


        val=val+1;
        elem=*val;

        xReal[1]=elem;


        val=val+1;
        elem=*val;

        xReal[2]=elem;


        val=val+1;
        elem=*val;

        xReal[3]=elem;
    }
    xReal[4]=',';
    xReal[5]='\0';

    printf("%s\n", xReal);

    numReal=0;

    if(yLlegida>0)
    {
        if(yLlegida<=9)
            numReal=1;
        else if(yLlegida > 9 && yLlegida<=99)
            numReal=2;
        else if(yLlegida>100)
            numReal=3;
    }else{
        if(yLlegida>=-9)
            numReal=1;
        else if(yLlegida>=-99 && yLlegida<-9)
            numReal=2;
        else if(yLlegida<-99)
            numReal=3;
    }


    char *p = &y;
    char elem1= *p;


    if(numReal == 1){
        yReal[1]='0';
        yReal[2]='0';


        p = p +1;
        elem1 = *p;

        yReal[3]=elem1;
    }else if (numReal == 2){
        yReal[1] ='0';

        p = p +1;
        elem1 = *p;

        yReal[2]= elem1;

        p=p+1;
        elem1 = *p;

        yReal[3]=elem1;
    }else if (numReal == 3){

        p=p+1;
        elem1 = *p;

        yReal[1]=elem1;

        p=p+1;
        elem1 = *p;

        yReal[2]=elem1;

        p=p+1;
        elem1 = *p;

        yReal[3]=elem1;
    }
    yReal[4]=',';
    yReal[5]='\0';

    printf("%s", yReal);

    strcat(resultat, xReal);
    strcat(resultat, yReal);

    int boto = 0;

    if(boto==0){
        strcat(resultat, "0");
    }else{
        strcat(resultat, "1");
    }

    printf("\n\nString a enviar: %s", resultat);

    return 0;
}
