#include <iostream>
#include <string>
using namespace std;

template <class T>
T SumArray(T *a, T *b)
{
	T sum = *a;
	for (T *ptr = a + 1; ptr < b; ++ptr) {
		sum += *ptr;
	}
	return sum;
}

int main() {
	string array[4] = { "Tom","Jack","Mary","John"};
	cout << SumArray(array,array+4) << endl;
	int a[4] = { 1, 2, 3, 4};  //提示：1+2+3+4 = 10
	cout << SumArray(a,a+4) << endl;
	return 0;
}