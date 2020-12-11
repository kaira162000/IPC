#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 

struct Student_mark { 
    long mesg_type; 
    float mark; 
} student_mark; 

struct Msg_read {
    long mesg_type;
} msg_read;

int main() 
{ 
	key_t key; 
	key = ftok("File1", 65); 
	int msgid, student_id; 
	msgid = msgget(key, 0666 | IPC_CREAT); 
        printf("Enter your ID: ");
        scanf("%d", &student_id);
	msgrcv(msgid, &student_mark, sizeof(student_mark), student_id, 0); 
	printf("Your mark : %f \n", student_mark.mark); 
	return 0; 
} 

