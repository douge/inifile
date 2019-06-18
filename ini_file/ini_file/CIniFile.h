#pragma once
//system

//cpp

//stl
#include <string>
#include <unordered_map>
#include <vector>

//mine

using namespace std;

#define ERR_NONE     0
#define ERR_READ_FILE 1
#define ERR_NOT_FIND  2

typedef struct ini_item
{
	string key;//索引
	string value;//键值
	string comment;//行注释，在上方
	string right_comment;//右侧注释
}IniItem;

typedef struct section_item
{
	void clear() {
		key.clear();
		vec_item.clear();
		comment.clear();
		right_comment.clear();
	}
	string key;//键值
	vector<IniItem> vec_item;//section中的内容
	string comment;//行注释，在上方
	string right_comment;//右侧注释
}SectionItem;

class CIniFile 
{
public:
	CIniFile();
	virtual ~CIniFile();
	int Save(const string& file_path);//保存配置文件
	int Load(const string& file_path);//读取配置文件
	int GetStringValue(const string& section, const string& item, string& value);//获取string类型值
	int SetStringValue(const string& section, const string& item, const string& value);//设置string类型值
	int GetIntValue(const string& section, const string& item, int& value);//获取int类型数据
	int SetIntValue(const string& section, const string& item, const int& value);//设置int类型数据

protected:
	bool isComment(const string& line);//判断是否是备注信息
	bool hasRightComment(const string& line, string& right_comment);//判断是否包含右侧注释
	bool isSectionHead(const string& line);//判断是否是section头
	string trimSectionHead(const string& line);//提取section头
	int getKeyAndValue(const string& line, string& key, string& value);//获取key=value中的key和value
	void trimString(string& line, char c);//将line中c全部去掉
	void trimStringHead(string& line, char c);//将line前方的c全部去掉
	void trimStringTail(string& line, char c);//将line尾部的c全部去掉

	unordered_map<string, SectionItem> m_map;//保存ini文件内容
};