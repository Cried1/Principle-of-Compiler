#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

class wordAna {
private:
	int temprow;
	int row, line = 1;
	char ch;
	vector<string> IDlist;
	vector<string> Constlist;
	set<string> ReservedWord;
	string strToken;
	fstream f;
public:
	void GetChar()
	{
		if (f.peek() != EOF)
		{
			f.get(ch);
			//cout << ch;
			temprow = row;
			row++;
			if (ch == '\n') {
				line++;
				temprow = row;
				row = 0;
			}
		}
		else ch = ' ';
	}

	void GetBC()
	{
		while (ch == ' ' || ch == '\n' || ch == '\t')
		{
			if (f.peek() != EOF)
			{
				f.get(ch);
				temprow = row;
				row++;
				if (ch == '\n') {
					line++;
					temprow = row;
					row = 0;
				}
			}
		}
	}

	void Concat()
	{
		strToken += ch;
	}

	bool IsLetter()
	{
		if (ch <= 'z'&&ch >= 'a' || ch >= 'A'&&ch <= 'Z')
		{
			return true;
		}
		else return false;
	}

	bool IsDigit()
	{
		if (ch <= '9'&&ch >= '0')
		{
			return true;
		}
		else return false;
	}

	int Reverse(string s)
	{
		int i;
		for (i = 1; i < (int)IDlist.size(); i++)
		{
			if (s.compare(IDlist[i]) == 0)
				return i;
		}
		return 0;
	}

	void Retract()
	{
		if (f.peek() != EOF)
		{
			if (ch == '\n') {
				line--;
				f.seekg(-1, ios::cur);
				row = temprow - 1;
			}
			else {
				ch = ' ';
				f.seekg(-1, ios::cur);
				temprow = row;
				row--;
			}
		}
	}

	int InsertId(string s)
	{
		IDlist.push_back(s);
		return IDlist.size() - 1;
	}

	int InsertConst(string s)
	{
		Constlist.push_back(s);
		return Constlist.size() - 1;
	}

	string Exception(int type)
	{
		switch (type)
		{
		case 1:
			printf("%d行%d列:后可能缺少=\n", row, line);
			break;
		case 2:
			printf("%d行%d列使用了数字开头的标识符\n", row, line);
			break;
		case 3:
			printf("%d行%d列多输入了一个=\n", row, line);
			break;
		default:
			printf("%d行%d列error\n", row, line);
		}
		return "";
	}


	string wordAnalysis()
	{
		int code, value;
		strToken = "";
		char res[1024];
		GetChar();
		GetBC();
		if (IsLetter())
		{
			while (IsLetter() || IsDigit())
			{
				Concat();
				GetChar();
			}
			Retract();
			if (ReservedWord.find(strToken) != ReservedWord.end())
			{
				sprintf_s(res, "<%s,-,(%d,%d)>", strToken.c_str(), row, line);
				return res;
			}
			code = Reverse(strToken);
			if (code == 0)
			{
				value = InsertId(strToken);
				sprintf_s(res, "<id,%d,(%d,%d)>", value, row, line);
				return res;
			}
			else
			{
				sprintf_s(res, "<id,%d,(%d,%d)>", code, row, line);
				return res;
			}
		}
		else if (IsDigit())
		{
			while (IsDigit())
			{
				Concat();
				GetChar();
			}
			Retract();
			if (ch == ' ' || ch == '\n' || ch == '\t')
			{
				value = InsertConst(strToken);
				sprintf_s(res, "<integer,%d,(%d,%d)>", value, row, line);
				return res;
			}
			else return Exception(2);

		}
		else if (ch == '=')
		{
			sprintf_s(res, "<=,-,(%d,%d)>", row, line);
			return res;
		}
		else if (ch == '+')
		{
			sprintf_s(res, "<+,-,(%d,%d)>", row, line);
			return res;
		}
		else if (ch == '*')
		{
			sprintf_s(res, "<*,-,(%d,%d)>", row, line);
			return res;
		}
		else if (ch == '-')
		{
			sprintf_s(res, "<-,-,(%d,%d)>", row, line);
			return res;
		}
		else if (ch == '/')
		{
			sprintf_s(res, "</,-,(%d,%d)>", row, line);
			return res;
		}

		else if (ch == '<') {
			GetChar();
			if (ch == '>')
			{
				sprintf_s(res, "<<>,-,(%d,%d)>", row, line);
				return res;
			}
			else if (ch == '=')
			{
				sprintf_s(res, "<<=,-,(%d,%d)>", row, line);
				return res;
			}
			else
			{
				sprintf_s(res, "<<,-,(%d,%d)>", row, line);
				Retract();
				return res;
				
			}
		}
		else if (ch == '>') {
			GetChar();
			if (ch == '=')
			{
				sprintf_s(res, "<>=,-,(%d,%d)>", row, line);
				return res;
			}
			else
			{
				sprintf_s(res, "<>,-,(%d,%d)>", row, line);
				Retract();
				return res;
				
			}
		}
		else if (ch == ';')
		{
			//处理分号后接block错误
			sprintf_s(res, "<;,-,(%d,%d)>", row, line);
			return res;
		}
		else if (ch == ',')
		{
			//处理逗号错误
			sprintf_s(res, "<,,-,(%d,%d)>", row, line);
			return res;
		}
		else if (ch == '(')
		{
			sprintf_s(res, "<(,-,(%d,%d)>", row, line);
			return res;
		}
		else if (ch == ')')
		{
			sprintf_s(res, "<),-,(%d,%d)>", row, line);
			return res;
		}
		else if (ch == '{')
		{
			sprintf_s(res, "<{,-,(%d,%d)>", row, line);
			return res;
		}
		else if (ch == '}')
		{
			sprintf_s(res, "<},-,(%d,%d)>", row, line);
			return res;
		}
		else if (ch == ':')
		{
			GetChar();
			if (ch == '=')
			{
				sprintf_s(res, "<:=,-,(%d,%d)>", row, line);
				GetChar();
				if (ch == '=')
				{
					Exception(3);
				}
				else Retract();
				return res;
			}
			else
			{
				Retract();
				return Exception(1);
			}
		}
		else
		{
			return "";
		}

	}

	void store()
	{
		fstream word, Reserved;
		string res, input;
		string name;
		cout << "请输入测试文件名：";
		cin >> name;
		f.open(name, ios::in);
		Reserved.open("保留字.txt", ios::in);
		word.open("word.txt", ios::out);
		fstream f_ID;
		fstream f_int;
		f_ID.open("ID.txt", ios::out);
		f_int.open("int.txt", ios::out);
		while (Reserved.peek() != EOF)
		{
			Reserved >> input;
			ReservedWord.insert(input);
		}
		IDlist.push_back("error");
		while (f.peek() != EOF)
		{
			res = wordAnalysis();
			if(res!="") word << res << endl;
		}
		for (int i = 0; i < (int)IDlist.size(); i++)
		{
			f_ID << IDlist[i] << endl;
		}
		for (int i = 0; i < (int)Constlist.size(); i++)
		{
			f_int << Constlist[i] << endl;
		}
		f_ID.close();
		f_int.close();
	}
};
