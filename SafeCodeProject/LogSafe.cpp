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
/*���ܣ���ʼ����־ģ�飬������־�ļ���ŵ�·����
���� path��ָ��һ���ļ�·���� C �ַ�����
����ֵ����־�ļ������ɹ����� 0�����򷵻�-1.
��ʾ����ʹ�� C �������ļ� IO ������*/
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
/*���ܣ����ַ��� str �������־�ļ��У����� level �ַ��������������־��Ϣ����־��ʽ��Level || �߳� id || ʱ���� || str �ַ�����Ҫ��ʵ���̰߳�ȫ��ȷ�����߳�ʹ��ʱ��������������ضϵȡ�����־�ļ����� 1MB ʱ����ִ�б��ݲ�����
���� level��C �ַ��������ܵ� level ������Normal��Warning��Alert��Error �ȡ�
���� str��C �ַ������û���Ҫ�������־��Ϣ��
����ֵ������Ҫ�󷵻� 0�����򷵻�-1.
��ʾ��ʹ�ñ�׼�߳̿⣬��ʹ�û�������֤�̰߳�ȫ������ RAII �÷���*/
{
	if (!level || !str || !logfile)
		return -1;
	lock_guard<mutex> lck(mtx); // RAII��ʽ�Ļ��������������٣������ӾͲ��Լ�����
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
		if (flag) {    //��Ҷ�˵Ҫ��������
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
/*���ܣ����ַ��� str �������־�ļ��У����� level �ַ��������������־��Ϣ����־��ʽ��Level || �߳� id || ʱ���� || str �ַ�����Ҫ��ʵ���̰߳�ȫ��ȷ�����߳�ʹ��ʱ��������������ضϵȡ�����־�ļ����� 1MB ʱ����ִ�б��ݲ�����
���� level��C �ַ��������ܵ� level ������Normal��Warning��Alert��Error �ȡ�
���� str��C �ַ������û���Ҫ�������־��Ϣ��
����ֵ������Ҫ�󷵻� 0�����򷵻�-1.
��ʾ��ʹ�ñ�׼�߳̿⣬��ʹ�û�������֤�̰߳�ȫ������ RAII �÷���*/
{
	if (!level || !str || !logfile)
		return -1;
	thread td(old_log_file, level, str);
	td.join();
	
	return 0;
}

