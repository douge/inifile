//system
#include "pch.h"

//cpp

//stl
#include <fstream>

//mine
#include "CIniFile.h"

CIniFile::CIniFile() {
}

CIniFile::~CIniFile() {
}

int CIniFile::Load(const string& file_path) {
	int ret = 0;
	fstream infs;
	string line;
	string key, value; //ini item块中的key和value
	//string section_head;
	string commnet;
	SectionItem section_item;
	infs.open(file_path, ios::binary | ios::in);
	if (!infs.is_open())return ERR_READ_FILE; //读取文件失败
	while (getline(infs, line)) {
		if (isComment(line)) {
			commnet = line + "\n";
			continue;
		}
		if (isSectionHead(line)) {//section头
			section_item.clear(); //清空section
			if (hasRightComment(line, commnet)) {
				section_item.right_comment = commnet;
				commnet.clear();
			}
			section_item.key = trimSectionHead(line);
			section_item.comment = commnet;
			commnet.clear();
			m_map[section_item.key] = section_item;//将section存储
			continue;
		}
		
		IniItem ini_item;
		ini_item.comment = commnet;
		if (hasRightComment(line, commnet)) {
			ini_item.right_comment = commnet;
		}
		getKeyAndValue(line, ini_item.key, ini_item.value);		
		m_map[section_item.key].vec_item.push_back(ini_item);
	}
	return ERR_NONE;
}

int CIniFile::GetStringValue(const string & section, const string & item, string & value){
	string temp;
	if (m_map.find(section) == m_map.cend())return ERR_NOT_FIND;
	for(auto iter=m_map[section].vec_item.cbegin();iter!=m_map[section].vec_item.cend();++iter){
		if (iter->key.substr(0,item.size()) == item) {
			temp = iter->value;
		}
	}
	value = temp;
	trimStringHead(value, ' ');
	trimStringTail(value, ' ');
	if (temp.empty())return ERR_NOT_FIND;
	return ERR_NONE;
}

int CIniFile::SetStringValue(const string & section, const string & item, const string & value) {
	string temp;
	if (m_map.find(section) == m_map.cend()) {//不存在section，直接写入
		SectionItem section_item_temp;
		section_item_temp.key = section;
		IniItem ini_item_temp;
		ini_item_temp.key = item;
		ini_item_temp.value = value;
		section_item_temp.vec_item.push_back(ini_item_temp);
		m_map[section] = section_item_temp;
	}
	else {
		for (auto iter = m_map[section].vec_item.begin(); iter != m_map[section].vec_item.end(); ++iter) {
			if (iter->key.substr(0, item.size()) == item) {
				iter->value = value;
			}
		}
	}
	return ERR_NONE;
}

int CIniFile::GetIntValue(const string & section, const string & item, int & value){
	string temp;
	GetStringValue(section, item, temp);
	value = atoi(temp.c_str());
	return ERR_NONE;
}

int CIniFile::SetIntValue(const string & section, const string & item, const int & value){
	SetStringValue(section, item, to_string(value));
	return ERR_NONE;
}

bool CIniFile::isComment(const string & line){
	string temp = line;
	//trimString(temp, ' ');
	if (temp.size() > 2) {
		if (temp[0] == '/'&&temp[1] == '/')return true; //"//"备注格式
	}
	if (temp.size() > 0) {
		if (temp[0] == '#')return true; // #备注格式
	}
	else {
		return true;  // 空行
	}
	return false;
}

bool CIniFile::hasRightComment(const string & line, string & right_comment)
{
	string temp = line;
	int pos = temp.rfind('/');
	if (pos != string::npos && pos > 0) {
		if (temp[pos - 1] == '/')return true;
	}
	return false;
}

bool CIniFile::isSectionHead(const string & line){
	string temp = line;
	//trimString(temp, ' ');
	if (temp.size() > 2) {
		if (temp[0] == '['&&temp.find(']') != string::npos)return true;
	}
	return false;
}

string CIniFile::trimSectionHead(const string & line){
	string ret;
	string temp = line;
	int begin_pos = temp.find('[');
	int end_pos = temp.find(']');
	if (begin_pos == string::npos || end_pos == string::npos)return ret;//没有找到
	ret = temp.substr(begin_pos + 1, end_pos - begin_pos - 1);
	return ret;
}

int CIniFile::getKeyAndValue(const string & line, string & key, string & value){
	string temp = line;
	//trimString(temp, ' ');
	int pos = temp.find('=');
	if (pos != string::npos && pos < (temp.size() - 1)) {
		key = temp.substr(0, pos);
		value = temp.substr(pos + 1);
	}
	return 0;
}

void CIniFile::trimString(string & line, char c){
	int index = 0;
	do {
		index = line.find(c);
		if (index != string::npos)line.erase(index, 1);
	} while (index != string::npos);
}

void CIniFile::trimStringHead(string & line, char c){
	while (true) {
		if (line[0] == c) {
			line.erase(0, 1);
		}
		else {
		    break;
		}
	}
}

void CIniFile::trimStringTail(string & line, char c){
	while (true){
		if (line[line.length() - 1] == c) {
			line.erase(line.length() - 1, 1);
		}
		else {
		    break;
		}
	}
}
