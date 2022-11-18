#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

int main() {
	int N;
	cin >> N;
	vector<vector<int>>arr(N+1,vector<int>(N+1,0));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> arr[i+1][j+1];

	vector<vector<int>>sum(N+1, vector<int>(N+1, 0));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			sum[i][j] = arr[i][j] - sum[i - 1][j - 1]
			+ sum[i - 1][j] + sum[i][j - 1];

	int globalMax = INT_MIN;
	for (int t = 1; t <= N; t++)
		for (int l = 1; l <= N; l++)
			for (int b = t; b <= N; b++)
				for (int r = l; r <= N; r++)
				{
					int temp = sum[b][r] + sum[t - 1][l - 1]
						- sum[t - 1][r] - sum[b][l - 1];
					globalMax = max(globalMax, temp);
				}
	cout << globalMax << endl;
}