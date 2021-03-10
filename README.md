# Interpreter
* 解释器
#### 高级编程语言大抵上可以分为两类，一类是编译型语言，一类是解释型语言，当然有的语言介于二者之间，常见的编译型语言有`C`和`C++`,解释语言比如`python`。编译型语言的优点就是快，消耗内存少，难点在于编译器的编写；解释型语言相对比较慢，运行时需要安全检查，但也有自己的优点，比如平台独立性，解释器编写相对简单。

* 开发一个解释器
### 成品展示
在记事本中编写一个简单的运算过程
```C
def Fabonaci(n){
	if(n==1||n==0){
		return 1;
	}
	else {
		return (Fabonaci(n-1)+Fabonaci(n-2));
	}
}

def foo(){
	a=0;
	i=1;
	for(i=1;i<10;i=i+1;){
		c = Fabonaci(i);
		print("Fabonaci (",i,") is ",c,"\n");
	}
	return 0;
}
foo();
```
输出结果
```

```
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
			else if (current_token == "*") state = 3;
			else if (current_token == "/") state = 4;
		  ...	...
			else if (is_alpha(current_token)) state = 23;     //token中包含字母或者下划线
		...	...
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
	...	...
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
词法分析最后的效果就是，将输入字符串拆分为有意义字符，测试案例如下
```C
//将下列文本以字符串形式输入进行测试
int main(){
a = 2021;
str ="hello,word!";
print(str);//print hello-world
return 0;
}
```
测试结果为
```C
int [type: ID]
main [type: ID]
( [type: registered]
) [type: registered]
{ [type: registered]
a [type: ID]
= [type: operator]
2021 [type: number]
; [type: registered]
str [type: ID]
= [type: operator]
"hello,word!" [type: string]
; [type: registered]
print [type: ID]
( [type: registered]
str [type: ID]
) [type: registered]
; [type: registered]
return [type: registered]
0 [type: number]
; [type: registered]
} [type: registered]
```
词法分析去掉了所有无意义的字符，比如注释，换行，空格等等，并为每一个字符打上了标签，其中变量类型统一为`ID`,数字为`number`，字符串为`string`,操作符为`operator`,其它合法字符为`registered`。
### 2.语法分析
语法分析的难点在于要解释每一段字符，即对token逐一处理组合为有意义的上下文，并解析。
其思想与[计算器](https://github.com/djh-sudo/Calc)的例子很相似，但是在规模和复杂度上有扩展。
* 递归解析过程
一共涉及到的函数有7类，而[计算器](https://github.com/djh-sudo/Calc)只有`2，3，4`这三种。
1. 语句块`statement`
2. 表达式`expression`
3. `term`
4. 因子`factor`
5. 布尔表达式`bool_expression`
6. 逻辑与`AND`
7. 逻辑或`OR`
解析过程采用递归下降，为每一个非终结符制定一个解析规则，直到全部被解析完成。
```
1. statement-> {statement}|expression|function
类似于if else while for def return 这样的语句都是语句块，需要递归解析

2. expression-> term +- term|var(number)
表达式，赋值运算，bool运算

3. term-> factor */ factor|var(number)
由于有优先级，所以先*/，后+-

4. factor-> var(number)|(expression)|function
最小单位为factor，可以是一个数字(变量)，也可以是(expression)表达式，也可以是一个函数调用
```
由于`C++`源代码有些冗长，这里放上伪代码
```python

double term(){
	t1 = factor();
	while(token is '*' or '/'){
		t1 = * / factor();
	}
	return t1;
}

double factor(){
	if(token is '(')
		f1 = expression();
	else if token is number
		f1 = number;
	else if token is var
		f1 = var.value();
	else if token is function
		f1 = function();
	return f1;
}

double expression(){
	t1 = term();
	while(token is '+' or '-'){
		t1 = t1 ± term();
	}
	return t1;
}

int AND(){
	t1 = expression_bool();
	while(token is '&&'){
		t1 = t1 && expression_bool();
	}
	return t1;
}

int OR(){
	t1 = expression_bool();
	while(token is '||'){
		t1 = t1 || expression_bool();
	}
	return t1;
}

int expression_bool(){
	if token is '('{
		t1 = OR();
		return t1;
	}
	t1 = (int)expression();
	else if token is '>'
		return t1 > expression();
	else if ...
	...	...
	return 0;
}

double statement(){
	if token is '{' ...
	else if token is 'if' ...
	else if token is number(var) ...
	else if token is 'def' ...
	else if token is 'return' ...
	else if token is 'for' ...
	...
	return 0;
}
```
整个核心的思想就是上面的伪代码部分，实际编写程序中，还需要注意很多安全问题，比如指针知否越界，除数为0时需要抛出异常，字符不匹配也需要抛出异常，所以为了统一管理，我们遍写了一个异常接管函数
```C
void syntaxError(int k, long int l = 0,string s = "") {
	switch (k)
	{
	case 1: {//非法字符
		cout << "Error [Line:" << line << "] " << s << " is invalid symbol." << endl;
		exit(1);
	}
	case 2: {//多行注释缺少边界
		cout << "Error [Line:" << line << "] Multi-line comments are missing boundaries." << endl;
		exit(1);
	}
	case 3: {//字符串缺少边界
		cout << "Warning [Line:" << line << "] String is missing boundaries." << endl;
		exit(1);
	}
	...	...
	case 11: {//形式参数与实际参数不匹配
		cout << "Error [Line:" << line << "] The formal and actual parameters do not match." << endl;
		exit(1);
	}
	case 12: {//系统函数不允许重载
		cout << "Error [Line:" << line << "] Can't reload the registered function " << s << endl;
		exit(1);
	}
	default:
		break;
	}
}
```
