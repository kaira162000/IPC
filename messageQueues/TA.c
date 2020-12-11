#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 

struct Ta_marks {
    long mesg_type;
    float marks[5];
} ta_marks;

struct Grades {
    long mesg_type;
    float avg;
    char grade[5];
} grades;

int main() 
{ 
        float marks[5];
        grades.avg = 0;
	key_t key; 
	key = ftok("File1", 65); 

	int msgid; 
	msgid = msgget(key, 0666 | IPC_CREAT); 
	msgrcv(msgid, &ta_marks, sizeof(ta_marks), 10, 0); 
        for(int i=0; i<5; i++) {
            grades.avg += ta_marks.marks[i];
        }
        grades.avg /= 5;
        grades.mesg_type = 100;

        printf("The avg mark is %f\n", grades.avg);

        for(int i=1; i<=5; i++) {
            printf("Enter grade of Student %d: ", i); 
            scanf(" %c", &(grades.grade[i-1]));
        }

        msgsnd(msgid, &grades, sizeof(grades), 0); 
	return 0; 
} 

