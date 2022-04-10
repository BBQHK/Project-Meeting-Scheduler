//test input: 
//Team_B 2022-04-26 10:00 3
//Fanny Helen 0 <-input separately
//Team_D 2022-04-26 14:00 2
//David Cathy 0 <-input separately
void MeetingAttendance(){
	char teamName[7];
	char date[11];
	char hour[6];
	char duration[2];
	struct Booking object;
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
	

	int i;
	for(i=0;i<bookingIndex;i++){
		
		if(bookingLists[i].isAttended[0]==1){
			printf("%-15.10s %02d:00    %2d:00    %-15.10s Project_%c\n",bookingLists[i].date,bookingLists[i].hour,(bookingLists[i].hour+bookingLists[i].duration),bookingLists[i].teamName,bookingLists[i].teamName[5]);
			fprintf(fp, "%-15.10s %02d:00    %2d:00    %-15.10s Project_%c\n",bookingLists[i].date,bookingLists[i].hour,(bookingLists[i].hour+bookingLists[i].duration),bookingLists[i].teamName,bookingLists[i].teamName[5]);
			int j;
			for(j=0;j<4;j++){
				getTeamMemberName(j,bookingLists[i].teamName);
				if(!strcmp(NameReturn,"0"))break;
				char memNameTmp[25];
				strcpy(memNameTmp,"------");
				strcat(memNameTmp,NameReturn);
				
				if(bookingLists[i].isAttended[j+1] == 1){
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
	fclose(fp);
}

int getTeamMemberName(int id,char tn[]){
	char temp[] = "00";
	int i;
	for(i=0;i<26;i++){
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
