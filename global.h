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
char team2_members[50][20]; // array for all member record
int team2_members_counter=0; // count team2_members;
int testFlag=0;
int checkMemberFlag=0; // 1 = have problem

int action_Create=0; // 0 = can create