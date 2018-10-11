#include "stdafx.h"
#include "LogSafe.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <time.h>
#include <string>
#include<Windows.h>  
#define NULL 0

using namespace std;


fstream logfile;
fstream bakfile;
mutex mtx;
char bak_path[] = "C:/temp/bak.txt";
char* log_path = NULL;
int flag = 1;

int initLog(char* path)
/*功能：初始化日志模块，设置日志文件存放的路径。
参数 path：指向一个文件路径的 C 字符串。
返回值：日志文件创建成功返回 0，否则返回-1.
提示：可使用 C 语言中文件 IO 操作。*/
{
	if (path == NULL) {
		return -1;
	} else {
		logfile.open(path, ios::app);
		if (!logfile) {
			return -1;
		}
		//logfile.close();
		log_path = path;
		return 0;
	}
}



int logStr(char* level, char* str)
/*功能：将字符串 str 输出到日志文件中，根据 level 字符串设置输出的日志信息。日志格式：Level || 线程 id || 时分秒 || str 字符串。要求实现线程安全，确保多线程使用时输出不产生乱序或截断等。当日志文件大于 1MB 时，需执行备份操作。
参数 level：C 字符串，可能的 level 包括：Normal，Warning，Alert，Error 等。
参数 str：C 字符串，用户需要输出的日志信息。
返回值：符合要求返回 0，否则返回-1.
提示：使用标准线程库，可使用互斥量保证线程安全，尝试 RAII 用法。*/
{
	if (!level || !str || !logfile)
		return -1;
	lock_guard<mutex> lck(mtx); // RAII形式的互斥锁，智能销毁，有轮子就不自己造了
	thread::id tid = this_thread::get_id();
	time_t time_seconds = time(0);
	struct tm now_time;
	localtime_s(&now_time, &time_seconds);
	//char time[8];
	//sprintf_s(time, "%d:%d:%d", now_time.tm_hour, now_time.tm_min, now_time.tm_sec);
	//logfile.open(log_path, ios::app);
	logfile << level << " || " << tid << " || " << now_time.tm_hour << ":" << now_time.tm_min << ":" << now_time.tm_sec  << " || " << str << "\n";
	//logfile.close();

	logfile.seekp(0, logfile.end);
	int FileSize = logfile.tellp();
	if (FileSize >= 1048576) { // 1024*1024 Byte
		if (flag) {    //大家都说要这样备份
			CopyFileA(log_path, bak_path, FALSE);
			flag = 0;
		} else {
			bakfile.open(bak_path, ios::app);
			bakfile << level << " || " << tid << " || " << now_time.tm_hour << ":" << now_time.tm_min << ":" << now_time.tm_sec << " || " << str << "\n";
			bakfile.close();
		}
	}
	return 0;
}

void old_log_file(char* level, char* str) {
	lock_guard<mutex> lck(mtx);
	thread::id tid = this_thread::get_id();
	time_t time_seconds = time(0);
	struct tm now_time;
	localtime_s(&now_time, &time_seconds);
	char time[8];
	sprintf_s(time, "%d:%d:%d", now_time.tm_hour, now_time.tm_min, now_time.tm_sec);
	logfile << level << " || " << tid << " || " << time << " || " << str << "\n";
}


int old_logStr(char* level, char* str)
/*功能：将字符串 str 输出到日志文件中，根据 level 字符串设置输出的日志信息。日志格式：Level || 线程 id || 时分秒 || str 字符串。要求实现线程安全，确保多线程使用时输出不产生乱序或截断等。当日志文件大于 1MB 时，需执行备份操作。
参数 level：C 字符串，可能的 level 包括：Normal，Warning，Alert，Error 等。
参数 str：C 字符串，用户需要输出的日志信息。
返回值：符合要求返回 0，否则返回-1.
提示：使用标准线程库，可使用互斥量保证线程安全，尝试 RAII 用法。*/
{
	if (!level || !str || !logfile)
		return -1;
	thread td(old_log_file, level, str);
	td.join();
	
	return 0;
}

