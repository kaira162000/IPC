make:
	gcc -o NamedandUnnamedPipes.out NamedandUnnamedPipes.c -lm
	gcc -o ./sharedMemory/process1 ./sharedMemory/p1.c -lpthread -lrt
	gcc -o ./sharedMemory/process2 ./sharedMemory/p2.c -lpthread -lrt
	gcc -o ./sharedMemory/process3 ./sharedMemory/p3.c -lpthread -lrt
clean:
	rm NamedandUnnamedPipes.out
	rm ./sharedMemory/process1
	rm ./sharedMemory/process2
	rm ./sharedMemory/process3
		
