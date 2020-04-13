#include "default.h"
using namespace std;

class member {
	string RRN, ID, password;

public:

	member(string put_RRN, string put_ID, string put_password); // ������

	string back_RRN() const;
	string back_ID() const;
	string back_password() const;
};

string member::back_RRN() const { return RRN; }
string member::back_ID() const { return ID; }
string member::back_password() const { return password; }

member::member(string put_RRN, string put_ID, string put_password)
{
	RRN = put_RRN;
	ID = put_ID;
	password = put_password;
}
// �α��εǾ� ����ϰ� �ִ� ������� Ŭ���� �����ʹ� temp�� �����س��´�.
// temp != NULL �̶�� �α��� �Ǿ��ִ� �����̹Ƿ�, �߰����� �α��� �Ұ���!
// �迭�� check �� �� for ���� ���� ����Ѵ�.

class vote_member {
	string vote_topic;
	string vote_sub; // ��ǥ�� �׸� ���� �̰Ÿ� vote_num �迭 ������ �Ѱ��ش�.
	int vote_num[10] = { 0, }; // ��ǥ �׸� ��ǥ ��Ȳ ++ --�� ��ǥ ��Ȳ �Խ�
	string vote_check[50]; // ��ǥ�� ȸ���� �ֹι�ȣ ����س���
	int vote_check_num = 0; // ó���� 0���� �Ǿ��ִٰ� �׸� vote �ϴ� member�� �����++

public:

	vote_member(string vote_topic, string vote_sub);

	string back_vote_topic() const;
	string back_vote_sub() const; // ��ǥ�� �׸� ���� ��ȯ
	string back_RRN(int i) const;
	int back_vote_check_num() const;
	int back_vote_num(int i) const; // �׸� ���� ��ǥ���� ���� ��ȯ
	void plus_vote_check_num(string RRN, int vote);
};

string vote_member::back_vote_topic() const { return vote_topic; }
string vote_member::back_vote_sub() const { return vote_sub; }
string vote_member::back_RRN(int i) const { return vote_check[i]; }
int vote_member::back_vote_num(int i) const { return vote_num[i]; }
int vote_member::back_vote_check_num() const { return vote_check_num; }

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


void join(member** members, int* mem_num, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);
void logout(member** temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);
void unjoin(member** members, int* mem_num, member** temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);
void login(member** members, int* mem_num, member** temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);

void delete_vote(vote_member** members, int* sub_num, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);
void add_vote(vote_member** members, int* sub_num, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);
void view_vote(vote_member** members, int sub_num, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);
void cast_vote(vote_member** members, int sub_num, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens);


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
void printMenu2(int num)
{
	cout << "\n\n=======================" << endl; fflush(stdout);
	cout << "Num:" << num << endl; fflush(stdout);
	cout << "n=======================" << endl; fflush(stdout);
	cout << "1. Register as a Member" << endl; fflush(stdout);
	cout << "2. Unsubscribe from System" << endl; fflush(stdout);
	cout << "3. Login" << endl; fflush(stdout);
	cout << "4. Logout" << endl; fflush(stdout);
	cout << "5. Delete Existing Vote Item" << endl; fflush(stdout);
	cout << "6. Add a New Vote Item" << endl; fflush(stdout);
	cout << "7. List All Vote Items" << endl; fflush(stdout);
	cout << "8. Cast a Vote" << endl; fflush(stdout);
	cout << "9. Program Exit" << endl; fflush(stdout);
	cout << "=======================" << endl; fflush(stdout);
	cout << "Select Menu:"; fflush(stdout);
}
void clearTokens(string * tokens)
{
	for (int i = 0; i < 4; i++)
		tokens[i].clear();
}

void doTask()
{

	int menu = 0;
	int num = 1; // ���� ����Ƚ��
	int loadMode;
	ofstream inLogWrite;
	ifstream inLogRead;
	string tokens[4], line;
	stringstream stream;
	int nTokens = 0; //number of tokens in string
	int tmp = 10;

	int mem_num = 0; // ���� �����ϴ� member�� ������ �� �� ���� (delete �� for ������ ���)
	int sub_num = 0; // ���� �����ϴ� vote�� ������ �� �� ����
	member* members[50];
	vote_member* vote_members[100];
	member* temp = NULL; // log_in_check ��

	loadMode = printMenu1(); // NO : 0 , YES : 1
	if (!loadMode) {
		inLogWrite.open(COMMAND_LOG_FILE_NAME, ios::out);
	}
	else {
		inLogRead.open(COMMAND_LOG_FILE_NAME, ios::in); //read mode
		inLogWrite.open(COMMAND_LOG_FILE_NAME, ios::in | ios::app); //concat without truncation
	}

	while (1)
	{
		printMenu2(num++);
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
					menu = atoi(line.c_str());
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
				//Read all tokens(seperated by " ")
				while (stream >> tokens[nTokens])
					nTokens++;
				stream.clear();
				menu = atoi(tokens[0].c_str());
				cout << menu << endl; fflush(stdout);
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
			menu = atoi(line.c_str());
		}

		// �޴� ���� �� �ش� ���� ����
		switch (menu)
		{
		case 1:
		{
			join(members, &mem_num, temp, loadMode, inLogRead, inLogWrite, tokens, nTokens);
			break;
		}
		case 2:
		{
			unjoin(members, &mem_num, &temp, loadMode, inLogRead, inLogWrite, tokens, nTokens);
			break;
		}
		case 3:
		{
			login(members, &mem_num, &temp, loadMode, inLogRead, inLogWrite, tokens, nTokens);
			break;
		}
		case 4:
		{
			logout(&temp, loadMode, inLogRead, inLogWrite, tokens, nTokens);
			break;
		}
		case 5:
		{
			delete_vote(vote_members, &sub_num, temp, loadMode, inLogRead, inLogWrite, tokens, nTokens);
			break;
		}
		case 6:
		{
			add_vote(vote_members, &sub_num, temp, loadMode, inLogRead, inLogWrite, tokens, nTokens);
			break;
		}
		case 7:
		{
			view_vote(vote_members, sub_num, temp, loadMode, inLogRead, inLogWrite, tokens, nTokens);
			break;
		}
		case 8:
		{
			cast_vote(vote_members, sub_num, temp, loadMode, inLogRead, inLogWrite, tokens, nTokens);
			break;
		}
		case 9:
		{

			inLogWrite.close();
			return;

		}
		default:
			cout << "Selected Menu: Undefined menu selection" << endl; fflush(stdout);
			if (!loadMode) {
				inLogWrite << menu << endl; // log.txt �� menu �� ���
				continue;
			}
			break;

		}
		if (!loadMode && (menu != 4 && menu != 7)) {
			getchar();
		}
	}
	return;
}


//1. ȸ������
void join(member** members, int* mem_num, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)

{
	bool valid_test = true;
	bool let = true;

	//ȸ�����Կ����� ������ �Է¹��� ���ڿ�����
	string RRN, ID, password;
	cout << "Selected Menu: 1. Register as a Member" << endl; fflush(stdout);

	if (!loadMode)
	{
		cout << "Resident Registration Number:"; fflush(stdout);
		cin >> RRN;
		cout << "ID:"; fflush(stdout);
		cin >> ID;
		cout << "Password:"; fflush(stdout);
		cin >> password;
		inLogWrite << "1 " << RRN << " " << ID << " " << password << " " << endl;


	}
	else {
		RRN = tokens[1]; ID = tokens[2]; password = tokens[3];
		cout << "1. Resident Registration Number: " << RRN << endl; fflush(stdout);
		cout << "ID: " << ID << endl; fflush(stdout);
		cout << "Password:" << password << endl; fflush(stdout);
	}

	for (int i = 0; i < *mem_num; i++)
	{
		if (RRN == members[i]->back_RRN() || ID == members[i]->back_ID())
			let = false;
	}

	if (temp != NULL) valid_test = false;
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

//2. ȸ��Ż��
void unjoin(member** members, int* mem_num, member** temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;
	bool let = false;
	int select_member_num;

	//ȸ�������� ������ �Է¹��� ���ڿ�����
	string ID, password;
	cout << "Selected Menu: 2. Unsubscribe from System" << endl; fflush(stdout);

	if (!loadMode)
	{
		cout << "ID:"; fflush(stdout);
		cin >> ID;
		cout << "Password:"; fflush(stdout);
		cin >> password;
		inLogWrite << "2 " << ID << " " << password << " " << endl;


	}
	else {
		ID = tokens[1]; password = tokens[2];
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

	if (*temp == NULL) valid_test = false;
	if (let == false) valid_test = false;

	// Valid Case
	if (valid_test == true) {
		(*temp) = NULL;
		delete members[select_member_num];

		for (int i = select_member_num; i < *mem_num - 1; i++)
			members[i] = members[i + 1]; // �������� �ִ� �ڸ��� ������ �ִµ� ����� �� �ٸ� �ּҸ� ������� �ǰ���?

		(*mem_num)--;

		cout << "Unsubscribe Done!" << endl; fflush(stdout);
		return;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Unsubscribe Fail" << endl; fflush(stdout);
		return;
	}
}

//3. �α���
void login(member** members, int* mem_num, member** temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;

	bool let = false;

	int select_member_num;

	//�α��� ������ �Է¹��� ���ڿ�����
	string ID, password;
	cout << "Selected Menu: 3. Login" << endl; fflush(stdout);

	if (!loadMode)
	{
		cout << "ID: "; fflush(stdout);
		cin >> ID;
		cout << "password:"; fflush(stdout);
		cin >> password;
		inLogWrite << "3 " << ID << " " << password << " " << " " << endl;
	}
	else {
		ID = tokens[1]; password = tokens[2];
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

	if (*temp != NULL) valid_test = false;
	if (let == false) valid_test = false;

	// Valid Case
	if (valid_test == true) {
		*temp = members[select_member_num];
		cout << "Login success" << endl; fflush(stdout);
		return;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Login Fail" << endl; fflush(stdout);
		return;
	}
}

//4. �α׾ƿ�
void logout(member** temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;

	cout << "Selected Menu: 4. Logout" << endl; fflush(stdout);

	if (!loadMode)
	{
		inLogWrite << "4" << endl;
	}
	else {

	}

	if (*temp == NULL) valid_test = false;

	// Valid Case
	if (valid_test == true) {
		*temp = NULL;
		cout << "Logout success" << endl; fflush(stdout);
		return;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Logout Fail" << endl; fflush(stdout);
		return;
	}

}

// 5. ��ǥ ����
void delete_vote(vote_member** members, int* sub_num, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;
	bool let = false;
	int select_member_num;

	//ȸ�����Կ����� ������ �Է¹��� ���ڿ�����
	string vote_topic;
	string num_item;
	cout << "Selected Menu: 5. Delete Existing Vote Item" << endl; fflush(stdout);

	if (!loadMode)
	{
		cout << "Vote Subject to Delete:"; fflush(stdout);
		cin >> vote_topic;
		inLogWrite << "5 " << vote_topic << " " << endl;
	}
	else {
		vote_topic = tokens[1];
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

//6. ��ǥ �߰�
void add_vote(vote_member** members, int* sub_num, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;

	// ��ǥ�� ���� ������ �Է¹��� ���ڿ�����
	string vote_topic;
	string num_item;
	cout << "Selected Menu: 6. Add a New Vote Item" << endl; fflush(stdout);

	if (!loadMode)
	{
		cout << "Vote subject:"; fflush(stdout);
		cin >> vote_topic;
		cout << "Number of Vote Items:"; fflush(stdout);
		cin >> num_item;

		inLogWrite << "6 " << vote_topic << " " << num_item << " " << endl;
	}
	else {
		vote_topic = tokens[1]; num_item = tokens[2];
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

//7. ��ǥ ���
void view_vote(vote_member** members, int sub_num, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;
	int num;

	cout << "Selected Menu: 7. List All Vote Items." << endl; fflush(stdout);

	if (!loadMode)
	{
		inLogWrite << "7 " << endl;
	}
	else {

	}

	if (temp == NULL) valid_test = false;

	// Valid Case
	if (valid_test == true) {

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
		return;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Not Login!" << endl; fflush(stdout);
		return;
	}

}

//8. ��ǥ�ϱ�
void cast_vote(vote_member** members, int sub_num, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	string vote_topic; // ��ǥ�� ��ǥ ����
	string num_item; // ��ǥ�� ������ ��ǥ�� �׸�
	int select_sub_num = 0;
	int num = 0;
	bool valid_test = true; // ���� �α��� �Ǿ��ִ���
	bool let = false;
	cout << "Selected Menu: 8. Cast a Vote" << endl; fflush(stdout);

	if (!loadMode)
	{
		cout << "Vote subject:"; fflush(stdout);
		cin >> vote_topic;
		cout << "Vote for:"; fflush(stdout);
		cin >> num_item;

		inLogWrite << "8 " << vote_topic << " " << num_item << " " << endl;
	}
	else {
		vote_topic = tokens[1]; num_item = tokens[2];
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
		members[select_sub_num]->plus_vote_check_num(temp->back_RRN(), num-1);
		cout << "Request processed successfully!" << endl; fflush(stdout);
		return;
	}

	//unValid Case
	if (valid_test == false) {
		cout << "Vote casting failed!" << endl; fflush(stdout);
		return;
	}
}

/*

class vote_member {
	string vote_topic;
	string vote_sub; // ��ǥ�� �׸� ���� �̰Ÿ� vote_num �迭 ������ �Ѱ��ش�.
	int vote_num[10] = { 0, }; // ��ǥ �׸� ��ǥ ��Ȳ ++ --�� ��ǥ ��Ȳ �Խ�
	string vote_check[50]; // ��ǥ�� ȸ���� �ֹι�ȣ ����س���
	int vote_check_num = 0; // ó���� 0���� �Ǿ��ִٰ� �׸� vote �ϴ� member�� �����++

public:

vote_member(string vote_topic, string vote_sub);

	string back_vote_topic() const;
	string back_vote_sub() const; // ��ǥ�� �׸� ���� ��ȯ
	string back_RRN(int i) const;
	int back_vote_check_num() const;
	int back_vote_num(int i) const; // �׸� ���� ��ǥ���� ���� ��ȯ
	void plus_vote_check_num(string RRN, int vote);
};

string vote_member::back_vote_topic() const { return vote_topic; }
string vote_member::back_vote_sub() const { return vote_sub; }
string vote_member::back_RRN(int i) const { return vote_check[i]; }
int vote_member::back_vote_num(int i) const { return vote_num[i]; }
int vote_member::back_vote_check_num() const { return vote_check_num; }

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
}*/