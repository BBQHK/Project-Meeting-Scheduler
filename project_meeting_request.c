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

// void BatchInput(){
//
// }
