#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include <fcntl.h>
#define writeEnd 1
#define readEnd 0
#include<string.h>
#include<math.h>
#include<sys/stat.h>

int main()
{
	
	float temp1,temp2,temp3,temp4,temp5;
	int pipe1_fd[2],pipe2_fd[2];
	if(pipe(pipe1_fd)==-1)
	{
		printf("Error creating a pipe\n");
		return 0;
	}
	else
	{
		pid_t pid_1;
		pid_1=fork();
		if(pid_1<0)
		{
			perror("fork");
			exit(1);
		}
		//printf("%d\n",pid_1);
		if(pid_1==0)
		{
			if(pipe(pipe2_fd)==-1)
			{
				printf("Error creating a pipe\n");
 		                return 0;
			}
			pid_t pid_2=fork();
			if(pid_2<0)
			{
				perror("fork");
				_exit(1);
			}
			else
			{
				float temperature[5];
				char cat[5];
				float avg,sd;
				if(pid_2==0)
				{
					char string[4];
					int i=0;
					close(pipe2_fd[writeEnd]);
					 while(i<7){
                                 		if(read(pipe2_fd[readEnd],string,4)>0){
						if(i<5)
                                         		temperature[i]=atof(string);
						else
						{
							if(i==5)
								avg=atof(string);
							else
								sd=atof(string);
						}
                                          	++i;
                                  	 	}
                         	 	}
					for(int i=0;i<5;++i){
						if(temperature[i]==avg)
							cat[i]='0';
						if(temperature[i]>avg+sd)
							cat[i]='1';
						if(temperature[i]<avg+sd && temperature[i]>avg)        
                                                     cat[i]='2';
						if(temperature[i]>avg-sd && temperature[i]<avg)
                                                        cat[i]='3';
						if(temperature[i]<avg-sd)
                                                        cat[i]='4';
					}
					int named_pipe1;
					named_pipe1= open("./fifo_file",O_WRONLY); 
					write(named_pipe1,cat,5); 
					_exit(0);
				}
				else
				{
					char tempo[50];
                          		float buf[5];
                         		char string[4];
                          		int i=0;
                          		float avg=0,sd,temp=0;
                         		close(pipe1_fd[writeEnd]);
					close(pipe2_fd[readEnd]);
                         		while(i<5){
                                 		if(read(pipe1_fd[readEnd],string,4)>0){
						write(pipe2_fd[writeEnd],string,4);
                                         	buf[i]=atof(string);
                                         	avg+=buf[i];
                                          	++i;
                                  		}
                          		}
                         		avg=avg/5;
                          		for(int i=0;i<5;++i){
                                  		temp+=pow(avg-buf[i],2);
                          		}
                          		temp/=5;
                          		sd=pow(temp,0.5);
					gcvt(avg,4,string);
					write(pipe2_fd[writeEnd],string,4);
					gcvt(sd,4,string);
                                      	write(pipe2_fd[writeEnd],string,4);
					_exit(0);
				}	
			}
		}else{
			 printf("Enter the five temperature values: \n");
			 float temp[5];
			 char string[4];
			 char cat[5];
			 int named_pipe;
			 float modified_temp[5];
			 close(pipe1_fd[readEnd]);
			 for(int i=0;i<5;++i)
			 {
				scanf("%f",&temp[i]);
				gcvt(temp[i],4,string);
			 	write(pipe1_fd[writeEnd],string,4);
			 }
			wait(NULL);
			printf("Modified temperatures are: \n");
			int i=0;		
			named_pipe = open("./fifo_file", O_RDONLY);
			while(read(named_pipe,cat,5)<0){
				int a=1;
			}
			while(i<5){
				if(cat[i]=='0'){
					modified_temp[i]=temp[i];
				}
				if(cat[i]=='1'){
					modified_temp[i]=temp[i]-3;
                                }
				if(cat[i]=='2'){
					modified_temp[i]=temp[i]-1.5;
                                }
				if(cat[i]=='3'){
					modified_temp[i]=temp[i]+2;
                                }
				if(cat[i]=='4'){
					modified_temp[i]=temp[i]+2.5;
                                }
				printf("%f\n",modified_temp[i]);
				++i;
			}
			exit(0);
		}
		return 0;
	}	
}
