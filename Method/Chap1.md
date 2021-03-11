# 全局总览

工程中用到的函数和全局变量如下
```C
/*******************************用到的辅助函数*****************************/
void inicializeFunction();					//初始化系统函数
string trim(string s);						//去掉字符串一头一尾函数
bool Compare(Symbol s1, Symbol s2);			        //比较两个符号是否相等
bool is_contain(Symbol s1);					//判断符号表中是否包含了查找的符号
void syntaxError(int k, long int l = 0, string s = "");         //根据错误类型抛出异常
int Find(string name, int level);			        //在当前的运行等级下查找变量名name
string tokenType(int Type);					//将整形的type转为对应的字符串
bool is_alpha(char c);						//判断字符c是否只包含字母和下划线
bool is_alpha(string s);					//判断字符串s是否只包含字母和下划线(重载)
bool is_num(string s);						//判断字符串s是否只包含数字
bool is_num(char c);						//判断字符c是否只包含数字(重载)
/*******************************关键算法函数*****************************/
void nextToken();						//修改current_token的值
void checkMatch(string s);					//检查字符是否匹配并获取下一个token
double expression();						//计算表达式的值
double factor();					        //计算因子的值
double term();
double function(vector<string>pre);			        //计算函数的值
int expression_bool();						//计算bool类型的值
int AND();
int OR();
void Skip();							//跳过无需执行的语句块
double statement();						//解析语句块
/*******************************符号类*****************************/
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
/*******************************关键字类型*****************************/
enum sys { ID, STRING, REGISTERED, OPERATOR, NUM, ID_FUN };
/*******************************全局变量*****************************/
char* src;				        //全局解析指针
string current_token;				//当前token值
string current_type;				//当前token的类型
int current_level = 0;				//当前运行级别
long int line = 1;			        //行号
int state = 0;				        //状态
int sys = -1;					//关键字类型
double return_val = 0;				//函数返回值
vector<Symbol>symbolTab;			//符号表
set<string>registeredFunction;		        //注册函数表
```
* 在上面的`C++`代码中，我们看到代码的核心算法函数并不多，主要是一个逐层次解析过程，辅助函数帮助我们判断一些信息，给出报错异常等。同时，我们用到了一个类，符号类。
在这个类里面，主要存放每个符号的信息，比如名称`name`，作用范围`level`,以及变量值`value`等，事实上，每当解析器遇到一个字符，都会将其装入字符表中，以便后续用到时查找是否存在，否则会报错。
* 目前支持的语法规则
### 1 变量
变量无需定义，只需要在声明时初始化即可，例如`a = 0;`,目前支持两类变量，一类是数字，一类是字符串，如`a = "hello world!";`。
### 2 语句
语句支持 `if(){}`,`else(){}`,`while(){}`,`for(;;;)`,注意`for`循环不同于C语言，需要在每个表达式后面加上`;`,其余表达式不可以省略`{}`。
### 3 函数定义
函数定义关键字为`def`,如`def Fibonacc(n){...}`,可以有多个参数，参数数量不做限制，但参数是值传递，不是引用传递，函数支持递归调用。函数必须有返回值,即不可以省略关键字`return `。

系统保留了3个注册函数，分别是`print()`,`input()`,`exit()`,分别是输出，输入，以及退出程序。

其中`print()`函数输出只需要用`,`间隔即可，可以有多个参数，`input()`,同理，用`,`间隔等待输入的值。

当你发现程序运行有误时，可以根据提示行号，检查对应行号的语法。

`bug`: 
(1) `print()`函数输出换行符时，只能够单独使用"\n",同时不支持中文编码，最好使用英文。

(2)`input()`函数在读入时，目前只支持数字类型，字符串会被判定为0处理。
### for example:
```C
def Fabonaci(n){
	if(n == 1 || n == 0){
		return 1;
	}
	else {
		return (Fabonaci(n-1)+Fabonaci(n-2));
	}
}

def foo(){
	a=0;
	b=0;
	i=1;
	print("pls input the number you want to calc:","\n");
	input(a);
	for(i=1;i < a;i = i + 1;){//输出前a-1个斐波那契数列值
		c = Fabonaci(i);
	print("Fabonaci (",i,") is ",c,"\n");
	}
	return 0;
}
foo();
```
最后，可以根据个人需要对源码进行修改和编辑。
## Thanks for watching ...
