#include "default.h"
using namespace std;

// �α��εǾ� ����ϰ� �ִ� ������� Ŭ���� �����ʹ� temp�� �����س��´�.
// temp != NULL �̶�� �α��� �Ǿ��ִ� �����̹Ƿ�, �߰����� �α����� �Ұ����ϴ�.
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

	// ��Ÿ member �Լ�
};

class group_member : public member {
	
	string group_name;

public:
	string back_group_name() const { return group_name; }
	int back_info() const { return info; }

	group_member() : member() { info = 1; }
	group_member(const member& put_member, string put_group_name) : member(put_member) { info = 1; group_name = put_group_name;}
	~group_member() {}

	// ��Ÿ group_member �Լ�

};




class group_leader : public member {

	string group_name;

public:
	string back_group_name() const { return group_name; }
	int back_info() const { return info; }

	group_leader() : member() { info = 2; }
	group_leader(const member& put_member, string put_group_name) : member(put_member) { info = 2; group_name = put_group_name;}
	~ group_leader() {}

	// ��Ÿ group_leader �Լ�

};

class vote_member {
	string vote_topic;
	string vote_sub; // ��ǥ�� �׸� ���� �̰Ÿ� vote_num �迭 ������ �Ѱ��ش�
	string vote_check[50]; // ��ǥ�� ȸ���� �ֹι�ȣ ����س���

	int vote_num[MAX_NUM_VOTEITEM] = { 0, }; // ��ǥ �׸� ��ǥ ��Ȳ ++ --�� ��ǥ ��Ȳ �Խ�
	int vote_check_num = 0; // ó���� 0���� �Ǿ��ִٰ� �׸� vote �ϴ� member�� �����++

public:
	vote_member(string vote_topic, string vote_sub);

	string back_vote_topic() const { return vote_topic; } // ��ǥ ���� ��ȯ
	string back_vote_sub() const { return vote_sub; } // ��ǥ�� �׸� ���� ��ȯ
	string back_RRN(int i) const { return vote_check[i]; } // �ߺ���ǥ���� Ȯ���ϱ� ���� RRN Ž��

	int back_vote_check_num() const { return vote_check_num; } // ��ǥ ������ ��ǥ�� ȸ�� �� ��ȯ
	int back_vote_num(int i) const { return vote_num[i]; } // ��ǥ �׸� ���� ��ǥ���� ���� ��ȯ

	void plus_vote_check_num(string RRN, int vote); // vote �� ���� vote �߰�
};

vote_member::vote_member(string put_vote_topic, string put_vote_sub) // ���� Token[0] [1] [2].. �ֱ�
{
	vote_topic = put_vote_topic;
	vote_sub = put_vote_sub;
}

void vote_member::plus_vote_check_num(string RRN, int vote) // vote -> ��ǥ�� �׸� ��ȣ
{
	vote_check[vote_check_num] = RRN;
	vote_check_num++;
	vote_num[vote]++;
}

class group {
	member* leader;
	string group_name, group_RRN[MAX_GROUP_MEMBER], group_id[MAX_GROUP_MEMBER];
	vote_member* vote_members[MAX_GROUP_VOTE]; // �ش� �׷� ��ǥ �迭
	int num_vote; // �ش� group�� �����ϴ� ��ǥ�� ���� ����
	int group_check_num; // �ش� group�� �����ϴ� �ο� ��

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
// �̹� assn ���� token�� �ִ� ������ 6���� Ȯ��ȴ�.

void doTask()
{
	int menu1 = 0; int menu2 = 0;
	int num = 1; // ���� ����Ƚ��
	int loadMode;
	ofstream inLogWrite;
	ifstream inLogRead;
	string tokens[6], line;
	stringstream stream;
	int nTokens = 0; //number of tokens in string
	int tmp = 10;

	int mem_num = 0; // ���� �����ϴ� member�� ������ �� �� ���� (delete �� for ������ ���)
	int sub_num = 0; // ���� �����ϴ� vote�� ������ �� �� ����
	int group_num = 0; // ���� �����ϴ� group�� ������ �� �� ����

	int invalid = 0; // invalid selection�� ���� ��� 1 �ƴҰ�� 0
	int select_member = 0; // login �� ����� �迭 �ε��� ����
	int is_login = 0; // login �Ǿ��ִٸ� 1, logout �Ǿ��ִٸ� 0

	member* members[MAX_NUM_MEMBER]; // �Ϲݸ�� + �׷��� + �׷츮�� �迭
	vote_member* vote_members[MAX_NUM_VOTE]; // �Ϲ���ǥ �迭 , �׷���ǥ �迭�� Group class �ȿ��� ���� �����Ѵ�
	group* groups[MAX_GROUP_MEMBER]; // �׷� �迭

	member* temp0 = NULL; // member�� log_in_check ������ ����Ѵ�.
	group_member* temp1 = NULL; // group_member�� log_in_check ������ ����Ѵ�.
	group_leader* temp2 = NULL; // group_leader�� log_in_check ������ ����Ѵ�.

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
			if (line == "") // loadMode�� �������� �� �� �ִ� ǥ�� " "
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
					menu1 = atoi(line.c_str()); // 1���� �ص� �ǳ�?
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
				menu1 = atoi(tokens[0].c_str()); // ************** �츮�� ���⼭ 2���� �о� �޴��� ����
				menu2 = atoi(tokens[1].c_str()); // ************** �츮�� ���⼭ 2���� �о� �޴��� ����
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

		// �޴� ���� �� �ش� ���� ����
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
					// �α��� �� member�� info �� 0���� 1���� 2���� Ȯ���ϰ�, �˸��� temp�� �־��ش�.
				
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
						inLogWrite << menu1 << " " << menu2 << endl; // log.txt �� menu �� ���
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
						inLogWrite << menu1 << " " << menu2 << endl; // log.txt �� menu �� ���
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
						inLogWrite << menu1 << " " << menu2 << endl; // log.txt �� menu �� ���
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
						inLogWrite << menu1 << " " << menu2 << endl; // log.txt �� menu �� ���
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

	//ȸ�����Կ����� ������ �Է¹��� ���ڿ�����
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

	//�α��� ������ �Է¹��� ���ڿ�����
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
		inLogWrite << menu1 << " " << menu2 << endl; // menu2 �ڿ� �����̽��� �ȳ־ �Ǵ��� Ȯ���ϰ� �������� ���� ��!
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

	//ȸ�������� ������ �Է¹��� ���ڿ�����
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
			members[i] = members[i + 1]; // �������� �ִ� �ڸ��� ������ �ִµ� ����� �� �ٸ� �ּҸ� ������� �ǰ���?

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

	//ȸ�����Կ����� ������ �Է¹��� ���ڿ�����
	string vote_topic;
	string num_item;
	cout << "Selected Menu: "<<menu1<<"."<<menu2<<" Delete Existing Vote Item" << endl; fflush(stdout);


	view_vote(members, *sub_num, menu1, menu2, temp, loadMode, inLogRead, inLogWrite, tokens, nTokens); // ��ǥ ��� ���

	if (!loadMode)
	{
		cout << "Vote Subject to Delete:"; fflush(stdout);
		cin >> vote_topic;
		inLogWrite << menu1 << " " <<menu2<< " 0 " << vote_topic << " " << endl; // " 0 " �κ� ���� �׷쿡�� �����ϱ�!
	}
	else {
		vote_topic = tokens[2];
		cout << "Vote Subject to Delete" << vote_topic << endl; fflush(stdout);
	}

	for (int i = 0; i < *sub_num; i++) // �ش� ��ǥ�� �����ϴ��� üũ
	{
		if (vote_topic == members[i]->back_vote_topic())
		{
			select_member_num = i;
			let = true;
			break;
		}
	}

	if (let == false) valid_test = false;
	if (temp == NULL) valid_test = false; // ������ ��û�� ȸ���� �α��� �Ǿ��ִ��� üũ

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

	// ��ǥ�� ���� ������ �Է¹��� ���ڿ�����
	string vote_topic;
	string num_item;
	cout << "Selected Menu: "<<menu1<<"."<<menu2<<" Add a New Vote Item" << endl; fflush(stdout);

	view_vote(members, *sub_num, menu1, menu2, temp, loadMode, inLogRead, inLogWrite, tokens, nTokens); // ��ǥ ��� ���

	if (!loadMode)
	{
		cout << "Vote subject:"; fflush(stdout);
		cin >> vote_topic;
		cout << "Number of Vote Items:"; fflush(stdout);
		cin >> num_item;

		inLogWrite << menu1 << " " << menu2 << " 0 " << vote_topic << " " << num_item << " " << endl; // " 0 " �κ� ���� �׷쿡�� �����ϱ�
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
	string vote_topic; // ��ǥ�� ��ǥ ����
	string num_item; // ��ǥ�� ������ ��ǥ�� �׸�
	int select_sub_num = 0;
	int num = 0;
	bool valid_test = true; // ���� �α��� �Ǿ��ִ���
	bool let = false;
	cout << "Selected Menu: "<<menu1<<"."<<menu2<<" Cast a Vote" << endl; fflush(stdout);

	view_vote(members, sub_num, menu1, menu2, temp, loadMode, inLogRead, inLogWrite, tokens, nTokens); // ��ǥ ��� ���

	if (!loadMode)
	{
		cout << "Vote subject:"; fflush(stdout);
		cin >> vote_topic;
		cout << "Vote for:"; fflush(stdout);
		cin >> num_item;

		inLogWrite << menu1<<" "<<menu2<<" 0 " << vote_topic << " " << num_item << " 0 " << endl; // " 0 ' �κе� ���� �׷쿡�� ��ġ��
	}
	else {
		vote_topic = tokens[2]; num_item = tokens[3];
		cout << "Vote subject: " << vote_topic << endl; fflush(stdout);
		cout << "Vote for: " << num_item << endl; fflush(stdout);
	}

	if (temp == NULL) valid_test = false; // �α��� �Ǿ����� ���� ���

	if (valid_test == true) {
		for (int i = 0; i < sub_num; i++) // �Է� ���� ��ǥ ������ �����ϴ��� üũ
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

		for (int j = 0; j < members[select_sub_num]->back_vote_check_num(); j++) // �̹� ��ǥ�� ȸ������ üũ num = int vote_sub
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

	// �׷� ��� ��� �Լ� �ֱ�

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

	// �׷� ��� ��� �Լ� �ֱ�

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