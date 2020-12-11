#include<stdio.h>
#include<string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include<stdlib.h>
#include<ctype.h>
#include<fcntl.h>
#include<semaphore.h>

int main()
{
	sem_unlink("/tmp_sem2");
	sem_t *sem2 = sem_open("/tmp_sem2",O_CREAT,0660,0);
	sem_t *sem1 = sem_open("/tmp_sem1",0);
	sem_wait(sem1);
	char password[10];
	//************create a temporary file************//
	key_t key;
	key=ftok("shmfile",65);
	while(key==-1)
		key=ftok("p1.c",65); 
	int id=shmget(key,1024,0666|IPC_CREAT);
	if(id==-1)
	{
		printf("Error in getting the shmId\n");
		exit(1);		
	}
	void *address;
	address=(char*)shmat(id,NULL,0);
	strcpy(password,(char *)address);
	if(address==(char *)-1)
	{
		printf("Error getting address\n");
		exit(1);
	}
	int alphanum=0,spclchar=0;
	for(int i=0;i<10;++i)
	{
		if(isalnum(password[i]))
			++alphanum;
		else
			++spclchar;
	}
	char array[3];
	array[0]=(char)(alphanum+97);
	array[1]=(char)(spclchar+97);
	array[2]=0;
	sprintf(address,"%s",array);
	sem_post(sem2);
	return 0;
}
