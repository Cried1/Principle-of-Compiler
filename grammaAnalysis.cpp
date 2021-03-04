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
	string lrow, lline;//上个单词的位置,报错点
	string word;
	string type;
	string value;
	fstream f;
	vector<string> IDlist;//id表
	vector<int> Constlist;//数字表
	fstream f_ID;
	fstream f_int;
	int flag;
	string name;//名字,ID的名字通过IDlist转换成真实的ID
	string kind;//类型
	int val;//值,变量的值通过常数表转换成真实的数
	int level;//嵌套层数
	string outer;
	string nowname;
	//int size;//存储空间
	int address;//address是本过程相对于基地址的偏移量
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
		while (f_ID.peek() != EOF)//读入id表
		{
			f_ID >> input;
			IDlist.push_back(input);
		}
		while (f_int.peek() != EOF)//读入数字表
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
			cout << lline << "行" << lrow << "列可能缺少program关键字" << endl;
			return;
		}
		else if (type == 2)
		{
			cout << lline << "行" << lrow << "列可能缺少id关键字" << endl;
			return;
		}
		else if (type == 3)
		{
			cout << lline << "行" << lrow << "列可能缺少;" << endl;
			return;
		}
		else if (type == 4)
		{
			cout << lline << "行" << lrow << "列缺少const项" << endl;
			return;
		}
		else if (type == 5)
		{
			cout << lline << "行" << lrow << "列缺少," << endl;
			return;
		}
		else if (type == 6)
		{
			cout << lline << "行" << lrow << "列缺少:=" << endl;
			return;
		}
		else if (type == 7)
		{
			cout << lline << "行" << lrow << "列缺少integer" << endl;
			return;
		}
		else if (type == 8)
		{
			cout << lline << "行" << lrow << "列缺少)" << endl;
			return;
		}
		else if (type == 9)
		{
			cout << lline << "行" << lrow << "列缺少begin" << endl;
			return;
		}
		else if (type == 10)
		{
			cout << lline << "行" << lrow << "列缺少statement关键词" << endl;
			return;
		}
		else if (type == 11)
		{
			cout << lline << "行" << lrow << "列缺少end" << endl;
			return;
		}
		else if (type == 12)
		{
			cout << lline << "行" << lrow << "列缺少lop符号" << endl;
			return;
		}
		else if (type == 13)
		{
			cout << lline << "行" << lrow << "列缺少exp" << endl;
			return;
		}
		else if (type == 14)
		{
			cout << lline << "行" << lrow << "列缺少do" << endl;
			return;
		}
		else if (type == 15)
		{
			cout << lline << "行" << lrow << "列缺少then" << endl;
			return;
		}
		else if (type ==16)
		{
			cout << lline << "行" << lrow << "列缺少(" << endl;
			return;
		}
		else if (type == 17)
		{
			cout << lline << "行" << lrow << "列变量未定义" << endl;
			return;
		}
		else if (type == 18)
		{
			cout << lline << "行" << lrow << "列对非变量赋值" << endl;
			return;
		}
		else if (type == 19)
		{
			cout << lline << "行" << lrow << "列缺少:" << endl;
			return;
		}
		else if (type == 20)
		{
			cout << lline << "行" << lrow << "列重复过程定义" << endl;
			return;
		}
		else if (type == 21)
		{
			cout << lline << "行" << lrow << "列变量重复定义" << endl;
			return;
		}
		else if (type == 22)
		{
			cout << lline << "行" << lrow << "列对常量赋值" << endl;
			return;
		}
		else if (type == 23)
		{
			cout << lline << "行" << lrow << "列过程名误调用" << endl;
			return;
		}
		else if (type == 24)
		{
			cout << lline << "行" << lrow << "列调用参数数量不匹配" << endl;
			return;
		}
		else if (type == 25)
		{
			cout << lline << "行" << lrow << "列缺少(" << endl;
			return;
		}
		else if (type == 26)
		{
			cout << lline << "行" << lrow << "列变量申明过程不能赋值" << endl;
			return;
		}
		else if (type == 27)
		{
			cout << lline << "行" << lrow << "列变量申明过程出现整数" << endl;
			return;
		}
		else if (type == 28)
		{
			cout << lline << "行" << lrow << "列缺少可以调用的过程" << endl;
			return;
		}
		else if (type == 30)
		{
			cout << lline << "行" << lrow << "列常量重复定义" << endl;
			return;
		}
		else if (type == 31)
		{
			cout << lline << "行" << lrow << "列已经定义了同名的变量" << endl;
			return;
		}
		else if (type == 32)
		{
			cout << lline << "行" << lrow << "列已经定义了同名的常量" << endl;
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
			Exceptions(1);//缺少program
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
		//未处理错误
		return 0;
	}

	int block()
	{
		//address指向已经放了代码的下一个位置,从0开始
		int address0=address;//进入block先保存address 和 Tx(表指针)
		int tx0 = T.getTx();
		int position;
		TableItem *Tp;
		Tp = T.getItems();
		if (tx0 > 0)
		{
			position = T.getLevelProc(outer,nowname);
			tx0 = tx0 - Tp[position].size;//tx0指向当前过程的第一个Table表项
			//为什么这里需要tx0
		}
		//position指向本层符号表的初始位置
		//tx0指向符号表已放置的下一位
		if (tx0 == 0)
		{//tx0=0表示是主程序,所以address变成3
			address = 3;      //每一层最开始位置的三个空间用来存放静态链SL、动态链DL、和返回地址RA
		}
		else {
			//每一层最开始位置的三个空间用来存放静态连SL、动态连DL、和返回地址RA
			//紧接着放参数
			address = 3 + T.getItems()[position].size;
		}
		int codePtr0 = GC.getCodePtr();
		GC.gen("JMP", 0, 0);//在执行代码前无条件跳转,跳过定义的过程,跳转到主程序的入口
		//下面是常量,变量,子过程的定义
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
		//完成申明后回填jmp,跳转到此处位置开始执行
		//回填语句
		//block先对变量进行赋值
		GC.getCodes()[codePtr0].A=GC.getCodePtr();//跳转到定义代码段之后的具体代码段
		GC.gen("INT", 0, address);        //给定义过程中的变量与动态链静态链返回地址分配空间,3+变量数
		if (tx0 != 0)
		{
			//由于定义中有递归会导致填不回去,考虑增加一个表来回填
			T.getItems()[position].val = GC.getCodePtr() - 1; 
			//BF.reFill(T.getItems()[position], GC);
			BF.setTarget(T.getItems()[position], GC);
			//符号表中的值设为本过程执行语句开始的位置,GC的CP是指向生成代码的下一条,因此需要-1
			//而T.getItems()[position].size是定义过程中的参数
			//计算的结果就是指向这段代码的运行起始位置proc的val是记录着起始位置
		}
		body();
		GC.gen("OPR", 0, 0);//过程结束调用 返回调用点并退栈
		//过程结束恢复address
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
						T.enterConst(name,val,level,outer, nowname);//只有变量才增加address
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
					Exceptions(7);//缺少integer
					return 0;
				}
			}
			else if (type == "=")
			{
				Exceptions(19);
				getword();
				if (type == "integer")
				{
					//T.enterConst(name, val, level, address);//只有变量才增加address吗???
					getword();
					return 0;
				}
				else
				{
					Exceptions(7);//缺少integer
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
			Exceptions(2);//缺少id
			getword();
			if (type == "integer")
			{
				getword();
				return 0;
			}
			else
			{
				Exceptions(7);//缺少integer
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
				Exceptions(5);//缺少,
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
			Exceptions(3);//缺少;
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

	int proc()//子程序过程还要完善
	{
		if (type == "procedure") getword();
		int count = 0;//记录参数数量
		int position;//记录proc符号表位置
		string outer0;
		string nowname0;
		if (type == ";")
		{
			Exceptions(2);
			getword();
			return 0;
		}
		else if (type == "(")//缺少id的就不进行翻译了
		{
			Exceptions(2);//缺少id
			getword();
			id();
			while (type == "," || type == "id")
			{
				if (type == ",") id();
				else if (type == "id")
				{
					Exceptions(5);//缺少,
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
				Exceptions(20);//过程已经定义过,不支持同一层次的同名定义
			}
			position = T.getTx();//这个子过程的第一个Table表项的指针,他的size表示这个过程中的Table占据的大小
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
		level++;//定义都在子过程里面了
		if (type == "(")
		{
			getword();
			if (type == "id")
			{
				T.enterVar(name, level,count + 3,outer, nowname);//位置从0开始,变量从3号开始放
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
						T.enterVar(name, level, count + 3, outer, nowname);//位置从0开始,变量从3号开始放
						count++;
						T.getItems()[position].size = count;
						getword();
					}
				}
				else if (type == "id")
				{
					Exceptions(5);//缺少,
					if (type == "id")
					{
						T.enterVar(name, level, count + 3, outer, nowname);//位置从0开始,变量从3号开始放
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
				T.enterVar(name, level, count + 3, outer, nowname);//位置从0开始,变量从3号开始放
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
						T.enterVar(name, level, count + 3, outer, nowname);//位置从0开始,变量从3号开始放
						count++;
						T.getItems()[position].size = count;
						getword();
					}
				}
				else if (type == "id")
				{
					Exceptions(5);//缺少,
					if (type == "id")
					{
						T.enterVar(name, level, count + 3, outer, nowname);//位置从0开始,变量从3号开始放
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

	int body()//现在读到的单词为begin就开始执行,不为begin表示在begin上一个单词需要读入一个begin
	{
		if (type != "begin") getword();
		if (type == "begin")
		{
			getword();
			statement();
			while (type == ";" || isStatement(type))//注意这个地方
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
			Exceptions(9);//缺少begin
			statement();
			while (type == ";" || isStatement(type))//注意这个地方
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

	int statement()//函数开始会读取一个字符,错误处理好多...
	{
		string target;
		if (!isStatement(type))//说明是分号进来的
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
					//变量未定义
					Exceptions(17);
				}
				else
				{
					TableItem TItem;
					//用名字确定不唯一
					TItem = T.getItems()[Tptr];
					if (TItem.kind == "var")
					{
						GC.gen("STO", level - TItem.lev, TItem.address);
					}
					else {
						//报错
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
					//变量未定义
					Exceptions(17);
				}
				else
				{
					TableItem TItem;
					//用名字确定可能会造成不唯一
					TItem = T.getItems()[Tptr];
					if (TItem.kind == "var")
					{
						GC.gen("STO", level - TItem.lev, TItem.address);
					}
					else {
						//报错
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
				GC.gen("JPC", 0, 0);//不满足条件跳转
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
				GC.gen("JPC", 0, 0);//不满足条件跳转
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
			int cp0 = GC.getCodePtr();//while开始的代码行
			int cp1;
			getword();
			lexp();
			if (type == "do")
			{
				cp1 = GC.getCodePtr();
				GC.gen("JPC", 0, 0);//不满足条件跳转
				getword();
				statement();
				GC.gen("JMP", 0, cp0);//运行完就跳转回while开始
				GC.getCodes()[cp1].A = GC.getCodePtr();//while的next代码
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
				if (type == "id")//cal 过程优先调用内层的proc
				{
					int Tptr = T.FindProc(name, outer, nowname);
					if (Tptr!=-1)
					{
						//用名字定义可能会造成错误
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
						//参数和定义时的参数不同
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
						//参数和定义时的参数不同
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
			else {//没有id无法调用
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
						//未定义报错
					}
					else
					{
						TableItem TItem;
						//只用名字定位可能会造成错误
						TItem = T.getItems()[T.FindVar(name, outer, nowname)];
						if (TItem.kind == "var")
						{
							GC.gen("OPR", 0, 16);
							//从命令行读入一个输入至于栈顶
							GC.gen("STO", level - TItem.lev, TItem.address);
							//将栈顶内容送入某变量单元中 a为偏移量 l为层差
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
							//未定义报错
						}
						else
						{
							TableItem TItem;
							TableItem *Tp;
							Tp = T.getItems();
							//只用名字定位可能会造成错误
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

	int lexp()//进入函数不会读入一个单词
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
						GC.gen("OPR", 0, 8);      //OPR 0 8	次栈顶与栈顶是否相等，退两个栈元素，结果值进栈
					}
					else if (lopRes == "<>") 
					{
						GC.gen("OPR", 0, 9);      //OPR 0 9	次栈顶与栈顶是否不等，退两个栈元素，结果值进栈
					}
					else if (lopRes == "<") 
					{
						GC.gen("OPR", 0, 10);     //OPR 0 10	次栈顶是否小于栈顶，退两个栈元素，结果值进栈
					}
					else if (lopRes == "<=")
					{
						GC.gen("OPR", 0, 13);     // OPR 0 13	次栈顶是否小于等于栈顶，退两个栈元素，结果值进栈
					}
					else if (lopRes == ">") 
					{
						GC.gen("OPR", 0, 12);     //OPR 0 12	次栈顶是否大于栈顶，退两个栈元素，结果值进栈
					}
					else if (lopRes == ">=")
					{
						GC.gen("OPR", 0, 11);     //OPR 0 11	次栈顶是否大于等于栈顶，退两个栈元素，结果值进栈
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
			GC.gen("OPR", 0, 1);//栈顶元素取反
		}
		tempType = aop();
		while (tempType !="")
		{
			term();
			if (tempType == "+") {
				GC.gen("OPR", 0, 2); //次栈顶与栈顶相加 退栈两个元素 结果进栈
			}
			else if (tempType == "-")
			{
				GC.gen("OPR", 0, 3);//次栈顶减栈顶 退栈两个元素 结果进栈
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
				//定义完变量需要操作
				TableItem TItem;
				TableItem *Tp;
				Tp = T.getItems();
				//只用名字定位可能会造成错误
				TItem = Tp[Tptr];
				if (TItem.kind == "var")
				{
					//变量放到栈顶
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
			cout << "编译成功" << endl;
			GC.show();
			GC.store();
			cout << "\n开始执行:" << endl;
			executant e;
			e.exe();
		}
		else {
			cout << "\n编译失败,请修改错误后重试" << endl;
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
