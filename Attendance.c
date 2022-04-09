void MeetingAttendance(){
	char teamName[7];
	char date[11];
	char hour[6];
	char duration[2];
	struct Booking object;
	printf(" ~~ Meeting Attendance ~~\n");
	while(1){
		printf("Enter Meeting Info \"Team_? YYYY-MM-DD HH:MM N\"> ");
		scanf("%s", &teamName);
		if(!strcmp(teamName,"0")) break;
		scanf("%s", &date);
		scanf("%s", &hour);
		scanf("%s", &duration);
		stpcpy(object.teamName,teamName); stpcpy(object.date,date);
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
				printf("Enter attended member's name (If there are no more member, enter 0) > ");
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
	int i;
	for(i=0;i<bookingIndex;i++){
		if(bookingLists[i].isAttended[0]==1){
			printf("%d.   %s %s %02d:00 %d\n",i,bookingLists[i].teamName,bookingLists[i].date,bookingLists[i].hour,bookingLists[i].duration);
			int j;
			for(j=0;j<4;j++){
				getTeamMemberName(j,bookingLists[i].teamName);
				printf("------%s ",NameReturn);
				if(bookingLists[i].isAttended[j+1] == 1){
					printf("O\n");
				}else{
					printf("X\n");
				}
			}
		}
	}
}

int getTeamMemberName(int id,char tn[]){
	char temp[] = "00";
	int i;
	for(i=0;i<26;i++){
		if(strcmp(teamLists[i].name,tn)==0){
			stpcpy(NameReturn,teamLists[i].members[id]);
			return 1;
		}
	}
	stpcpy(NameReturn,"0");
	return 0;
}
