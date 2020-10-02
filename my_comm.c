#include"allin_header.h"

int perform(char*cmd)
{
	int flg=-1;int what_is=-1;
	if((strcmp(cmd,"cd")==0) && cind<3){
		if(cind>1){cd(cinp[1]);}
		else
			chdir(shell_h);}
	else if((strcmp(cmd,"pwd")==0) && cind<2)
	{
		getcwd(pwdis,pm+2);printf("%s\n",pwdis);return 0;
	}
	else if(strcmp(cmd,"echo")==0)
	{		
		int i=1;
		while(i<cind){
			printf("%s ",cinp[i]);i++;}
		printf("\n");
		return 0;	
	}
	else if(strcmp(cmd,"exit")==0)
	{
		printf("\nLeaving...\n");
		exit(1); 
	}
	else if(strcmp(cmd,"ls")==0)
	{
		char *only="ha";int ind=0,i=1; 
		if(cind==1)what_is=ls(only,3);
		else if((strcmp(cinp[i],".")==0) ||(strcmp(cinp[i],"./")==0))what_is=ls(only,3);
		else if(strcmp(cinp[i],"-l")==0)
		{
			int nflg=-1,dflg=0;flg=1;char *mainlem=cinp[i];i=2;
			while(i<cind)
			{
				if((strcmp(cinp[i],"-a")==0) || (strcmp(cinp[i],"-al")==0) || (strcmp(cinp[i],"--all")==0) || (strcmp(cinp[i],"-all")==0) || (strcmp(cinp[i],"-la")==0)) nflg=2;
				else if((strcmp(cinp[i],"-l")==0)) flg=1;
				else
				{	if(direxists(cinp[i])!=1){flg=-1; break;}
					else			{dflg=5; lsdir[ind]=cinp[i];ind++;strcpy(mainlem,cinp[i]);}
				}
				i++;
			}
			if(nflg==2)flg=2;if(dflg==0)mainlem="."; 
			if((flg==1) || (flg==2))what_is=ls(mainlem,flg);
		}
		else if((strcmp(cinp[i],"-a")==0)||(strcmp(cinp[i],"--all")==0)){
			char* mainlem=cinp[i];int nflg=-1,dflg=0;flg=0;i=2;
			while(i<cind)
			{
				if((strcmp(cinp[i],"-l")==0) || (strcmp(cinp[i],"-la")==0)||(strcmp(cinp[i],"-al")==0)||(strcmp(cinp[i],"-all")==0))nflg=2;
				else if((strcmp(cinp[i],"-a")==0) || (strcmp(cinp[i],"--all")==0))flg=0;
				else
				{	if(direxists(cinp[i])!=1){flg=-1; break;}
					else			{dflg=5;lsdir[ind]=cinp[i];ind++; strcpy(mainlem,cinp[i]);}
				}i++;
			}
			if(nflg==2)flg=2;if(dflg==0)mainlem=".";
			if((flg==0) || (flg==2))what_is=ls(mainlem,flg);
		}
		else if((strcmp(cinp[i],"-al")==0)||(strcmp(cinp[i],"-all")==0) || (strcmp(cinp[i],"-la")==0))
		{
			char*mainlem=cinp[i];flg=2;int dflg=0;i=2;
			while(i<cind)
			{
				if((strcmp(cinp[i],"-l")==0) || (strcmp(cinp[i],"-la")==0)||(strcmp(cinp[i],"-al")==0)||(strcmp(cinp[i],"-all")==0) || (strcmp(cinp[i],"-a")==0) || (strcmp(cinp[i],"--all")==0))flg=2;
				else
				{	if(direxists(cinp[i])!=1){flg=-1; break;}
					else			{dflg=5;lsdir[ind]=cinp[i];ind++; strcpy(mainlem,cinp[i]);}
				}i++;
			}
			if(dflg==0)mainlem=".";
			if(flg==2)what_is=ls(mainlem,flg);
		}
		else if(direxists(cinp[i])==1)
		{
			lsdir[ind]=cinp[i];i++;int lflg=-1,aflg=-1;flg=3;
			while(i<cind)
			{
				if(strcmp(cinp[i],"-l")==0)lflg=0;
				else if((strcmp(cinp[i],"-a")==0)||(strcmp(cinp[i],"--all")==0))aflg=0;
				else if((strcmp(cinp[i],"-la")==0)||(strcmp(cinp[i],"-al")==0)||(strcmp(cinp[i],"-all")==0))flg=2;
				else
				{	if(direxists(cinp[i])!=1){flg=-1; break;}
					else			{lsdir[ind]=cinp[i];ind++;}
				}i++;
			}
			if(!aflg && !lflg)flg=2;
			else if(!lflg)flg=1;
			else if(!aflg)flg=0;
			if((flg==2)||(flg==1)||(flg==0)||(flg==3))what_is=ls(cinp[1],flg);
		}

		else
			what_is=ls(cinp[1],flg);
	}
	else if(strcmp(cmd,"pinfo")==0)
	{
		if(cind>1){
			if(cind>2){printf("Pinfo too many arguments\n");perror("pinf");return -1;}
			else
				return pinf((atoi(cinp[1])));
		}
		else {return pinf(0);}
	}
	return what_is;			
}
