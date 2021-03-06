// SafeCodeProject.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdafx.h"
#include "StrSafe.h"
#include "MemPool.h"
#include "MathSafe.h"
#include "LogSafe.h"
#include <iostream>
#include <thread>
using namespace std;

void ThreadFun()
{
	logStr((char *)"Normal", (char *)"Start Normal Testing...");
	logStr((char *)"Warning", (char *)"Start Warning Testing...");
	logStr((char *)"Alert", (char *)"Start Alert Testing...");
	logStr((char *)"Error", (char *)"Start Error Testing...");
}

void ThreadFun2()
{
	for (int i = 0; i < 7000; ++i) {
		logStr((char *)"Normal", (char *)"Start Normal Testing...");
		logStr((char *)"Warning", (char *)"Start Warning Testing...");
		logStr((char *)"Alert", (char *)"Start Alert Testing...");
		logStr((char *)"Error", (char *)"Start Error Testing...");
	}
}

int main()
{
	//-------------1.1---------------//
	/*
	char a[] = "a12345678";
	cout << isUsernameOK(a) << endl;
	char b[] = "a123";
	cout << isUsernameOK(b) << endl;
	char c[] = "a123bcdefg4567890";
	cout << isUsernameOK(c) << endl;
	char d[] = "0";
	cout << isUsernameOK(d) << endl;
	cout << isUsernameOK(0) << endl;
	char f[] = "123456789";
	cout << isUsernameOK(f) << endl;
	char g[] = "abcdefghjik";
	cout << isUsernameOK(g) << endl;
	*/

	//-------------1.2---------------//
	/*
	char h[] = "1234A5678";
	cout << isPasswordOK(h) << endl;
	char i[] = "a123";
	cout << isPasswordOK(i) << endl;
	char j[] = "a123Bcdefg4567890";
	cout << isPasswordOK(j) << endl;
	char k[] = "";
	cout << isPasswordOK(k) << endl;
	cout << isPasswordOK(0) << endl;
	char m[] = "123456789";
	cout << isPasswordOK(m) << endl;
	char n[] = "abcdefghjik";
	cout << isPasswordOK(n) << endl;
	char o[] = "1234abcde8";
	cout << isPasswordOK(o) << endl;
	*/

	//-------------2.1---------------//
	//char buf[8];
	//char* buf = 0;
	//cout << gets_safe(buf, sizeof(buf));
	//char buf[8];
	//cout << gets_safe(buf, 0);

	//-------------2.2---------------//
	/*
	char dest1[8];
	char src1[] = "12345";
	cout << strcpy_safe(dest1, sizeof(dest1), src1) << endl;
	char dest2[8];
	char src2[] = "1234567";
	cout << strcpy_safe(dest2, sizeof(dest2), src2) << endl;
	char dest3[8];
	char src3[] = "12345678";
	cout << strcpy_safe(dest3, sizeof(dest3), src3) << endl;
	char src4[] = "1234567";
	cout << strcpy_safe(0, 8, src4) << endl;
	char dest5[8];
	cout << strcpy_safe(dest5, sizeof(dest5), 0) << endl;
	char dest6[8];
	char src6[] = "12345678";
	cout << strcpy_safe(dest6, 0, src6) << endl;
	*/

	//-------------3.all---------------//
	/*
	initPool(8);
	allocBlock();
	char* buf = allocBlock();
	//cout << &buf << endl;
	int count = 0;
	for (int i = 0; i < 256; ++i){
		if (buf[i] == 0) ++count;
	}
	if (count == 256)
		cout << "buf[0] + buf[1] + ... +buf[255] = 0" << endl;
	cout << getBlockCount() << endl;
	cout << getAvailableBlockCount() << endl;
	allocBlock();
	char* buf2 = allocBlock();
	//cout << &buf2 << endl;
	cout << getAvailableBlockCount() << endl;
	freeBlock(buf2);
	cout << getBlockCount() << endl;
	cout << getAvailableBlockCount() << endl;
	freeBlock(buf);
	count = 0;
	for (int i = 0; i < 256; ++i) {
		if (buf[i] == 0) ++count;
	}
	if (count == 256)
		cout << "buf[0] + buf[1] + ... +buf[255] = 0" << endl;
	cout << freePool() << endl;
	freePoolForce();
	cout << getBlockCount() << endl;
	cout << getAvailableBlockCount() << endl;
	*/

	//-------------4.1---------------//
	/*
	int* of = new int;
	int result;
	char text1[] = "-128";
	result = my_atoi8(text1, of);
	cout << "text=" << text1 << " result=" << result << " *of=" << *of << endl;
	char text2[] = "127";
	result = my_atoi8(text2, of);
	cout << "text=" << text2 << " result=" << result << " *of=" << *of << endl;
	char text3[] = "0";
	result = my_atoi8(text3, of);
	cout << "text=" << text3 << " result=" << result << " *of=" << *of << endl;
	char text4[] = "-1";
	result = my_atoi8(text4, of);
	cout << "text=" << text4 << " result=" << result << " *of=" << *of << endl;

	char text5[] = "1285";
	result = my_atoi8(text5, of);
	cout << "text=" << text5 << " result=" << result << " *of=" << *of << endl;
	char text6[] = "-129";
	result = my_atoi8(text6, of);
	cout << "text=" << text6 << " result=" << result << " *of=" << *of << endl;
	char text7[] = "130";
	result = my_atoi8(text7, of);
	cout << "text=" << text7 << " result=" << result << " *of=" << *of << endl;

	char text8[] = "";
	result = my_atoi8(text8, of);
	cout << "text=" << text8 << " result=" << result << " *of=" << *of << endl;
	result = my_atoi8(0, of);
	cout << "text=NULL" << " result=" << result << " *of=" << *of << endl;
	char text9[] = "abc";
	result = my_atoi8(text9, of);
	cout << "text=" << text9 << " result=" << result << " *of=" << *of << endl;
	char text10[] = "12a";
	result = my_atoi8(text10, of);
	cout << "text=" << text10 << " result=" << result << " *of=" << *of << endl;

	char text11[] = "123a";
	result = my_atoi8(text11, of);
	cout << "text=" << text11 << " result=" << result << " *of=" << *of << endl;
	char text12[] = "12a";
	result = my_atoi8(text12, of);
	cout << "text=" << text12 << " result=" << result << " *of=" << *of << endl;
	char text13[] = "-12a";
	result = my_atoi8(text13, of);
	cout << "text=" << text13 << " result=" << result << " *of=" << *of << endl;

	char text14[] = "00123";
	result = my_atoi8(text14, of);
	cout << "text=" << text14 << " result=" << result << " *of=" << *of << endl;
	char text15[] = "-00123";
	result = my_atoi8(text15, of);
	cout << "text=" << text15 << " result=" << result << " *of=" << *of << endl;

	char text16[] = " 123 ";
	result = my_atoi8(text16, of);
	cout << "text=" << text16 << " result=" << result << " *of=" << *of << endl;
	char text17[] = "-23 ";
	result = my_atoi8(text17, of);
	cout << "text=" << text17 << " result=" << result << " *of=" << *of << endl;
	char text18[] = "-2 3 ";
	result = my_atoi8(text18, of);
	cout << "text=" << text18 << " result=" << result << " *of=" << *of << endl;
	*/
	
	//-------------4.2---------------//
	/*
	int* of = new int;
	int result;
	cout << "Add" << endl;
	result = iAdd_Safe(12, 13, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iAdd_Safe(127, 0, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iAdd_Safe(-12, -13, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iAdd_Safe(-127, 13, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iAdd_Safe(127, 3, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iAdd_Safe(-126, -13, of);
	cout << "result=" << result << " of=" << *of << endl;
	cout << "Subtract" << endl;
	result = iSubtract_Safe(12, 13, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iSubtract_Safe(127, 0, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iSubtract_Safe(-12, -13, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iSubtract_Safe(-127, 1, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iSubtract_Safe(127, -1, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iSubtract_Safe(-126, 13, of);
	cout << "result=" << result << " of=" << *of << endl;
	cout << "Multiply" << endl;
	result = iMultiply_Safe(2, 30, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iMultiply_Safe(127, 1, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iMultiply_Safe(-2, 30, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iMultiply_Safe(-12, -3, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iMultiply_Safe(-128, 1, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iMultiply_Safe(127, 3, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iMultiply_Safe(-28, 6, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iMultiply_Safe(-128, -1, of);
	cout << "result=" << result << " of=" << *of << endl;
	cout << "Divide" << endl;
	result = iDivide_Safe(127, 3, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iDivide_Safe(-28, 7, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iDivide_Safe(-128, 1, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iDivide_Safe(-128, -1, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iDivide_Safe(127, 0, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iDivide_Safe(-28, 0, of);
	cout << "result=" << result << " of=" << *of << endl;
	result = iDivide_Safe(-128, 0, of);
	cout << "result=" << result << " of=" << *of << endl;
	*/

	//-------------4.3---------------//
	/*
	int* of = new int;
	int result;
	cout << "Add" << endl;
	result = Add_Safe(12, 13, of);
	cout << "result=" << result << " *of=" << *of << endl;
	result = Add_Safe(255, 0, of);
	cout << "result=" << result << " *of=" << *of << endl;
	result = Add_Safe(132, 13, of);
	cout << "result=" << result << " *of=" << *of << endl;
	result = Add_Safe(255, 1, of);
	cout << "result=" << result << " *of=" << *of << endl;
	result = Add_Safe(124, 123, of); //这个应该没溢出吧
	cout << "result=" << result << " *of=" << *of << endl;
	cout << "Subtract" << endl;
	result = Subtract_Safe(17, 13, of);
	cout << "result=" << result << " *of=" << *of << endl;
	result = Subtract_Safe(127, 0, of);
	cout << "result=" << result << " *of=" << *of << endl;
	result = Subtract_Safe(232, 13, of);
	cout << "result=" << result << " *of=" << *of << endl;
	result = Subtract_Safe(127, 128, of);
	cout << "result=" << result << " *of=" << *of << endl;
	result = Subtract_Safe(2, 255, of);
	cout << "result=" << result << " *of=" << *of << endl;
	cout << "Multiply" << endl;
	result = Multiply_Safe(2, 30, of);
	cout << "result=" << result << " *of=" << *of << endl;
	result = Multiply_Safe(127, 1, of);
	cout << "result=" << result << " *of=" << *of << endl;
	result = Multiply_Safe(122, 2, of);
	cout << "result=" << result << " *of=" << *of << endl;
	result = Multiply_Safe(127, 3, of);
	cout << "result=" << result << " *of=" << *of << endl;
	result = Multiply_Safe(28, 26, of);
	cout << "result=" << result << " *of=" << *of << endl;
	cout << "Divide" << endl;
	result = Divide_Safe(234, 3, of);
	cout << "result=" << result << " *of=" << *of << endl;
	result = Divide_Safe(228, 7, of);
	cout << "result=" << result << " *of=" << *of << endl;
	*/
	
	//-------------5.1and2---------------//
	/*
	char path[] = "C:/temp/log.txt";
	initLog(path);
	thread td1(ThreadFun);
	thread td2(ThreadFun);
	thread td3(ThreadFun);
	//td1.join();
	//td2.join();
	//td3.join();
	td1.detach();
	td2.detach();
	td3.detach();
	thread test(ThreadFun2); // 测试备份功能
	test.join();
	*/
	
	system("pause");
    return 0;
}

