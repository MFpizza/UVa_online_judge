#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#define INF 1000000000
using namespace std;

int main() {
	int N, X, T, K, V;
	while (cin >> N >> X >> T >> K, N | X | T | K) {
		vector<int> favor;
		vector<int> price;
		N += 1;
		V = (X * N) / 1.1 + 1e-9;
		V -= T * N;
		for (int i = 0; i < K; i++) {
			int tmp, Sum = 0;
			cin >> tmp;
			price.push_back(tmp);
			price.push_back(tmp);
			for (int j = 0; j < N; j++) {
				cin >> tmp;
				Sum += tmp;
			}
			favor.push_back(Sum);
			favor.push_back(Sum);
		}

		vector<vector<int>> dp(2 * N + 1, vector<int>(V + 1));
		for (int i = 0; i < K * 2; i++)
			for (int j = 2 * N; j > 0; j--)
				for (int k = V; k >= price[i]; k--)
					dp[j][k] = max(dp[j - 1][k - price[i]] + favor[i], max(dp[j - 1][k], dp[j][k]));

		int Max = -INF;
		for (int i = 0; i <= 2 * N; i++) {
			Max = max(dp[i][V], Max);
		}
		cout << setprecision(2) << fixed << (double)Max / N << endl;
	}
}