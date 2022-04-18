struct Team
{
	char name[7];
	char project_name[10];
	char members[4][20];
	int meetingRecord[5];
	//0:Number of meetings held , 1:First member's meeting attendance...
	int ReqRec;
	int ReqAcc_FCFS;
	int ReqAcc_SJF;
};

struct Booking
{
	char teamName[7];
	char date[11];
	int hour;
	int duration;
	int isAttended[5];//only store 0/1
	//0:Has the booking been executed? , 1:is first member Attended ...

};

struct Team teamLists[26];
int teamsIndex = 0;

struct Booking bookingLists[170];
int bookingIndex = 0;


struct Booking rBL_FCFS[170];//rejected BookingLists
int rBLIndex_FCFS = 0;
struct Booking rBL_SJF[170];//rejected BookingLists
int rBLIndex_SJF = 0;

int Total_ReqAcc_FCFS = 0;
int Total_ReqAcc_SJF = 0;
int Total_ReqRej_FCFS = 0;
int Total_ReqRej_SJF = 0;
int AEFlag = 0;


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

int staffRr[8]={0,0,0,0,0,0,0,0};
int staffAr_FCFS[8]={0,0,0,0,0,0,0,0};
int staffAr_SJF[8]={0,0,0,0,0,0,0,0};
double staffAtten[8]={0,0,0,0,0,0,0,0};
