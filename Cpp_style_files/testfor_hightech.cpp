#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include<list>

using namespace std;

class A
{
	
public:
	static int a;
	int pub;
	static void in()
	{
		//this->pub;
	}
private:
	int priva;
protected:
	int pro;
};

class B: protected A
{
protected:
	int subpro;
public:
	B()
	{
		pub = 0;
		pro = 0;
	}

	B(A op)
	{
		
	}

	B(B & op)
	{
		
		//op.subpro
	}
};

int A::a = 0;

void f()
{
	cout << 1;
}
int main()
{
	A * ptr = new A();
	ptr->a = 0;
	vector<int>bubu(10, 0);
	string a;
	string b = "fasdf";
	list<int>ks;
	ks.insert(ks.begin() , 1);
	ks.insert(ks.begin(),2);

	ks.sort();

	cout << *ks.begin();
	int p = 1;
	int && y = p;

}