#include <unistd.h>

int isStaffInProject(char s[], char tn[]);
int isMeetingConflict_FCFS(struct Booking sbj,struct Booking bl[170],int index);
int isMeetingConflict_SJF(struct Booking sbj,struct Booking bl[170],int index);
int isMeetingInList(struct Booking sbj,struct Booking bl[170],int index);
int rBLSetEmpty();

int pms_FCFS(){
	rBLIndex_FCFS=0;
	int pid, id, i, n;
	int pipe_Staff[8][2];
	int pipe_BI[2];
	int pipe_Fin[2];//from child to parent

	struct Booking StaffBookingLists[170];
	int StaffBookingIndex = 0;

	char dateStart[11];
	char dateEnd[11];
	if(AEFlag==0){
		printf("Enter date period > ");//test input: 2022-04-24 2022-04-27
		scanf("%s", &dateStart);
		if(strcmp(dateStart,"0")==0)return 0;
		scanf("%s", &dateEnd);
	}else{
		stpcpy(dateStart,"2022-04-25");
		stpcpy(dateEnd,"2022-05-14");
	}
	
	
	printf(" *** Project Meeting ***\n");
	printf("\nAlgorithm used: FCFS\n");
	printf("Period: %s to %s\n",dateStart,dateEnd);
	
	
	FILE *fp = NULL;
	fp = fopen("output/G10_FCFS_Schd_01.dat", "w+");
	if(fp == NULL)
	{
		printf("File open error!\n");
		exit(1);
	}
	
	fprintf(fp, " *** Project Meeting ***\n");
	fprintf(fp, "\nAlgorithm used: FCFS\n");
	fprintf(fp,"Period: %s to %s\n",dateStart,dateEnd);
	fclose(fp);

	if (pipe(pipe_BI) < 0 || pipe(pipe_Fin) < 0) {
		printf("pipe creation error\n");
		exit(1);
	}
	for(id =0;id<8;id++){//init Children pipe
		if(pipe(pipe_Staff[id]) < 0){
			printf("Child pipe creation error\n");
			exit(1);
		}
	}
	for(id =0;id<8;id++){//fork child
		pid = fork();
		if(pid <= 0)break;
	}
	if (pid <0) {//fork error
		printf("Fork Failed\n");
		exit(1);
	}
	else if (pid == 0){//Child---------------------------------------------------------
		for(i =0;i<8;i++){//close other child's pipe
			close(pipe_Staff[i][1]);
			if(i==id) continue;
			close(pipe_Staff[i][0]);
		}
		close(pipe_BI[1]);
		close(pipe_Fin[0]);
		
		if ((n = read(pipe_Staff[id][0],StaffBookingLists,sizeof(StaffBookingLists))) > 0){
			read(pipe_BI[0],&StaffBookingIndex,sizeof(StaffBookingIndex));
			fp = fopen("output/G10_FCFS_Schd_01.dat", "a");
			if(fp == NULL){printf("File open error!\n");exit(1);}
			if(StaffBookingIndex>0){
				printf("\n%-15.10s %-8.7s %-8.7s %-15.10s %-15.10s\n======================================================================\n","Date","Start","End","Team","Project");
				fprintf(fp, "\n%-15.10s %-8.7s %-8.7s %-15.10s %-15.10s\n======================================================================\n","Date","Start","End","Team","Project");
				
				i=0;
				for(;i<StaffBookingIndex;i++){
					printf("%-15.10s %02d:00    %2d:00    %-15.10s Project_%c\n",StaffBookingLists[i].date,StaffBookingLists[i].hour,(StaffBookingLists[i].hour+StaffBookingLists[i].duration),StaffBookingLists[i].teamName,StaffBookingLists[i].teamName[5]);
					fprintf(fp, "%-15.10s %02d:00    %2d:00    %-15.10s Project_%c\n",
					StaffBookingLists[i].date,StaffBookingLists[i].hour,(StaffBookingLists[i].hour+StaffBookingLists[i].duration),StaffBookingLists[i].teamName,StaffBookingLists[i].teamName[5]);
				}
			}else{
				printf("\n%-15.10s %-8.7s %-8.7s %-15.10s %-15.10s\n======================================================================\n  no schedule\n","Date","Start","End","Team","Project");
				fprintf(fp, "\n%-15.10s %-8.7s %-8.7s %-15.10s %-15.10s\n======================================================================\n  no schedule\n","Date","Start","End","Team","Project");
			}
			printf("======================================================================\nStaff: %s\n\n\n",staffNames[id]);
			fprintf(fp, "======================================================================\nStaff: %s\n\n\n",staffNames[id]);
			fclose(fp);

		}else{
			printf("<Child%d> pid %d: failed to check pipe_Staff\n",id,getpid());
		}
		
		char cFin ='e';
		write(pipe_Fin[1],&cFin,sizeof(char));
		
		close(pipe_Fin[1]);
		close(pipe_BI[0]);
		close(pipe_Staff[id][0]);
		exit(0);
	}else {//parent---------------------------------------------------------
		close(pipe_BI[0]);
		close(pipe_Fin[1]);
		char cFin;
		for(id =0;id<8;id++){
			close(pipe_Staff[id][0]);
		}
		id=0;
		for(id =0;id<8;id++){
			StaffBookingIndex = 0;
			for(i=0;i<bookingIndex;i++){
				if(strcmp(bookingLists[i].date,dateStart)<0 || strcmp(bookingLists[i].date,dateEnd)>0)continue;

				if(isStaffInProject(staffNames[id],bookingLists[i].teamName)>=0){
					if(isMeetingConflict_FCFS(bookingLists[i],StaffBookingLists,StaffBookingIndex))continue;

					strcpy(StaffBookingLists[StaffBookingIndex].teamName, bookingLists[i].teamName);
					strcpy(StaffBookingLists[StaffBookingIndex].date, bookingLists[i].date);
					StaffBookingLists[StaffBookingIndex].hour = bookingLists[i].hour;
					StaffBookingLists[StaffBookingIndex].duration = bookingLists[i].duration;
					StaffBookingIndex++;
				}
			}

			write(pipe_Staff[id][1],StaffBookingLists,sizeof(StaffBookingLists));
			write(pipe_BI[1],&StaffBookingIndex,sizeof(StaffBookingIndex));
			
			read(pipe_Fin[0],&cFin,sizeof(char));
		}
		printf("\n=============END=============\n");
		
		
		Total_ReqRej_FCFS = rBLIndex_FCFS;
		Total_ReqAcc_FCFS = bookingIndex - rBLIndex_FCFS;
		printBookingLists(rBL_FCFS,rBLIndex_FCFS,"output/G10_FCFS_Schd_01.dat");
		
		close(pipe_Fin[0]);
		close(pipe_BI[1]);
		for(id =0;id<8;id++){
			close(pipe_Staff[id][1]);
		}

	}
	usleep(10);
	return 1;
}


int pms_SJF(){
	rBLIndex_SJF=0;
	int pid, id, i, n;
	int pipe_Staff[8][2];
	int pipe_BI[2];
	int pipe_Fin[2];//from child to parent

	struct Booking StaffBookingLists[170];
	int StaffBookingIndex = 0;

	char dateStart[11];
	char dateEnd[11];
	
	if(AEFlag==0){
		printf("Enter date period > ");//test input: 2022-04-24 2022-04-27
		scanf("%s", &dateStart);
		if(strcmp(dateStart,"0")==0)return 0;
		scanf("%s", &dateEnd);
	}else{
		stpcpy(dateStart,"2022-04-25");
		stpcpy(dateEnd,"2022-05-14");
	}

	printf(" *** Project Meeting ***\n");
	printf("\nAlgorithm used: SJF\n");
	printf("Period: %s to %s\n",dateStart,dateEnd);
	
	
	FILE *fp = NULL;
	fp = fopen("output/G10_SJF_Schd_01.dat", "w+");
	if(fp == NULL)
	{
		printf("File open error!\n");
		exit(1);
	}
	
	fprintf(fp, " *** Project Meeting ***\n");
	fprintf(fp, "\nAlgorithm used: SJF\n");
	fprintf(fp,"Period: %s to %s\n",dateStart,dateEnd);
	fclose(fp);

	if (pipe(pipe_BI) < 0 || pipe(pipe_Fin) < 0) {
		printf("pipe creation error\n");
		exit(1);
	}
	for(id =0;id<8;id++){//init Children pipe
		if(pipe(pipe_Staff[id]) < 0){
			printf("Child pipe creation error\n");
			exit(1);
		}
	}
	for(id =0;id<8;id++){//fork child
		pid = fork();
		if(pid <= 0)break;
	}
	if (pid <0) {//fork error
		printf("Fork Failed\n");
		exit(1);
	}
	else if (pid == 0){//Child---------------------------------------------------------
		for(i =0;i<8;i++){//close other child's pipe
			close(pipe_Staff[i][1]);
			if(i==id) continue;
			close(pipe_Staff[i][0]);
		}
		close(pipe_BI[1]);
		close(pipe_Fin[0]);
		
		if ((n = read(pipe_Staff[id][0],StaffBookingLists,sizeof(StaffBookingLists))) > 0){
			read(pipe_BI[0],&StaffBookingIndex,sizeof(StaffBookingIndex));
			fp = fopen("output/G10_SJF_Schd_01.dat", "a");
			if(fp == NULL){printf("File open error!\n");exit(1);}
			if(StaffBookingIndex>0){
				printf("\n%-15.10s %-8.7s %-8.7s %-15.10s %-15.10s\n======================================================================\n","Date","Start","End","Team","Project");
				fprintf(fp, "\n%-15.10s %-8.7s %-8.7s %-15.10s %-15.10s\n======================================================================\n","Date","Start","End","Team","Project");
				
				i=0;
				for(;i<StaffBookingIndex;i++){
					printf("%-15.10s %02d:00    %2d:00    %-15.10s Project_%c\n",StaffBookingLists[i].date,StaffBookingLists[i].hour,(StaffBookingLists[i].hour+StaffBookingLists[i].duration),StaffBookingLists[i].teamName,StaffBookingLists[i].teamName[5]);
					fprintf(fp, "%-15.10s %02d:00    %2d:00    %-15.10s Project_%c\n",
					StaffBookingLists[i].date,StaffBookingLists[i].hour,(StaffBookingLists[i].hour+StaffBookingLists[i].duration),StaffBookingLists[i].teamName,StaffBookingLists[i].teamName[5]);
				}
			}else{
				printf("\n%-15.10s %-8.7s %-8.7s %-15.10s %-15.10s\n======================================================================\n  no schedule\n","Date","Start","End","Team","Project");
				fprintf(fp, "\n%-15.10s %-8.7s %-8.7s %-15.10s %-15.10s\n======================================================================\n  no schedule\n","Date","Start","End","Team","Project");
			}
			printf("======================================================================\nStaff: %s\n\n\n",staffNames[id]);
			fprintf(fp, "======================================================================\nStaff: %s\n\n\n",staffNames[id]);
			fclose(fp);

		}else{
			printf("<Child%d> pid %d: failed to check pipe_Staff\n",id,getpid());
		}
		
		char cFin ='e';
		write(pipe_Fin[1],&cFin,sizeof(char));
		
		close(pipe_Fin[1]);
		close(pipe_BI[0]);
		close(pipe_Staff[id][0]);
		exit(0);
	}else {//parent---------------------------------------------------------
		close(pipe_BI[0]);
		close(pipe_Fin[1]);
		char cFin;
		for(id =0;id<8;id++){
			close(pipe_Staff[id][0]);
		}
		id=0;
		for(id =0;id<8;id++){
			StaffBookingIndex = 0;
			for(i=0;i<bookingIndex;i++){
				if(strcmp(bookingLists[i].date,dateStart)<0 || strcmp(bookingLists[i].date,dateEnd)>0)continue;

				if(isStaffInProject(staffNames[id],bookingLists[i].teamName)>=0){
					int conIndex = -1;//the index of Meeting if Conflict
					conIndex = isMeetingConflict_SJF(bookingLists[i],StaffBookingLists,StaffBookingIndex);
					if(conIndex==-1){
						strcpy(StaffBookingLists[StaffBookingIndex].teamName, bookingLists[i].teamName);
						strcpy(StaffBookingLists[StaffBookingIndex].date, bookingLists[i].date);
						StaffBookingLists[StaffBookingIndex].hour = bookingLists[i].hour;
						StaffBookingLists[StaffBookingIndex].duration = bookingLists[i].duration;
						StaffBookingIndex++;
					}else{
						if(conIndex==-2)continue;
						strcpy(StaffBookingLists[conIndex].teamName, bookingLists[i].teamName);
						strcpy(StaffBookingLists[conIndex].date, bookingLists[i].date);
						StaffBookingLists[conIndex].hour = bookingLists[i].hour;
						StaffBookingLists[conIndex].duration = bookingLists[i].duration;
					}

					
				}
			}

			write(pipe_Staff[id][1],StaffBookingLists,sizeof(StaffBookingLists));
			write(pipe_BI[1],&StaffBookingIndex,sizeof(StaffBookingIndex));
			
			read(pipe_Fin[0],&cFin,sizeof(char));
		}


		printf("\n=============END=============\n");
		
		Total_ReqRej_SJF = rBLIndex_SJF;
		Total_ReqAcc_SJF = bookingIndex - rBLIndex_SJF;
		printBookingLists(rBL_SJF,rBLIndex_SJF,"output/G10_SJF_Schd_01.dat");
		
		close(pipe_Fin[0]);
		close(pipe_BI[1]);
		for(id =0;id<8;id++){
			close(pipe_Staff[id][1]);
		}

	}
	usleep(10);
	return 1;
}










int isStaffInProject(char s[], char tn[]){
	int i,j;
	for(i=0;i<26;i++){
		if(strcmp(teamLists[i].name,tn)==0){
			for(j=0;j<4;j++){
				if(strcmp(teamLists[i].members[j],s)==0)
				return j;
			}
			break;
		}
	}
	return -1;
}

int isMeetingInList(struct Booking sbj,struct Booking bl[170],int index){
	int i;
	for(i=0;i<index;i++){
		if(strcmp(bl[i].teamName,sbj.teamName)==0 &&
			strcmp(bl[i].date,sbj.date)==0 &&
			bl[i].hour == sbj.hour &&
			bl[i].duration == sbj.duration){
			return i;
		}
	}
	return -1;
}


int isMeetingConflict_FCFS(struct Booking sbj,struct Booking bl[170],int index){
	int i;
	for(i=0;i<index;i++){
		if(strcmp(bl[i].date,sbj.date)<0 || strcmp(bl[i].date,sbj.date)>0)continue;
		if((sbj.hour>=bl[i].hour && sbj.hour<(bl[i].hour+bl[i].duration)) || (sbj.hour<=bl[i].hour && (sbj.hour+sbj.duration)>bl[i].hour)){
			printf("booking reject:%s %02d:00-%2d:00 %s Project_%c\n",sbj.date,sbj.hour,(sbj.hour+sbj.duration),sbj.teamName,sbj.teamName[5]);
			if(isMeetingInList(sbj,rBL_FCFS,rBLIndex_FCFS)>=0) return i;
			FILE *fp = NULL;
			fp = fopen("output/G10_FCFS_Schd_01.dat", "a");
			fprintf(fp, "booking reject:%s %02d:00-%2d:00 %s Project_%c\n",sbj.date,sbj.hour,(sbj.hour+sbj.duration),sbj.teamName,sbj.teamName[5]);
			fclose(fp);
			
			strcpy(rBL_FCFS[rBLIndex_FCFS].teamName, sbj.teamName);
			strcpy(rBL_FCFS[rBLIndex_FCFS].date, sbj.date);
			rBL_FCFS[rBLIndex_FCFS].hour = sbj.hour;
			rBL_FCFS[rBLIndex_FCFS].duration = sbj.duration;
			rBLIndex_FCFS++;
			return 1;
		}
	}
	return 0;
}

int isMeetingConflict_SJF(struct Booking sbj,struct Booking bl[170],int index){
	int i;
	for(i=0;i<index;i++){
		if(strcmp(bl[i].date,sbj.date)<0 || strcmp(bl[i].date,sbj.date)>0)continue;
		if((sbj.hour>=bl[i].hour && sbj.hour<(bl[i].hour+bl[i].duration)) || (sbj.hour<=bl[i].hour && (sbj.hour+sbj.duration)>bl[i].hour)){
			struct Booking temp;
			if (bl[i].duration>sbj.duration){
				stpcpy(temp.teamName,bl[i].teamName); stpcpy(temp.date,bl[i].date);
				temp.hour = bl[i].hour; temp.duration = bl[i].duration;
			}else{
				printf("%s ---%s\n",bl[i].teamName,sbj.teamName);
				stpcpy(temp.teamName,sbj.teamName); stpcpy(temp.date,sbj.date);
				temp.hour = sbj.hour; temp.duration = sbj.duration;
				i=-2;
			}
			printf("booking reject:%s %02d:00-%2d:00 %s Project_%c\n",temp.date,temp.hour,(temp.hour+temp.duration),temp.teamName,temp.teamName[5]);
			if(isMeetingInList(temp,rBL_SJF,rBLIndex_SJF)>=0) return i;
			FILE *fp = NULL;
			fp = fopen("output/G10_SJF_Schd_01.dat", "a");
			fprintf(fp, "booking reject:%s %02d:00-%2d:00 %s Project_%c\n",temp.date,temp.hour,(temp.hour+temp.duration),temp.teamName,temp.teamName[5]);
			fclose(fp);
			
			strcpy(rBL_SJF[rBLIndex_SJF].teamName, temp.teamName);
			strcpy(rBL_SJF[rBLIndex_SJF].date, temp.date);
			rBL_SJF[rBLIndex_SJF].hour = temp.hour;
			rBL_SJF[rBLIndex_SJF].duration = temp.duration;
			rBLIndex_SJF++;
			return i;
		}
	}
	return -1;
}

int printBookingLists(struct Booking bl[170],int index,char fileName[]){
	FILE *fp = NULL;
	fp = fopen(fileName, "a");
	
	printf("*** Meeting Request - REHECTED ***\n\nThere are %d requests rejected for the required period. \n\n======================================================================\n",index);
	
	fprintf(fp, "*** Meeting Request - REHECTED ***\n\nThere are %d requests rejected for the required period. \n\n======================================================================\n",index);
	int i;
	for(i=0;i<index;i++){
		printf("%d.   %s %s %02d:00 %d\n",i,bl[i].teamName,bl[i].date,bl[i].hour,bl[i].duration);
		fprintf(fp, "%d.   %s %s %02d:00 %d\n",i,bl[i].teamName,bl[i].date,bl[i].hour,bl[i].duration);
	}
	printf("\n======================================================================\n");
	fprintf(fp, "\n======================================================================\n");
	fclose(fp);
	return 1;
}

int getAddStaffRrAr(int value, char name[],int type){
	int i=0;
	for(i=0;i<8;i++){
		if(!strcmp(staffNames[i],name)){
			if(type==0){
				staffRr[i] = staffRr[i]+value;
				return staffRr[i];
			}else if(type==1){
				staffAr_FCFS[i] = staffAr_FCFS[i]+value;
				return staffAr_FCFS[i];
			}else{
				staffAr_SJF[i] = staffAr_SJF[i]+value;
				return staffAr_SJF[i];
			}
		}
	}
	return-1;
}


void getTeamAccRecinfo(){
	int i,j,k;
	for(i=0;i<bookingIndex;i++){
		for(j=0;j<teamsIndex;j++){
			if(!strcmp(bookingLists[i].teamName,teamLists[j].name)){
				teamLists[j].ReqRec++;
				for(k=0;k<4;k++){
					getAddStaffRrAr(1,teamLists[j].members[k],0);
				}
			}
		}
	}
	
	for(i=0;i<rBLIndex_FCFS;i++){
		for(j=0;j<teamsIndex;j++){
			if(!strcmp(rBL_FCFS[i].teamName,teamLists[j].name)){
				teamLists[j].ReqAcc_FCFS++;
				for(k=0;k<4;k++){
					getAddStaffRrAr(1,teamLists[j].members[k],1);
				}
			}
		}
	}
	for(i=0;i<rBLIndex_SJF;i++){
		for(j=0;j<teamsIndex;j++){
			if(!strcmp(rBL_SJF[i].teamName,teamLists[j].name)){
				teamLists[j].ReqAcc_SJF++;
				for(k=0;k<4;k++){
					getAddStaffRrAr(1,teamLists[j].members[k],2);
				}
			}
		}
	}
	for(i=0;i<8;i++){
		staffAr_FCFS[i] = staffRr[i] - staffAr_FCFS[i];
		staffAr_SJF[i] = staffRr[i] - staffAr_SJF[i];
	}
	for(i=0;i<teamsIndex;i++){
		teamLists[i].ReqAcc_FCFS = teamLists[i].ReqRec - teamLists[i].ReqAcc_FCFS;
		teamLists[i].ReqAcc_SJF = teamLists[i].ReqRec - teamLists[i].ReqAcc_SJF;
	}
	
}


int summary(){
	
	
	getTeamAccRecinfo();
	
	printf("Performance:--FCFS\n");
	printf("Total Number of Request Received: %d\n",bookingIndex);
	printf("      Number of Request Accepted: %d (%.1f%)\n",Total_ReqAcc_FCFS, (double)Total_ReqAcc_FCFS/bookingIndex*100);
	printf("      Number of Request Rejected: %d (%.1f%)\n\n",Total_ReqRej_FCFS, (double)Total_ReqRej_FCFS/bookingIndex*100);
	
	printf("Utilization of Time slot:\n");
	printf("      Accepted Request:    -%.1f%\n", (double)Total_ReqAcc_FCFS/bookingIndex*100);
	
	int i;
	for(i=0;i<teamsIndex;i++){
		printf("      %-20.10s -%.1f%\n",teamLists[i].name,(double)teamLists[i].ReqAcc_FCFS/teamLists[i].ReqRec*100);
	}
	printf("\n");
	for(i=0;i<8;i++){
		printf("      %-20.10s -%.1f%\n",staffNames[i],(double)staffAr_FCFS[i]/staffRr[i]*100);
	}
	
	
	printf("\n\nPerformance:--SJF\n");
	printf("Total Number of Request Received: %d\n",bookingIndex);
	printf("      Number of Request Accepted: %d (%.1f%)\n",Total_ReqAcc_SJF, (double)Total_ReqAcc_SJF/bookingIndex*100);
	printf("      Number of Request Rejected: %d (%.1f%)\n\n",Total_ReqRej_SJF, (double)Total_ReqRej_SJF/bookingIndex*100);
	
	printf("Utilization of Time slot:\n");
	printf("      Accepted Request:    -%.1f%\n", (double)Total_ReqAcc_SJF/bookingIndex*100);
	
	for(i=0;i<teamsIndex;i++){
		printf("      %-20.10s -%.1f%\n",teamLists[i].name,(double)teamLists[i].ReqAcc_SJF/teamLists[i].ReqRec*100);
	}
	printf("\n");
	for(i=0;i<8;i++){
		printf("      %-20.10s -%.1f%\n",staffNames[i],(double)staffAr_SJF[i]/staffRr[i]*100);
	}
	
	printf("\nAttendance:\n");
	for(i=0;i<8;i++){
		printf("      %-20.10s -%.1f%\n",staffNames[i],staffAtten[i]);
	}
	
	
	printf("\n");
	printf("\n");
}


