/***
test input: Can copy all in once

Team_B 2022-04-26 10:00 3 Fanny Helen 0
Team_B 2022-04-26 14:00 3 Fanny Alan 0
Team_D 2022-04-26 14:00 2 Billy Cathy 0
Team_D 2022-04-27 14:00 2 David Cathy Eva 0

***/
int TeamMeetingHeld(char tn[]);
int getTeamMemberName(int id,char tn[]);
void PrintAttendanceRecord();

void MeetingAttendance(){
	char teamName[7];
	char date[11];
	char hour[6];
	char duration[2];
	struct Booking object;
	initMeetingRecord();
	printf(" ~~ Meeting Attendance ~~\n");
	while(1){
		printf("Enter Meeting Info (Team_? YYYY-MM-DD HH:MM N)> ");
		scanf("%s", &teamName);
		if(!strcmp(teamName,"0")) break;
		scanf("%s", &date);
		scanf("%s", &hour);
		scanf("%s", &duration);
		strcpy(object.teamName,teamName); strcpy(object.date,date);
		char temp[3];
		sprintf(temp, "%c%c", hour[0], hour[1]);
		object.hour = atoi(temp);
		object.duration = atoi(duration);
		printf(" ~ %s  %s  %d  %d ~ \n",object.teamName,object.date,object.hour,object.duration);
		int n;
		if((n = isMeetingInList(object,bookingLists,bookingIndex))<0){
			printf("Incorrect bookingInfo entered, please try again.\n");
			continue;
		}
		bookingLists[n].isAttended[0] = 1;
		//printf("n = %d\n",n);
		int i = 0;
		while(1){
			if(i>3)break;
			while(1){
				char tempName[20];
				printf("Enter attended member's name (enter 0 to end) > ");
				scanf("%s", &tempName);
				if(!strcmp(tempName,"0")) {i=4;break;}
				int m;
				if((m = isStaffInProject(tempName,bookingLists[n].teamName))<0){
					printf("Incorrect name entered, please try again.\n");
					continue;
				}
				//printf("m = %d\n",m);
				bookingLists[n].isAttended[m+1] = 1;
				break;
			}
			i++;
		}
	}
	chooseMenuOption();
}
char NameReturn[20];
void PrintAttendanceRecord(){
	FILE *fp = NULL;
	fp = fopen("output/G10_MeetingAttendanceRecord.dat", "w+");
	if(fp == NULL){printf("File open error!\n");exit(1);}
	fprintf(fp, " ~~~ Meeting Attendance Record ~~~\n");
	printf("\n%-15.10s %-8.7s %-8.7s %-15.10s %-15.10s\n======================================================================","Date","Start","End","Team","Project");
	fprintf(fp, "\n%-15.10s %-8.7s %-8.7s %-15.10s %-15.10s\n======================================================================","Date","Start","End","Team","Project");
	

	int i,j;
	for(i=0;i<bookingIndex;i++){
		if(bookingLists[i].isAttended[0]==1){
			int teamID = TeamMeetingHeld(bookingLists[i].teamName);
			printf("%-15.10s %02d:00    %2d:00    %-15.10s Project_%c\n",bookingLists[i].date,bookingLists[i].hour,(bookingLists[i].hour+bookingLists[i].duration),bookingLists[i].teamName,bookingLists[i].teamName[5]);
			fprintf(fp, "%-15.10s %02d:00    %2d:00    %-15.10s Project_%c\n",bookingLists[i].date,bookingLists[i].hour,(bookingLists[i].hour+bookingLists[i].duration),bookingLists[i].teamName,bookingLists[i].teamName[5]);
			for(j=0;j<4;j++){
				getTeamMemberName(j,bookingLists[i].teamName);
				if(!strcmp(NameReturn,"0"))break;
				char memNameTmp[25];
				strcpy(memNameTmp,"------");
				strcat(memNameTmp,NameReturn);
				
				if(bookingLists[i].isAttended[j+1] == 1){
					teamLists[teamID].meetingRecord[j+1]++;//employees attended the meeting
					strcat(memNameTmp," O\n");
				}else{
					strcat(memNameTmp," X\n");
				}
				printf(memNameTmp);
				fprintf(fp,memNameTmp);
			}
		}
		printf("\n");
		fprintf(fp, "\n");
	}
	printf("======================================================================\n");
	fprintf(fp, "======================================================================\n");
	for(i=0;i<teamsIndex;i++){
		if(teamLists[i].meetingRecord[0]>0){
			printf("%s : [%d] meeting held\n",teamLists[i].name,teamLists[i].meetingRecord[0]);
			fprintf(fp, "%s : [%d] meeting held\n",teamLists[i].name,teamLists[i].meetingRecord[0]);
			for(j=0;j<4;j++){
				getTeamMemberName(j,teamLists[i].name);
				if(!strcmp(NameReturn,"0"))break;
				char memNameTmp[25];
				sprintf(memNameTmp,"------ %-10.5s : meeting attended:%.1f%\n",NameReturn,(double)teamLists[i].meetingRecord[j+1]/teamLists[i].meetingRecord[0]*100);
				saveStaffAtten(teamLists[i].members[j],(double)teamLists[i].meetingRecord[j+1]/teamLists[i].meetingRecord[0]*100);
				printf(memNameTmp);
				fprintf(fp, memNameTmp);
			}
		}
		printf("\n");
		fprintf(fp, "\n");
	}
	
	fclose(fp);
	printf("======================================================================\n");
}

int saveStaffAtten(char name[], double value){
	int i;
	for(i=0;i<8;i++){
		if(!strcmp(staffNames[i],name)){
			staffAtten[i] = value;
		}
	}
	return 1;
}


int getTeamMemberName(int id,char tn[]){
	char temp[] = "0";
	int i;
	for(i=0;i<teamsIndex;i++){
		if(strcmp(teamLists[i].name,tn)==0){
			stpcpy(NameReturn,teamLists[i].members[id]);
			int temp = NameReturn[0];
			//printf("[%c-%d]",NameReturn[0],temp);
			if(temp==0)break;
			return 1;
		}
	}
	strcpy(NameReturn,"0");
	return 0;
}

int TeamMeetingHeld(char tn[]){
	int i;
	for(i=0;i<teamsIndex;i++){
		if(strcmp(teamLists[i].name,tn)==0){
			teamLists[i].meetingRecord[0]++;
			return i;
		}
	}
	return -1;
}

int initMeetingRecord(){
	int i,j;
	for(i=0;i<teamsIndex;i++){
		for(j=0;j<5;j++){
			teamLists[i].meetingRecord[j]=0;
		}
	}
	return 1;
}
