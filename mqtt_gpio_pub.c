#include <stdio.h>
#include <string.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>


#define MQTT_HOSTNAME "10.24.3.66"
#define MQTT_PORT 1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_TOPIC "test2"

int publish(char text[]){
	struct mosquitto *mosq = NULL;
	int ret;
	
	mosquitto_lib_init();
		
	mosq = mosquitto_new(NULL, true, NULL);
	if(!mosq){
		printf("Can't initialize Mosquitto library");
		return 1;
	}
	mosquitto_username_pw_set(mosq, MQTT_USERNAME, MQTT_PASSWORD);
	ret = mosquitto_connect(mosq, MQTT_HOSTNAME, MQTT_PORT, 0);
	if (ret){
		printf("Can't connect to Mosquitto Server");
		return 1;
	}
	ret = mosquitto_publish(mosq, NULL, MQTT_TOPIC, strlen(text), text, 1, false);
	
	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
	return 0;
}


int main(int argc, char *argv[])
{
	int R;
	int comp;
	int _gpio_pin = atoi(argv[1]);
	char buffer[100], timestr[95];
	time_t rawtime;
	struct tm* timeinfo;
	char *Meldung[] = {"LOW", "HIGH"};
	
	if(wiringPiSetup() == -1)
	{
		puts("FEHLER");
		return 1;
	}
	puts("LÄUFT");
	pinMode(_gpio_pin, OUTPUT);
	
	puts("MIT Strg C ABBRECHEN");
	while(1){
		R=digitalRead(_gpio_pin);
		if(R != comp){
			rawtime = time(0);
			timeinfo = localtime (&rawtime);
			strftime(timestr, 90, "%e/%m/%Y %X", timeinfo);
			sprintf(buffer, "%s: %s",  timestr, Meldung[R] );
			publish(buffer);
			printf("%s", buffer);
			delay(100);
		}
		comp = R;
	}
	return 0;
}

