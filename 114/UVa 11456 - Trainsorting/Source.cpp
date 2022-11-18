#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

int main() {
	int cas;
	cin >> cas;
	while (cas--) {
		int num, num2;
		int* A = new int[40000];
		int* length = new int[40000];
		cin >> num;
		for (int i = 0; i < num; i++)
		{
			cin >> num2;
			A[num-i - 1] = A[i + num] = num2;
		}
		num <<= 1;
		int maxLength = 0;
		for (int i = 0; i <num ; i++)
		{
			length[i] = 1;
			for (int j = 0; j < i; j++)
				if (A[j] < A[i])
					length[i] = max(length[i], length[j] + 1);
			maxLength = max(maxLength, length[i]);
		}
			
		cout << maxLength << endl;
	}
}

//http://naivered.github.io/2018/03/04/Problem_Solving/UVa/UVa-11456-Trainsorting/
//由於可以將火車選擇皆在前方或後方，所以將原本的數列前接上顛倒的。
//
//1 2 3 4 = >
//4 3 2 1 1 2 3 4
//
//以 2 來說它可以是在 1 前面或後面。
//
//接著算 LIS 即可。