#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main(void){
	

	FILE *fp;
	char strnum[5];
	int ppid,pid,i;
	fp = fopen("Junk.txt","w");

	ppid = getppid();

	//printf("%d\n",ppid);
	
	fputs("before fork\n",fp);

	pid = fork();

	for(i = 0;i<10;i++){

		
		if(pid==0)
			fputs("child\n",fp);
		else
			fputs("parent\n",fp);
	}


	return 0;
}

//The parent process prints first followed by the child process. Also, "before fork is printed twice".

