#pragma once

typedef enum{
	ES_Idle,
	ES_Dead,
	ES_Trick,		//In Process of Performing Trick
	ES_TrickF,		//Trick Failed
	ES_TrickS		//Trick Successful

}EntityState;


typedef struct Entity_S {

	int id;
};