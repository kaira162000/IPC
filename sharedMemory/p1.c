#include<stdio.h>
#include<string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<fcntl.h>

int main()
{
	sem_unlink("/tmp_sem1");
        sem_unlink("/tmp_sem3");
        sem_t *sem1 = sem_open("/tmp_sem1", O_CREAT, 0660, 0);
        sem_t *sem3 = sem_open("/tmp_sem3", O_CREAT, 0660, 0);
	if(sem1==SEM_FAILED||sem3==SEM_FAILED)
	{
		printf("failed to create a semaphore");
		exit(1);
	}
	char password[10];
	printf("%s","Enter a password: ");
	scanf("%s",password);
	key_t key;
	key=ftok("p1.c",65);
	while(key==-1){
		key=ftok("p1.c",65); 
		printf("%s","two");
	}
	int id=shmget(key,1024,0666|IPC_CREAT);
	if(id==-1)
	{
		printf("shmId not created\n");
		exit(1);		
	}
	void *address;
	address=(char*)shmat(id,NULL,0);
	if(address==(char *)-1)
	{
		perror("Memory not assigned");
		exit(1);
	}
	sprintf(address,"%s",password);
	sem_post(sem1);
	sem_wait(sem3);
	printf("%s\n",(char *)address);
	// Detach shared memory 
	shmdt(address); 
	// Destroy shared memory 
	shmctl(id,IPC_RMID,NULL); 
	//removing the semaphores
	sem_unlink("/tmp_sem1");
        sem_unlink("/tmp_sem2");
        sem_unlink("/tmp_sem3");
	return 0;
}
