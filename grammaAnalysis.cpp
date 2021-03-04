#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include "wordAnalysis.cpp"
#include "Table.cpp"
#include "genCode.cpp"
#include "execution.cpp"
#include "backfill.cpp"
using namespace std;

stringstream str2int; 

class languageAna
{
private:
	string row,line;
	string lrow, lline;//�ϸ����ʵ�λ��,�����
	string word;
	string type;
	string value;
	fstream f;
	vector<string> IDlist;//id��
	vector<int> Constlist;//���ֱ�
	fstream f_ID;
	fstream f_int;
	int flag;
	string name;//����,ID������ͨ��IDlistת������ʵ��ID
	string kind;//����
	int val;//ֵ,������ֵͨ��������ת������ʵ����
	int level;//Ƕ�ײ���
	string outer;
	string nowname;
	//int size;//�洢�ռ�
	int address;//address�Ǳ���������ڻ���ַ��ƫ����
	Table T;
	genCode GC;
	backFill BF;
public:
	languageAna()
	{
		row = "0", line = "0";
		flag = 0;
		string input;
		int inputInt;
		f_ID.open("ID.txt", ios::in);
		f_int.open("int.txt", ios::in);
		f.open("word.txt", ios::in);
		//size = 4;
		while (f_ID.peek() != EOF)//����id��
		{
			f_ID >> input;
			IDlist.push_back(input);
		}
		while (f_int.peek() != EOF)//�������ֱ�
		{
			f_int >> inputInt;
			Constlist.push_back(inputInt);
		}
	}
	void getword()
	{
		if (f.peek() != EOF)
		{
			getline(f, word);
		}
		else word = "<EOF,-,(-1,-1)>";

		regex pattern("^<(\,|.*?)\,(.*?)\,\(.*?\)>$");
		regex pattern2("^(.*?)\,(.*?)$");
		smatch results;
		string rowline;
		regex_match(word, results, pattern);
		type = results[1];
		value = results[2];
		rowline = results[3];
		rowline.erase(rowline.begin());
		rowline.erase(rowline.end() - 1);
		regex_match(rowline, results, pattern2);
		lrow = row;
		lline = line;
		row = results[1];
		line = results[2];
		str2int.clear();
		str2int << value;
		str2int >> val;
		if (type == "id")
		{
			name = IDlist[val];
		}
		else if (type == "integer")
		{
			val = Constlist[val];
		}
		
	}
	
	void Exceptions(int type)
	{
		if (flag == 0) flag = 1;
		if (lline == "-1") return;
		if (type == 1)
		{
			cout << lline << "��" << lrow << "�п���ȱ��program�ؼ���" << endl;
			return;
		}
		else if (type == 2)
		{
			cout << lline << "��" << lrow << "�п���ȱ��id�ؼ���" << endl;
			return;
		}
		else if (type == 3)
		{
			cout << lline << "��" << lrow << "�п���ȱ��;" << endl;
			return;
		}
		else if (type == 4)
		{
			cout << lline << "��" << lrow << "��ȱ��const��" << endl;
			return;
		}
		else if (type == 5)
		{
			cout << lline << "��" << lrow << "��ȱ��," << endl;
			return;
		}
		else if (type == 6)
		{
			cout << lline << "��" << lrow << "��ȱ��:=" << endl;
			return;
		}
		else if (type == 7)
		{
			cout << lline << "��" << lrow << "��ȱ��integer" << endl;
			return;
		}
		else if (type == 8)
		{
			cout << lline << "��" << lrow << "��ȱ��)" << endl;
			return;
		}
		else if (type == 9)
		{
			cout << lline << "��" << lrow << "��ȱ��begin" << endl;
			return;
		}
		else if (type == 10)
		{
			cout << lline << "��" << lrow << "��ȱ��statement�ؼ���" << endl;
			return;
		}
		else if (type == 11)
		{
			cout << lline << "��" << lrow << "��ȱ��end" << endl;
			return;
		}
		else if (type == 12)
		{
			cout << lline << "��" << lrow << "��ȱ��lop����" << endl;
			return;
		}
		else if (type == 13)
		{
			cout << lline << "��" << lrow << "��ȱ��exp" << endl;
			return;
		}
		else if (type == 14)
		{
			cout << lline << "��" << lrow << "��ȱ��do" << endl;
			return;
		}
		else if (type == 15)
		{
			cout << lline << "��" << lrow << "��ȱ��then" << endl;
			return;
		}
		else if (type ==16)
		{
			cout << lline << "��" << lrow << "��ȱ��(" << endl;
			return;
		}
		else if (type == 17)
		{
			cout << lline << "��" << lrow << "�б���δ����" << endl;
			return;
		}
		else if (type == 18)
		{
			cout << lline << "��" << lrow << "�жԷǱ�����ֵ" << endl;
			return;
		}
		else if (type == 19)
		{
			cout << lline << "��" << lrow << "��ȱ��:" << endl;
			return;
		}
		else if (type == 20)
		{
			cout << lline << "��" << lrow << "���ظ����̶���" << endl;
			return;
		}
		else if (type == 21)
		{
			cout << lline << "��" << lrow << "�б����ظ�����" << endl;
			return;
		}
		else if (type == 22)
		{
			cout << lline << "��" << lrow << "�жԳ�����ֵ" << endl;
			return;
		}
		else if (type == 23)
		{
			cout << lline << "��" << lrow << "�й����������" << endl;
			return;
		}
		else if (type == 24)
		{
			cout << lline << "��" << lrow << "�е��ò���������ƥ��" << endl;
			return;
		}
		else if (type == 25)
		{
			cout << lline << "��" << lrow << "��ȱ��(" << endl;
			return;
		}
		else if (type == 26)
		{
			cout << lline << "��" << lrow << "�б����������̲��ܸ�ֵ" << endl;
			return;
		}
		else if (type == 27)
		{
			cout << lline << "��" << lrow << "�б����������̳�������" << endl;
			return;
		}
		else if (type == 28)
		{
			cout << lline << "��" << lrow << "��ȱ�ٿ��Ե��õĹ���" << endl;
			return;
		}
		else if (type == 30)
		{
			cout << lline << "��" << lrow << "�г����ظ�����" << endl;
			return;
		}
		else if (type == 31)
		{
			cout << lline << "��" << lrow << "���Ѿ�������ͬ���ı���" << endl;
			return;
		}
		else if (type == 32)
		{
			cout << lline << "��" << lrow << "���Ѿ�������ͬ���ĳ���" << endl;
			return;
		}
	}

	int prog() {
		getword();
		if (type == "program")
		{
			getword();
			if (type == "id")
			{
				outer = "";
				nowname = name;
				getword();
				if (type == ";")
				{
					block();
				}
				else {
					Exceptions(3);
					block();
				}
			}
		}
		else
		{
			Exceptions(1);//ȱ��program
			if (type == "id")
			{
				outer = "";
				nowname = name;
				getword();
				if (type == ";")
				{
					block();
				}
				else {
					Exceptions(3);
					block();
				}
			}
			else {
				Exceptions(2);
				if (type == ";")
				{
					block();
				}
				else if (type == "const" || type == "var" || type == "procedure" || type == "begin") {
					Exceptions(3);
					block();
				}
			}
		}
		//δ�������
		return 0;
	}

	int block()
	{
		//addressָ���Ѿ����˴������һ��λ��,��0��ʼ
		int address0=address;//����block�ȱ���address �� Tx(��ָ��)
		int tx0 = T.getTx();
		int position;
		TableItem *Tp;
		Tp = T.getItems();
		if (tx0 > 0)
		{
			position = T.getLevelProc(outer,nowname);
			tx0 = tx0 - Tp[position].size;//tx0ָ��ǰ���̵ĵ�һ��Table����
			//Ϊʲô������Ҫtx0
		}
		//positionָ�򱾲���ű�ĳ�ʼλ��
		//tx0ָ����ű��ѷ��õ���һλ
		if (tx0 == 0)
		{//tx0=0��ʾ��������,����address���3
			address = 3;      //ÿһ���ʼλ�õ������ռ�������ž�̬��SL����̬��DL���ͷ��ص�ַRA
		}
		else {
			//ÿһ���ʼλ�õ������ռ�������ž�̬��SL����̬��DL���ͷ��ص�ַRA
			//�����ŷŲ���
			address = 3 + T.getItems()[position].size;
		}
		int codePtr0 = GC.getCodePtr();
		GC.gen("JMP", 0, 0);//��ִ�д���ǰ��������ת,��������Ĺ���,��ת������������
		//�����ǳ���,����,�ӹ��̵Ķ���
		if (!(type == "const" || type == "var" || type == "procedure" || type == "begin"))
			getword();
		if (type == "const")
			condecl();
		if (type == "var")
			valdecl();
		if (type == "procedure"){
			proc();
		}
		Tp = T.getItems();
		//������������jmp,��ת���˴�λ�ÿ�ʼִ��
		//�������
		//block�ȶԱ������и�ֵ
		GC.getCodes()[codePtr0].A=GC.getCodePtr();//��ת����������֮��ľ�������
		GC.gen("INT", 0, address);        //����������еı����붯̬����̬�����ص�ַ����ռ�,3+������
		if (tx0 != 0)
		{
			//���ڶ������еݹ�ᵼ�����ȥ,��������һ����������
			T.getItems()[position].val = GC.getCodePtr() - 1; 
			//BF.reFill(T.getItems()[position], GC);
			BF.setTarget(T.getItems()[position], GC);
			//���ű��е�ֵ��Ϊ������ִ����俪ʼ��λ��,GC��CP��ָ�����ɴ������һ��,�����Ҫ-1
			//��T.getItems()[position].size�Ƕ�������еĲ���
			//����Ľ������ָ����δ����������ʼλ��proc��val�Ǽ�¼����ʼλ��
		}
		body();
		GC.gen("OPR", 0, 0);//���̽������� ���ص��õ㲢��ջ
		//���̽����ָ�address
		address = address0;
		//T.setTx(tx0);
		return 0;
	}

	int condecl()
	{
		if (type == "const") getword();
		if (type == ";")
		{
			Exceptions(4);
			getword();
			return 0;
		}
		myconst();
		while (type == "id" || type == ",")
		{
			if (type == ",") myconst();
			else if (type == "id")
			{
				Exceptions(5);
				myconst();
			}
		}
		if (type == ";") getword();
		else {
			Exceptions(3);
		}
		return 0;
	}

	int myconst()
	{
		string idName;
		if (type != "id")
			getword();
		if (type == "id")
		{
			idName = name;
			getword();
			if (type == ":=")
			{
				getword();
				if (type == "integer")
				{
					int Tptr1 = T.FindConstInNowname(idName,outer,nowname);
					int Tptr2= T.FindVarInNowname(idName, outer, nowname);
					if(Tptr1==-1&& Tptr2==-1)
						T.enterConst(name,val,level,outer, nowname);//ֻ�б���������address
					else if(Tptr1 != -1)
					{
						Exceptions(30);
					}
					else if (Tptr2 != -1)
					{
						Exceptions(31);
					}
					getword();
					return 0;
				}
				else
				{
					Exceptions(7);//ȱ��integer
					return 0;
				}
			}
			else if (type == "=")
			{
				Exceptions(19);
				getword();
				if (type == "integer")
				{
					//T.enterConst(name, val, level, address);//ֻ�б���������address��???
					getword();
					return 0;
				}
				else
				{
					Exceptions(7);//ȱ��integer
					return 0;
				}
			}
			else
			{
				Exceptions(6);
				if (type == "integer")
				{
					getword();
					return 0;
				}
				else
				{
					Exceptions(7);
					return 0;
				}
			}
		}
		else if (type == ":=")
		{
			Exceptions(2);//ȱ��id
			getword();
			if (type == "integer")
			{
				getword();
				return 0;
			}
			else
			{
				Exceptions(7);//ȱ��integer
				return 0;
			}
		}
		return -1;
	}

	int valdecl()
	{
		if (type == "var") getword();
		if (type == ";")
		{
			Exceptions(2);
			getword();
			return 0;
		}
		if (type == "id")
		{
			int Tptr1 = T.FindConstInNowname(name, outer, nowname);
			int Tptr2 = T.FindVarInNowname(name, outer, nowname);
			if ( Tptr1!= -1||Tptr2!=-1)
			{
				if (Tptr1 != -1)
				{
					Exceptions(32);
					getword();
				}
				else if (Tptr2 != -1)
				{
					Exceptions(21);
					getword();
				}
			}
			else
			{
				T.enterVar(name, level, address, outer, nowname);
				address++;
				getword();
			}
		}
		while (type == "," || type == "id"||type==":="||type=="integer")
		{
			if (type == ":=")
			{
				Exceptions(26);
				getword();
			}
			if (type == "integer")
			{
				Exceptions(27);
				getword();
			}
			if (type == ",") 
			{
				getword();
				if (type == "id")
				{
					int Tptr1 = T.FindConstInNowname(name, outer, nowname);
					int Tptr2 = T.FindVarInNowname(name, outer, nowname);
					if (Tptr1 != -1 || Tptr2 != -1)
					{
						if (Tptr1 != -1)
						{
							Exceptions(32);
							getword();
						}
						else if (Tptr2 != -1)
						{
							Exceptions(21);
							getword();
						}
					}
					else
					{
						T.enterVar(name, level, address, outer, nowname);
						address++;
						getword();
					}
				}
			}
			else if (type == "id")
			{
				Exceptions(5);//ȱ��,
				int Tptr1 = T.FindConstInNowname(name, outer, nowname);
				int Tptr2 = T.FindVarInNowname(name, outer, nowname);
				if (Tptr1 != -1 || Tptr2 != -1)
				{
					if (Tptr1 != -1)
					{
						Exceptions(32);
						getword();
					}
					else if (Tptr2 != -1)
					{
						Exceptions(21);
						getword();
					}
				}
				else
				{
					T.enterVar(name, level, address, outer, nowname);
					address++;
					getword();
				}
			}
		}
		if (type == ";") getword();
		else
		{
			Exceptions(3);//ȱ��;
		}
		return 0;

	}

	int id()
	{
		if (type != "id")
			getword();
		if (type == "id")
		{
			getword();
			return 1;
		}
		return 0;
	}

	int proc()//�ӳ�����̻�Ҫ����
	{
		if (type == "procedure") getword();
		int count = 0;//��¼��������
		int position;//��¼proc���ű�λ��
		string outer0;
		string nowname0;
		if (type == ";")
		{
			Exceptions(2);
			getword();
			return 0;
		}
		else if (type == "(")//ȱ��id�ľͲ����з�����
		{
			Exceptions(2);//ȱ��id
			getword();
			id();
			while (type == "," || type == "id")
			{
				if (type == ",") id();
				else if (type == "id")
				{
					Exceptions(5);//ȱ��,
					id();
				}
			}
			if (type == ")")
			{
				getword();
				if (type == ";")
				{
					block();
					while (type == ";" || type == "procedure")
					{
						if (type == ";")
							proc();
						else if (type == "procedure")
						{
							Exceptions(3);
							proc();
						}
					}
				}
			}
			else if (type == ";")
			{
				Exceptions(8);
				block();
				while (type == ";" || type == "procedure")
				{
					if (type == ";")
						proc();
					else if (type == "procedure")
					{
						Exceptions(3);
						proc();
					}
				}
			}
			else if (type == "const" || type == "var" || type == "procedure" || type == "begin")
			{
				Exceptions(3);
				block();
				while (type == ";" || type == "procedure")
				{
					if (type == ";")
						proc();
					else if (type == "procedure")
					{
						Exceptions(3);
						proc();
					}
				}
			}
			return 0;
		}
		if (type == "id")
		{
			if (T.isExitInLevel(name, outer,nowname))
			{
				Exceptions(20);//�����Ѿ������,��֧��ͬһ��ε�ͬ������
			}
			position = T.getTx();//����ӹ��̵ĵ�һ��Table�����ָ��,����size��ʾ��������е�Tableռ�ݵĴ�С
			//T.enterProc(name, level, address, outer, nowname);
			T.enterProc(name, level, outer, nowname);
			TableItem TItem;
			TItem = T.getItems()[T.FindProc(name, outer, nowname)];
			BF.insert(TItem);
			nowname0 = nowname;
			outer0 = outer;
			outer = nowname;
			nowname = name;
			getword();
		}
		level++;//���嶼���ӹ���������
		if (type == "(")
		{
			getword();
			if (type == "id")
			{
				T.enterVar(name, level,count + 3,outer, nowname);//λ�ô�0��ʼ,������3�ſ�ʼ��
				count++;
				T.getItems()[position].size = count;
				getword();
			}

			while (type == "," || type == "id")
			{
				if (type == ",")
				{
					getword();
					if (type == "id")
					{
						T.enterVar(name, level, count + 3, outer, nowname);//λ�ô�0��ʼ,������3�ſ�ʼ��
						count++;
						T.getItems()[position].size = count;
						getword();
					}
				}
				else if (type == "id")
				{
					Exceptions(5);//ȱ��,
					if (type == "id")
					{
						T.enterVar(name, level, count + 3, outer, nowname);//λ�ô�0��ʼ,������3�ſ�ʼ��
						count++;
						T.getItems()[position].size = count;
						getword();
					}
				}
			}
			if (type == ")")
			{
				getword();
				if (type == ";")
				{
					block();
					outer = outer0;
					nowname = nowname0;
					level--;

					while (type == ";" || type == "procedure")
					{
						if (type == ";")
						{
							getword();
							proc();
						}
						else if (type == "procedure")
						{
							Exceptions(3);
							proc();
						}
					}
				}
				else if (type == "const" || type == "var" || type == "procedure" || type == "begin")
				{
					Exceptions(3);
					block();
					outer = outer0;
					nowname = nowname0;
					level--;
					while (type == ";" || type == "procedure")
					{
						if (type == ";")
							proc();
						else if (type == "procedure")
						{
							Exceptions(3);
							proc();
						}
					}
				}

			}
			else if (type == ";")
			{
				Exceptions(8);
				block();
				outer = outer0;
				nowname = nowname0;
				level--;
				while (type == ";" || type == "procedure")
				{
					if (type == ";")
						proc();
					else if (type == "procedure")
					{
						Exceptions(3);
						proc();
					}
				}
			}
			else if (type == "const" || type == "var" || type == "procedure" || type == "begin")
			{
				Exceptions(3);
				block();
				outer = outer0;
				nowname = nowname0;
				level--;
				while (type == ";" || type == "procedure")
				{
					if (type == ";")
						proc();
					else if (type == "procedure")
					{
						Exceptions(3);
						proc();
					}
				}
			}
		}
		else if (type == "id")
		{
			Exceptions(25);
			if (type == "id")
			{
				T.enterVar(name, level, count + 3, outer, nowname);//λ�ô�0��ʼ,������3�ſ�ʼ��
				count++;
				T.getItems()[position].size = count;
				getword();
			}

			while (type == "," || type == "id")
			{
				if (type == ",")
				{
					getword();
					if (type == "id")
					{
						T.enterVar(name, level, count + 3, outer, nowname);//λ�ô�0��ʼ,������3�ſ�ʼ��
						count++;
						T.getItems()[position].size = count;
						getword();
					}
				}
				else if (type == "id")
				{
					Exceptions(5);//ȱ��,
					if (type == "id")
					{
						T.enterVar(name, level, count + 3, outer, nowname);//λ�ô�0��ʼ,������3�ſ�ʼ��
						count++;
						T.getItems()[position].size = count;
						getword();
					}
				}
			}
			if (type == ")")
			{
				getword();
				if (type == ";")
				{
					block();
					outer = outer0;
					nowname = nowname0;
					level--;

					while (type == ";" || type == "procedure")
					{
						if (type == ";")
						{
							getword();
							proc();
						}
						else if (type == "procedure")
						{
							Exceptions(3);
							proc();
						}
					}
				}
				else if (type == "const" || type == "var" || type == "procedure" || type == "begin")
				{
					Exceptions(3);
					block();
					outer = outer0;
					nowname = nowname0;
					level--;
					while (type == ";" || type == "procedure")
					{
						if (type == ";")
							proc();
						else if (type == "procedure")
						{
							Exceptions(3);
							proc();
						}
					}
				}

			}
			else if (type == ";")
			{
				Exceptions(8);
				block();
				outer = outer0;
				nowname = nowname0;
				level--;
				while (type == ";" || type == "procedure")
				{
					if (type == ";")
						proc();
					else if (type == "procedure")
					{
						Exceptions(3);
						proc();
					}
				}
			}
			else if (type == "const" || type == "var" || type == "procedure" || type == "begin")
			{
				Exceptions(3);
				block();
				outer = outer0;
				nowname = nowname0;
				level--;
				while (type == ";" || type == "procedure")
				{
					if (type == ";")
						proc();
					else if (type == "procedure")
					{
						Exceptions(3);
						proc();
					}
				}
			}
			}
		return 0;
	}

	int isStatement(string &type)
	{
		if (type == "id" || type == "if" || type == "while" || type == "call" || type == "begin" || type == "read" || type == "write")
		{
			return 1;
		}
		return 0;
	}

	int body()//���ڶ����ĵ���Ϊbegin�Ϳ�ʼִ��,��Ϊbegin��ʾ��begin��һ��������Ҫ����һ��begin
	{
		if (type != "begin") getword();
		if (type == "begin")
		{
			getword();
			statement();
			while (type == ";" || isStatement(type))//ע������ط�
			{
				if (type == ";") statement();
				else if (isStatement(type))
				{
					Exceptions(3);
					statement();
				}
			}
			if (type == "end")
			{
				getword();
				return 0;
			}
			else
			{
				Exceptions(11);
				return 0;
			}
		}
		else {
			Exceptions(9);//ȱ��begin
			statement();
			while (type == ";" || isStatement(type))//ע������ط�
			{
				if (type == ";") statement();
				else if (isStatement(type))
				{
					Exceptions(3);
					statement();
				}
			}
			if (type == "end")
			{
				getword();
				return 0;
			}
			else
			{
				Exceptions(11);
				return 0;
			}
		}
		return -1;
	}

	int statement()//������ʼ���ȡһ���ַ�,������ö�...
	{
		string target;
		if (!isStatement(type))//˵���ǷֺŽ�����
			getword();
		while(type == ";") {
			getword();
		} 
		if (type == "end") return 0;
		if (type == "id")
		{
			target = name;
			getword();
			if (type == ":=")
			{
				getword();
				exp();
				int Tptr = T.FindVar(target, outer, nowname);
				if (Tptr==-1)
				{
					//����δ����
					Exceptions(17);
				}
				else
				{
					TableItem TItem;
					//������ȷ����Ψһ
					TItem = T.getItems()[Tptr];
					if (TItem.kind == "var")
					{
						GC.gen("STO", level - TItem.lev, TItem.address);
					}
					else {
						//����
						Exceptions(18);
					}
				}
			}
			else if (type == "=")
			{
				Exceptions(19);
				getword();
				exp();
				int Tptr = T.FindVar(target, outer, nowname);
				if (Tptr==-1)
				{
					//����δ����
					Exceptions(17);
				}
				else
				{
					TableItem TItem;
					//������ȷ�����ܻ���ɲ�Ψһ
					TItem = T.getItems()[Tptr];
					if (TItem.kind == "var")
					{
						GC.gen("STO", level - TItem.lev, TItem.address);
					}
					else {
						//����
						Exceptions(18);
					}
				}
			}

		}
		else if (type == "if")
		{
			getword();
			int cp0,cp1;
			lexp();
			if (type == "then")
			{
				cp0 = GC.getCodePtr();
				GC.gen("JPC", 0, 0);//������������ת
				getword();
				statement();
				cp1 = GC.getCodePtr();
				GC.gen("JMP", 0, 0);
				GC.getCodes()[cp0].A = GC.getCodePtr();
				GC.getCodes()[cp1].A = GC.getCodePtr();
				if (type == "else")
				{
					statement();
					GC.getCodes()[cp1].A = GC.getCodePtr();
				}
			}
			else {
				Exceptions(15);
				cp0 = GC.getCodePtr();
				GC.gen("JPC", 0, 0);//������������ת
				statement();
				cp1 = GC.getCodePtr();
				GC.gen("JMP", 0, 0);
				GC.getCodes()[cp0].A = GC.getCodePtr();
				GC.getCodes()[cp1].A = GC.getCodePtr();
				if (type == "else")
				{
					statement();
					GC.getCodes()[cp1].A = GC.getCodePtr();
				}
			}

		}
		else if (type == "while")
		{
			int cp0 = GC.getCodePtr();//while��ʼ�Ĵ�����
			int cp1;
			getword();
			lexp();
			if (type == "do")
			{
				cp1 = GC.getCodePtr();
				GC.gen("JPC", 0, 0);//������������ת
				getword();
				statement();
				GC.gen("JMP", 0, cp0);//���������ת��while��ʼ
				GC.getCodes()[cp1].A = GC.getCodePtr();//while��next����
			}
			else
			{
				Exceptions(14);
				cp1 = GC.getCodePtr();
				GC.gen("JPC", 0, 0);
				statement();
				GC.gen("JMP", 0, cp0);
				GC.getCodes()[cp1].A = GC.getCodePtr();;
			}
		}
		else if (type == "call")
		{
			getword();
			int count = 0;
			int wrongflag = 0;
			TableItem TItem;
			if (type != "(")
			{
				if (type == "id")//cal �������ȵ����ڲ��proc
				{
					int Tptr = T.FindProc(name, outer, nowname);
					if (Tptr!=-1)
					{
						//�����ֶ�����ܻ���ɴ���
						TItem = T.getItems()[Tptr];
						getword();
					}
					else
					{
						Exceptions(28);
						wrongflag = 1;
						getword();
					}

				}
				if (type == "(")
				{
					getword();
					if (type != ")")
					{
						exp();
						count++;
					}
					while (type == ",")
					{
						getword();
						exp();
						count++;
					}
					if (wrongflag==0&&count != TItem.size)
					{
						//�����Ͷ���ʱ�Ĳ�����ͬ
						Exceptions(24);
						getword();
						return -1;
					}
					if(wrongflag==0) GC.gen("LIT", 0, count);
					if (type == ")")
					{
						getword();
						if (wrongflag == 0) BF.insertGC(TItem,GC.getCodePtr());
						if (wrongflag == 0) GC.gen("CAL", level - TItem.lev, TItem.val);
					}
					else
					{
						Exceptions(8);
					}
				}
				else if(type=="id")
				{
					Exceptions(25);
					exp();
					count++;
					while (type == ",")
					{
						getword();
						exp();
						count++;
					}
					if (wrongflag == 0&&count != TItem.size)
					{
						//�����Ͷ���ʱ�Ĳ�����ͬ
						Exceptions(24);
						getword();
						return -1;
					}
					if (wrongflag == 0) GC.gen("LIT", 0, count);
					if (type == ")")
					{
						getword();
						if (wrongflag == 0) BF.insertGC(TItem, GC.getCodePtr());
						if (wrongflag == 0) GC.gen("CAL", level - TItem.lev, TItem.val);
					}
					else
					{
						Exceptions(8);
					}
				}
			}
			else {//û��id�޷�����
				Exceptions(2);
				return -1;
			}
		}
		else if (type == "begin")
		{
			body();
		}
		else if (type == "read")
		{
			getword();
			if (type == "(")
			{
				getword();
				if (type == "id")
				{
					int Tptr = T.FindVar(name,outer, nowname);
					if (Tptr==-1)
					{
						Exceptions(17);
						getword();
						//δ���屨��
					}
					else
					{
						TableItem TItem;
						//ֻ�����ֶ�λ���ܻ���ɴ���
						TItem = T.getItems()[T.FindVar(name, outer, nowname)];
						if (TItem.kind == "var")
						{
							GC.gen("OPR", 0, 16);
							//�������ж���һ����������ջ��
							GC.gen("STO", level - TItem.lev, TItem.address);
							//��ջ����������ĳ������Ԫ�� aΪƫ���� lΪ���
							getword();
						}
						else if (TItem.kind == "const")
						{
							Exceptions(22);
							getword();
						}

					}
				}
				while (type == ",")
				{
					if(type==",") getword();
					if(type=="id")
					{
						int Tptr = T.FindVar(name, outer, nowname);
						if (Tptr==-1)
						{
							Exceptions(17);
							//δ���屨��
						}
						else
						{
							TableItem TItem;
							TableItem *Tp;
							Tp = T.getItems();
							//ֻ�����ֶ�λ���ܻ���ɴ���
							TItem = Tp[Tptr];
							if (TItem.kind == "var")
							{
								GC.gen("OPR", 0, 16);
								GC.gen("STO", level - TItem.lev, TItem.address);
								getword();
							}
							else
							{
								Exceptions(18);
								getword();
							}

						}
					}
				}
				if (type == ")")
				{
					getword();
				}
				else
				{
					Exceptions(8);
				}
			}
			else {
				Exceptions(16);
				if (type == "id")
				{
					id();
					while (type == ",")
					{
						id();
					}
					if (type == ")")
					{
						getword();
					}
					else
					{
						Exceptions(8);
					}
				}
				else {
					if (type == ")")
					{
						getword();
					}
					else
					{
						Exceptions(8);
					}
				}
			}
		}
		else if (type == "write")
		{
			getword();
			if (type == "(")
			{
				getword();
				exp();
				GC.gen("OPR", 0, 14);
				while (type == ",")
				{
					exp();
					GC.gen("OPR", 0, 14);
				}
				GC.gen("OPR", 0, 15);
				if (type == ")")
				{
					getword();
				}
			}
		}
		else
		{
			Exceptions(10);
		}
		return 0;
	}

	int isExp()
	{
		if (type == "+" || type == "-" || type == "id" || type == "integer" || type == "(")
		{
			return 1;
		}
		return 0;
	}

	int lexp()//���뺯���������һ������
	{
		if (type == "odd")
		{
			getword();
			if (isExp()) 
			{
				exp();
				GC.gen("OPR", 0, 6);
			}
			else {
				Exceptions(12);
			}

		}
		else if (isExp()) {
			exp();
			string lopRes = lop();
			if (lopRes!="")
			{
				if (isExp())
				{
					exp();
					if (lopRes == "=") {
						GC.gen("OPR", 0, 8);      //OPR 0 8	��ջ����ջ���Ƿ���ȣ�������ջԪ�أ����ֵ��ջ
					}
					else if (lopRes == "<>") 
					{
						GC.gen("OPR", 0, 9);      //OPR 0 9	��ջ����ջ���Ƿ񲻵ȣ�������ջԪ�أ����ֵ��ջ
					}
					else if (lopRes == "<") 
					{
						GC.gen("OPR", 0, 10);     //OPR 0 10	��ջ���Ƿ�С��ջ����������ջԪ�أ����ֵ��ջ
					}
					else if (lopRes == "<=")
					{
						GC.gen("OPR", 0, 13);     // OPR 0 13	��ջ���Ƿ�С�ڵ���ջ����������ջԪ�أ����ֵ��ջ
					}
					else if (lopRes == ">") 
					{
						GC.gen("OPR", 0, 12);     //OPR 0 12	��ջ���Ƿ����ջ����������ջԪ�أ����ֵ��ջ
					}
					else if (lopRes == ">=")
					{
						GC.gen("OPR", 0, 11);     //OPR 0 11	��ջ���Ƿ���ڵ���ջ����������ջԪ�أ����ֵ��ջ
					}
				}
				else {
					Exceptions(13);
				}
			}
			else {
				Exceptions(12);
				if (isExp())
					exp();
			}
		}
		return 0;
	}

	int exp()
	{
		string tempType = type;
		if (type == "+" || type == "-")
		{
			getword();
		}
		term();
		if (tempType == "-")
		{
			GC.gen("OPR", 0, 1);//ջ��Ԫ��ȡ��
		}
		tempType = aop();
		while (tempType !="")
		{
			term();
			if (tempType == "+") {
				GC.gen("OPR", 0, 2); //��ջ����ջ����� ��ջ����Ԫ�� �����ջ
			}
			else if (tempType == "-")
			{
				GC.gen("OPR", 0, 3);//��ջ����ջ�� ��ջ����Ԫ�� �����ջ
			}
			tempType = aop();
		}
		return 0;
	}

	int term()
	{
		string tempType;
		factor();
		tempType = mop();
		while (tempType!="")
		{
			factor();
			if (tempType == "*") {
				GC.gen("OPR", 0, 4);
			}
			else if (tempType == "/")
			{
				GC.gen("OPR", 0, 5);
			}
			tempType = mop();
		}
		return 0;
	}

	int factor()
	{
		if (type == "id")
		{
			int Tptr = T.FindVar(name, outer, nowname);
			if (Tptr==-1)
			{
				Exceptions(17);
			}
			else {
				//�����������Ҫ����
				TableItem TItem;
				TableItem *Tp;
				Tp = T.getItems();
				//ֻ�����ֶ�λ���ܻ���ɴ���
				TItem = Tp[Tptr];
				if (TItem.kind == "var")
				{
					//�����ŵ�ջ��
					GC.gen("LOD", level - TItem.lev, TItem.address);
				}
				else if (TItem.kind == "const")
				{
					GC.gen("LIT", 0, TItem.val);
				}
				else if(TItem.kind == "proc")
				{
					Exceptions(23);
				}
			}
			getword();
			return 0;
		}
		else if (type == "integer")
		{
			GC.gen("LIT", 0, val);
			getword();
			return 0;
		}
		else  if (type == "(")
		{
			getword();
			exp();
			if (type == ")")
			{
				getword();
				return 0;
			}
			else {
				Exceptions(8);
				return -1;
			}
		}
		return -1;
	}

	string lop()
	{
		if (type == "=") {
			getword();
			return  "=";
		}
		else if (type == "<>")
		{
			getword();
			return "<>";
		}
		else if (type == "<")
		{
			getword();
			return "<";
		}
		else if (type == "<=")
		{
			getword();
			return "<=";
		}
		else if (type == ">")
		{
			getword();
			return ">";
		}
		else if (type == ">=")
		{
			getword();
			return ">=";
		}
		return 0;
	}

	string aop()
	{
		if (type == "+" )
		{
			getword();
			return "+";
		}
		else if (type == "-")
		{
			getword();
			return "-";
		}
		else return "";
	}

	string mop()
	{
		if (type == "*")
		{
			getword();
			return "*";
		}
		else if (type == "/")
		{
			getword();
			return "/";
		}
		else return "";
	}

	int interger()
	{
		if (type != "integer")
			getword();
		if (type == "integer")
		{
			getword();
			return 0;
		}
		return -1;
	}

	int languageAnalysis()
	{
		prog();
		if (flag == 0) {
			cout << "����ɹ�" << endl;
			GC.show();
			GC.store();
			cout << "\n��ʼִ��:" << endl;
			executant e;
			e.exe();
		}
		else {
			cout << "\n����ʧ��,���޸Ĵ��������" << endl;
		}
		
		return 0;
	}
};

int main()
{
	wordAna wa;
	wa.store();
	languageAna la;
	la.languageAnalysis();
	
	system("Pause");
}
