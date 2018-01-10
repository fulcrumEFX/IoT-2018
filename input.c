
 
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int main(int argc, char *argv[])
{
	int R;
	if(wiringPiSetup() == -1)
	{
		puts("FEHLER");
		return 1;
	}
	puts("LÄUFT");
	pinMode(0, OUTPUT);
	
	puts("MIT Strg C ABBRECHEN");
	while(1){
		R=digitalRead(0);
		printf("GPIO17 : [%i]%c",R,13);
	}
	return 0;
}
