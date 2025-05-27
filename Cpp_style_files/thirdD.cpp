#include <iostream>
#include <cstring>
using namespace std;

class Array2
{
    private:
        int ** nums;
    public:

    Array2(int rows, int cols)
    {
        nums = new int*[rows];
        for (int i = 0; i < rows; ++i)
            nums[i] = new int[cols];
    }
    Array2()
    {
        nums = nullptr;
    }
    int * operator[](int row)
    {
        return nums[row];
    }
    int operator()(int i, int j)
    {
        return nums[i][j];
    }
};

int main()
{
    Array2 a(3, 4);
    int i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 4; j++)
            a[i][j] = i * 4 + j;
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 4; j++)
        {
            cout << a(i, j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;
    b = a;
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 4; j++)
        {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}