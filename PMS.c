//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永無BUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"

#include "create_project_team.c"

void displayMenu() {
    printf("   ~~ WELCOME TO PolyStar ~~\n\n");

    printf("1. Create Project Team\n\n");

    printf("2. Project Meeting Request\n");
    printf("   2a. Single input\n");
    printf("   2b. Batch input\n");
    printf("   2c. Meeting Attendance\n\n");

    printf("3. Print Meeting Schedule\n");
    printf("   3a. FCFS (First Come First Served)\n");
    printf("   3b. XXXX (Another algorithm implemented)\n");
    printf("   3c. YYYY (Attendance Report)\n\n");

    printf("4. Exit\n\n");

    printf("5. Check the fucking list\n\n");
}

void chooseMenuOption();

void CheckTeamList(){
    printf("Check Team Mode\n");
    int i;
    for(i=0;i<teamsIndex;i++){
        printf("Team : %s\n",teamLists[i].name);
        printf("Project : %s\n", teamLists[i].project_name);
        int j;
        int membersCounter = 0;
        for(j = 0;j < 4; j++){
          if(strcmp(teamLists[i].members[j], "")){
            membersCounter++;
          }
        }
        printf("Number of members : %d\n",membersCounter);
        for(j = 0;j < membersCounter; j++){
          printf("%s member : %s\n", teamLists[i].name, teamLists[i].members[j]);
        }
        printf("\n");
    }
    
    chooseMenuOption();
}

void chooseMenuOption(){
  int opNum;
  printf("Enter an option: ");
  scanf("%d", &opNum);
  if(opNum == 1){ // Create Project Team
    CreateProjectTeam();
    opNum=0;
  }else if(opNum == 2){
    printf("To be implement!\n");
    displayMenu();
    chooseMenuOption();

  }else if(opNum == 3){
    printf("To be implement!\n");

  }else if(opNum == 4){ // Exit
    printf("See you next time :)\n");
    exit(0);
  }else if(opNum == 5){
    printf("Check the fucking list :)\n");
    CheckTeamList();
  }else{
    printf("Invalid number, please enter again!\n");
    chooseMenuOption();
  }
}

int main() {
    displayMenu();
    chooseMenuOption();
    return 0;
}
