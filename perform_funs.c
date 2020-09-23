#include "allin_header.h"

char * formatDate(char *str,time_t val)
{
    strftime(str,36,"%d.%m.%Y %H:%M:%S",localtime(&val));
    return str;
}
int direxists(char* dirname){
	struct stat buffer;
	if(stat(dirname,&buffer)==0)
	{if(!S_ISDIR(buffer.st_mode))return 0;
		else
			return 1;}
	else
		return 0;}
	int filexists(char *filename){
	struct stat buffer;
	int exist = stat(filename,&buffer);if(exist == 0){	
	if(!S_ISREG(buffer.st_mode)){
                return 0;}
        else
            return 1;}
    else 
        return 0;}

int cd(char * flag)
{
	//printf("Yes cd\n %s",flag);
	if((strcmp(flag,"~")==0) || (cind==1))
	{
		int check=chdir(shell_h);if(check<0){perror("home directory error");return -1;}
	}
	else
	{
		int check=chdir(cinp[1]);if(check<0){perror("Directory");return -1;}
	}
	return 0;
}
void permissions(char * pathis,char * nam)
{
	struct stat f; 
	stat(pathis,&f);
	if(filexists(nam)==1){printf("-");}
	else if(direxists(pathis)==1)printf("d");
	if((f.st_mode& S_IRUSR)&&(f.st_mode& S_IREAD))printf("r");
	else printf("-");
	if((f.st_mode& S_IWUSR)&&(f.st_mode& S_IWRITE))printf("w");
	else printf("-");
	if((f.st_mode& S_IXUSR)&&(f.st_mode& S_IEXEC))printf("x");
	else printf("-");
	if((f.st_mode& S_IRGRP)&&(f.st_mode& S_IREAD))printf("r");
	else printf("-");
	if((f.st_mode& S_IWGRP)&&(f.st_mode& S_IWRITE))printf("w");
	else printf("-");
	if((f.st_mode& S_IXGRP)&&(f.st_mode& S_IEXEC))printf("x");
	else printf("-");
	if((f.st_mode& S_IROTH)&&(f.st_mode& S_IREAD))printf("r");
	else printf("-");
	if((f.st_mode& S_IWOTH)&&(f.st_mode& S_IWRITE))printf("w");
	else printf("-");
	if((f.st_mode& S_IXOTH)&&(f.st_mode& S_IEXEC))printf("x\t");
	else printf("-\t");
	printf("%zu\t %s\t %s\t %zu\t",f.st_nlink,getpwuid(f.st_uid)->pw_name,getgrgid(f.st_gid)->gr_name,f.st_size);
    char dbuf[1024];formatDate(dbuf,f.st_mtime);printf("%s\t%s\n",dbuf,nam);
	return;
}
//all about ls command starts here
int large_dispaly(char * direc,int a)
{
    struct dirent **namesl; 
    if(strcmp(direc,"~")==0){
   strcpy(direc,shell_h);}
 	int r=scandir(direc,&namesl,NULL,alphasort);
 	if(r==-1){
 			perror("scandir");return -1;}int i=0;
 	while(i<r)
 	{
 		if((a==0)&&((strcmp(namesl[i]->d_name ,".")==0)||(strcmp(namesl[i]->d_name ,"..")==0)))
 				{free(namesl[i]);i++; continue;}
 		char *nam=(namesl[i]->d_name),*pathis=(namesl[i]->d_name);
 		if(strcmp(direc,".")!=0){
 			char * for_now=direc;
 			if(strcmp(direc,"~")==0){strcat(for_now,"/");strcat(for_now,pathis);permissions(for_now,nam);}
 			else 	{strcat(for_now,"/");strcat(for_now,pathis);permissions(for_now,nam);}}
 		
 		else permissions(pathis,nam);
 		free(namesl[i]);
 		i++;
 	} free(namesl);
 	return 0;
}
int printls(char * direc,int g)
{
    	struct dirent **namesl; 
 		int r=scandir(direc,&namesl,NULL,alphasort);
 		if(r==-1){
 			perror("scandir");return -1;}int i=0;
 		while(i<r)
 		{
 			int last=strlen(namesl[i]->d_name)-1;
 			if((g==0)&&((strcmp(namesl[i]->d_name ,".")==0)||(strcmp(namesl[i]->d_name ,"..")==0)))
 				{free(namesl[i]);i++;continue;}
 			printf("%s\n",namesl[i]->d_name);free(namesl[i]);i++;
 		}  free(namesl);
    return 0;
}
int ls(char * flag,int see)
{
	if(see==3)return printls(".",0);
	else if(strcmp(flag,"~")==0)return printls(shell_h,0);
	else if(strcmp(flag,"..")==0)return printls("..",0);
	else if(see==2)return large_dispaly(flag,1);
	else if((see==1))return large_dispaly(flag,0);
	else if(see==0){return printls(flag,1);}
	else
	{
		int ret=direxists(flag);
		if(ret==1)return printls(flag,0);
		else
			{perror("ls flag error: ");return -1;}
	}

	return 0;
}

//all about ls command ends here
int pinf(int pid)
{
	char *filep = (char *)malloc(1024);
	char id[10] = {"self"};
	if(pid>0)sprintf(id,"%d",pid);
	snprintf(filep,1024,"/proc/%s/stat",id);
	char *fxpath = (char *)malloc(1024);
	snprintf(fxpath,1024,"/proc/%s/exe",id);
	FILE* f = fopen(filep,"r");
	if(f==NULL)
	{
		puts("Check the pid");perror("File open Error: ");return -1;
	}
	char fileComm[128],fileState;int filePid;
	fscanf(f,"%d %s %c",&filePid,fileComm,&fileState);fclose(f);
	strcat(filep,"m"); // to check memory usage information
	FILE *finMem = fopen(filep,"r");
	if(!finMem)
	{
		puts("Check the pid");perror("File open Error: ");return -1;
	}
	char exePath[1024];
	int ip = readlink(fxpath,exePath,1024);
	if(ip<0){
		printf("%d",ip);puts("Check the pid");perror("From Readlink command: ");return 1;}
	long unsigned int vmsize;
	fscanf(finMem,"%lu",&vmsize);
	printf("pid -- %d\n",filePid);
	printf("Process Status -- %c memory \n",fileState);
	printf("memory -- %lu {Virtual memory}\n",vmsize);
	printf("Executable Path -- %s\n",exePath);
	fclose(finMem);
	free(filep);

	return 0;
}

