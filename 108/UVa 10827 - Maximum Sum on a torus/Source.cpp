#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

int main() {
	int cas,N;
	cin >> cas;
	while (cas--) {
		cin >> N;
		vector<vector<int>>arr(2 * N+ 1, vector<int>(2 * N +1 , 0));
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				cin >> arr[i + 1][j + 1];
				arr[i + N + 1][j + 1] = arr[i + 1][j + N + 1] = arr[i + 1 + N][j + N + 1] = arr[i + 1][j + 1];
			}

		vector<vector<int>>sum(2 * N + 1, vector<int>(2 * N + 1, 0));

		for (int i = 1; i <= 2 * N; i++)
			for (int j = 1; j <= 2 * N; j++) 
				sum[i][j] = arr[i][j] - sum[i - 1][j - 1] + sum[i - 1][j] + sum[i][j - 1];

		int globalMax = INT_MIN;
		for (int i = 0; i <= N; i++)
			for (int j = 0; j <= N; j++)
				for (int k = 0; k <= N; k++)
					for (int l = 0; l <= N; l++)
						if (sum[i + k][j + l] - sum[i][j + l] - sum[i + k][j] + sum[i][j] > globalMax)
							globalMax = sum[i + k][j + l] - sum[i][j + l] - sum[i + k][j] + sum[i][j];

		cout << globalMax << endl;
	}
}