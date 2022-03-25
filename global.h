struct Team
{
   char name[20];
   char project_name[20];
   char members[4][20];
};

struct Team teamLists[26];
int teamsIndex = 0;

//pad test
int temp2_times[2];
char team2_members[20][20]; // array
int team2_members_counter=0;
int testFlag=0;