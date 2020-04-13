#include "default.h"
using namespace std;

class member {
	string RRN, ID, password;

public:

	member(string put_RRN, string put_ID, string put_password); // 생성자

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
// 로그인되어 사용하고 있는 사용자의 클래스 포인터는 temp에 저장해놓는다.
// temp != NULL 이라면 로그인 되어있는 상태이므로, 추가적인 로그인 불가능!
// 배열은 check 할 때 for 문을 위해 사용한다.

class vote_member {
	string vote_topic;
	string vote_sub; // 투표별 항목 개수 이거를 vote_num 배열 개수로 넘겨준다.
	int vote_num[10] = { 0, }; // 투표 항목별 득표 현황 ++ --로 득표 현황 게시
	string vote_check[50]; // 투표한 회원의 주민번호 등록해놓기
	int vote_check_num = 0; // 처음에 0으로 되어있다가 항목에 vote 하는 member가 생기면++

public:

	vote_member(string vote_topic, string vote_sub);

	string back_vote_topic() const;
	string back_vote_sub() const; // 투표별 항목 개수 반환
	string back_RRN(int i) const;
	int back_vote_check_num() const;
	int back_vote_num(int i) const; // 항목 마다 투표받은 개수 반환
	void plus_vote_check_num(string RRN, int vote);
};

string vote_member::back_vote_topic() const { return vote_topic; }
string vote_member::back_vote_sub() const { return vote_sub; }
string vote_member::back_RRN(int i) const { return vote_check[i]; }
int vote_member::back_vote_num(int i) const { return vote_num[i]; }
int vote_member::back_vote_check_num() const { return vote_check_num; }

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
	int num = 1; // 파일 실행횟수
	int loadMode;
	ofstream inLogWrite;
	ifstream inLogRead;
	string tokens[4], line;
	stringstream stream;
	int nTokens = 0; //number of tokens in string
	int tmp = 10;

	int mem_num = 0; // 현재 존재하는 member의 개수가 몇 개 인지 (delete 등 for 문에서 사용)
	int sub_num = 0; // 현재 존재하는 vote의 개수가 몇 개 인지
	member* members[50];
	vote_member* vote_members[100];
	member* temp = NULL; // log_in_check 용

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

		// 메뉴 구분 및 해당 연산 수행
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
				inLogWrite << menu << endl; // log.txt 에 menu 값 기록
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


//1. 회원가입
void join(member** members, int* mem_num, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)

{
	bool valid_test = true;
	bool let = true;

	//회원가입에대한 정보를 입력받을 문자열변수
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

//2. 회원탈퇴
void unjoin(member** members, int* mem_num, member** temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;
	bool let = false;
	int select_member_num;

	//회원에대한 정보를 입력받을 문자열변수
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
			members[i] = members[i + 1]; // 마지막에 있던 자리에 포인터 있는데 등록할 때 다른 주소를 덧씌우면 되겠지?

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

//3. 로그인
void login(member** members, int* mem_num, member** temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;

	bool let = false;

	int select_member_num;

	//로그인 정보를 입력받을 문자열변수
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

//4. 로그아웃
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

// 5. 투표 삭제
void delete_vote(vote_member** members, int* sub_num, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;
	bool let = false;
	int select_member_num;

	//회원가입에대한 정보를 입력받을 문자열변수
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

//6. 투표 추가
void add_vote(vote_member** members, int* sub_num, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	bool valid_test = true;

	// 투표에 대한 정보를 입력받을 문자열변수
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

//7. 투표 출력
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

//8. 투표하기
void cast_vote(vote_member** members, int sub_num, member* temp, int loadMode, ifstream & inLogRead, ofstream & inLogWrite, string *tokens, int nTokens)
{
	string vote_topic; // 투표할 투표 주제
	string num_item; // 투표할 주제의 투표할 항목
	int select_sub_num = 0;
	int num = 0;
	bool valid_test = true; // 현재 로그인 되어있는지
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
	string vote_sub; // 투표별 항목 개수 이거를 vote_num 배열 개수로 넘겨준다.
	int vote_num[10] = { 0, }; // 투표 항목별 득표 현황 ++ --로 득표 현황 게시
	string vote_check[50]; // 투표한 회원의 주민번호 등록해놓기
	int vote_check_num = 0; // 처음에 0으로 되어있다가 항목에 vote 하는 member가 생기면++

public:

vote_member(string vote_topic, string vote_sub);

	string back_vote_topic() const;
	string back_vote_sub() const; // 투표별 항목 개수 반환
	string back_RRN(int i) const;
	int back_vote_check_num() const;
	int back_vote_num(int i) const; // 항목 마다 투표받은 개수 반환
	void plus_vote_check_num(string RRN, int vote);
};

string vote_member::back_vote_topic() const { return vote_topic; }
string vote_member::back_vote_sub() const { return vote_sub; }
string vote_member::back_RRN(int i) const { return vote_check[i]; }
int vote_member::back_vote_num(int i) const { return vote_num[i]; }
int vote_member::back_vote_check_num() const { return vote_check_num; }

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
}*/