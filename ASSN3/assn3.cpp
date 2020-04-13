#include "default.h"
using namespace std;

// 로그인되어 사용하고 있는 사용자의 클래스 포인터는 temp에 저장해놓는다.
// temp != NULL 이라면 로그인 되어있는 상태이므로, 추가적인 로그인이 불가능하다.
class member {

protected:
	string RRN, ID, password;
	int info;


public:
	string back_ID() const {return ID;}
	string back_password() const { return password; }
	string back_RRN() const { return RRN; }
	virtual int back_info() const { return info; }

	member() { info = 0;  }
	member(string put_RRN, string put_ID, string put_password) {
		RRN = put_RRN;
		ID = put_ID;
		password = put_password;
		info = 0;

	}
	member(const member& put_member) {
		RRN = put_member.RRN;
		ID = put_member.ID;
		password = put_member.password;
		info = 0;
	
	}
	virtual ~member() {};

	// 기타 member 함수
};

class group_member : public member {
	
	string group_name;

public:
	string back_group_name() const { return group_name; }
	int back_info() const { return info; }

	group_member() : member() { info = 1; }
	group_member(const member& put_member, string put_group_name) : member(put_member) { info = 1; group_name = put_group_name;}
	~group_member() {}

	// 기타 group_member 함수

};




class group_leader : public member {

	string group_name;

public:
	string back_group_name() const { return group_name; }
	int back_info() const { return info; }

	group_leader() : member() { info = 2; }
	group_leader(const member& put_member, string put_group_name) : member(put_member) { info = 2; group_name = put_group_name;}
	~ group_leader() {}

	// 기타 group_leader 함수

};

class vote_member {
	string vote_topic;
	string vote_sub; // 투표별 항목 개수 이거를 vote_num 배열 개수로 넘겨준다
	string vote_check[50]; // 투표한 회원의 주민번호 등록해놓기

	int vote_num[MAX_NUM_VOTEITEM] = { 0, }; // 투표 항목별 득표 현황 ++ --로 득표 현황 게시
	int vote_check_num = 0; // 처음에 0으로 되어있다가 항목에 vote 하는 member가 생기면++

public:
	vote_member(string vote_topic, string vote_sub);

	string back_vote_topic() const { return vote_topic; } // 투표 주제 반환
	string back_vote_sub() const { return vote_sub; } // 투표별 항목 개수 반환
	string back_RRN(int i) const { return vote_check[i]; } // 중복투표인지 확인하기 위해 RRN 탐색

	int back_vote_check_num() const { return vote_check_num; } // 투표 주제에 투표한 회원 수 반환
	int back_vote_num(int i) const { return vote_num[i]; } // 투표 항목 마다 투표받은 개수 반환

	void plus_vote_check_num(string RRN, int vote); // vote 한 곳에 vote 추가
};

vote_member::vote_member(string put_vote_topic, string put_vote_sub) // 받은 Token[0] [1] [2].. 넣기
{
	vote_topic = put_vote_topic;
	vote_sub = put_vote_sub;
}

void vote_member::plus_vote_check_num(string RRN, int vote) // vote -> 투표한 항목 번호
{
	vote_check[vote_check_num] = RRN;
	vote_check_num++;
	vote_num[vote]++;
}

class group {
	member* leader;
	string group_name, group_RRN[MAX_GROUP_MEMBER], group_id[MAX_GROUP_MEMBER];
	vote_member* vote_members[MAX_GROUP_VOTE]; // 해당 그룹 투표 배열
	int num_vote; // 해당 group에 존재하는 투표의 종류 개수
	int group_check_num; // 해당 group에 존재하는 인원 수

public:
	group(member* put_leader, string put_group_name)
	{
		leader = put_leader;
		group_name = put_group_name;
		num_vote = 0;
		group_check_num = 0;
	}

	void group_put(string put_RRN, string put_id,int i)
	{
		group_RRN[i] = put_RRN;
		group_id[i] = put_id;
		group_check_num++;
	}

	string back_group_name () const { return group_name; }
	string back_group_RRN(int i) const { return group_RRN[i]; }
	string back_group_id(int i) const { return group_id[i]; }
	int back_group_check_num() const { return group_check_num;  group_check_num; }
};

void join(member** members, int* mem_num, int is_login, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);
int login(member** members, int* mem_num, int is_login, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);

//

void logout(member** temp, int* is_login, int menu1, int menu2, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);
void unjoin(member** members, member** temp, int* mem_num, int *is_login, int menu1, int menu2, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);
void delete_vote(vote_member** members, int* sub_num, member* temp, int menu1, int menu2, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);
void add_vote(vote_member** members, int* sub_num, member* temp, int menu1, int menu2, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);
void view_vote(vote_member** members, int sub_num, int menu1, int menu2, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);
void cast_vote(vote_member** members, int sub_num, member* temp, int menu1, int menu2, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);
void join_group(int select_mem_num, member** members, member** temp, group** groups, int* group_num, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);
void create_group(int select_mem_num, member** members, member** temp, group** groups, int* group_num, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);

//


//////////////////////////////////////////////////////////////////////////////////////////////////////

int printMenu1()
{
	string line;
	int loadMode;
	cout << "Load log file?(1:yes, 0:no (log will be deleted)):"; fflush(stdout);
	//cin >> line;
	getline(cin, line);
	loadMode = atoi(line.c_str());
	const char* tmp = line.c_str();
	return loadMode;
}

void printMenu(int num)
{
	cout << "\n\n=======================" << endl; fflush(stdout);
	cout << "Num:" << num << endl; fflush(stdout);
	cout << "n=======================" << endl; fflush(stdout);
	cout << "1.1 Register as a Member" << endl; fflush(stdout);
	cout << "1.2 Login" << endl; fflush(stdout);
	cout << "1.3 Program Exit" << endl; fflush(stdout);
	cout << "=======================" << endl; fflush(stdout);
	cout << "[Current Position]: Non Member" << endl; fflush(stdout);
	cout << "Select Menu:"; fflush(stdout);
}

void printMenu0(int num, member* put_member)
{
	cout << "\n\n=======================" << endl; fflush(stdout);
	cout << "Num:" << num << endl; fflush(stdout);
	cout << "n=======================" << endl; fflush(stdout);
	cout << "2.1 Logout" << endl; fflush(stdout);
	cout << "2.2 Unsubscribe from System" << endl; fflush(stdout);
	cout << "2.3 Delete Existing Vote Item" << endl; fflush(stdout);
	cout << "2.4 Add a New Vote Item" << endl; fflush(stdout);
	cout << "2.5 List All Vote Items" << endl; fflush(stdout);
	cout << "2.6 Cast a Vote" << endl; fflush(stdout);
	cout << "2.7 Join Group" << endl; fflush(stdout);
	cout << "2.8 Create a Group" << endl; fflush(stdout);
	cout << "2.9 Program Exit" << endl; fflush(stdout);
	cout << "=======================" << endl; fflush(stdout);
	cout << "[ID] : " << put_member->back_ID() << ", [Current Position]: Member" << endl; fflush(stdout);
	cout << "Select Menu:"; fflush(stdout);
}

void printMenu1(int num, group_member* put_member)
{
	cout << "\n\n=======================" << endl; fflush(stdout);
	cout << "Num:" << num << endl; fflush(stdout);
	cout << "n=======================" << endl; fflush(stdout);
	cout << "3.1 Logout" << endl; fflush(stdout);
	cout << "3.2 Unsubscribe from System" << endl; fflush(stdout);
	cout << "3.3 Delete Existing Vote Item" << endl; fflush(stdout);
	cout << "3.4 Add a New Vote Item" << endl; fflush(stdout);
	cout << "3.5 List All Vote Items" << endl; fflush(stdout);
	cout << "3.6 Cast a Vote" << endl; fflush(stdout);
	cout << "3.7 Unsubscribe from Group" << endl; fflush(stdout);
	cout << "3.8 Program Exit" << endl; fflush(stdout);
	cout << "=======================" << endl; fflush(stdout);
	cout << "[ID] : " << put_member->back_ID() << ", [Current Position]: Group Member, [Joined Group]: " << put_member->back_group_name() << endl; fflush(stdout);
	cout << "Select Menu:"; fflush(stdout);
}

void printMenu2(int num, group_leader* put_leader)
{
	cout << "\n\n=======================" << endl; fflush(stdout);
	cout << "Num:" << num << endl; fflush(stdout);
	cout << "n=======================" << endl; fflush(stdout);
	cout << "4.1 Logout" << endl; fflush(stdout);
	cout << "4.2 Delete Existing Vote Item" << endl; fflush(stdout);
	cout << "4.3 Add a New Vote Item" << endl; fflush(stdout);
	cout << "4.4 List All Vote Items" << endl; fflush(stdout);
	cout << "4.5 Cast a Vote" << endl; fflush(stdout);
	cout << "4.6 List All Group Members" << endl; fflush(stdout);
	cout << "4.7 Ban a Member from Group" << endl; fflush(stdout);
	cout << "4.8 Program Exit" << endl; fflush(stdout);
	cout << "=======================" << endl; fflush(stdout);
	cout << "[ID] : " << put_leader->back_ID() << ", [Current Position]: Group Leader, [Joined Group]: " << put_leader->back_group_name() << endl; fflush(stdout);
	cout << "Select Menu:"; fflush(stdout);
}

void clearTokens(string * tokens)
{
	for (int i = 0; i < 6; i++)
		tokens[i].clear();
}
// 이번 assn 에서 token의 최대 개수는 6개로 확장된다.

void doTask()
{
	int menu1 = 0; int menu2 = 0;
	int num = 1; // 파일 실행횟수
	int loadMode;
	ofstream inLogWrite;
	ifstream inLogRead;
	string tokens[6], line;
	stringstream stream;
	int nTokens = 0; //number of tokens in string
	int tmp = 10;

	int mem_num = 0; // 현재 존재하는 member의 개수가 몇 개 인지 (delete 등 for 문에서 사용)
	int sub_num = 0; // 현재 존재하는 vote의 개수가 몇 개 인지
	int group_num = 0; // 현재 존재하는 group의 개수가 몇 개 인지

	int invalid = 0; // invalid selection을 했을 경우 1 아닐경우 0
	int select_member = 0; // login 된 멤버의 배열 인덱스 저장
	int is_login = 0; // login 되어있다면 1, logout 되어있다면 0

	member* members[MAX_NUM_MEMBER]; // 일반멤버 + 그룹멤버 + 그룹리더 배열
	vote_member* vote_members[MAX_NUM_VOTE]; // 일반투표 배열 , 그룹투표 배열은 Group class 안에서 따로 관리한다
	group* groups[MAX_GROUP_MEMBER]; // 그룹 배열

	member* temp0 = NULL; // member의 log_in_check 용으로 사용한다.
	group_member* temp1 = NULL; // group_member의 log_in_check 용으로 사용한다.
	group_leader* temp2 = NULL; // group_leader의 log_in_check 용으로 사용한다.

	loadMode = printMenu1(); // NO : 0 , YES : 1
	if (!loadMode) {
		inLogWrite.open(COMMAND_LOG_FILE_NAME, ios::out);
	}
	else {
		inLogRead.open(COMMAND_LOG_FILE_NAME, ios::in); //read mode
		inLogWrite.open(COMMAND_LOG_FILE_NAME, ios::in | ios::app); //concat without truncation
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	while (1)
	{
		invalid = 0;
		if(is_login == 0) printMenu(num++);

		if (is_login == 1)

		{
			switch (members[select_member]->back_info())
			{
				case 0:
				{
					printMenu0(num++, temp0);
						break;
				}

				case 1:
					{
					printMenu1(num++, temp1);
					break;
				}

				case 2:
				{
						printMenu2(num++, temp2);
					break;
				}
			}
		}

		if (loadMode == 1)
		{
			getline(inLogRead, line);
			if (line == "") // loadMode가 끝났음을 알 수 있는 표시 " "
			{
				//end of file with newline
				if (inLogRead.eof())
				{
					//stop reading from logfile 
					//stdin mode starts
					inLogRead.close();
					loadMode = 0;
					getline(cin, line);
					//when first stdin input was newline
					//continue without loggin input
					if (line == "")
					{
						cout << "Selected Menu: Undefined menu selection" << endl; fflush(stdout);
						continue;
					}
					menu1 = atoi(line.c_str()); // 1개만 해도 되나?
				}
				//middle of file with new line
				//continue without logging
				else
				{
					cout << "\nSelected Menu: Undefined menu selection" << endl; fflush(stdout);
					continue;
				}
			}

			//inputs != newline
			else
			{
				stream.str(line);
				nTokens = 0;
				clearTokens(tokens);
				//Read all tokens(seperated by " ") *********************
				while (stream >> tokens[nTokens])
					nTokens++;
				stream.clear();
				menu1 = atoi(tokens[0].c_str()); // ************** 우리는 여기서 2개를 읽어 메뉴를 선택
				menu2 = atoi(tokens[1].c_str()); // ************** 우리는 여기서 2개를 읽어 메뉴를 선택
				cout << menu1 << " " << menu2 << endl; fflush(stdout);
			}


		}
		//stdin mode
		else
		{
			getline(cin, line);
			if (line == "")
			{
				cout << "Selected Menu: Undefined menu selection" << endl; fflush(stdout);
				continue;
			}
			menu1 = atoi(line.substr(0).c_str());
			menu2 = atoi(line.substr(2).c_str());
		}

		// 메뉴 구분 및 해당 연산 수행
		switch (menu1)
		{
			case 1:
			{
				switch (menu2)
				{
				case 1:
				{
					if (is_login == 1) 
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}
					join(members, &mem_num, is_login, loadMode, inLogRead, inLogWrite, tokens, nTokens);
					break;
				}
				case 2:
				{
					if (is_login == 1)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}
					select_member = login(members, &mem_num, is_login, loadMode, inLogRead, inLogWrite, tokens, nTokens);
					// 로그인 한 member의 info 가 0인지 1인지 2인지 확인하고, 알맞은 temp에 넣어준다.
				
					if(select_member != 100) 
					{
						switch (members[select_member]->back_info())
						{
							case 0:
							{
								temp0 = members[select_member];
								break;
							}
							case 1:
							{
								temp1 = (group_member*)members[select_member];
								break;
							}
							case 2:
							{
								temp2 = (group_leader*)members[select_member];
								break;
							}
						}
						is_login = 1;
					}
					break;
				}
				case 3:
				{
					if (is_login == 1)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}
					inLogWrite.close();
					return;
				}
				default:
					cout << "Selected Menu: Undefined menu selection" << endl; fflush(stdout);
					if (!loadMode) {
						inLogWrite << menu1 << " " << menu2 << endl; // log.txt 에 menu 값 기록
						continue;
					}
					break;
				}
				break;
			}
			case 2:
			{
				switch (menu2)
				{
				case 1:
				{
					if (temp0 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}
					logout(&temp0, &is_login, menu1, menu2, loadMode, inLogRead, inLogWrite, tokens, nTokens);
					select_member = 101;
					break;
				}
				case 2:
				{
					if (temp0 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					unjoin(members, &temp0, &mem_num, &is_login, menu1, menu2, loadMode, inLogRead, inLogWrite, tokens, nTokens);
					select_member = 101;
					break;
				}
				case 3:
				{
					if (temp0 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					delete_vote(vote_members, &sub_num, temp0, menu1, menu2, loadMode, inLogRead, inLogWrite, tokens, nTokens);
					break;
				}
				case 4:
				{
					if (temp0 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					add_vote(vote_members, &sub_num, temp0, menu1, menu2, loadMode, inLogRead, inLogWrite, tokens, nTokens);
					break;
				}
				case 5:
				{
					if (temp0 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}
					view_vote(vote_members, sub_num, menu1, menu2, temp0, loadMode, inLogRead, inLogWrite, tokens, nTokens);
					break;
				}
				case 6:
				{
					if (temp0 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					cast_vote(vote_members, sub_num, temp0, menu1, menu2, loadMode, inLogRead, inLogWrite, tokens, nTokens);
					break;
				}
				case 7:
				{
					if (temp0 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					join_group(select_member, members, &temp0, groups, &group_num, loadMode, inLogRead, inLogWrite, tokens, nTokens);
					break;
				}
				case 8:
				{
					if (temp0 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					create_group(select_member, members, &temp0, groups, &group_num, loadMode, inLogRead, inLogWrite, tokens, nTokens);
					break;
				}
				case 9:
				{
					if (temp0 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}
					inLogWrite.close();
					return;
				}
				default:
					cout << "Selected Menu: Undefined menu selection" << endl; fflush(stdout);
					if (!loadMode) {
						inLogWrite << menu1 << " " << menu2 << endl; // log.txt 에 menu 값 기록
						continue;
					}
					break;
				}
				break;
			}
			case 3:
			{
				switch (menu2)
				{
				case 1:
				{
					if (temp1 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}


					select_member = 101;
					break;
				}
				case 2:
				{
					if (temp1 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					select_member = 101;
					break;
				}
				case 3:
				{
					if (temp1 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					break;
				}
				case 4:
				{
					if (temp1 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					break;
				}
				case 5:
				{
					if (temp1 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					break;
				}
				case 6:
				{
					if (temp1 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					break;
				}
				case 7:
				{
					if (temp1 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					break;
				}
				case 8:
				{
					if (temp1 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}
					inLogWrite.close();
					return;
				}
				default:
					cout << "Selected Menu: Undefined menu selection" << endl; fflush(stdout);
					if (!loadMode) {
						inLogWrite << menu1 << " " << menu2 << endl; // log.txt 에 menu 값 기록
						continue;
					}
					break;
				}
				break;
			}
			case 4:
			{
				switch (menu2)
				{
				case 1:
				{
					if (temp2 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					select_member = 101;
					break;
				}
				case 2:
				{
					if (temp2 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					break;
				}
				case 3:
				{
					if (temp2 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					break;
				}
				case 4:
				{
					if (temp2 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					break;
				}
				case 5:
				{
					if (temp2 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					break;
				}
				case 6:
				{
					if (temp2 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					break;
				}
				case 7:
				{
					if (temp2 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}

					break;
				}
				case 8:
				{
					if (temp2 == NULL)
					{
						cout << "invalid menu selection" << endl;
						invalid = 1;
						break;
					}
					inLogWrite.close();
					return;
				}
				default:
					cout << "Selected Menu: Undefined menu selection" << endl; fflush(stdout);
					if (!loadMode) {
						inLogWrite << menu1 << " " << menu2 << endl; // log.txt 에 menu 값 기록
						continue;
					}
					break;
				}
				break;

			}

		}
		if (invalid ==1 || (menu2 == 1) && ((menu1 == 2) || (menu1 == 3) || (menu1 == 4)) || ((menu1 == 2) && (menu2 == 5)) || ((menu1 == 3) && (menu2 == 5)) || ((menu1 == 3) && (menu2 == 7)) || ((menu1 == 4) && (menu2 == 4)) || ((menu1 == 4) && (menu2 == 6)) || ((menu1 == 0) && (menu2 == 0)) || (loadMode == 1) )
		{
			continue;
		}
		getchar();
	}
	return;
}

////////////1.1
void join(member** members, int* mem_num, int is_login, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)

{
	bool valid_test = true;
	bool let = true;

	//회원가입에대한 정보를 입력받을 문자열변수
	string RRN, ID, password;
	cout << "Selected Menu: 1.1 Register as a Member" << endl; fflush(stdout);

	if (!loadMode)
	{
		cout << "Resident Registration Number:"; fflush(stdout);
		cin >> RRN;
		cout << "ID:"; fflush(stdout);
		cin >> ID;
		cout << "Password:"; fflush(stdout);
		cin >> password;
		inLogWrite << "1" << " " << "1 " << RRN << " " << ID << " " << password << " " << endl;


	}
	else {
		RRN = tokens[2]; ID = tokens[3]; password = tokens[4];
		cout << "1. Resident Registration Number: " << RRN << endl; fflush(stdout);
		cout << "ID: " << ID << endl; fflush(stdout);
		cout << "Password:" << password << endl; fflush(stdout);
	}

	for (int i = 0; i < *mem_num; i++)
	{
		if (RRN == members[i]->back_RRN() || ID == members[i]->back_ID())
			let = false;
	}

	if (is_login == 1) valid_test = false;
	if (let == false) valid_test = false;

	// Valid Case
	if (valid_test == true) {
		members[*mem_num] = new member(RRN, ID, password);
		(*mem_num)++;
		cout << "Registration Done!" << endl; fflush(stdout);
		return;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Regstration Fail" << endl; fflush(stdout);
		return;
	}

}

////////////1.2
int login(member** members, int* mem_num, int is_login, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;

	bool let = false;

	int select_member_num;

	//로그인 정보를 입력받을 문자열변수
	string ID, password;
	cout << "Selected Menu: 1.2 Login" << endl; fflush(stdout);

	if (!loadMode)
	{
		cout << "ID: "; fflush(stdout);
		cin >> ID;
		cout << "password:"; fflush(stdout);
		cin >> password;
		inLogWrite << "1" << " " << "2 " << ID << " " << password << " " << endl;
	}
	else {
		ID = tokens[2]; password = tokens[3];
		cout << "ID: " << ID << endl; fflush(stdout);
		cout << "Password:" << password << endl; fflush(stdout);
	}

	for (int i = 0; i < *mem_num; i++)
	{
		if (ID == members[i]->back_ID() && password == members[i]->back_password())
		{
			select_member_num = i;
			let = true;
			break;
		}
	}

	if (is_login == 1) valid_test = false;
	if (let == false) valid_test = false;

	// Valid Case
	if (valid_test == true) {
		cout << "Login success" << endl; fflush(stdout);
		return select_member_num;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Login Fail" << endl; fflush(stdout);
		return 100;
	}
}

///////////2.1
void logout(member** temp, int* is_login, int menu1, int menu2, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;

	cout << "Selected Menu: " << menu1 << "." << menu2 << " Logout" << endl; fflush(stdout);

	if (!loadMode)
	{
		inLogWrite << menu1 << " " << menu2 << endl; // menu2 뒤에 스페이스바 안넣어도 되는지 확인하고 오류나면 넣을 것!
	}
	else {

	}

	if (is_login == 0) valid_test = false;

	// Valid Case
	if (valid_test == true) {
		(*temp) = NULL;
		(*is_login) = 0;
		cout << "Logout success" << endl; fflush(stdout);
		return;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Logout Fail" << endl; fflush(stdout);
		return;
	}

}

////////// 2.2
void unjoin(member** members, member** temp, int* mem_num, int *is_login, int menu1, int menu2, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;
	bool let = false;
	int select_member_num;

	//회원에대한 정보를 입력받을 문자열변수
	string ID, password;
	cout << "Selected Menu: " << menu1 << "." << menu2 << " Unsubscribe from System" << endl; fflush(stdout);

	if (!loadMode)
	{
		cout << "ID:"; fflush(stdout);
		cin >> ID;
		cout << "Password:"; fflush(stdout);
		cin >> password;
		inLogWrite << menu1 << " " << menu2 << " " << ID << " " << password << " " << endl;


	}
	else {
		ID = tokens[2]; password = tokens[3];
		cout << "ID: " << ID << endl; fflush(stdout);
		cout << "Password:" << password << endl; fflush(stdout);
	}

	for (int i = 0; i < *mem_num; i++)
	{
		if (ID == members[i]->back_ID() && password == members[i]->back_password())
		{
			select_member_num = i;
			let = true;
			break;
		}
	}

	if (*temp != NULL) {
		if (ID != (*temp)->back_ID() || password != (*temp)->back_password())
			valid_test = false;
	}

	if (*is_login == 0) valid_test = false;
	if (let == false) valid_test = false;

	// Valid Case
	if (valid_test == true) {
		(*temp) = NULL;
		delete members[select_member_num];

		for (int i = select_member_num; i < *mem_num - 1; i++)
			members[i] = members[i + 1]; // 마지막에 있던 자리에 포인터 있는데 등록할 때 다른 주소를 덧씌우면 되겠지?

		(*mem_num)--;

		*is_login = 0;
		cout << "Unsubscribe Done!" << endl; fflush(stdout);
		return;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Unsubscribe Fail" << endl; fflush(stdout);
		return;
	}
}

//////////2.5
void view_vote(vote_member** members, int sub_num, int menu1, int menu2, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;
	int num;

	cout << "Selected Menu: "<<menu1<<"."<<menu2<<" List All Vote Items." << endl; fflush(stdout);

	if (!loadMode)
	{
		inLogWrite << menu1 << " " << menu2 << endl;
	}
	else {

	}

	if (temp == NULL) valid_test = false;

	// Valid Case
	if (valid_test == true) {

		if (menu1 == 2)
		{
			cout << "<General Vote>" << endl;
		}

		if (menu1 == 3 || menu1 == 4)
		{
			cout << "<Group Vote>" << endl;
		}

		for (int i = 0; i < sub_num; i++) {

			cout << "Vote Subject: ";
			istringstream ss(members[i]->back_vote_sub());
			ss >> num;

			cout << members[i]->back_vote_topic() << ", Vote Counts per Item -"; fflush(stdout);

			for (int j = 0; j < num; j++) {

				cout << " item" << j + 1 << ": " << members[i]->back_vote_num(j); fflush(stdout);
			}

			cout << endl; fflush(stdout);
		}

		if (sub_num == 0) cout << "NONE" << endl;

		return;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Not Login!" << endl; fflush(stdout);
		return;
	}

}


/////////////2.3
void delete_vote(vote_member** members, int* sub_num, member* temp, int menu1, int menu2, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;
	bool let = false;
	int select_member_num;

	//회원가입에대한 정보를 입력받을 문자열변수
	string vote_topic;
	string num_item;
	cout << "Selected Menu: "<<menu1<<"."<<menu2<<" Delete Existing Vote Item" << endl; fflush(stdout);


	view_vote(members, *sub_num, menu1, menu2, temp, loadMode, inLogRead, inLogWrite, tokens, nTokens); // 투표 목록 출력

	if (!loadMode)
	{
		cout << "Vote Subject to Delete:"; fflush(stdout);
		cin >> vote_topic;
		inLogWrite << menu1 << " " <<menu2<< " 0 " << vote_topic << " " << endl; // " 0 " 부분 추후 그룹에서 수정하기!
	}
	else {
		vote_topic = tokens[2];
		cout << "Vote Subject to Delete" << vote_topic << endl; fflush(stdout);
	}

	for (int i = 0; i < *sub_num; i++) // 해당 투표가 존재하는지 체크
	{
		if (vote_topic == members[i]->back_vote_topic())
		{
			select_member_num = i;
			let = true;
			break;
		}
	}

	if (let == false) valid_test = false;
	if (temp == NULL) valid_test = false; // 삭제를 요청한 회원이 로그인 되어있는지 체크

	// Valid Case
	if (valid_test == true) {
		delete members[select_member_num];

		for (int i = select_member_num; i < *sub_num - 1; i++)
			members[i] = members[i + 1];
		(*sub_num)--;

		cout << "Vote Deleted!" << endl; fflush(stdout);
		return;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Vote Deleted Fail" << endl; fflush(stdout);
		return;
	}

}

/////////////2.4
void add_vote(vote_member** members, int* sub_num, member* temp, int menu1, int menu2, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;

	// 투표에 대한 정보를 입력받을 문자열변수
	string vote_topic;
	string num_item;
	cout << "Selected Menu: "<<menu1<<"."<<menu2<<" Add a New Vote Item" << endl; fflush(stdout);

	view_vote(members, *sub_num, menu1, menu2, temp, loadMode, inLogRead, inLogWrite, tokens, nTokens); // 투표 목록 출력

	if (!loadMode)
	{
		cout << "Vote subject:"; fflush(stdout);
		cin >> vote_topic;
		cout << "Number of Vote Items:"; fflush(stdout);
		cin >> num_item;

		inLogWrite << menu1 << " " << menu2 << " 0 " << vote_topic << " " << num_item << " " << endl; // " 0 " 부분 추후 그룹에서 수정하기
	}
	else {
		vote_topic = tokens[2]; num_item = tokens[3];
		cout << "Vote subject: " << vote_topic << endl; fflush(stdout);
		cout << "Number of Vote Items: " << num_item << endl; fflush(stdout);
	}

	if (temp == NULL) valid_test = false;

	for (int i = 0; i < *sub_num; i++)
	{
		if (vote_topic == members[i]->back_vote_topic()) {
			valid_test = false;
			break;
		}
	}

	// Valid Case
	if (valid_test == true) {
		members[*sub_num] = new vote_member(vote_topic, num_item);
		(*sub_num)++;

		cout << "Vote added!" << endl; fflush(stdout);
		return;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Vote added Fail" << endl; fflush(stdout);
		return;
	}

}

/////////////2.6
void cast_vote(vote_member** members, int sub_num, member* temp, int menu1, int menu2, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	string vote_topic; // 투표할 투표 주제
	string num_item; // 투표할 주제의 투표할 항목
	int select_sub_num = 0;
	int num = 0;
	bool valid_test = true; // 현재 로그인 되어있는지
	bool let = false;
	cout << "Selected Menu: "<<menu1<<"."<<menu2<<" Cast a Vote" << endl; fflush(stdout);

	view_vote(members, sub_num, menu1, menu2, temp, loadMode, inLogRead, inLogWrite, tokens, nTokens); // 투표 목록 출력

	if (!loadMode)
	{
		cout << "Vote subject:"; fflush(stdout);
		cin >> vote_topic;
		cout << "Vote for:"; fflush(stdout);
		cin >> num_item;

		inLogWrite << menu1<<" "<<menu2<<" 0 " << vote_topic << " " << num_item << " 0 " << endl; // " 0 ' 부분들 이후 그룹에서 고치기
	}
	else {
		vote_topic = tokens[2]; num_item = tokens[3];
		cout << "Vote subject: " << vote_topic << endl; fflush(stdout);
		cout << "Vote for: " << num_item << endl; fflush(stdout);
	}

	if (temp == NULL) valid_test = false; // 로그인 되어있지 않을 경우

	if (valid_test == true) {
		for (int i = 0; i < sub_num; i++) // 입력 받은 투표 주제가 존재하는지 체크
		{
			if (vote_topic == members[i]->back_vote_topic())
			{
				select_sub_num = i;
				let = true;
				break;
			}
		}
	}

	if (let == false) valid_test = false;

	if (let == true) {
		istringstream ss(num_item);
		ss >> num;

		for (int j = 0; j < members[select_sub_num]->back_vote_check_num(); j++) // 이미 투표한 회원인지 체크 num = int vote_sub
		{
			if (members[select_sub_num]->back_RRN(j) == temp->back_RRN())
				valid_test = false;
		}
	}

	// Valid Case
	if (valid_test == true) {
		members[select_sub_num]->plus_vote_check_num(temp->back_RRN(), num - 1);
		cout << "Request processed successfully!" << endl; fflush(stdout);
		return;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Vote casting failed!" << endl; fflush(stdout);
		return;
	}
}

/////////////2.7
void join_group(int select_mem_num, member** members, member** temp, group** groups, int* group_num, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = false;
	bool test = true;

	int select_group = 0;

	string group_name;
	cout << "Seleceted Menu: 2.7 Join Group" << " " << endl; fflush(stdout);

	// 그룹 목록 출력 함수 넣기

	if (!loadMode)
	{
		cout << "Group Name to Join: "; fflush(stdout);
		cin >> group_name;
		inLogWrite << "2" << " " << "7" << " " << group_name << " " << endl; fflush(stdout);
	}
	else {
		group_name = tokens[2];
		cout << "Group Name to Join: " << group_name << endl; fflush(stdout);
	}

	for (int i = 0; i < *group_num; i++)
	{
		if (group_name == groups[i]->back_group_name())
		{
			valid_test = true;
			select_group = i;
			break;
		}
	}

	if ((*temp)->back_info() != 0) test = false;
	if (test == false) valid_test = false;

	// Valid Case
	if (valid_test == true) {

		group_member* temp1 = new group_member((**temp), group_name);
		member* temp2;

		temp2 = (*temp);
		(*temp) = temp1;

		delete temp2;
		members[select_mem_num] = (*temp);

		groups[*group_num]->group_put((*temp)->back_RRN(), (*temp)->back_ID(), groups[*group_num]->back_group_check_num());
		return;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Group join Failed" << endl; fflush(stdout);
		return;
	}
}

/////////////2.8
void create_group(int select_mem_num,  member** members, member** temp, group** groups, int* group_num, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;
	bool test = true;

	string group_name;
	cout << "Seleceted Menu: 2.8 Create a Group" << " " << endl; fflush(stdout);

	// 그룹 목록 출력 함수 넣기

	if (!loadMode)
	{
		cout << "Group Name to Create: "; fflush(stdout);
		cin >> group_name;
		inLogWrite << "2" << " " << "8" << " " << group_name << " " << endl; fflush(stdout);
	}
	else {
		group_name = tokens[2];
		cout << "Group Name to Create: " << group_name << endl; fflush(stdout);
	}

	for (int i = 0; i < *group_num; i++)
	{
		if (group_name == groups[i]->back_group_name())
		{
			valid_test = false;
			break;
		}
	}

	if ((*temp)->back_info() != 0) test = false;
	if (test == false) valid_test = false;

	// Valid Case
	if (valid_test == true) {

		group_leader* temp1 = new group_leader((**temp), group_name);
		member* temp2;

		temp2 = (*temp);
		(*temp) = temp1;

		delete temp2;

		members[select_mem_num] = (*temp);

		groups[*group_num] = new group((*temp), group_name);

		groups[*group_num]->group_put((*temp)->back_RRN(), (*temp)->back_ID(), 0);
		*group_num++;
		return;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Group create Failed" << endl; fflush(stdout);
		return;
	}
}