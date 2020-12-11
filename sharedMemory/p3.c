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
	sem_t *sem2 = sem_open("/tmp_sem2",0);
	sem_wait(sem2);
	sem_t *sem3 = sem_open("/tmp_sem3", 0);
	char alphanum,spclchar;
	key_t key;
	key=ftok("p1.c",65);
	while(key==-1)
		key=ftok("shmfile",65); 
	int id=shmget(key,1024,0666|IPC_CREAT);
	if(id==-1)
	{
		printf("Id not created");
		exit(1);		
	}
	void *address;
	address=(char*)shmat(id,NULL,0);
	if(address==(char *)-1)
	{
		perror("Error retreiving the address of the shared memory region");
		exit(1);
	}
	char array[2];
	char *strength;
	strcpy(array,(char *)address);
	if(array[0]>=array[1])
		strength="Weak";
	else
		strength="Strong";
	sprintf(address,"%s",strength);
	sem_post(sem3);
	return 0;
}
