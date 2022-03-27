void SingleInput(){
  char cmd[100];
  printf("   ~~ Project Meeting Request Single Input ~~\n");
  while(1){
    printf("Enter> ");
    int i = 1;
    while(1){
      scanf("%s", &cmd);
      if(!strcmp(cmd, "0")){
          displayMenu();
          chooseMenuOption();
          break;
      }
      if(i == 1){
        // printf("%s\n", cmd);
        strcpy(bookingLists[bookingIndex].teamName, cmd);
      }else if(i == 2){
        // printf("%s\n", cmd);
        strcpy(bookingLists[bookingIndex].date, cmd);
      }else if(i == 3){
        char temp[3];
        sprintf(temp, "%c%c", cmd[0], cmd[1]);
        // printf("%d\n", atoi(temp));
        bookingLists[bookingIndex].hour = atoi(temp);
      }else if(i == 4){
        // printf("%s\n", cmd);
        bookingLists[bookingIndex].duration = atoi(cmd);
      }
      i++;

      char c = getchar();
      if(c == '\n'){
        break;
      }
    }
    printf("Request has been received.\n");
    bookingIndex++;
  }
}

void BatchInput(){
	char dir[50];
	char cmd[100];
	
	printf(" ~~ Project Meeting Request Single Input ~~\n");
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
