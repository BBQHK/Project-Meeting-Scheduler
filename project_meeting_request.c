void SingleInput(){
  char cmd[100];
  printf("   ~~ Project Meeting Request Single Input ~~\n");
  while(1){
    printf("Enter> ");
    int i = 1;
	//Team_A 2022-04-25 09:00 2

	int bookingWorkingTimeFlag=0,bookingDayFlag=0,bookingWorkDayFlag=0,bookingTimeFlag=0; // control the error 
	// 4個先放一放啲value
	char bookingTeamName[20];
	char bookingTime[20];
	int bookingHour;
	int bookingDuration;

	// save住個cmd先做checking
	int time1;

    while(1){
      scanf("%s", &cmd);
      if(!strcmp(cmd, "0")){
          displayMenu();
          chooseMenuOption();
          break;
      }
      if(i == 1){
        // printf("%s\n", cmd);
        //strcpy(bookingLists[bookingIndex].teamName, cmd);
		strcpy(bookingTeamName, cmd);
      }else if(i == 2){
        // printf("%s\n", cmd);
        //strcpy(bookingLists[bookingIndex].date, cmd);
		char month1[3];
		sprintf(month1, "%c%c", cmd[5], cmd[6]);
		int month2 = atoi(month1);

		if(month2!=4 && month2!=5){
			bookingDayFlag=1;
		}

		char date1[3];
		sprintf(date1, "%c%c", cmd[8], cmd[9]);
		int date2 = atoi(date1);

		if(month2==4){
			if(date2<25 || date2>30){
				bookingDayFlag=1;
			}			
		}else if(month2==5 && date2<1 || date2>14){
			bookingDayFlag=1;
		}
		if(month2==5 && date2==1){
			bookingWorkDayFlag=1;
		}else if(month2==5 && date2==8){
			bookingWorkDayFlag=1;
		}

		strcpy(bookingTime, cmd);

      }else if(i == 3){
        char temp[3];
        sprintf(temp, "%c%c", cmd[0], cmd[1]);
        //printf("%d\n", atoi(temp));
		bookingHour = atoi(temp);
        //bookingLists[bookingIndex].hour = atoi(temp);

		time1 = atoi(temp);
		if(time1 <9 || time1>18){
			bookingTimeFlag=1;
		}
      }else if(i == 4){
        //printf("%s\n", cmd);
        //bookingLists[bookingIndex].duration = atoi(cmd);
		bookingDuration = atoi(cmd);
		if(bookingDuration+time1>18){
			bookingWorkingTimeFlag=1;
		}
      }
      i++;

      char c = getchar();
      if(c == '\n'){
        break;
      }
    }
    

	if(bookingDayFlag==0 && bookingWorkDayFlag==0 && bookingTimeFlag==0 && bookingWorkingTimeFlag==0){
		strcpy(bookingLists[bookingIndex].teamName, bookingTeamName);
		strcpy(bookingLists[bookingIndex].date, bookingTime);
        bookingLists[bookingIndex].hour = bookingHour;
		bookingLists[bookingIndex].duration = bookingDuration;
		printf("Request has been received.\n");
		bookingIndex++;
	}

	if(bookingDayFlag==1){
		printf("%s\n","Wrong Day (You should input 2022-04-25 to 2022-05-14)");
	}
	if(bookingWorkDayFlag==1){
		printf("%s\n","Wrong Day (2022-05-01 and 2022-05-08 is Sunday)");
	}
    if(bookingTimeFlag==1){
		printf("%s\n","Wrong Working Time (You should input 09:00 to 18:00)");
	}
	if(bookingWorkingTimeFlag==1){
		printf("%s\n","Wrong Working Time (You can not still working after than 18:00)");
	}
  }
}

void BatchInput(){
	char dir[50];
	char cmd[100];

	printf(" ~~ Project Meeting Request Batch Input ~~\n");
	while(1){
		printf("Enter file name> ");
		scanf("%s", &cmd);
		if(!strcmp(cmd, "0")){
			displayMenu();
			chooseMenuOption();
			break;
		}
		FILE * fp;
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		stpcpy(dir,"data/");
		strcat(dir,cmd);
		fp = fopen(dir, "r");

		if (fp == NULL)
			exit(EXIT_FAILURE);
		while ((read = getline(&line, &len, fp)) != -1) {
			printf("Request: %s",line);
			char *parts;
			int i = 1;
			parts = strtok(line, " ");
			//printf("%d:%s\n",i,parts);
			strcpy(bookingLists[bookingIndex].teamName, parts);
			i++;
			while((parts = strtok(NULL, " "))){
				//printf("%d:%s\n",i,parts);
				if(i == 2){
					strcpy(bookingLists[bookingIndex].date, parts);
				}else if(i == 3){
					char temp[3];
					sprintf(temp, "%c%c", parts[0], parts[1]);
					bookingLists[bookingIndex].hour = atoi(temp);
				}else if(i == 4){
					bookingLists[bookingIndex].duration = atoi(parts);
				}
				i++;
			}
			bookingIndex++;
		}
		fclose(fp);
		printf("Request has been received.\n");
	}
}
