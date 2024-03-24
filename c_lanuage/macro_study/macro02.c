#include <stdio.h>

/*
ANSI C标准中有几个标准预定义宏:
__LINE__:			在源代码中插入当前源代码行号；
__FUNCTION__: 		在源代码中插入当前源代码的函数名；
__FILE__:			在源文件中插入当前源文件名；
__DATE__:			在源文件中插入当前的编译日期
__TIME__:			在源文件中插入当前编译时间；
__STDC__:			当要求程序严格遵循ANSI C标准时该标识被赋值为1；
__cplusplus:		当编写C++程序时该标识符被定义。
**/

void func1()
{
	printf("Date : %s\n", __DATE__);
	printf("Time : %s\n", __TIME__);
	printf("File : %s\n", __FILE__);
	printf("Function : %s\n", __FUNCTION__);
	printf("Line : %d\n", __LINE__);
}

void func2()
{
	printf("Date : %s\n", __DATE__);
	printf("Time : %s\n", __TIME__);
	printf("File : %s\n", __FILE__);
	printf("Function : %s\n", __FUNCTION__);
	printf("Line : %d\n", __LINE__);
}

int main()
{
	func1();
	puts("\n******************************************************");
	func2();
	return 0;
}
