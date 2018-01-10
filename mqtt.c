#include <stdio.h>
#include <string.h>
#include <mosquitto.h>
#include <stdlib.h>


#define MQTT_HOSTNAME "localhost"
#define MQTT_PORT 1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_TOPIC "from_Client_01"
#define MQTT_TOPIC_1 "from_Client_01"
#define MQTT_TOPIC_2 "from_Client_02"
#define MQTT_TOPIC_3 "from_Client_03"

/*
void onConnect(struct mosquitto *mosq, void *userdata, int result){
	if (!result) mosquitto_subscribe(mosq, NULL, MQTT_TOPIC_1, 1);
	else printf("Error: Failed to connect");
}

void onMessage(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message){
	int X1, X2;
	char msg[50];
	
	if(message->payloadlen){
		printf("%i: %i go/retain [%i/%i]: qual Topic: %s, Message: %s\n", cnt++, message->mid, message->qos, message->retain, (char*)message->topic, (char*)message->payload);
		X1 = 0;
		X2 = 0;
		strcpy(msg, message->payload);
		if(message->retain==0) WriteDataBase(X1, X2, msg);
	}else{
		printf("Topic: %s, Message: (null)\n", message->topic);
	}
}

int WriteDataBase( int X1, int X2, char msg[50]){
	MYSQL *conn;
	MYSQL *err;
	int res;
	char sqlString[80];
	
	mysql_library_init(0, NULL, NULL);
	
	conn = mysql_init(NULL);
	
	if(conn==NULL){
		puts("NO INIT DATABASE!");
		return 1;
	}
	err = mysql_real_connect(conn, hostname, username, password, database, port, socketname, flag);
	if (!err){
		puts("NO DATABASE!");
		mysql_close(conn);
		return 1;
	}
	sprintf(sqlString, "INSERT INTO Tabelle01(X1,X2,msg) VALUES (%i, %i, '%s');", X1, X2, msg);
	
	res = mysql_query(conn, sqlString);
	if(res){
		puts("NO ACCESS!");
		mysql_close(conn);
		return 1;
	}
	mysql_close(conn);
	mysql_library_end;
	return 0;
}
*/

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
