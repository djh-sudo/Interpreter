#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<set>
#define BUFFER 4096*4096		//��������С
#define FLAG 9999999			//����ֵ����
using namespace std;

/*******************************������*****************************/
typedef class SYM {
private:
	string name;
	string type;
	int level;
	string value;
	char* location;
	long int line;
public:
	SYM() {}
	SYM(string name, string type = "void", int level = 0, string value = "") {
		this->name = name;
		this->type = type;
		this->level = level;
		this->value = value;
		location = NULL;
	}
	string getName() {
		return this->name;
	}
	string getType() {
		return this->type;
	}
	int get_Level() {
		return this->level;
	}
	string get_value() {
		return this->value;
	}
	void modifyValue(string value) {
		this->value = value;
	}
	void modifyType(string type) {
		this->type = type;
	}
	void modifyLevel(int level) {
		this->level = level;
	}
	void modifyLocation(char* loc) {
		this->location = loc;
	}
	char* getLocation() {
		return this->location;
	}
	void modifyLine(long int line) {
		this->line = line;
	}
	long int get_Line() {
		return this->line;
	}
}Symbol;

/*******************************�õ��ĸ�������*****************************/
void inicializeFunction();					//��ʼ��ϵͳ����
string trim(string s);						//ȥ���ַ���һͷһβ����
bool Compare(Symbol s1, Symbol s2);			//�Ƚ����������Ƿ����
bool is_contain(Symbol s1);					//�жϷ��ű����Ƿ�����˲��ҵķ���
void syntaxError(int k, long int l = 0, string s = "");//���ݴ��������׳��쳣
int Find(string name, int level);			//�ڵ�ǰ�����еȼ��²��ұ�����name
string tokenType(int Type);					//�����ε�typeתΪ��Ӧ���ַ���
bool is_alpha(char c);						//�ж��ַ�c�Ƿ�ֻ������ĸ���»���
bool is_alpha(string s);					//�ж��ַ���s�Ƿ�ֻ������ĸ���»���(����)
bool is_num(string s);						//�ж��ַ���s�Ƿ�ֻ��������
bool is_num(char c);						//�ж��ַ�c�Ƿ�ֻ��������(����)
/*******************************�ؼ��㷨����*****************************/
void nextToken();							//�޸�current_token��ֵ
void checkMatch(string s);					//����ַ��Ƿ�ƥ�䲢��ȡ��һ��token
double expression();						//������ʽ��ֵ
double factor();							//�������ӵ�ֵ
double term();
double function(vector<string>pre);			//���㺯����ֵ
int expression_bool();						//����bool���͵�ֵ
int AND();
int OR();
char* Skip();								//��������ִ�е�����
double statement();							//��������

/*******************************�ؼ�������*****************************/
enum sys { ID, STRING, REGISTERED, OPERATOR, NUM, ID_FUN };
/*******************************ȫ�ֱ���*****************************/
char* src;							//ȫ�ֽ���ָ��
string current_token;				//��ǰtokenֵ
string current_type;				//��ǰtoken������
int current_level = 0;				//��ǰ���м���
long int line = 1;					//�к�
int state = 0;						//״̬
int sys = -1;						//�ؼ�������
double return_val = 0;				//��������ֵ
vector<Symbol>symbolTab;			//���ű�
set<string>registeredFunction;		//ע�ắ����
char* ending;						//����β��������û��return���������ѭ��
/*******************************��������ģ��*****************************/
void inicializeFunction() {										//��ʼ��
	registeredFunction.clear();
	symbolTab.push_back(Symbol("print", "function_name", 0));	//��ӡ����
	symbolTab.push_back(Symbol("exit", "function_name", 0));	//�˳�����
	symbolTab.push_back(Symbol("input", "function_name", 0));	//���뺯��
	for (int i = 0; i < symbolTab.size(); i++) {
		registeredFunction.insert(symbolTab[i].getName());
	}
}

string trim(string s) {//ȥ���ַ�����β�ַ�
	return s.substr(1, s.size() - 2);
}

bool Compare(Symbol s1, Symbol s2) {//�Ƚ�s1��s2�Ƿ�����ͬһ���ͱ���
	if ((s1.getName() == s2.getName()) && s1.get_Level() == s2.get_Level())
		return true;
	else
		return false;
}

bool is_contain(Symbol s1) {//��ѯ�ַ������Ƿ��������s1
	for (int i = 0; i < symbolTab.size(); i++) {
		if (Compare(symbolTab[i], s1))
			return true;
	}
	return false;
}

void syntaxError(int k, long int l,string s) {//����ӹܺ���
	switch (k)
	{
	case 1: {
		cout << "Error [Line:" << line << "] " << s << " is invalid symbol." << endl;
		exit(1);
	}
	case 2: {// ����ע��ȱ�ٱ߽�
		cout << "Error [Line:" << line << "] Multi-line comments are missing boundaries." << endl;
		exit(1);
	}
	case 3: {// �ַ���ȱ�ٱ߽�
		cout << "Warning [Line:" << line << "] String is missing boundaries." << endl;
		exit(1);
	}
	case 4: {
		//ע�Ͳ����Ϲ淶
		cout << "Error [Line:" << line << "] The comment does not meet the specification." << endl;
		//exit(1);
	}
	case 5: {//ȱ��ƥ�����
		cout << "Error [Line:" << line << "] Expected the symbol '" << s << "',but not have." << endl;
		exit(1);
	}
	case 6: {
		cout << "Error [Line:" << line << "] Divisor cannot be 0." << endl;
		exit(1);
	}
	case 7: {
		cout << "Error [Line:" << line << "] " << s << " defination is duplicated!" << endl;
		exit(1);
	}
	case 8:
	{
		cout << "Error [Line:" << line << "] function '" << s << "' is not defined!" << endl;
		exit(1);
	//�Ҳ�������def
	}
	case 9: {
		cout << "Error [Line:" << line << "] " << s << " is not inicialized or can't find." << endl;
		exit(1);
	}
	case 10: {
		cout << "Warning [Line:" << line << "] " << s << " is not used." << endl;
	}
	case 11: {
		cout << "Error [Line:" << line << "] The formal and actual parameters do not match." << endl;
		exit(1);
	}
	case 12: {
		cout << "Error [Line:" << line << "] Can't reload the registered function " << s << endl;
		exit(1);
	}
	case 13: {
		cout << "Warning [Line:" << line << "] function with no statement 'return'. "  << endl;
	}
	default:
		break;
	}
}

int Find(string name,int level) {//�������ֲ���Tab�Ƿ����
	for (int i = 0; i < symbolTab.size(); i++) {
		if (symbolTab[i].getName() == name) {
			if (symbolTab[i].get_Level() == level) {
				return i;
			}
			else if (symbolTab[i].getType() == "function_name") {//����ȫ��ֻ��һ��
				return i;
			}
		}
	}
	return -1;
}

string tokenType(int Type) {
	switch (Type)
	{
	case 0:return "ID";
	case 1:return "string";
	case 2:return "registered";
	case 3:return "operator";
	case 4:return "number";
	case 5:return "function";
	default:return "";
	}
}

bool is_alpha(char c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'z') || c == '_')
		return true;
	else return false;
}

bool is_num(char c) {
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}

bool is_alpha(string s) {
	if (s.size() == 1) {
		if ((s >= "a" && s <= "z") || (s >= "A" && s <= "Z") || s == "_")
			return true;
	}
	return false;
}

bool is_num(string s) {
	if (s.size() == 1) {
		if (s >= "0" && s <= "9")
			return true;
	}
	return false;
}

/*******************************���ĺ���ģ��*****************************/
void nextToken() {
	if (*src != 0) {
		current_token = *src;
		src++;
	}
	while (*src != 0 && current_token != "") {
		switch (state)
		{
		case 0: {
			if (current_token == "\t" || current_token == " ") {
				state = 0;
				current_token = *src;
				if (*src != 0)
					src++;
				else return;
			}
			else if (current_token == "+") state = 1;
			else if (current_token == "-") state = 2;
			else if (current_token == "*") state = 3;
			else if (current_token == "/") state = 4;
			else if (current_token == "%") state = 5;
			else if (current_token == "<") state = 6;
			else if (current_token == ">") state = 7;
			else if (current_token == "=") state = 8;
			else if (current_token == "[") state = 9;
			else if (current_token == "]") state = 10;
			else if (current_token == "(") state = 11;
			else if (current_token == ")") state = 12;
			else if (current_token == "{") state = 13;
			else if (current_token == "}") state = 14;
			else if (current_token == "\n") state = 15;
			else if (current_token == "&") state = 16;
			else if (current_token == "^") state = 17;
			else if (current_token == "#") state = 18;
			else if (current_token == "|") state = 19;
			else if (current_token == "\"") state = 20;
			else if (current_token == ";") state = 21;
			else if (current_token == "!") state = 22;
			else if (is_alpha(current_token)) state = 23;
			else if (is_num(current_token)) state = 24;
			else if (current_token == ",") state = 30;
			else state = 99;
			break;
		}
		case 1: {// ƥ�䵽 +
			sys = OPERATOR;
			if (*src == '+') {//��������
				current_token = "++";
				src++;
				state = 0;
				return;
			}
			else {
				state = 0;
				return;
			}
		}
		case 2: {
			sys = OPERATOR;
			if (*src == '-') {//�Լ�����
				current_token = "--";
				src++;
				state = 0;
			}
			else {
				state = 0;
				return;
			}
		}
		case 3: {
			sys = OPERATOR;
			state = 0;
			return;
		}
		case 4: {
			if (*src == '/') {
				state = 25;
				src++;
			}
			else if (*src == '*') {
				state = 26;
				src++;
			}
			else {
				sys = OPERATOR;
				state = 0;
				return;
			}
			break;
		}
		case 5: {
			sys = OPERATOR;
			state = 0;
			return;
		}
		case 6:{//ƥ�䵽<
			sys = OPERATOR;
			if (*src == '=') {
				current_token = "<=";
				src++;
				state = 0;
				return;
			}
			else {
				state = 0;
				return;
			}
		}
		case 7: {
			sys = OPERATOR;
			if (*src == '=') {
				current_token = ">=";
				src++;
				state = 0;
				return;
			}
			else {
				state = 0;
				return;
			}
		}
		case 8: {
			sys = OPERATOR;
			if (*src == '=') {
				current_token = "==";
				src++;
				state = 0;
				return;
			}
			else {
				state = 0;
				return;
			}
		}
		case 18: {
			while (*src != '\n' && *src != 0)// ƥ�䵽����
				src++;
			state = 0;
			if (*src != 0) {
				src++;
				line++;
			}
			current_token = *src;
			if (*src != 0)
				src++;
			break;
		}
		case 9:
		case 10:
		case 11:
		case 12:
		case 21:
		case 17:
		case 30: {
			sys = REGISTERED;
			state = 0;
			return;
		}
		case 13: {
			sys = REGISTERED;
			state = 0;
			return;
		}
		case 14: {
				sys = REGISTERED;
				state = 0;
				return;
		}
		case 15: {//ƥ�䵽����
			line++;
			state = 0;
			current_token = *src;
			src++;
			break;
		}
		case 16: {
			sys = OPERATOR;
			if (*src == '&') {
				current_token = "&&";
				state = 0;
				src++;
				return;
			}
			else {
				state = 0;
				return;
			}
		}
		case 19: {//||
			sys = OPERATOR;
			if (*src == '|') {
				current_token = "||";
				state = 0;
				src++;
				return;
			}
			else {
				state = 0;
				return;
			}
		}
		case 20: {// ƥ�䵽"
			if (*src == '"') {
				state = 28;
				current_token += *src;
				break;
			}
			else {
				current_token += *src;
				src++;
				state = 20;
				break;
			}
		}
		case 25: {
			while (*src != '\n' && *src != 0)// ƥ�䵽//
				src++;
			state = 0;
			if (*src != 0) {
				src++;
				line++;
			}
			current_token = *src;
			if (*src != 0)
				src++;
			break;
		}
		case 26: {
			if (*src == '*') {// ƥ�䵽/*
				state = 27;
				src++;
			}
			else {
				if (*src == '\n')
					line++;
				state = 26;
				src++;
			}
			break;
		}
		case 27: {// ƥ�䵽 /**
			if (*src == '/') {
				state = 32;
				break;
			}
			else {
				if (*src == '\n')
					line++;
				state = 27;
				src++;
				break;
			}
		}
		case 28: {
			src++;
			sys = STRING;
			state = 0;
			return;
		}
		case 22: {//ƥ�䵽!=
			if (*src == '=') {
				current_token = "!=";
				sys = OPERATOR;
				src++;
				state = 0;
				return;
			}
			else {
				syntaxError(1, line, "!");
			}
		}
		case 23: {
			if (is_alpha(*src)) {
				current_token += *src;
				src++;
				state = 23;
				break;
			}
			else {
				if (current_token == "if") sys = REGISTERED;
				else if (current_token == "else") sys = REGISTERED;
				else if (current_token == "return") sys = REGISTERED;
				else if (current_token == "for") sys = REGISTERED;
				else if (current_token == "def") {
					sys = REGISTERED;
					current_type = "function";
				}
				else if (current_token == "while") sys = REGISTERED;
				else {
					sys = ID;
					int id = Find(current_token, current_level);
					if (current_type == "function") {
						if (registeredFunction.count(current_token) != 0) {
							syntaxError(12, line, current_token);
						}
						sys = ID_FUN;
						current_type = "";
						Symbol temp(current_token, current_type,0);
						temp.modifyLocation((src-current_token.size()));//���溯������Ӧ��ָ��
						temp.modifyLine(line);
						if (id != -1)
							 syntaxError(7,line,current_token);//������������
						else symbolTab.push_back(temp);
					}
					else {
						Symbol temp(current_token,"void", current_level);
						if (id != -1);
						else symbolTab.push_back(temp);
					}
				}
				state = 0;
				return;
			}
		}
		case 24: {
			if (is_num(*src)) {
				current_token += *src;
				src++;
				state = 24;
				break;
			}
			else if (*src == '.') {
				current_token += *src;
				src++;
				state = 31;
				break;
			}
			else {
				sys = NUM;
				state = 0;
				return;
			}
		}
		case 31: {
			if (is_num(*src)) {
				current_token += *src;
				src++;
				state = 31;
				break;
			}
			else
			{
				sys = NUM;
				state = 0;
				return;
			}
		}
		case 32: {
			if (current_token == "/" && *(src - 1) == '*') {
				state = 0;
				src++;
				current_token = *src;
				if (*src != 0)
					src++;
				break;
			}
			else {
				syntaxError(4, line);
				break;
			}
		}
		case 99: {
			syntaxError(1, line,current_token);//�Ƿ��ַ�
			break;
		}
		default:
			break;
		}
	}
	switch (state)
	{
	case 27: {
		syntaxError(2,line);//����ע��ȱ�ٱ߽�
		break;
	}
	case 20: {
		syntaxError(3, line);//�ַ���ȱ�ٱ߽�
	}
	default:
		break;
	}
}

void checkMatch(string s) {
	if (s == current_token) {
		nextToken();
	}
	else {
		syntaxError(5, line, s);
	}
}

double term() {
	double t1 = 0; 
	double t2 = 0;
	t1 = factor();
	while (current_token == "*" || current_token == "/"||current_token=="%") {
		if (current_token == "*") {
			checkMatch("*");
			t2 = factor();
			t1 = t1 * t2;
		}
		else if (current_token == "/") {
			checkMatch("/");
			t2 = factor();
			if (t2 == 0) 
				syntaxError(6, line);
			t1 = t1 / t2;
		}
		else {
			checkMatch("%");
			t2 = factor();
			if (t2 == 0)
				syntaxError(6, line);
			t1 = t1 / t2;
		}
	}
	return t1;
}

double factor() {
	double f1 = 0;
	if (current_token == "(") {
		checkMatch("(");
		f1 = expression();
		checkMatch(")");
	}
	else if (sys == NUM) {//����
		f1 = atof(current_token.c_str());
		checkMatch(current_token);
	}
	int id = Find(current_token, current_level);
	if (sys == ID && id != -1) {//������
		if (symbolTab[id].getType() != "function_name") {
			Symbol temp = symbolTab[id];
			if (temp.getType() == "void") {//����δ����ʼ�������Ҳ�������
				string name = temp.getName();
				syntaxError(9, line, name);
			}
			string s = temp.get_value();
			f1 = atof(s.c_str());
			checkMatch(current_token);
		}
		else {//������
			checkMatch(current_token);
			checkMatch("(");
			vector<string>pra;
			pra.clear();
			while (current_token != ")" && *src != 0) {
				pra.push_back(to_string(expression()));//����ʵ��
				if (current_token == ",")
					checkMatch(",");
			}
			if (current_token != ")") {
				syntaxError(5, line, ")");
			}
			char* start = src;
			src = symbolTab[id].getLocation();
			long int lineTemp = line;
			line = symbolTab[id].get_Line();
			nextToken();
			f1 = function(pra);
			pra.clear();
			src = start;
			line = lineTemp;//�ָ��к�
			nextToken();
		}
	}
	//
	return f1;
}

double expression() {
	double t1 = term();
	while (current_token == "+" || current_token == "-") {
		if (current_token == "+") {
			checkMatch("+");
			t1 = t1 + term();
		}
		else if(current_token=="-"){
			checkMatch("-");
			t1 = t1 - term();
		}
	}
	return t1;
}

int expression_bool() {//�߼�������ʽ
	if (current_token == "(") {
		checkMatch("(");
		int temp = OR();
		checkMatch(")");
		return temp;
	}
	double temp = expression();
	if (current_token == "!=") {
		checkMatch("!=");
		return ((int)temp != (int)expression());
	}
	else if (current_token == ">") {
		checkMatch(">");
		return (temp > expression());
	}
	else if (current_token == "<") {
		checkMatch("<");
		return (temp < expression());
	}
	else if (current_token==">=") {
		checkMatch(">=");
		return (temp >= expression());
	}
	else if (current_token=="<=") {
		checkMatch("<=");
		return(temp <= expression());
	}
	else if (current_token == "==") {
		checkMatch("==");
		return ((int)temp == (int)expression());
	}
	return 0;
}

int AND() {
	int temp = expression_bool();
	while (current_token == "&&") {
		checkMatch("&&");
		if (temp == 0) {
			int count = 0;
			while (!(current_token == ")" && count == 0) && *src != 0 && current_token != "\n") {
				if (current_token == "(") count++;
				if (current_token == ")") count--;
				checkMatch(current_token);
			}
			return 0;//�߼���·
		}
		temp = temp && expression_bool();
		if (temp == 0) {
			int count = 0;
			while (!(current_token == ")" && count == 0) && *src != 0 && current_token != "\n") {
				if (current_token == "(") count++;
				if (current_token == ")") count--;
				checkMatch(current_token);
			}
			return 0;//�߼���·
		}
	}
	return temp;
}

int OR() {
	int temp = AND();
	while (current_token == "||") {
		checkMatch("||");
		if (temp == 1) {
			int count = 0;
			while (!(current_token == ")" && count == 0) && *src != 0 && current_token != "\n") {
				if (current_token == "(") count++;
				if (current_token == ")") count--;
				checkMatch(current_token);
			}
			return 1;//�߼���·
		}
		temp = temp || AND();
		if (temp == 1) {
			int count = 0;
			while (!(current_token == ")" && count == 0) && *src != 0 && current_token != "\n") {
				if (current_token == "(") count++;
				if (current_token == ")") count--;
				checkMatch(current_token);
			}
			return 1;//�߼���·
		}
	}
	return temp;
}

char* Skip() {//�������ʽ����while/if-else
	char* temp = (char*)malloc(sizeof(char));
	if (current_token == "{") {
		current_token = *(src++);
		if (current_token == "\n")
			line++;
		int count = 0;
		while (*src != 0 && !(current_token == "}" && count == 0)) {
			if (current_token == "}") count++;
			if (current_token == "{")count--;
			if (*src == '}') {
				temp = src;
			}
			current_token = *src++;
			if (current_token == "\n")
				line++;
		}
	}
	checkMatch("}");
	return temp;
}

double statement() {//��
	if (current_token == "{") {
		checkMatch("{");
		while (current_token != "}") {
			if (current_token == "return")
				return FLAG;
			if (FLAG == (int)statement())
				return FLAG;
		}
		checkMatch("}");
	}
	else if (current_token == "if") {//if���
		checkMatch("if");
		checkMatch("(");
		int temp = OR();
		checkMatch(")");
		if (temp) {//tempΪ��,ִ��if
			if (current_token == "return") {
				return FLAG;
			}
			else if (FLAG == (int)statement()) {
				return FLAG;
			}
		}
		else
			Skip();//����if�������
		if (current_token == "else") {//elsen���
			checkMatch("else");
			if (!temp) {//tempΪ��,ִ��else
				if (FLAG == (int)statement()) {
					return FLAG;
				}
			}
			else
				Skip();//����else����
		}
	}
	else if (current_token == "while") {//while���
		checkMatch("while");
		int temp;
		long int current_line = line;
		char* start = src;
		do {
			src = start;
			line = current_line;
			current_token = "(";
			checkMatch("(");
			temp = OR();
			checkMatch(")");
			if (temp) {
				if (current_token == "return")
					return FLAG;
				if (FLAG == (int)statement()) {
					return FLAG;
				}
			}
			else
				Skip();
		} while (temp);
	}
	else if (sys == ID && registeredFunction.count(current_token) == 0) {//������
		int id = Find(current_token, current_level);//�ҵ� current_token �ڷ��ű��λ��
		if (id != -1 && symbolTab[id].getType() != "function_name") {
			checkMatch(current_token);
			if (current_token == "=")
				checkMatch("=");
			else return atof(symbolTab[id].get_value().c_str());
			if (sys == STRING) {
				symbolTab[id].modifyValue(current_type);
				symbolTab[id].modifyType("string");
				checkMatch(current_token);
			}
			else {
				symbolTab[id].modifyType("number");
				symbolTab[id].modifyValue(to_string(expression()));
			}
			checkMatch(";");
		}
		else if (id != -1 && symbolTab[id].getType() == "function_name" && symbolTab[id].getType() != "void") {//ִ�к���
			double temp = expression();
			checkMatch(";");
			return temp;
		}
	}
		else if (current_token == "def") {
			int count = 0;
			checkMatch("def");
			int id = Find(current_token, current_level);
			if (id != -1) {
				symbolTab[id].modifyType("function_name");
				checkMatch(current_token);
				checkMatch("(");
				while (current_token != ")" && *src != '\n' && *src != 0) {
					if (sys == ID) {//�β����ַ�
						checkMatch(current_token);
						count++;
						symbolTab.pop_back();
						if (current_token == ",")
							checkMatch(",");
					}
					else //ȱ��)
						syntaxError(5, line, ")");
				}
				symbolTab[id].modifyValue(to_string(count));//��������value�洢��Ӧ�βεĸ���
				checkMatch(")");
				ending = Skip();//��������������ִ��

			}
			else syntaxError(8, line, current_token);
		}
		else if (current_token == "return") {
			checkMatch("return");
			return_val = expression();
			checkMatch(";");
			return FLAG;
		}
		else if (current_token == "for") {
		checkMatch("for");
		int temp = 0;
		long int current_line = line;
		checkMatch("("); 
		statement();
		if (current_token == ";")
		checkMatch(";");
		char* start = src;
		string old_token1 = current_token;
		int sys_old1 = sys;
		do {
			line = current_line;
			src = start;
			current_token = old_token1;
			sys = sys_old1;
;			temp = OR();
			checkMatch(";");
			int count = 0;
			char* check = src;
			string old_token2 = current_token;
			int sys_old2 = sys;
			while (!(current_token == ")" && count == 0) && *src != 0 && current_token != "\n") {
				if (current_token == "(") count++;
				if (current_token == ")") count--;
				checkMatch(current_token);
			}
			checkMatch(")");
			if (temp) {
				if (current_token == "return")
					return FLAG;
				if (FLAG == (int)statement()) {
					return FLAG;
				}
			}
			else {
				Skip();
				old_token1 = current_token;
				sys_old1 = sys;
				start = src;
				break;
			}
			src = check;
			current_token = old_token2;
			sys = sys_old2;
			statement();
		} while (temp);
		//�ָ�ָ��
		src = start;
		current_token = old_token1;
		sys = sys_old1;
}	
		else if (registeredFunction.count(current_token)!=0) {//�ڲ�Ԥ���庯��
		if (current_token == "print") {
			checkMatch("print");
			checkMatch("(");
			int count = 0;
			while (!(current_token == ")"&&count==0) && *src != 0) {
				if (current_token == "(") count++;
				if (current_token == ")") count--;
				if (sys == NUM || sys == STRING) {
					if (sys == NUM)
						cout << current_token;
					else if (trim(current_token) != "\\n")
						cout << trim(current_token);
					else cout << endl;
					checkMatch(current_token);
					if (current_token == ",")
						checkMatch(",");
				}
				else {
					double temp = statement();
					cout << temp;
					if (current_token == ",")
						checkMatch(",");
				}
			}
			checkMatch(")");
			checkMatch(";");
			return 0;
		}
		else if (current_token == "input") {
			checkMatch("input");
			checkMatch("(");
			while (current_token != ")" && *src != 0) {
				string name;
				int id = Find(current_token, current_level);
				if (id != -1) {
					cin >> name;
					symbolTab[id].modifyValue(name);
					checkMatch(current_token);
				}
				else {
					syntaxError(9, line, current_token);
				}
				if (current_token == ",")
					checkMatch(",");
			}
			checkMatch(")");
			checkMatch(";");
			return 0;
		}
		else if (current_token == "exit") {
			checkMatch("exit");
			checkMatch("(");
			int b = expression();
			exit(b);
		}
	}
		else {
			double temp = expression();
			checkMatch(";");
			return temp;
		}
		return 0;
}

double function(vector<string>pre) {
	int id = Find(current_token, current_level);
	if (id != -1 && symbolTab[id].get_value() == to_string(pre.size())) {
		current_level++;
		return_val = 0;
		checkMatch(current_token);
		checkMatch("(");
		int i = 0;
		while (current_token != ")") {//��ʽ����
			//����ʵ��
			string name = current_token;
			int id = Find(current_token, current_level);
			if (id != -1) {
				symbolTab[id].modifyValue(pre[i++]);
				symbolTab[id].modifyType("number");
			}
			checkMatch(name);
			if (current_token == ",")
				checkMatch(",");
		}
		checkMatch(")");
		char* start = src;//����srcָ��
		nextToken();//�޸�current_token
		while (current_token != "return" && *src != 0 && (src - 1) != ending) {
			statement();//�������
		}
		if (current_token == "return")
			statement();
		else syntaxError(13, line);
		src = start;//�ָ�ָ��
		nextToken();//�ָ�current_token
		for (vector<Symbol>::iterator it = symbolTab.begin(); it != symbolTab.end();) {
			if (it->get_Level() == current_level) {//�ͷź����ڲ�����

				it = symbolTab.erase(it);
			}
			else it++;
		}
		current_level--;
	}
	else if (id == -1) {//�Ҳ�����������
		syntaxError(8, line, current_token);
	}
	else {//�βκ�ʵ�β�ƥ��
		syntaxError(11, line);
	}
	return return_val;
}

int main() {
	inicializeFunction();
	ifstream in("temp.txt", ios::in);
	if (!in.is_open()) {
		cout << "fail to open file" << endl;
		exit(1);
	}
	char c;
	int n = 0;
	while (in.get(c))n++;
	cout<<"�ļ��ַ�����:" << n << endl;
	if (n > BUFFER) {//�ļ������˻�������С
		cout << "file is to large!" << endl;
		exit(1);
	}
	else {
		in.close();
		in.open("temp.txt", ios::in);
		if (!in.is_open()) {
			cout << "fail" << endl;
			exit(1);
		}
		src = (char*)malloc(sizeof(char) * (n + 1));
		while (!in.eof()) {
			in.read(src, n);
		}
		src[n+1] = 0;
		nextToken();
		while (*src != 0) {//��ʼ�𽥽���
			statement();
		}
	}
	symbolTab.clear();
	return 0;
}