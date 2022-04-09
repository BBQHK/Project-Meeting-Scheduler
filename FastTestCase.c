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

  strcpy(bookingLists[bookingIndex].teamName, "Team_B");//Team_B 2022-04-26 10:00 3
  strcpy(bookingLists[bookingIndex].date, "2022-04-26");
  bookingLists[bookingIndex].hour = 10;
  bookingLists[bookingIndex].duration = 3;
  bookingIndex++;

  strcpy(bookingLists[bookingIndex].teamName, "Team_C");
  strcpy(bookingLists[bookingIndex].date, "2022-04-26");
  bookingLists[bookingIndex].hour = 11;
  bookingLists[bookingIndex].duration = 2;
  bookingIndex++;

  strcpy(bookingLists[bookingIndex].teamName, "Team_D");//Team_D 2022-04-26 14:00 2
  strcpy(bookingLists[bookingIndex].date, "2022-04-26");
  bookingLists[bookingIndex].hour = 14;
  bookingLists[bookingIndex].duration = 2;
  bookingIndex++;

  strcpy(bookingLists[bookingIndex].teamName, "Team_E");
  strcpy(bookingLists[bookingIndex].date, "2022-04-27");
  bookingLists[bookingIndex].hour = 9;
  bookingLists[bookingIndex].duration = 2;
  bookingIndex++;
  
  
  
  strcpy(bookingLists[bookingIndex].teamName, "Team_A");
  strcpy(bookingLists[bookingIndex].date, "2022-04-26");
  bookingLists[bookingIndex].hour = 9;
  bookingLists[bookingIndex].duration = 2;
  bookingIndex++;

  strcpy(bookingLists[bookingIndex].teamName, "Team_B");
  strcpy(bookingLists[bookingIndex].date, "2022-04-26");
  bookingLists[bookingIndex].hour = 14;
  bookingLists[bookingIndex].duration = 3;
  bookingIndex++;

  strcpy(bookingLists[bookingIndex].teamName, "Team_C");
  strcpy(bookingLists[bookingIndex].date, "2022-04-27");
  bookingLists[bookingIndex].hour = 11;
  bookingLists[bookingIndex].duration = 3;
  bookingIndex++;

  strcpy(bookingLists[bookingIndex].teamName, "Team_D");
  strcpy(bookingLists[bookingIndex].date, "2022-04-27");
  bookingLists[bookingIndex].hour = 14;
  bookingLists[bookingIndex].duration = 2;
  bookingIndex++;

  strcpy(bookingLists[bookingIndex].teamName, "Team_E");
  strcpy(bookingLists[bookingIndex].date, "2022-04-28");
  bookingLists[bookingIndex].hour = 9;
  bookingLists[bookingIndex].duration = 4;
  bookingIndex++;


  printf("Teams %s request at %s has been received.\n",bookingLists[0].teamName,bookingLists[0].date);
  printf("Teams %s request at %s has been received.\n",bookingLists[1].teamName,bookingLists[1].date);
  printf("Teams %s request at %s has been received.\n",bookingLists[2].teamName,bookingLists[2].date);
  printf("Teams %s request at %s has been received.\n",bookingLists[3].teamName,bookingLists[3].date);
  printf("Teams %s request at %s has been received.\n",bookingLists[4].teamName,bookingLists[4].date);
  printf("Teams %s request at %s has been received.\n",bookingLists[5].teamName,bookingLists[5].date);
  printf("Teams %s request at %s has been received.\n",bookingLists[6].teamName,bookingLists[6].date);
  printf("Teams %s request at %s has been received.\n",bookingLists[7].teamName,bookingLists[7].date);
  printf("Teams %s request at %s has been received.\n",bookingLists[8].teamName,bookingLists[8].date);
  printf("Teams %s request at %s has been received.\n",bookingLists[9].teamName,bookingLists[9].date);
  chooseMenuOption();
}
