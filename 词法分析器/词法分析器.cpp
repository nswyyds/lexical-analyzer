#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <map>

using namespace std;

string str;
int biaoshi_rukou = 0;
multimap<string, int> m_reserved_word;//�����ּ���
multimap<string, int> m_character;//���������
multimap<string, int> m_symbolch;//�ָ�������
multimap<string, int> m_biaoshi;//�����ʶ����ڵ�ַ

void Init_data();//��ȡ�ļ�����
void Init_analy();//��ʼ���ؼ��ּ���
int word_analy(string);//�ؼ��ַ���
void words_separate(string);//�������
bool integer_ch(char x);//�жϵ����ַ��Ƿ�Ϊ����
bool character(char x);//�ж��Ƿ�Ϊ��ĸ
void Init_result_m(string,int);//������
void createstr();//����Ԥ������֮����ӿո�
void insert(int);//���ַ���ĳλ�ò����ַ�

int main() {
	
	Init_data();
	Init_analy();

	cout << "��ʶ�����ֱ���Ϊ-1������Ϊ-2��������Ϊ-3�������Ϊ-4�����Ϊ-5��" << endl;
	cout << "�ֱ���" << "\t\t" << "����ֵ" << endl;
	words_separate(str);
	cout << str << endl;

	return 0;
}

void Init_data() {
	ifstream ifs;
	ostringstream buf;
	char ch;
	ifs.open("data.txt", ios::in);

	if (!ifs.is_open()) {
		cout << "�ļ���ʧ��" << endl;
	}

	while (buf && ifs.get(ch)) {

		buf.put(ch);
	}
	str = buf.str();
	ifs.close();
	createstr();
	str += ' ';
}

void Init_analy() {
	m_reserved_word.insert({"if",0});
	m_reserved_word.insert({ "then",1 });
	m_reserved_word.insert({ "else",2 });
	m_reserved_word.insert({ "while",3 });
	m_reserved_word.insert({ "do",4 });
	m_reserved_word.insert({ "auto",5 });
	m_reserved_word.insert({ "int",6 });
	m_reserved_word.insert({ "double",7 });
	m_reserved_word.insert({ "for",8 });
	m_reserved_word.insert({ "void",9 });
	m_reserved_word.insert({ "string",10 });
	m_reserved_word.insert({ "cout",11 });


	m_character.insert({ ">", 12 });
	m_character.insert({ "<",13 });
	m_character.insert({ "=",14 });
	m_character.insert({ ">=",15 });
	m_character.insert({ "<=",16 });
	m_character.insert({ "&&",17 });
	m_character.insert({ "||",18 });
	m_character.insert({ "+",19 });
	m_character.insert({ "-",20 });
	m_character.insert({ "*",21 });
	m_character.insert({ "/",22 });
	m_character.insert({ ">>",23 });
	m_character.insert({ "<<",24 });
	m_character.insert({ ":=",25 });

	m_symbolch.insert({ ";",26 });
	m_symbolch.insert({ "(",27 });
	m_symbolch.insert({ ")",28 });
	m_symbolch.insert({ "{",29 });
	m_symbolch.insert({ "}",30 });
	m_symbolch.insert({ "[",31 });
	m_symbolch.insert({ "]",32 });
	m_symbolch.insert({ """",33 });
	m_symbolch.insert({ "'",34 });
	m_symbolch.insert({ "<",35 });
	m_symbolch.insert({ ">",36 });

}

void words_separate(string linshi) {
	char ch_read;
	string str_identify;
	int x = 0;
	string str0 = linshi;
	for (int i = 0; str0[i] != '\0'; i++) {

		ch_read = str0[i];

		if (ch_read != ' ' && ch_read != '\n' && ch_read != '\t') {
			str_identify += ch_read;
		}
		else if (str_identify != "") {
			x = word_analy(str_identify);
			Init_result_m(str_identify, x);
			str_identify = "";
		}
	}

}

int word_analy(string linshi) {
	int result = 0;
	int length = linshi.size();
	int i;

	multimap<string, int>::iterator ite_character;
	multimap<string, int>::iterator ite_reserved_word;
	multimap<string, int>::iterator ite_symbolch;
	multimap<string, int>::iterator ite_bool;

	ite_character = m_character.end();
	ite_reserved_word = m_reserved_word.end();
	ite_symbolch = m_symbolch.end();

	//�ж��Ƿ�Ϊ������
	ite_bool = m_reserved_word.find(linshi);
	if (ite_bool != ite_reserved_word) {
		return 3;
	}

	//�ж��Ƿ�Ϊ�����
	ite_bool = m_character.find(linshi);
	if (ite_bool != ite_character) {
		return 4;
	}
	

	//�ж��Ƿ�Ϊ���
	ite_bool = m_symbolch.find(linshi);
	if (ite_bool != ite_symbolch) {
		return 5;
	}


	//�ж��Ƿ�Ϊ����
	for (i = 0; i < length; i++) {
		if (integer_ch(linshi[i]) == false) {
			i = length + 1;
		}
	}
	if (i == length) {
		return 2;
	}

	//�ж��Ƿ�Ϊ��ʶ��
	if (integer_ch(linshi[0]) == true) {
		return 0;
	}
	for (i = 0; i < length; i++) {
		if (integer_ch(linshi[i]) == false && character(linshi[i]) == false) {
			return 0;
		}
	}
	m_biaoshi.insert({linshi, biaoshi_rukou});
	biaoshi_rukou++;

	return 1;

}

bool integer_ch(char x) {
	if (x >= '0' && x <= '9') {
		return true;
	}
	return false;
}

bool character(char x) {
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z')) {
		return true;
	}
	return false;
}

void Init_result_m(string linshi, int x) {
	if (x == 0) {
		cout << linshi << "\terror" << endl;
	}
	else if (x == 1) {
		cout << -1 << "\t\t" << to_string(m_biaoshi.find(linshi)->second) << endl;
	}
	else if (x == 2) {
		cout << -2 << "\t\t" << linshi << endl;
	}
	else if (x == 3) {
		cout << m_reserved_word.find(linshi)->second << "\t\t" << linshi << endl;
	}
	else if (x == 4) {
		cout << m_character.find(linshi)->second << "\t\t" << linshi << endl;

	}
	else if (x == 5) {
		cout << m_symbolch.find(linshi)->second << "\t\t" << linshi << endl;
	}
}

void insert(int i) {
	string st1 = "";
	int length = str.size();
	for (int j = 0; j <= i; j++) {
		st1 += str[j];
	}
	st1 += " ";
	for (int j = i + 2; j < length + 1; j++) {
		st1 += str[j - 1];
	}
	str = st1;
}

bool different(char i, char j) {
	if ((integer_ch(str[i]) == true || character(str[i]) == true) && (integer_ch(str[j]) == true || character(str[j]) == true)) {
		return false;
	}
	if ((str[i] == '>' || str[i] == '=' || str[i] == '<' || str[i] == '|' || str[i] == '&' || str[i] == ':') && ((str[j] == '>' || str[j] == '=' || str[j] == '<' || str[j] == '|' || str[j] == '&' || str[j] == ':'))) {
		return false;
	}
	return true;
}

void createstr() {
	int length = str.size();
	int i = 0;

	while (i != length - 1) {
		if (str[i] == ' ' || str[i + 1] == ' ') {
			i++;
			length = str.size();
			continue;
		}
		if (different(i, i + 1) == true) {
			insert(i);
			length = str.size();
		}
		i++;
		length = str.size();
	}

}