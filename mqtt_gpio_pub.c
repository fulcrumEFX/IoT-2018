#include <stdio.h>
#include <string.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <wiringPi.h>


#define MQTT_HOSTNAME "localhost"
#define MQTT_PORT 1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_TOPIC "from_Client_01"

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
	ret = mosquitto_publish(mosq, NULL, MQTT_TOPIC, strlen(text), text, 0, false);
	
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
			if(R==0) publish("low");
			if(R==1) publish("high");
			delay(100);
		}
		comp = R;
	}
	return 0;
}

