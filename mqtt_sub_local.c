#include <stdio.h>
#include <string.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <mysql/mysql.h>		//`mysql_config --cflags --libs`
#include <time.h>

#define MQTT_HOSTNAME "10.24.3.66"
#define MQTT_PORT 1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_TOPIC_1 "test15"
#define MQTT_TOPIC_2 "test17"
#define MQTT_TOPIC_3 "test01"
#define MQTT_TOPIC_4 "test14"
#define MQTT_TOPIC_5 "test18"
#define MQTT_TOPIC_6 "test19"
#define MQTT_TOPIC_7 "test20"
#define MQTT_TOPIC_8 "test13"
#define MQTT_TOPIC_9 "test12"
#define MQTT_TOPIC_10 "test11"
#define MQTT_QOS 1

//SQL Connect parameters
static char *hostname = "localhost";
static char *username = "root";
static char *password = "iot2018";
static char *database = "EddyDB";
static char *socketname = NULL;
unsigned int port = 3306;
unsigned int flag = 0;

void onConnect(struct mosquitto *mosq, void *userdata, int result){
	if (!result){
		 mosquitto_subscribe(mosq, NULL, MQTT_TOPIC_1, MQTT_QOS);
		 mosquitto_subscribe(mosq, NULL, MQTT_TOPIC_2, MQTT_QOS);
		 mosquitto_subscribe(mosq, NULL, MQTT_TOPIC_3, MQTT_QOS);
		 mosquitto_subscribe(mosq, NULL, MQTT_TOPIC_4, MQTT_QOS);
		 mosquitto_subscribe(mosq, NULL, MQTT_TOPIC_5, MQTT_QOS);
		 mosquitto_subscribe(mosq, NULL, MQTT_TOPIC_6, MQTT_QOS);
		 mosquitto_subscribe(mosq, NULL, MQTT_TOPIC_7, MQTT_QOS);
		 mosquitto_subscribe(mosq, NULL, MQTT_TOPIC_8, MQTT_QOS);
		 mosquitto_subscribe(mosq, NULL, MQTT_TOPIC_9, MQTT_QOS);
		 mosquitto_subscribe(mosq, NULL, MQTT_TOPIC_10, MQTT_QOS);
	 }
	else printf("Error: Failed to connect");
}
void getLocalTime(char * _addr){
	time_t rawtime;
	struct tm* timeinfo;
	char timestr[50];
	
	rawtime = time(0);
	timeinfo = localtime(&rawtime);
	strftime(timestr, 50, "%e/%m/%Y %X", timeinfo);
	
	strcpy(_addr, timestr);
	return;
	
}

int WriteDataBase( const struct mosquitto_message *message){
	MYSQL *conn;
	MYSQL *err;
	int res;
	char sqlString[200], timestr[50];
	
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
	getLocalTime(timestr);
	sprintf(sqlString, "INSERT INTO gpio_status(Broker, Topic, QOS, Message, Time_received) VALUES ('%s', '%s', %i, '%s', '%s');",MQTT_HOSTNAME, (char*)message->topic, message->qos, (char*)message->payload, timestr);
	
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
void onMessage(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message){
	int cnt = 0;
	
	if(message->payloadlen){
		printf("%i: %i go/retain [%i/%i]: qual Topic: %s, Message: %s\n", cnt++, message->mid, message->qos, message->retain, (char*)message->topic, (char*)message->payload);
		cnt++;
		if(message->retain==0) WriteDataBase(message);
	}else{
		printf("Topic: %s, Message: (null)\n", message->topic);
	}
}



int main(){
	int retain = 0;
	bool clean_session = true;
	struct mosquitto *mosq = NULL;
	mosquitto_lib_init();
	mosq = mosquitto_new(NULL, clean_session, NULL);
	mosquitto_username_pw_set(mosq, MQTT_USERNAME, MQTT_PASSWORD);
	mosquitto_connect_callback_set(mosq, onConnect);
	mosquitto_message_callback_set(mosq, onMessage);
	mosquitto_connect(mosq, MQTT_HOSTNAME, MQTT_PORT, retain);
	puts("...working");
	while(!mosquitto_loop_forever(mosq, 0, 1)){}
	
	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
	
	return 0;
} 

