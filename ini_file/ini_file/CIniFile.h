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
	string key;//����
	string value;//��ֵ
	string comment;//��ע�ͣ����Ϸ�
	string right_comment;//�Ҳ�ע��
}IniItem;

typedef struct section_item
{
	void clear() {
		key.clear();
		vec_item.clear();
		comment.clear();
		right_comment.clear();
	}
	string key;//��ֵ
	vector<IniItem> vec_item;//section�е�����
	string comment;//��ע�ͣ����Ϸ�
	string right_comment;//�Ҳ�ע��
}SectionItem;

class CIniFile 
{
public:
	CIniFile();
	virtual ~CIniFile();
	int Save(const string& file_path);//���������ļ�
	int Load(const string& file_path);//��ȡ�����ļ�
	int GetStringValue(const string& section, const string& item, string& value);//��ȡstring����ֵ
	int SetStringValue(const string& section, const string& item, const string& value);//����string����ֵ
	int GetIntValue(const string& section, const string& item, int& value);//��ȡint��������
	int SetIntValue(const string& section, const string& item, const int& value);//����int��������

protected:
	bool isComment(const string& line);//�ж��Ƿ��Ǳ�ע��Ϣ
	bool hasRightComment(const string& line, string& right_comment);//�ж��Ƿ�����Ҳ�ע��
	bool isSectionHead(const string& line);//�ж��Ƿ���sectionͷ
	string trimSectionHead(const string& line);//��ȡsectionͷ
	int getKeyAndValue(const string& line, string& key, string& value);//��ȡkey=value�е�key��value
	void trimString(string& line, char c);//��line��cȫ��ȥ��
	void trimStringHead(string& line, char c);//��lineǰ����cȫ��ȥ��
	void trimStringTail(string& line, char c);//��lineβ����cȫ��ȥ��

	unordered_map<string, SectionItem> m_map;//����ini�ļ�����
};