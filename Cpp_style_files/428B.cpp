/*
后缀表达式的计算 
用一个栈来存储数字，从左向左右遍历表达式 
遇到数字就压栈 
遇到操作符就弹出栈中的两个数字计算并压栈 
最后栈中剩余的数字是我们要的结果  
*/
#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<math.h>
#include<stack>
#include<queue>
using namespace std;

void cal(string param, stack<double> &num)
{
    double num1=num.top();num.pop();
    double num2=num.top();num.pop();
    if(param=="+")num.push(num2+num1);
    if(param=="-")num.push(num2-num1);
    if(param=="*")num.push(num2*num1);
    if(param=="/")num.push(num2/num1);
    if(param=="^")num.push(pow(num2,num1));
}

void bolan(string &param, stack<double> &num)
{
    if(param!="+" && param!="*" && param!="-" && param!="/" && param!="^")// 遇到数字就入栈 
        num.push(atof(param.c_str()));
    else// 遇到操作符就计算，并将结果入栈 
        cal(param, num);
}

int main()
{
    int n,i,index1,index2,count;
    string param;
    cin>>n;

    // 初始化memory
    priority_queue < double,vector<double>,greater<double> > p;
    vector<double> nums;
    for(i=0;i<n;i++)
    {
        double inData;
        cin>>inData;
        p.push(inData);
    }
    getchar();

    // 计算后缀表达式的值
    stack <double> bolan_num;
    string command;
    while(getline(cin,command))
    {
        index1=0,index2=command.length()-1;
        // 从右向左遍历表达式 获取操作符和数字
        for(i=0; i<=command.length(); i++)
            if(command[i]==' ' || command[i]=='\0')
            {
                index2=i;
                param=command.substr(index1, index2-index1);
                index1=index2+1;
                if(param=="=")
                {
                    // 用新计算出的值，替换掉memory中的最小值
                    printf("%e\n",bolan_num.top());
                    p.pop();
                    p.push(bolan_num.top());

                    bolan_num.pop();
                    if(!bolan_num.empty())
                        cout<<"expect empty"<<endl;
                }
				else
                    bolan(param, bolan_num);
            }
    }
    printf("\n");
    // 输出memory中的值
    count=0;
    for(i=1; i<=n; i++)
    {
        count++;
        if(i==n)
        	printf("%e",p.top());
        else if(count%10==0)
        	printf("%e\n",p.top());
        else
        	printf("%e ",p.top());
        p.pop();
    }
    
    return 0;
}
