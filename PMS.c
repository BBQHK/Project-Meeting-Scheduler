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
#include "project_meeting_request.c"
#include "meeting_schedule.c"

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
    printf("6. Check the booking list\n\n");
    printf("7. Add the fucking test case\n\n");
}

void chooseMenuOption();

void CheckBookingList(){
  printf("\n\n");
  printf("Check Booking List Mode\n");
  // int i;
  // for(i=0;i<bookingIndex;i++){
  //     printf("Booking request %d\n", i+1);
  //     printf("Team : %s\n",bookingLists[i].teamName);
  //     printf("Date : %s\n", bookingLists[i].date);
  //     printf("Hour : %d\n", bookingLists[i].hour);
  //     printf("Duration : %d\n", bookingLists[i].duration);
  //     printf("--------------------------\n");
  // }
    printf("%-12s %-10s %-12s %-5s %-2s\n","Request Id", "Team", "Date", "Hour", "Duration");
    int i;
    for(i=0;i<bookingIndex;i++){
      printf("%-12d %-10s %-12s %-2d:00 %-2d\n",i+1, bookingLists[i].teamName, bookingLists[i].date, bookingLists[i].hour, bookingLists[i].duration);
    }
    printf("\n\n");
  chooseMenuOption();
}

void CheckTeamList(){
    printf("\n\n");
    printf("Check Team Mode\n");
    // int i;
    // for(i=0;i<teamsIndex;i++){
    //     printf("Team : %s\n",teamLists[i].name);
    //     printf("Project : %s\n", teamLists[i].project_name);
    //     int j;
    //     int membersCounter = 0;
    //     for(j = 0;j < 4; j++){
    //       if(strcmp(teamLists[i].members[j], "")){
    //         membersCounter++;
    //       }
    //     }
    //     printf("Number of members : %d\n",membersCounter);
    //     for(j = 0;j < membersCounter; j++){
    //       printf("%s member : %s\n", teamLists[i].name, teamLists[i].members[j]);
    //     }
    //     printf("\n");
    // }
    printf("%-10s %-10s %-20s %-10s %-10s %-10s %-10s\n","Team", "Project", "Number of members", "Leader", "Member 1", "Member 2", "Member 3");
    int i;
    for(i=0;i<teamsIndex;i++){      
        int j;
        int membersCounter = 0;
        for(j = 1;j < 4; j++){
          if(strcmp(teamLists[i].members[j], "")){
            membersCounter++;
          }
        }
        printf("%-10s %-10s %-20d %-10s %-10s %-10s %-10s\n",teamLists[i].name, teamLists[i].project_name, membersCounter, 
        teamLists[i].members[0], teamLists[i].members[1], teamLists[i].members[2], teamLists[i].members[3]);
    }
    printf("\n\n");
    chooseMenuOption();
}

void Testcase(){
  strcpy(teamLists[teamsIndex].name, "Team_A");
  strcpy(teamLists[teamsIndex].project_name, "Project_A");
  strcpy(teamLists[teamsIndex].members[0], "Alan");
  strcpy(teamLists[teamsIndex].members[1], "Cathy");
  strcpy(teamLists[teamsIndex].members[2], "Fanny");
  strcpy(teamLists[teamsIndex].members[3], "Helen");
  teamsIndex++;  
  strcpy(teamLists[teamsIndex].name, "Team_B");
  strcpy(teamLists[teamsIndex].project_name, "Project_B");
  strcpy(teamLists[teamsIndex].members[0], "Fanny");
  strcpy(teamLists[teamsIndex].members[1], "Alan");
  strcpy(teamLists[teamsIndex].members[2], "Helen");
  teamsIndex++;
  strcpy(teamLists[teamsIndex].name, "Team_C");
  strcpy(teamLists[teamsIndex].project_name, "Project_C");
  strcpy(teamLists[teamsIndex].members[0], "Cathy");
  strcpy(teamLists[teamsIndex].members[1], "Helen");
  strcpy(teamLists[teamsIndex].members[2], "Fanny");
  teamsIndex++;
  strcpy(teamLists[teamsIndex].name, "Team_D");
  strcpy(teamLists[teamsIndex].project_name, "Project_D");
  strcpy(teamLists[teamsIndex].members[0], "Billy");
  strcpy(teamLists[teamsIndex].members[1], "David");
  strcpy(teamLists[teamsIndex].members[2], "Cathy");
  strcpy(teamLists[teamsIndex].members[3], "Eva");
  teamsIndex++;
  strcpy(teamLists[teamsIndex].name, "Team_E");
  strcpy(teamLists[teamsIndex].project_name, "Project_E");
  strcpy(teamLists[teamsIndex].members[0], "Gary");
  strcpy(teamLists[teamsIndex].members[1], "Eva");
  strcpy(teamLists[teamsIndex].members[2], "David");
  teamsIndex++;

  printf("Project %s is created.\n","Team_A");
  printf("Project %s is created.\n","Team_B");
  printf("Project %s is created.\n","Team_C");
  printf("Project %s is created.\n","Team_D");
  printf("Project %s is created.\n","Team_E");

  strcpy(bookingLists[bookingIndex].teamName, "Team_A");
  strcpy(bookingLists[bookingIndex].date, "2022-04-25");
  bookingLists[bookingIndex].hour = 9;
  bookingLists[bookingIndex].duration = 2;
  bookingIndex++;

  strcpy(bookingLists[bookingIndex].teamName, "Team_B");
  strcpy(bookingLists[bookingIndex].date, "2022-04-26");
  bookingLists[bookingIndex].hour = 10;
  bookingLists[bookingIndex].duration = 3;
  bookingIndex++;

  strcpy(bookingLists[bookingIndex].teamName, "Team_C");
  strcpy(bookingLists[bookingIndex].date, "2022-04-26");
  bookingLists[bookingIndex].hour = 11;
  bookingLists[bookingIndex].duration = 3;
  bookingIndex++;

  strcpy(bookingLists[bookingIndex].teamName, "Team_D");
  strcpy(bookingLists[bookingIndex].date, "2022-04-26");
  bookingLists[bookingIndex].hour = 14;
  bookingLists[bookingIndex].duration = 2;
  bookingIndex++;

  strcpy(bookingLists[bookingIndex].teamName, "Team_E");
  strcpy(bookingLists[bookingIndex].date, "2022-04-27");
  bookingLists[bookingIndex].hour = 9;
  bookingLists[bookingIndex].duration = 2;
  bookingIndex++;

  printf("Teams %s request at %s has been received.\n",bookingLists[0].teamName,bookingLists[0].date);
  printf("Teams %s request at %s has been received.\n",bookingLists[1].teamName,bookingLists[1].date);
  printf("Teams %s request at %s has been received.\n",bookingLists[2].teamName,bookingLists[2].date);
  printf("Teams %s request at %s has been received.\n",bookingLists[3].teamName,bookingLists[3].date);
  printf("Teams %s request at %s has been received.\n",bookingLists[4].teamName,bookingLists[4].date);
  chooseMenuOption();
}

void chooseMenuOption(){
  char opNum[3];
  printf("Enter an option: ");
  scanf("%s", &opNum);
  if(!strcmp(opNum, "1")){ // Create Project Team
    CreateProjectTeam();
    strcpy(opNum, "0");

  }else if(!strcmp(opNum, "2a")){
    SingleInput(); // Project Meeting Request Single Input
    strcpy(opNum, "0");

  }else if(!strcmp(opNum, "2b")){
    BatchInput(); // Project Meeting Request Batch Input
    strcpy(opNum, "0");

  }else if(!strcmp(opNum, "3a")){
    pms_FCFS();
	strcpy(opNum, "0");
  }else if(!strcmp(opNum, "4")){ // Exit
    printf("See you next time :)\n");
    exit(0);
  }else if(!strcmp(opNum, "5")){
    printf("Check the fucking list :)\n");
    CheckTeamList();
  }else if(!strcmp(opNum, "6")){
    CheckBookingList();
  }else if(!strcmp(opNum, "7")){
    Testcase();
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
