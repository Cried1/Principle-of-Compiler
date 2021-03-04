#include <string>
#include <iostream>
#include <fstream>
#pragma once
using namespace std;
struct instruction {
	string OP;
	int L;
	int A;
};

class genCode {
	/*
	*    ����ľ�����ʽ��
	*    FLA
	*    ���У�F�δ���α������
	*    L�δ�����ò���˵����Ĳ��ֵ
	*    A�δ���λ��������Ե�ַ��
	*    ��һ��˵����
	*    INT��Ϊ�����õĹ��̣����������̣�������ջS�п�������������ʱA��Ϊ�������ݵ�Ԫ���������������������ݣ���L�κ�Ϊ0��
	*    CAL�����ù��̣���ʱA��Ϊ�����ù��̵Ĺ����壨������֮ǰһ��ָ���Ŀ�����������ڵ�ַ��
	*    LIT���������͵�����ջS��ջ������ʱA��Ϊ����ֵ��
	*    LOD���������͵�����ջS��ջ������ʱA��Ϊ��������˵�����е����λ�á�
	*    STO��������ջS��ջ����������ĳ��������Ԫ�У�A��Ϊ��������˵�����е����λ�á�
	*    JMP��������ת�ƣ���ʱA��Ϊת���ַ��Ŀ����򣩡�
	*    JPC������ת�ƣ�������ջS��ջ���Ĳ���ֵΪ�٣�0��ʱ����ת��A����ָĿ������ַ������˳��ִ�С�
	*    OPR����ϵ���������㣬A��ָ���������㣬����A=2�����������㡰������A��12�����ϵ���㡰>���ȵȡ��������ȡ������ջS��ջ������ջ����
	*
	*    OPR 0 0	���̵��ý�����,���ص��õ㲢��ջ
	*    OPR 0 1	ջ��Ԫ��ȡ��
	*    OPR 0 2	��ջ����ջ����ӣ�������ջԪ�أ����ֵ��ջ
	*    OPR 0 3	��ջ����ȥջ����������ջԪ�أ����ֵ��ջ
	*    OPR 0 4	��ջ������ջ����������ջԪ�أ����ֵ��ջ
	*    OPR 0 5	��ջ������ջ����������ջԪ�أ����ֵ��ջ
	*    OPR 0 6	ջ��Ԫ�ص���ż�жϣ����ֵ��ջ��
	*    OPR 0 7
	*    OPR 0 8	��ջ����ջ���Ƿ���ȣ�������ջԪ�أ����ֵ��ջ
	*    OPR 0 9	��ջ����ջ���Ƿ񲻵ȣ�������ջԪ�أ����ֵ��ջ
	*    OPR 0 10	��ջ���Ƿ�С��ջ����������ջԪ�أ����ֵ��ջ
	*    OPR 0 11	��ջ���Ƿ���ڵ���ջ����������ջԪ�أ����ֵ��ջ
	*    OPR 0 12	��ջ���Ƿ����ջ����������ջԪ�أ����ֵ��ջ
	*    OPR 0 13	��ջ���Ƿ�С�ڵ���ջ����������ջԪ�أ����ֵ��ջ
	*    OPR 0 14	ջ��ֵ�������Ļ
	*    OPR 0 15	��Ļ�������
	*    OPR 0 16	�������ж���һ����������ջ��
	*/
private:
	int codePtr;
	int codeMax=2000;
	instruction *instructions;
public:
	genCode()
	{
		codePtr = 0;
		instructions = new instruction[codeMax];
		for (int i = 0; i < codeMax; i++)
		{
			instructions[i].A = 0;
			instructions[i].L = 0;
			instructions[i].OP = "";
		}
	}

	int getCodePtr()
	{
		return codePtr;
	}
	instruction* getCodes()
	{
		return instructions;
	}
	void gen(string OP, int L, int A)
	{
		instructions[codePtr].OP=OP;
		instructions[codePtr].L=L;
		instructions[codePtr].A=A;
		codePtr++;
	}
	void show()
	{
		for (int i = 0; i < codePtr; i++)
		{
			cout <<"("<<i<<") "<<instructions[i].OP << " " << instructions[i].L << " " << instructions[i].A << endl;
		}
	}
	void store()
	{
		fstream f;
		f.open("code_out.txt", ios::out);
		for (int i = 0; i < codePtr; i++)
		{
			f<<instructions[i].OP << " " << instructions[i].L << " " << instructions[i].A << endl;
		}
		f.close();
	}
};