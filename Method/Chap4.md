# Part 4-1
# 语法分析器(`Parser`)之表达式求值
对于词法分析器(`Lexical analyzer`)给出的一个个`token`,语法分析器要做的就是分析其语义，用一套解释规则去解释我们书写的程序

* 1.`term`函数
对于`*`,`/`,`%`,三种运算符进行处理
```C
double term() {
	double t1 = 0; 
	double t2 = 0;
	t1 = factor();                                                               			//获取第一操作数
	while (current_token == "*" || current_token == "/"||current_token=="%") {
		if (current_token == "*") {
			checkMatch("*");
			t2 = factor();                                                           	//获取第2操作数
			t1 = t1 * t2;
		}
		else if (current_token == "/") {
			checkMatch("/");
			t2 = factor();                                                            	//获取第2操作数
			if (t2 == 0)                                                             	//除数不可以为0
				syntaxError(6, line);                                             	//抛出异常
			t1 = t1 / t2;
		}
		else {
			checkMatch("%");
			t2 = factor();                                                            	//获取第2操作数
			if (t2 == 0)                                                              	//除数不可以为0
				syntaxError(6, line);                                             	//抛出异常
			t1 = t1 / t2;
		}
	}
	return t1;											//返回计算结果
}
```
* 2.`factor`函数
对于各个因子进行处理，这里包括类型有`(expression)|number|function|var`
```C
	double f1 = 0;
	if (current_token == "(") {								//匹配到左括号
		checkMatch("(");
		f1 = expression();								//进行表达式求值
		checkMatch(")");								//检查右括号是否缺失
	}
	else if (sys == NUM) {									//匹配到数字
		f1 = atof(current_token.c_str());
		checkMatch(current_token);
	}
	int id = Find(current_token, current_level);						//判断是否为变量名
	if (sys == ID && id != -1) {								//在symbolTab中找到变量名
		if (symbolTab[id].getType() != "function_name") {
			Symbol temp = symbolTab[id];
			if (temp.getType() == "void") {						//变量未被初始化或者找不到变量
				string name = temp.getName();
				syntaxError(9, line, name);					//抛出未初始化异常
			}
			string s = temp.get_value();						//获取变量名的值
			f1 = atof(s.c_str());
			checkMatch(current_token);
		}
		else {                                                                       	//函数名
			checkMatch(current_token);
			checkMatch("(");
			vector<string>pra;
			pra.clear();
			while (current_token != ")" && *src != 0) {
				pra.push_back(to_string(expression()));				//保存实参
				if (current_token == ",")					//实参用逗号分割
					checkMatch(",");
			}
			if (current_token != ")") {						//函数的右括号是否缺失
				syntaxError(5, line, ")");                                 	//抛出异常
			}
			char* start = src;
			src = symbolTab[id].getLocation();					//保存函数的位置指针
			long int lineTemp = line;						//保存函数的所在行号
			line = symbolTab[id].get_Line();					//修改记录当前行号
			nextToken();
			f1 = function(pra);							//调用函数
			pra.clear();								//清空实参表
			src = start;								//恢复指针
			line = lineTemp;							//恢复行号
			nextToken();
		}
	}
	return f1;
```
* 3.`expression`函数
处理`+`,`-`两类运算
```C
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
```
这三个函数构成了表达式求值的全部思路，与[计算器](https://github.com/djh-sudo/Calc)是类似的。
后续章节讲继续解释`bool`表达式的求值以及语句块的执行过程。

### [上一章(词法分析器)](https://github.com/djh-sudo/Interpreter/blob/main/Method/Chap3.md)

### [下一章(语法分析器3-2)](https://github.com/djh-sudo/Interpreter/blob/main/Method/Chap4.md)
