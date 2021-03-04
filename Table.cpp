#include <string>
#include <vector>
#pragma once
using namespace std; 
typedef struct
{
	string name;//����
	string kind;//����
	int val;//ֵ
	int lev;//Ƕ�ײ���
	int address;//��Ե�ַ
	int size;//�洢�ռ�
	string outer;//���
	string nowname;
	//int JMP;
}TableItem;


class Table {
private:
	int tx;
	int rowMax=2000;
	int length;
	TableItem *Items;
public:
	Table()
	{
		tx = 0;
		length = 0;
		Items = new TableItem[rowMax];
		for (int i = 0; i < rowMax; i++) {
			Items[i].name="";//����
			Items[i].kind="";//����
			Items[i].val=0;//ֵ
			Items[i].lev=0;//Ƕ�ײ���
			Items[i].address=0;//��Ե�ַ
			Items[i].size=0;//�洢�ռ�
			Items[i].outer = "";//�մ����������
		}
	}
	TableItem* getItems()
	{
		return Items;
	}

	int getTx()
	{
		return tx;
	}
	void setTx(int tx)
	{
		this->tx = tx;
	}
	void enterVar(string name,int lev,int address,string outer, string nowname)
	{
		length++;
		Items[tx].name = name;
		Items[tx].kind = "var";
		Items[tx].lev = lev;
		Items[tx].address = address;
		Items[tx].size = 0;//�洢�ռ�?
		Items[tx].outer = outer;
		Items[tx].nowname = nowname;
		tx++;
	}

	void enterConst(string name, int val, int lev,string outer, string nowname)
	{
		length++;
		Items[tx].name = name;
		Items[tx].kind = "const";
		Items[tx].val = val;
		Items[tx].lev = lev;
		//Items[tx].address = address;
		Items[tx].size = 4;//�洢�ռ�
		Items[tx].outer = outer;
		Items[tx].nowname = nowname;
		tx++;
	}
	void enterProc(string name, int lev, string outer, string nowname)//size��ʾ��������ռ��С
	{
		length++;
		Items[tx].name = name;
		Items[tx].kind = "proc";
		Items[tx].lev = lev;
		//Items[tx].address = address;
		Items[tx].size = 0;
		Items[tx].outer = outer;
		Items[tx].nowname = nowname;
		tx++;
	}
	//Ѱ��proc�Ƿ���nowname�㱻�����
	bool isExitInLevel(string name,string outer,string nowname) {
		for (int i = length - 1; i >= 0; i--) {
			if (Items[i].name == name&&Items[i].kind == "proc"&&Items[i].nowname == nowname&& Items[i].outer==outer) {
				return true;
			}
		}
		return false;
	}
	int  FindProc(string name,string outer,string nowname) {
		int procI = -1;
		int i;
		while (nowname != "")
		{
			procI = -1;
			for (i = length - 1; i >= 0; i--) {
				if (Items[i].kind == "proc"&&Items[i].name == name && Items[i].nowname == nowname&&Items[i].outer==outer) {
					return i;
				}
				if (Items[i].kind == "proc"&&Items[i].name == nowname && Items[i].nowname == outer) {
					procI = i;
				}
			}
			if (i == -1 && procI == -1) return -1;
			nowname = Items[procI].nowname;
			if(nowname != "")
				outer = Items[procI].outer;
		}
		return -1;
	}
	int  FindVar(string name, string outer, string nowname) {
		int procI = -1;
		int i;
		while (nowname != "")
		{
			procI = -1;
			for ( i= length - 1; i >= 0; i--) {
				if (Items[i].kind == "proc"&&Items[i].name == nowname && Items[i].nowname == outer) {
					procI = i;
				}
				if (Items[i].kind!="proc"&&Items[i].name == name && Items[i].nowname == nowname && Items[i].outer == outer)
				{
					return i;
				}
			}
			if (i == -1 && procI == -1) return -1;
			nowname = Items[procI].nowname;//proc��nownameָ�����,outerָ���������
			if (nowname != "")
				outer = Items[procI].outer;
		}
		return -1;
	}
	int  FindVarInNowname(string name, string outer, string nowname) {
		int i;
		for (i = length - 1; i >= 0; i--) {
			if (Items[i].kind=="var"&&Items[i].name == name && Items[i].nowname == nowname && Items[i].outer == outer)
			{
				return i;
			}
		}
		return -1;
	}
	int  FindConstInNowname(string name, string outer, string nowname) {
		int i;
		for (i = length - 1; i >= 0; i--) {
			if (Items[i].kind == "const"&&Items[i].name == name && Items[i].nowname == nowname && Items[i].outer == outer)
			{
				return i;
			}
		}
		return -1;
	}
	//���ر���ķ��ű�ʼλ��
	int getLevelProc(string outer,string nowname) {
		for (int i = length - 1; i >= 0; i--) {
			if (Items[i].kind == "proc"&&Items[i].name == nowname && Items[i].nowname == outer) {
				return i;
			}
		}
		return -1;
	}
};
