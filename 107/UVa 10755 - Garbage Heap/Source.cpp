#include <iostream>
#include <vector>
#define INF 0x3f3f3f3f3f3f3f3f

using namespace std;

long long int solve2d(vector<vector<long long>>& graph, int b, int c) {
	vector<long long> dp;
	long long int ans = -INF;
	for (int st = 0; st < b; st++) {
		dp.clear();
		dp.resize(c, 0);
		for (int ed = st; ed < b; ed++) {
			for (int i = 0; i < c; i++) {
				dp[i] = dp[i] + graph[ed][i];
			}
			long long int tmp = 0;
			for (int i = 0; i < c; i++) {
				tmp += dp[i];
				if (tmp > ans) ans = tmp;
				if (tmp < 0) tmp = 0;
			}
		}
	}
	return ans;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		int a, b, c;
		cin >> a >> b >> c;
		vector<vector<vector<long long>>> graph( a, vector<vector<long long>>(b, vector<long long>(c)));
		for (int i = 0; i < a; i++)
			for (int j = 0; j < b; j++)
				for (int k = 0; k < c; k++) cin >> graph[i][j][k];

		vector<vector<long long>> dp2;
		long long int ans = -INF;
		for (int st = 0; st < a; st++) {
			dp2.clear();
			dp2.resize(b, vector<long long>(c));
			for (int ed = st; ed < a; ed++) {
				for (int i = 0; i < b; i++) {
					for (int j = 0; j < c; j++) {
						dp2[i][j] += graph[ed][i][j];
					}
				}
				ans = max(solve2d(dp2, b, c), ans);
			}
		}
		cout << ans << endl;
		if (T != 0) cout << endl;
	}
}