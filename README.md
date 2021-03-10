# Interpreter
* 解释器
#### 高级编程语言大抵上可以分为两类，一类是编译型语言，一类是解释型语言，当然有的语言介于二者之间，常见的编译型语言有`C`和`C++`,解释语言比如`python`。编译型语言的优点就是快，消耗内存少，难点在于编译器的编写；解释型语言相对比较慢，运行时需要安全检查，但也有自己的优点，比如平台独立性，解释器编写相对简单。

* 开发一个解释器

下面我们简单开发一个解释器，了解解释器的工作原理是什么，大题需要经过哪一些流程。解释器主要部分为词法分析器和语法分析器，其次就是输出输出的接口。
### 1.词法分析
词法分析的实质是将输入的字符串流拆分为一个个有意义`token`,并为他们打上标签，比如那些是变量，那些是保留字等等。整个过程相对简单，稍有些繁琐。实现思路可以分为两类，一类用`if else`语句块，逐个判断，一类用`switch case`有限状态机的思想,下面是第2种方式的`C++代码(节选)`。
 ```C
 void nextToken() {
	if (*src != 0) {                                           //检查指针src边界
		current_token = *src;                                 //current_token表示当前的token
		src++;                                                //src为current_token的下一个字符
	}
	while (*src != 0 && current_token != "") {
		switch (state)                                        //根据state状态进行转换，state默认为0
		{
		case 0: {                                             //跳过所有的空格和制表符
			if (current_token == "\t" || current_token == " ") {
				state = 0;
				current_token = *src;
				if (*src != 0)
					src++;
				else return;
			}                                              //判断token属于那种类型，每一种类型转移到对应状态处理
			else if (current_token == "+") state = 1;
			else if (current_token == "-") state = 2;
			else if (current_token == "*") state = 3;
			else if (current_token == "/") state = 4;
			else if (current_token == "%") state = 5;
		  ...
			else if (is_alpha(current_token)) state = 23;     //token中包含字母或者下划线
			else if (is_num(current_token)) state = 24;       //token为纯数字
			else if (current_token == ",") state = 30;        //token为逗号
			else state = 99;                                  //其余状态识别为非法字符
			break;
		}
		case 1: {                                                 //匹配到 +
			sys = OPERATOR;
			if (*src == '+') {                                //连续两个+为自增操作
				current_token = "++";
				src++;
				state = 0;
				return;
			}
			else {                                             //+运算符
				state = 0;                                 //恢复到默认状态0
				return;                                    //返回
			}
		}
		case 2: {                                                //匹配到-
			sys = OPERATOR;
			if (*src == '-') {                                //匹配到两个-，自减操作
				current_token = "--";
				src++;
				state = 0;
			}
			else {                                             //-运算符
				state = 0;
				return;
			}
		}
		case 3: {                                               //匹配到*
			sys = OPERATOR;                                  //识别为操作符
			state = 0;                                       //恢复默认状态0
			return;                                          //返回
		}
		case 4: {                                               //匹配到/
			if (*src == '/') {                               //单行注释
				state = 25;                               //跳转到25处理单行注释
				src++;
			}
			else if (*src == '*') {                          //多行注释
				state = 26;                               //跳转到状态26处理多行注释
				src++;
			}
			else {                                            //除法运算符
				sys = OPERATOR;
				state = 0;
				return;
			}
			break;
		}
	...

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
    
...
		case 99: {
			syntaxError(1, line,current_token);           //非法字符，抛出错误，解释器停止工作
			break;
		}
		default:
			break;
		}
	}
 ```
