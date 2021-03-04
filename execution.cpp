#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <sstream>
#include "genCode.cpp"
#define MAX_INT 0x3f3f3f3f
#pragma once

using namespace std;

class executant {
private:
	int maxStack=10000000;
	int* STACK;
	vector<instruction> CODE;
	instruction I;//��ŵ�ǰҪִ�еĴ���
	int Top;//ָ������ջSTACK��ջ������һ��
	int Base;//��ŵ�ǰ���й��̵���������STACK�е���ʼ��ַ
	int NPC;//�����һ��Ҫִ�е�ָ���ַ
	int showflag = 0;
public:
	executant()
	{
		STACK = new int[maxStack];
		for (int i = 0; i < maxStack; i++)
		{
			STACK[i] = 88888;
		}
		STACK[0] = 0;
		STACK[1] = 0;
		STACK[2] = 0;
		Top = -1;
		Base = 0;
		NPC = 0;
		instruction input;
		fstream f;
		f.open("code_out.txt", ios::in);
		while(f.peek()!=EOF)
		{
			f >>input.OP >> input.L >>input.A ;
			CODE.push_back(input);
		}
		f.close();
		cout << "�Ƿ���ʾջ����(1��ʾ0����ʾ)��";
		cin >> showflag;
	} 
	void exe()
	{
		do {
			I = CODE[NPC];
			NPC++;
			ana();
			if(showflag) show();
		} while (NPC != 0);
	}
	void pop()
	{
		Top--;
	}

	void push(int a)
	{
		//size ++;
		Top++;
		STACK[Top] = a;
	}

	int base()//��ֱ������̵Ļ���ַ
	{
		int b1=Base;
		int l = I.L;
		while (l>0)
		{
			b1 = STACK[b1];
			l--;
		}
		return b1;
	}

	void show()
	{
		cout <<"ָ��" <<I.OP<<" "<<I.L<<" "<<I.A<<"\tջ:";
		for (int i = 0; i <= Top; i++)
		{
			if(STACK[i]!=88888) cout << STACK[i] << ' ';
			else cout <<"��";
		}
		cout << endl;
	}
	 
	void ana()
	{
		if (I.OP == "LIT")
		{
			Top++;
			STACK[Top] = I.A;
		}
		else if (I.OP == "LOD")
		{
			Top++;
			STACK[Top] = STACK[base()+I.A];
		}
		else if (I.OP == "STO")
		{
			STACK[base() + I.A] = STACK[Top];
			Top--;
		}
		else if (I.OP == "CAL")//��װ������������Ѿ���ջ��
		{
			int num = STACK[Top];
			Top = Top - num;
			for (int i = num-1; i >= 0; i--)
			{
				STACK[Top + i + 3]=STACK[Top+i];
			}

			STACK[Top] = base();
			STACK[Top + 1] = Base;
			STACK[Top + 2] = NPC;
			Base = Top;
			NPC = I.A;
		}
		else if (I.OP == "INT")
		{
			Top = Base + I.A-1;
		}
		else if (I.OP == "JMP")
		{
			NPC = I.A;
		}
		else if (I.OP == "JPC")
		{
			if(!STACK[Top]) NPC = I.A;//����������ת,�����޲���
		}
		else if (I.OP == "OPR")
		{
			if (I.A == 0)
			{
				Top = Base - 1;
				NPC = STACK[Top + 3];
				Base = STACK[Top + 2];
			}
			else if (I.A ==1)
			{
				STACK[Top] = -STACK[Top];
			}
			else if (I.A == 2)
			{
				int a = STACK[Top];
				int b = STACK[Top - 1];
				pop();
				pop();
				push(a + b);
			}
			else if (I.A == 3)
			{
				int a = STACK[Top];
				int b = STACK[Top - 1];
				pop();
				pop();
				push(b-a);
			}
			else if (I.A ==4 )
			{
				int a = STACK[Top];
				int b = STACK[Top - 1];
				pop();
				pop();
				push(b * a);
			}
			else if (I.A ==5 )
			{
				int a = STACK[Top];
				int b = STACK[Top - 1];
				pop();
				pop();
				push(b / a);
			}
			else if (I.A == 6)
			{
				int a = STACK[Top];
				push(a % 2 == 1);
			}
			else if (I.A ==8 )
			{
				int a = STACK[Top];
				int b = STACK[Top - 1];
				pop();
				pop();
				push(b == a);
			}
			else if (I.A == 9)
			{
				int a = STACK[Top];
				int b = STACK[Top - 1];
				pop();
				pop();
				push(b != a);
			}
			else if (I.A ==10 )
			{
				int a = STACK[Top];
				int b = STACK[Top - 1];
				pop();
				pop();
				push(b < a);
			}
			else if (I.A == 11)
			{
				int a = STACK[Top];
				int b = STACK[Top - 1];
				pop();
				pop();
				push(b >= a);
			}
			else if (I.A ==12)
			{
				int a = STACK[Top];
				int b = STACK[Top - 1];
				pop();
				pop();
				push(b > a);
			}
			else if (I.A == 13)
			{
				int a = STACK[Top];
				int b = STACK[Top - 1];
				pop();
				pop();
				push(b <= a);
			}
			else if (I.A == 14)
			{
				if(showflag==1)
					cout << "\n  write:" << STACK[Top] << endl<<endl;
				else cout << "  write:" << STACK[Top] << endl;
			}
			else if (I.A == 15)
			{
			if(showflag==1)
				cout <<"\n  ���\"\\n\""<<endl<<endl;	
			else cout << endl;
			}
			else if (I.A == 16)
			{
				int a;
				cout << "�����룺";
				cin >> a;
				push(a);
			}
		}
	}
};
