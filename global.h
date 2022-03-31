struct Team
{
   char name[7];
   char project_name[10];
   char members[4][20];
};

struct Booking
{
  char teamName[7];
  char date[11];
  int hour;
  int duration;
};

struct Team teamLists[26];
struct Booking bookingLists[170];
int teamsIndex = 0;
int bookingIndex = 0;

//pad test
int temp2_times[2];
char team2_members[50][20]; // array for all member record
int team2_members_counter=0; // count team2_members;
int testFlag=0;
int checkMemberFlag=0; // 1 = have problem

int action_Create=0; // 0 = can create

char staffNames[8][10] = {
	"Alan","Billy","Cathy","David","Eva","Fanny","Gary","Helen"
};
