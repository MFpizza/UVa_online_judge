#include<iostream>
using namespace std;

long long int f[51][51];

int main() {
	int n, m, k;
	while (cin >> n >> k >> m ) {
		for (int i = 1; i <= k; i++)
			for (int j = 1; j <= n; j++)
				f[i][j] = 0;

		for (int i = 1; i <= n && i <= m; i++)
			f[1][i] = 1;

		for (int i = 2; i <= k; i++)
			for (int j = i; j <= n; j++)
				for (int p = 1; p <= m && j - p > 0; p++)
					f[i][j] += f[i - 1][j - p];
		
		cout << f[k][n] << endl;
	}
}