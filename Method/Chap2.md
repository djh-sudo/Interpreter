# Part 1

在这一部分中，首先介绍一些简单的辅助函数，以及一些全局变量的作用
# 判断字符类型函数
 ```C
bool is_alpha(char c);						  //判断字符c是否只包含字母和下划线
bool is_alpha(string s);					  //判断字符串s是否只包含字母和下划线(重载)
bool is_num(string s);						  //判断字符串s是否只包含数字
bool is_num(char c);						  //判断字符c是否只包含数字(重载)
 ```
 这里，由于用户的输入均为字符串类型，因此，需要程序判断哪些是数字，哪些是一般字符。以上4个函数，分别判断输入是否仅有数字(`is_num`)或者字母以及下划线(`is_alpha`).
 # 检查符号合法性相关函数
 
 ```C
bool Compare(Symbol s1, Symbol s2);				//比较两个符号是否相等
bool is_contain(Symbol s1);					//判断符号表中是否包含了查找的符号
int Find(string name, int level);				//在当前的运行等级下查找变量名name
 ```
这里的三个函数主要是处理我们定义的变量名和变量
1. `Compare`比较两个变量是否属于同一变量，这里不仅会比较名字，还有运行等级，也就是作用域，在不同的函数中，可以有同名变量
``` C
bool Compare(Symbol s1, Symbol s2) {//比较s1和s2是否属于同一类型变量
	if ((s1.getName() == s2.getName()) && s1.get_Level() == s2.get_Level())
		return true;
	else
		return false;
}
```
2.`is_contain`函数判断，目前符号表`vector<Symbol>symbolTab`中是否已经包含了`s1`这个符号。

3.`Find`函数返回当前作用域下，查找`name`的下标，如果没有，则返回`-1`。

4.`syntaxError`是一个异常接管函数，接管解释过程中出现的各种异常

```
void syntaxError(int k, long int l,string s) {//错误接管函数
	switch (k)
	{
	case 1: {
		cout << "Error [Line:" << line << "] " << s << " is invalid symbol." << endl;
		exit(1);
	}
	case 2: {// 多行注释缺少边界
		cout << "Error [Line:" << line << "] Multi-line comments are missing boundaries." << endl;
		exit(1);
	}
	case 3: {// 字符串缺少边界
		cout << "Warning [Line:" << line << "] String is missing boundaries." << endl;
		exit(1);
	}
	case 4: {
		//注释不符合规范
		cout << "Error [Line:" << line << "] The comment does not meet the specification." << endl;
		//exit(1);
	}
	case 5: {//缺少匹配符号
		cout << "Error [Line:" << line << "] Expected the symbol '" << s << "',but not have." << endl;
		exit(1);
	}
	case 6: {//除数为0
		cout << "Error [Line:" << line << "] Divisor cannot be 0." << endl;
		exit(1);
	}
	case 7: {//重定义
		cout << "Error [Line:" << line << "] " << s << " defination is duplicated!" << endl;
		exit(1);
	}
	case 8:
	{//找不到定义
		cout << "Error [Line:" << line << "] function '" << s << "' is not defined!" << endl;
		exit(1);
	//找不到函数def
	}
	case 9: {//变量未初始化
		cout << "Error [Line:" << line << "] " << s << " is not inicialized or can't find." << endl;
		exit(1);
	}
	case 10: {//变量未使用
		cout << "Warning [Line:" << line << "] " << s << " is not used." << endl;
	}
	case 11: {//函数形参与实参不匹配
		cout << "Error [Line:" << line << "] The formal and actual parameters do not match." << endl;
		exit(1);
	}
	case 12: {//系统函数不允许重载
		cout << "Error [Line:" << line << "] Can't reload the registered function " << s << endl;
		exit(1);
	}
	case 13: {//缺少return
		cout << "Warning [Line:" << line << "] function with no statement 'return'. "  << endl;
	}
	default:
		break;
	}
}
```
5.`inicializeFunction`初始化自己编写的函数

6.`trim`去掉字符串一头一尾字符
# To be continue...
