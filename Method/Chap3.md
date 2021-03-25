# Part 3
# 词法分析器(`Lexical analyzer`)

我们需要对输入的字符串文本，拆分，得到一个个打好标签的`token`

函数的核心思想，使用`switch-case`或者多个连续的`if-else`进行判断，在不同状态下转换，每调用一次`nextToken`,`current_token`进行更新。

主要用到的变量有:
1. `current_token`:全局变量，当前的`token`
2. `src`:全局指针,指向`token`的下一个字符
3. `state`:转换状态标记
4. `sys`:当前`token`的标签

虽然当前一些运算符后续的语法分析并不支持，如自增运算`++`，但是在词法分析中可以识别出来。

```C
void nextToken() {
	if (*src != 0) {//判断指针是否为空
		current_token = *src;
		src++;
	}
	while (*src != 0 && current_token != "") {
		switch (state)
		{
		case 0: {
			if (current_token == "\t" || current_token == " ") {//跳过空格和制表符
				state = 0;//初始状态为0
				current_token = *src;
				if (*src != 0)
					src++;
				else return;
			}
			else if (current_token == "+") state = 1;		//判断当前字符是否为+
			else if (current_token == "-") state = 2;		//判断当前字符是否为-
			else if (current_token == "*") state = 3;		//判断当前字符是否为*
			else if (current_token == "/") state = 4;		//判断当前字符是否为/
			else if (current_token == "%") state = 5;		//判断当前字符是否为%
			else if (current_token == "<") state = 6;		//判断当前字符是否为<
			else if (current_token == ">") state = 7;		//判断当前字符是否为>
			else if (current_token == "=") state = 8;		//判断当前字符是否为=
			else if (current_token == "[") state = 9;		//判断当前字符是否为[
			else if (current_token == "]") state = 10;		//判断当前字符是否为]
			else if (current_token == "(") state = 11;		//判断当前字符是否为(
			else if (current_token == ")") state = 12;		//判断当前字符是否为)
			else if (current_token == "{") state = 13;		//判断当前字符是否为{
			else if (current_token == "}") state = 14;		//判断当前字符是否为}
			else if (current_token == "\n") state = 15;		//判断当前字符是否为换行
			else if (current_token == "&") state = 16;		//判断当前字符是否为&
			else if (current_token == "^") state = 17;		//判断当前字符是否为^
			else if (current_token == "#") state = 18;		//判断当前字符是否为#
			else if (current_token == "|") state = 19;		//判断当前字符是否为|
			else if (current_token == "\"") state = 20;		//判断当前字符是否为\
			else if (current_token == ";") state = 21;		//判断当前字符是否为;
			else if (current_token == "!") state = 22;		//判断当前字符是否为!
			else if (is_alpha(current_token)) state = 23;		//判断当前字符是否为字母
			else if (is_num(current_token)) state = 24;		//判断当前字符是否为数字
			else if (current_token == ",") state = 30;		//判断当前字符是否为，
			else state = 99;					//异常字符
			break;
		}
		case 1: {							// 匹配到 +
			sys = OPERATOR;
			if (*src == '+') {					//自增操作
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
			if (*src == '-') {					//自减操作
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
		case 6:{//匹配到<
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
			while (*src != '\n' && *src != 0)// 匹配到换行
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
		case 15: {//匹配到换行
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
		case 20: {// 匹配到"
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
			while (*src != '\n' && *src != 0)// 匹配到//
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
			if (*src == '*') {// 匹配到/*
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
		case 27: {// 匹配到 /**
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
		case 22: {//匹配到!=
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
						temp.modifyLocation((src-current_token.size()));	//保存函数名对应的指针
						temp.modifyLine(line);
						if (id != -1)	
							 syntaxError(7,line,current_token);		//函数定义重名
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
			syntaxError(1, line,current_token);	//非法字符
			break;
		}
		default:
			break;
		}
	}							//上述匹配结束，若state不为0，说明存在异常
	switch (state)
	{
	case 27: {
		syntaxError(2,line);				//多行注释缺少边界
		break;
	}
	case 20: {
		syntaxError(3, line);				//字符串缺少边界
	}
	default:
		break;
	}
}
```

### [上一章(辅助函数简介)](https://github.com/djh-sudo/Interpreter/blob/main/Method/Chap2.md)

### [下一章(语法分析器)](https://github.com/djh-sudo/Interpreter/blob/main/Method/Chap4.md)
