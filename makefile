make:
	gcc -o NamedandUnnamedPipes.out NamedandUnnamedPipes.c -lm
	gcc -o ./sharedMemory/process1.out ./sharedMemory/p1.c -lpthread -lrt
	gcc -o ./sharedMemory/process2.out ./sharedMemory/p2.c -lpthread -lrt
	gcc -o ./sharedMemory/process3.out ./sharedMemory/p3.c -lpthread -lrt
	gcc -o ./messageQueues/CI.out ./messageQueues/CI.c
	gcc -o ./messageQueues/TA.out ./messageQueues/TA.c
	gcc -o ./messageQueues/student.out ./messageQueues/student.c
clean:
	rm ./NamedandUnnamedPipes.out
	rm ./sharedMemory/process1.out
	rm ./sharedMemory/process2.out
	rm ./sharedMemory/process3.out
	rm ./messageQueues/CI.out
	rm ./messageQueues/TA.out
	rm ./messageQueues/student.out
		
