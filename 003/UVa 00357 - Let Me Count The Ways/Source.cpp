#include <iostream>
#include <cstdio>
using namespace std;
#include <vector>

int main() {
	vector<long long int>dp(30005);
	dp[0] = 1;
	const long long money[] = { 1, 5, 10, 25, 50 };
	for (int i = 0; i < 5; ++i) {
		for (int j = money[i]; j <= 30000; ++j) {
			dp[j] += dp[j - money[i]];
		}
	}

	int n;
	while (cin >> n) {
		if (dp[n] == 1)
			cout << "There is only 1 way to produce " << n << " cents change.\n";
		else
			cout << "There are " << dp[n] << " ways to produce " << n << " cents change.\n";
	}
	return 0;
}