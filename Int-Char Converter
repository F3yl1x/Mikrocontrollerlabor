#include <stdio.h>

void itoc(int in, char ch[]);
void ctoi(char ch[], int *i);

int main() {
    
    int testi = 216;
    char testch[4]= "000";
    printf("Integer: %d \nChar: %s\n", testi, testch);
    itoc(testi,testch);
    printf("ITOC: \nInteger: %d \nChar: %s\n", testi, testch);
    testch[0] = '1';
    testch[1] = '8';
    testch[2] = '7';
    ctoi(testch, &testi);
    printf("CTOI: \nInteger: %d \nChar: %s\n", testi, testch);
    return 0;
}


void itoc(int in, char ch[])
{
    ch[0] = ((in - (in%10)) - ((in - (in%10))%100))/100 + '0';
    ch[1] = ((in - (in%10))%100)/10 + '0';
    ch[2] = in%10 + '0';

}

void ctoi(char ch[], int *i)
{
    *i = ((ch[0] - '0')*100) + ((ch[1] - '0')*10) + (ch[2] - '0');
}
