#include<iostream>
#include<map>
using namespace std;
int main()
{
	int id,power,num;
	multimap<int ,int> data;
	data.insert(make_pair(1000000000,1));//第一个数据 
	cin >> num;
	while(num --)
	{
		cin >> id >> power;
		multimap<int ,int>::iterator im,in,i,j;
		im = data.insert(make_pair(power,id));
		if(im == data.begin()){//判断是否是第一个元素
			in = im;
			in++;
		 	cout<<im->second <<" "<< in->second << endl;
		}
		else if(im == (--data.end())){//判断是否是最后一个元素
			in = im;
			--in;
			cout<<im->second <<" "<< in->second << endl;
		}
		else{
			i = im;
			--i;
			j = im;
			++j;
			if(im->first - i->first > (j->first - im->first))
				cout<<im->second <<" "<< j->second<<endl;
			else
				cout<<im->second <<" "<< i->second<<endl;
		}
		
	}
}
 
