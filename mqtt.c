#include <stdio.h>
#include <string.h>
#include <mosquitto.h>
#include <stdlib.h>

#define MQTT_HOSTNAME "localhost"
#define MQTT_PORT 1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_TOPIC "from_Client_01"

int main(int argc, char *argv[]){
	struct mosquitto *mosq = NULL;
	int ret;
	char text[50];
	
	if(argc == 2){
		strcpy(text, argv[1]);
		
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
	}
	return 0;
}
