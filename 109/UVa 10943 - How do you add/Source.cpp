#include <iostream>
using namespace std;

int main() {
	const long long int mod = 1000000;
	long long int combinationTable[205][205] = { 0 };
	combinationTable[0][0] = 1;
	for (int i = 1; i <= 200; ++i) {
		combinationTable[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			combinationTable[i][j] = (combinationTable[i - 1][j - 1] + combinationTable[i - 1][j]) % mod;
		}
	}
	int n, k;
	while (cin >> n >> k) {
		if (n == 0 && k == 0)
			break;
		cout << combinationTable[n + k - 1][k - 1] << endl;
	}
}