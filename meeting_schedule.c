#include <unistd.h>

int isStaffInProject(char s[], char tn[]);
int isMeetingConflict_FCFS(struct Booking sbj,struct Booking bl[170],int index);
int isMeetingConflict_SJF(struct Booking sbj,struct Booking bl[170],int index);

void pms_FCFS(){
	int pid, id, i, n;
	int pipe_Staff[8][2];
	int pipe_BI[2];
	int pipe_Fin[2];//from child to parent

	struct Booking StaffBookingLists[170];
	int StaffBookingIndex = 0;

	char dateStart[11];
	char dateEnd[11];
	printf("Enter date period > ");//test input: 2022-04-24 2022-04-27
	scanf("%s", &dateStart);
	scanf("%s", &dateEnd);

	printf(" *** Project Meeting ***\n");
	printf("\nAlgorithm used: FCFS\n");
	printf("Period: %s to %s\n",dateStart,dateEnd);
	
	
	FILE *fp = NULL;
	fp = fopen("output/GXX_FCFS_Schd_01.dat", "w+");
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
			fp = fopen("output/GXX_FCFS_Schd_01.dat", "a");
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

				if(isStaffInProject(staffNames[id],bookingLists[i].teamName)==1){
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
		close(pipe_Fin[0]);
		close(pipe_BI[1]);
		for(id =0;id<8;id++){
			close(pipe_Staff[id][1]);
		}

	}
	usleep(10);
	// displayMenu();
	// chooseMenuOption();
}


void pms_SJF(){
	int pid, id, i, n;
	int pipe_Staff[8][2];
	int pipe_BI[2];
	int pipe_Fin[2];//from child to parent

	struct Booking StaffBookingLists[170];
	int StaffBookingIndex = 0;

	char dateStart[11];
	char dateEnd[11];
	printf("Enter date period > ");//test input: 2022-04-24 2022-04-27
	scanf("%s", &dateStart);
	scanf("%s", &dateEnd);

	printf(" *** Project Meeting ***\n");
	printf("\nAlgorithm used: FCFS\n");
	printf("Period: %s to %s\n",dateStart,dateEnd);
	
	
	FILE *fp = NULL;
	fp = fopen("output/GXX_FCFS_Schd_01.dat", "w+");
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
			fp = fopen("output/GXX_FCFS_Schd_01.dat", "a");
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

				if(isStaffInProject(staffNames[id],bookingLists[i].teamName)==1){
					int conIndex = -1;//the index of Meeting if Conflict
					conIndex = isMeetingConflict_SJF(bookingLists[i],StaffBookingLists,StaffBookingIndex);
					printf("index: %d\n",conIndex);
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
		close(pipe_Fin[0]);
		close(pipe_BI[1]);
		for(id =0;id<8;id++){
			close(pipe_Staff[id][1]);
		}

	}
	usleep(10);
	// displayMenu();
	// chooseMenuOption();
}










int isStaffInProject(char s[], char tn[]){
	int i,j;
	for(i=0;i<26;i++){
		if(strcmp(teamLists[i].name,tn)==0){
			for(j=0;j<4;j++){
				if(strcmp(teamLists[i].members[j],s)==0)
				return 1;
			}
			break;
		}
	}
	return 0;
}

int isMeetingConflict_FCFS(struct Booking sbj,struct Booking bl[170],int index){
	int i;
	for(i=0;i<index;i++){
		if(strcmp(bl[i].date,sbj.date)<0 || strcmp(bl[i].date,sbj.date)>0)continue;
		if((sbj.hour>=bl[i].hour && sbj.hour<(bl[i].hour+bl[i].duration)) || (sbj.hour<=bl[i].hour && (sbj.hour+sbj.duration)>bl[i].hour)){
			printf("booking reject:%s %02d:00-%2d:00 %s Project_%c\n",sbj.date,sbj.hour,(sbj.hour+sbj.duration),sbj.teamName,sbj.teamName[5]);
			FILE *fp = NULL;
			fp = fopen("output/GXX_FCFS_Schd_01.dat", "a");
			fprintf(fp, "booking reject:%s %02d:00-%2d:00 %s Project_%c\n",sbj.date,sbj.hour,(sbj.hour+sbj.duration),sbj.teamName,sbj.teamName[5]);
			fclose(fp);
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
			char temp_teamName[7];
			char temp_date[11];
			int temp_hour;
			int temp_duration;
			if (bl[i].duration>sbj.duration){
				stpcpy(temp_teamName,bl[i].teamName); stpcpy(temp_date,bl[i].date);
				temp_hour = bl[i].hour; temp_duration = bl[i].duration;
			}else{
				printf("%s ---%s\n",bl[i].teamName,sbj.teamName);
				stpcpy(temp_teamName,sbj.teamName); stpcpy(temp_date,sbj.date);
				temp_hour = sbj.hour; temp_duration = sbj.duration;
				i=-2;
			}
			printf("booking reject:%s %02d:00-%2d:00 %s Project_%c\n",temp_date,temp_hour,(temp_hour+temp_duration),temp_teamName,temp_teamName[5]);
			FILE *fp = NULL;
			fp = fopen("output/GXX_FCFS_Schd_01.dat", "a");
			fprintf(fp, "booking reject:%s %02d:00-%2d:00 %s Project_%c\n",temp_date,temp_hour,(temp_hour+temp_duration),temp_teamName,temp_teamName[5]);
			fclose(fp);
			return i;
		}
	}
	return -1;
}
