#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char *s)
{
    int i = 0;
    for (; s[i]; ++i)
        ;
    return i;
}
void strcpy(char *d, const char *s)
{
    int i = 0;
    for (i = 0; s[i]; ++i)
        d[i] = s[i];
    d[i] = 0;
}
int strcmp(const char *s1, const char *s2)
{
    for (int i = 0; s1[i] && s2[i]; ++i)
    {
        if (s1[i] < s2[i])
            return -1;
        else if (s1[i] > s2[i])
            return 1;
    }
    return 0;
}
void strcat(char *d, const char *s)
{
    int len = strlen(d);
    strcpy(d + len, s);
}
class MyString
{
private:
    char * string;
    int strlenth = 0;
public:

    MyString(char * a)
    {
        strlenth = strlen(a);
        string = new char[strlenth + 1];
        strcpy(string, a);
    }
    MyString() {
        this->string = new char[1];
        this->string[0] = 0;
        this->strlenth = 0;
    }

    MyString(const MyString & a)
    {
        this->strlenth = a.strlenth;
        this->string = new char[this->strlenth + 1];
        strcpy(this->string, a.string);
    }

    friend ostream & operator<<(ostream & a,const MyString & c)
    {
        return a << c.string;
        
    }

    friend  MyString  operator+(MyString & a, MyString& b)
    {
        char * temp = new char[a.strlenth + b.strlenth + 1];
        strcpy(temp, a.string);
        strcat(temp, b.string);
        MyString c(temp);
        delete[] temp;
        return   c;
    }

    char& operator[](int a)
    {
        return this->string[a];
    }

    friend MyString & operator+=(MyString & a, char * b)
    {
        a.strlenth += strlen(b);
        strcat(a.string, b);
        return a;
    }

    friend MyString  operator+(const char * a, const MyString & b)
    {
        char * temp = new char[strlen(a) + b.strlenth + 1];
        strcpy(temp, a);
        strcat(temp, b.string);
        MyString c(temp);
        delete [] temp;
        return c;
    }

    friend MyString  operator+(const MyString& a,const char * b)
    {
        char * temp = new char[a.strlenth + strlen(b) + 1];
        strcpy(temp, a.string);
        strcat(temp, b);
        MyString c(temp);
        delete []temp;
        return c;
    }

    bool operator==(const MyString & b)
    {
        if(this->strlenth != b.strlenth)
        {
            return false;
        }
        else
        {
            for(int i = 0; i < this->strlenth; i++)
            {
                if(this->string[i] != b.string[i])
                {
                    return false;
                }
            }
            return true;
        }
    }

    bool operator>(const MyString & b)
    {
        if(this->string[0] < b.string[0])
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool operator<(const MyString & b)
    {
        return !(*this > b);
    }

    char * operator()(const int a, const int b)
    {
        char * res = new char[b + 1];
        for(int i = 0; i < b; i++)
        {
            res[i] = this->string[a + i];
        }
        res[b] = 0;
        return res;
    }
};

int CompareString(const void *e1, const void *e2)
{
    MyString *s1 = (MyString *)e1;
    MyString *s2 = (MyString *)e2;
    if (*s1 < *s2)
        return -1;
    else if (*s1 == *s2)
        return 0;
    else if (*s1 > *s2)
        return 1;
}
int main()
{
    MyString s1("abcd-"), s2, s3("efgh-"), s4(s1);
    MyString SArray[4] = {"big", "me", "about", "take"};
    cout << "1. " << s1 << s2 << s3 << s4 << endl;

    s4 = s3;
    s3 = s1 + s3;
    cout << "2. " << s1 << endl;
    cout << "3. " << s2 << endl;
    cout << "4. " << s3 << endl;
    cout << "5. " << s4 << endl;
    cout << "6. " << s1[2] << endl;
    s2 = s1;
    s1 = "ijkl-";
    s1[2] = 'A';
    cout << "7. " << s2 << endl;
    cout << "8. " << s1 << endl;
    s1 += "mnop";
    cout << "9. " << s1 << endl;
    s4 = "qrst-" + s2;
    cout << "10. " << s4 << endl;
    s1 = s2 + s4 + " uvw " + "xyz";
    cout << "11. " << s1 << endl;
    qsort(SArray, 4, sizeof(MyString), CompareString);
    for (int i = 0; i < 4; i++)
        cout << SArray[i] << endl;
    // s1的从下标0开始长度为4的子串
    cout << s1(0, 4) << endl;
    // s1的从下标5开始长度为10的子串
    cout << s1(5, 10) << endl;
    return 0;
}