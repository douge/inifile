// ini_file.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//system
#include "pch.h"

//cpp

//stl
#include <iostream>

//mine
#include "CIniFile.h"


int main(){
    std::cout << "Hello World!\n"; 
	CIniFile ini_file;
	ini_file.Load("C:/Users/dou/Downloads/inifile2-master/inifile2-master/test/new.ini");
	string value;
	
	ini_file.SetStringValue("Translation", "TRANSLATION_NAME", "test");
	ini_file.GetStringValue("Translation", "TRANSLATION_NAME", value);
	return 0;
}
