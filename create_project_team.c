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
    char temp_members[20][20];

    while(1){
      scanf("%s", &cmd);
      if(!strcmp(cmd, "0")){
          displayMenu();
          chooseMenuOption();
          break;
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

          if(testFlag==0){
            strcpy(team2_members[team2_members_counter], cmd); // for me after check
            team2_members_counter++;
          }else{
            int aa;
            for(aa=0;aa<team2_members_counter;aa++){
                if(strcmp(team2_members[aa], cmd)){
                  if(aa==team2_members_counter-1){
                    strcpy(team2_members[team2_members_counter], cmd); // for me after check
                    team2_members_counter++;
                  }
                }else{
                  break;
                }
            }
          }


      }
      i++;

      char c = getchar();
      if(c == '\n'){
        break;
      }
    }
    int k;
    for(k = 0; k < teamsIndex; k++){
        // printf("[Check] team: %s\n",teamLists[k].name);
      if(!strcmp(teamLists[k].name, temp_name)){
        printf("%s is already exist!\n", temp_name);
        CreateProjectTeam();
      }
    }

    for(k = 0; k < teamsIndex; k++){
        // printf("[Check] team: %s\n",teamLists[k].name);
      if(!strcmp(teamLists[k].members[0], temp_leader)){
        printf("%s is already working as another project manager!\n", temp_leader);
        CreateProjectTeam();
      }
    }
    int a,b,c,d;
    int checkMemberFlag=0;
    for(a=0;a<teamsIndex;a++){
        for(b=1;b<=3;b++){
            for(c=1;c<=3;c++){
                if(!strcmp(teamLists[a].members[b], temp_members[c])){
                    for(d=0;d<team2_members_counter;d++){
                        if(!strcmp(team2_members[d], temp_members[c])){
                            if(temp2_times[d]==4){
                                checkMemberFlag=1;
                            }
                            break;
                        }
                    }
                break;
                }
            }

        }
    }

    int e,f,g,h;
    int checkTimes=0;
    for(e=0;e<teamsIndex;e++){
        for(f=1;f<=3;f++){
            for(g=0;g<=3;g++){
                if(!strcmp(teamLists[e].members[f], temp_members[g])){
                    for(h=0;h<team2_members_counter;h++){
                        if(!strcmp(team2_members[h], temp_members[g])){
                            checkTimes=temp2_times[h];
                            // printf("[Check Times : %s %d ; %s %d\n",team2_members[h],temp2_times[h],temp_members[g],temp2_times[h]);
                            if(checkMemberFlag==1){
                              printf("[Warning]%s is already member! %d times so gg\n", team2_members[h],4);
                              CreateProjectTeam();
                            }
                            if(checkTimes==0){
                              if(checkMemberFlag==0){
                                temp2_times[h]=3;
                                printf("[Warning]%s is already member! %d times\n", team2_members[h],2);
                              }
                            }else if(checkTimes==3){
                              if(checkMemberFlag==0){
                                temp2_times[h]=4;
                                printf("[Warning]%s is already member! %d times\n", team2_members[h],3);
                              }
                            }
                            break;
                        }
                    }
                break;
                }
            }

        }
    }
    if(i<4){
      printf("create error\n");
      CreateProjectTeam();
    }

    strcpy(teamLists[teamsIndex].name, temp_name);
    strcpy(teamLists[teamsIndex].project_name, temp_project_name);
    strcpy(teamLists[teamsIndex].members[0], temp_leader);
    for(k = 1; k < NumOfMembers; k++){
      strcpy(teamLists[teamsIndex].members[k], temp_members[k]);
    }
    printf("Project %s is created.\n",teamLists[teamsIndex].name);

    // printf("[Team] %s\n", teamLists[teamsIndex].name);
    // printf("[Project] %s\n", teamLists[teamsIndex].project_name);
    // int j;
    // for(j = 0;j < NumOfMembers; j++){
    //     if(j == 0){
    //         printf("[Leader] %s\n", teamLists[teamsIndex].members[j]);
    //     }else{
    //         printf("[Member %d] %s\n",j, teamLists[teamsIndex].members[j]);
    //     }
    // }

    for(a=0;a<=3;a++){
        strcpy(temp_members[a], "");
    }

    teamsIndex++;
    testFlag++;
  }
  // CreateProjectTeam();
}

void padMemberList(){
  int p;
  for(p=0;p<team2_members_counter;p++){
    printf("[Check Member] %d. %s has %d times\n",p+1,team2_members[p],temp2_times[p]);
  }
}
