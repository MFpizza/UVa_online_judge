#include <iostream>
#include <algorithm>
using namespace std;
int lis1(int A[], int n, int weight[])
{
	int* length = new int[n];
	int* w = new int[n]();

	length[0] = 1;
	w[0] = weight[0];
	for (int i = 1; i < n; i++)
	{
		length[i] = 1;
		w[i] = weight[i];
		for (int j = 0; j < i; j++)
			if (A[j] < A[i]) {
				length[i] = max(length[i], length[j] + 1);
				w[i] = max(w[i], w[j] + weight[i]);
			}
	}

	int maxW = 0;
	for (int i = 0; i < n; i++)
		maxW = max(maxW, w[i]);
	return maxW;
}

int main() {
	int cas;
	int cas2 = 1;
	cin >> cas;
	while (cas--) {
		int num;
		cin >> num;
		int* high1 = new int[num], * high2 = new int[num];
		int* weight1 = new int[num], * weight2 = new int[num];
		int num2;
		for (int i = 0; i < num; i++) {
			cin >> num2;
			high1[i] = num2;
			high2[num - i - 1] = num2;
		}
		for (int i = 0; i < num; i++) {
			cin >> num2;
			weight1[i] = num2;
			weight2[num - i - 1] = num2;
		}
		int increasing = lis1(high1, num, weight1);
		int decreasing = lis1(high2, num, weight2);
		if (increasing >= decreasing)
			cout << "Case " << cas2++ << ". Increasing (" << increasing << "). Decreasing (" << decreasing << ").\n";
		else
			cout << "Case " << cas2++ << ". Decreasing (" << decreasing << "). Increasing (" << increasing << ").\n";
	}
}