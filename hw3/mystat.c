#include "mystat.h"


int main(int argc,char **argv){


	//printf("%s\n", argv[1]);

	char buf[100];
	char file_type_buf[10000];
	struct stat file_type;
	int link = lstat(argv[1],&file_type);
	char buffersym[1000];
	char temp[1000];
	strcpy(temp,"Symbolic link -");
	ssize_t rds;
	//printf("%u\n", file_type_buf.st_uid);
	//printf("%07o\n",file_type_buf.st_mode);
	

	strcpy(file_type_buf," File type:                ");
	//strcpy(file_type_buf," I-node number:            ");
	printf("%s",file_type_buf );
	char c = 'z';
	switch(file_type.st_mode & S_IFMT){

		case S_IFBLK:
			c = 'b';
			strcpy(file_type_buf,"block");
			printf("%s",file_type_buf);
			break;
		case S_IFCHR:
			c = 'c';
			strcpy(file_type_buf,"character device\n");
			printf("%s",file_type_buf);
			break;
		case S_IFDIR:
			c = 'd';
			strcpy(file_type_buf,"directory\n");
			printf("%s",file_type_buf);
			break;

		case S_IFIFO:
			c = 'p';
			strcpy(file_type_buf,"FIFO/pipe\n");
			printf("%s",file_type_buf);
			break;
		case S_IFLNK:
			//printf("%d\n",link );
			
			c = 'l';
			readlink(argv[1],buffersym,1000);
			link = lstat(buffersym,&temp);


			//printf("%s\n",buffersym);

			if(strcmp(buffersym,"JUNK")==0){
				//temp = 
				//sprintf(temp,"%s","Symbolic link - with dangling destination\n");

				strcat(temp," with dangling destination");

			}else{
				//temp = "Symbolic link -> ";  
				//sprintf(temp,"Symbolic link -> %s\n",buffersym);
				strcat(temp,"> ");
				strcat(temp,buffersym);
			}
			
			//strcpy(file_type_buf,temp);
			printf("%s\n",temp);
			break;
		case S_IFREG:

			c = '-';
			strcpy(file_type_buf,"regular file\n");
			printf("%s",file_type_buf);
			break;
		case S_IFSOCK:
			c='s'; 
			strcpy(file_type_buf,"socket\n");
			printf("%s",file_type_buf);
			break;
		default:

			printf("This is a new file  type discovered me\n");
	}

	strcpy(file_type_buf," Device Id number:         ");
	printf("%s",file_type_buf);
	//printf("%d\n",file_type.st_dev);
	sprintf(file_type_buf,"%ld",file_type.st_dev);
	printf("%s\n",file_type_buf);

	

	strcpy(file_type_buf," I-node number:            ");
	printf("%s",file_type_buf);
	sprintf(file_type_buf,"%ld",file_type.st_ino);
	printf("%s\n",file_type_buf);



	strcpy(file_type_buf," Mode:                     ");
	printf("%s",file_type_buf);

// Citation mentioned in mystat.h	
	printf("%c",c);

	char pp = (file_type.st_mode & S_IRUSR) ? 'r' : '-';
	char q = (file_type.st_mode & S_IWUSR) ? 'w' : '-';
	char r = (file_type.st_mode & S_IXUSR) ? 'x' : '-';
	char s = (file_type.st_mode & S_IRGRP) ? 'r' : '-';
	char tt = (file_type.st_mode & S_IWGRP) ? 'w' : '-';
	char u = (file_type.st_mode & S_IXGRP) ? 'x' : '-';
	char v = (file_type.st_mode & S_IROTH) ? 'r' : '-';
	char w = (file_type.st_mode & S_IWOTH) ? 'w' : '-';
	char x = (file_type.st_mode & S_IXOTH) ? 'x' : '-';
    
    char permission[9] ={pp,q,r,s,tt,u,v,w,x}; 
    printf("%s",permission);

    //int x = file_type.st_mode;
    
	strcpy(file_type_buf,"          (");
	sprintf(temp,"%o",(file_type.st_mode%512));

	strcat(file_type_buf,temp);
	strcat(file_type_buf,") in octal");
	
	printf("%s\n",file_type_buf);





	strcpy(file_type_buf," Link count:               ");
	printf("%s",file_type_buf);
	sprintf(file_type_buf,"%d",file_type.st_nlink);
	printf("%s\n",file_type_buf);




	strcpy(file_type_buf," Owner Id:                 ");
	printf("%s",file_type_buf);
	sprintf(file_type_buf,"%d",file_type.st_uid);
	struct passwd *p = getpwuid(file_type.st_uid);
	printf("%s            (UID = %s)\n",p->pw_name,file_type_buf);


	strcpy(file_type_buf," Group Id:                 ");
	printf("%s",file_type_buf);
	sprintf(file_type_buf,"%d",file_type.st_gid);
	struct group *t = getgrgid(file_type.st_gid);
	printf("%s            (GID = %s)\n",t->gr_name,file_type_buf);



	strcpy(file_type_buf," Preferred I/O block size: ");
	printf("%s",file_type_buf);
	sprintf(file_type_buf,"%d",file_type.st_blksize);
	
	printf("%s bytes\n",file_type_buf);


	strcpy(file_type_buf," File size:                ");
	printf("%s",file_type_buf);
	sprintf(file_type_buf,"%d",file_type.st_size);
	printf("%s bytes\n",file_type_buf);


	strcpy(file_type_buf," Blocks allocated:         ");
	printf("%s",file_type_buf);
	sprintf(file_type_buf,"%d",file_type.st_blocks);
	printf("%s\n",file_type_buf);


	strcpy(file_type_buf," Last file access:         ");
	printf("%s",file_type_buf);
	char buf1[100];
	char *format = "%F %T %z (%Z) %a";
	strftime(buf1,80,format,localtime(&file_type.st_atime));
	printf("%s (local)\n",buf1);

	strcpy(file_type_buf," Last file modification:   ");
	printf("%s",file_type_buf);
	char buf2[100];
	size_t a = strftime(buf2,80,format,localtime(&file_type.st_mtime));
	//printf("%u\n",a );
	printf("%s (local)\n",buf2);

	strcpy(file_type_buf," Last status change:       ");
	printf("%s",file_type_buf);	
	char buf3[100];
	strftime(buf3,80,format,localtime(&file_type.st_ctime));
	printf("%s (local)\n",buf3);



	exit(0);
}