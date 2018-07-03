#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "dhtxx.h"
#include "crud.h"

/*  #define DHTPIN 7 */
#define SITECODE "default"

int main(int argc, char **argv) {
	float ftemp;
	float fhumidity;
	int retval;
	uint8_t dht_pin;
	char sitecode[50];

	
	// controlla il numero di parametri
	if (argc < 2) {
		fprintf(stderr, "Command line error!\n");
		fprintf(stderr, "Usage: %s <WiringPi_Pin> [<sitecode>]\n", argv[0]);
		return -1;
	}
	
	dht_pin=atoi(argv[1]);
	if (dht_pin<0 || dht_pin>30) {
		fprintf(stderr, "Wrong <WiringPi_Pin>\n");
		return -1;
	}
	
	if (argc > 2) {
		strncpy(sitecode, argv[2], sizeof(sitecode));
	}
	else {
		strncpy(sitecode, SITECODE, sizeof(sitecode));
	}
	
	retval = DHTxx_read_m_data(dht_pin,&ftemp,&fhumidity,3);
	
	//inizio codice creazione data
	time_t rawtime;
	struct tm *info;
	char data[50];
	
	time(&rawtime);
	info = localtime(&rawtime);
	strftime(data,sizeof(data),"%Y-%m-%d %H:%M:%S",info);
	//fine
	
	if(retval==0){
		printf("data: %s temp: %4.1f umidita: %4.1f\n",data,ftemp,fhumidity);
		CRUD_insert_temp_hum(sitecode,data,ftemp,fhumidity);
	}
	else{
		printf("Errore\n");
	}	
	
	return 0;
}
