void chooseMenuOption();
void displayMenu();

void CreateProjectTeam(){
  char cmd[100];
  printf("   ~~ Create Project Team ~~\n");
  while(1){
    printf("Enter> ");
    int i = 1;
    int NumOfMembers = 0;
    char temp_name[20];
    char temp_project_name[20];
    char temp_leader[20];
    char temp_members[20][3];

    while(1){
      scanf("%s", &cmd);
      if(!strcmp(cmd, "0")){
          displayMenu();
          chooseMenuOption();
      }
      //printf("[String %d]%s\n", i, cmd);
      if(i == 1){
          // printf("[Team] %s\n","Saved");
          strcpy(temp_name, cmd);
          // strcpy(teamLists[teamsIndex].name, cmd);
      }else if(i == 2){
          // printf("[Project] %s\n","Saved");
          strcpy(temp_project_name, cmd);
      }else if(i == 3){
          // printf("[Leader] %s\n","Saved");
          // int k;
          // for(k = 0; k < teamsIndex; k++){
          //   if(!strcmp(teamLists[k].members[0], cmd)){
          //     printf("error!!!\n");
          //     strcpy(cmd, "0");
          //     break;
          //     // CreateProjectTeam();
          //   }
          // }
          strcpy(temp_leader, cmd);
          // strcpy(teamLists[teamsIndex].members[NumOfMembers], cmd);
          NumOfMembers++;
      }else if(i > 3 && i <= 6){
          // printf("[Member %d] %s\n", NumOfMembers,"Saved");
          // strcpy(teamLists[teamsIndex].members[NumOfMembers], cmd);
          strcpy(temp_members[NumOfMembers], cmd);
          NumOfMembers++;
      }
      i++;

      char c = getchar();
      if(c == '\n'){
        break;
      }
    }
    int k;
    for(k = 0; k < teamsIndex; k++){
      if(!strcmp(teamLists[k].members[0], temp_leader)){
        printf("%s is already working as another project manager!\n", temp_leader);
        CreateProjectTeam();
      }
    }

    // for(k = 0; k < teamsIndex; k++){
    //   int j;
    //   for(j = 1; j < NumOfMembers; j++){
    //     if(!strcmp(teamLists[k].members[j], temp_members[j-1])){
    //
    //     }
    //   }
    // }

    strcpy(teamLists[teamsIndex].name, temp_name);
    strcpy(teamLists[teamsIndex].project_name, temp_project_name);
    strcpy(teamLists[teamsIndex].members[0], temp_leader);
    for(k = 1; k < NumOfMembers; k++){
      strcpy(teamLists[teamsIndex].members[k], temp_members[k]);
    }
    printf("Project %s is created.\n",teamLists[teamsIndex].name);

    printf("[Team] %s\n", teamLists[teamsIndex].name);
    printf("[Project] %s\n", teamLists[teamsIndex].project_name);
    int j;
    for(j = 0;j < NumOfMembers; j++){
        if(j == 0){
            printf("[Leader] %s\n", teamLists[teamsIndex].members[j]);
        }else{
            printf("[Member %d] %s\n",j, teamLists[teamsIndex].members[j]);
        }
    }

    teamsIndex++;
  }
  // CreateProjectTeam();
}
