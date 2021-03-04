#include <iostream>
#include <string>
#include <vector>
#include "genCode.cpp"
#include "Table.cpp"
using namespace std;

struct bf
{
	TableItem Item;
	vector <int> GC;
	int target;
};

class backFill
{
public:
	bf *TB;
	int maxTB=2000;
	int size = 0;
	backFill()
	{
		TB = new bf[maxTB];
		for (int i = 0; i < maxTB; i++)
		{
			TB[i].target = 0;
		}

	}
	void insertGC(TableItem Item,int GC)
	{
		int i;
		for (i = 0; i < size; i++)
		{
			if(TB[i].Item.name == Item.name&&TB[i].Item.nowname== Item.nowname&&TB[i].Item.outer==Item.outer)
				break;
		}
		TB[i].GC.push_back(GC);
	}
	void insert(TableItem Item)
	{	
		TB[size].Item = Item;
		size++;
		//把过程记下来
	}
	void setTarget(TableItem Item,genCode& GC)
	{
		int i;
		for (i = 0; i < maxTB; i++)
		{
			if (TB[i].Item.name == Item.name&&TB[i].Item.nowname == Item.nowname&&TB[i].Item.outer == Item.outer)
				break;
		}
		TB[i].target = Item.val;
		reFill(Item, GC);
	}

	void reFill(TableItem Item, genCode& GC)
	{
		int i, j,k;
		for ( i = 0; i < maxTB; i++)
		{
			if (TB[i].Item.name == Item.name&&TB[i].Item.nowname == Item.nowname&&TB[i].Item.outer == Item.outer)
				break;
		}
		for (j = 0; j < TB[i].GC.size(); j++)
		{
			k = TB[i].GC[j];
			cout << GC.getCodes()[k].A << endl;
			GC.getCodes()[k].A = TB[i].target;
			cout << GC.getCodes()[k].A<<endl;
		}
	}
}
;