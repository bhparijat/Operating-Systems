#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main(void){
	

	int pid = fork();

	if(pid==0)
		kill(getppid(),SIGSTOP);


	if(pid==0){

		printf("hello\n");


		kill(getppid(),SIGCONT);

		//exit(0);
	}else{

		
		printf("goodbye\n");
	}

	//printf("%d\n",pid);
	//kill(getpid(),SIGKILL);
	return 0;
}