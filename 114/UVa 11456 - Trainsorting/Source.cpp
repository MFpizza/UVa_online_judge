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
//�ѩ�i�H�N������ܬҦb�e��Ϋ��A�ҥH�N�쥻���ƦC�e���W�A�˪��C
//
//1 2 3 4 = >
//4 3 2 1 1 2 3 4
//
//�H 2 �ӻ����i�H�O�b 1 �e���Ϋ᭱�C
//
//���ۺ� LIS �Y�i�C