#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int cas;
	cin >> cas;
	while (cas--) {
		int km;
		cin >> km;
		int num = km / 100, num2;
		vector<vector<int>>map;
		map.resize(10);
		for (int j = 9; j >= 0;j--) {
			for (int i = 0; i < num; i++) {
				cin >> num2;
				map[j].push_back(num2);
			}
			map[j].push_back(0);
		}
		vector<vector<int>>dp;
		dp.resize(10);
		for (int j = 9; j >= 0; j--) {
			for (int i = 0; i <= num; i++) {
				dp[j].push_back(100000);
			}
		}
		dp[0][0] = 0 -map[0][0];
		int i, j;
		for (i = 0; i < num; i++) {
			for (j = 0; j < 10; j++) {
				if (j + 1 < 10)
					dp[j + 1][i + 1] = min(dp[j + 1][i + 1], dp[j][i] + 60 - map[j + 1][i + 1]);
				if (j - 1 >= 0)
					dp[j - 1][i + 1] = min(dp[j - 1][i + 1], dp[j][i] + 20 - map[j - 1][i + 1]);
				dp[j][i + 1] = min(dp[j][i + 1], dp[j][i] + 30 - map[j][i + 1]);
			}
		}
		cout << dp[0][num] << endl<<endl;
	}
}