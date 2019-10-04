#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main(void){
	

	int pid1 = fork();

	if(pid1==0){
		char *v[] = {"ls","-l","-F","-h",NULL};
		//int status = execl( "ls", "ls -l -F -h",NULL);
		//int status = execlp( "ls", "ls -l -F -h",NULL);
		//int status = execv( "ls",v);
		int status = execvp( "ls",v);

	}else{

		int status;
		pid1 = wait(&status);
	}


	//printf("hello\n");
	return 0;
}

// execl and execv do not seem to produce any output
// execlp produces names of the files
// execvp gives more info of the directory