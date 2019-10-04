#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(void){
	

	int xx = 100;

	printf("printing at the beginning %d \n",xx);
	if(fork()==0){

		
		xx =  999;

		printf("Inside child process %d \n",xx);
	}else{
		
		xx = 777;
		printf("Inside parent process %d\n",xx);
	}
	printf("%d\n",xx);

	return 0;
}