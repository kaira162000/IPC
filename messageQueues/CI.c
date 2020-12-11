#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 

struct Student_mark { 
    long mesg_type; 
    float mark; 
} student_mark; 

struct Ta_marks {
    long mesg_type;
    float marks[5];
} ta_marks;

struct Grades {
    long mesg_type;
    float avg;
    char grade[5];
} grades;

struct Msg_read {
    long mesg_type;
} msg_read;

int main() 
{ 
    key_t key; 
    key = ftok("File1", 65); 

    int msgid; 
    msgid = msgget(key, 0666 | IPC_CREAT); 

    for(int i=1; i<=5; i++) {
        student_mark.mesg_type = i; 

        printf("Enter mark of Student %d: ", i); 
        scanf("%f", &(student_mark.mark));
        // Send marks to students
        msgsnd(msgid, &student_mark, sizeof(student_mark), 0); 

        ta_marks.marks[i-1] = student_mark.mark;
    }

    // Send marks to TA
    ta_marks.mesg_type = 10;
    msgsnd(msgid, &ta_marks, sizeof(ta_marks), 0); 

    // Recv grades from TA
    printf("Waiting for students to read marks and TA to send Grades\n");
    msgrcv(msgid, &grades, sizeof(grades), 100, 0); 
    printf("Recv Grade from TA\n");

    printf("Class Avg is %f\n", grades.avg);
    for(int i=1; i<=5; i++) {
        printf("Grade of student %d is %c\n", i, grades.grade[i-1]);
    }

    int count = 0;
    while(count < 5) {
        msgrcv(msgid, &msg_read, sizeof(msg_read), 999, 0); 

        count++;
        printf("%d Students read mark\n", count);
    }

    msgctl(msgid, IPC_RMID, NULL); 
    return 0; 
} 

