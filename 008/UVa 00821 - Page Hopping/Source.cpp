#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
	ofstream out("o.txt");
	int a, b,t=1;
	int D[101][101];
	while (cin >> a >> b) {
		if (!a && !b)
			break;
		for (int i = 0; i < 101; ++i)
			for (int j = 0; j < 101; ++j)
				D[i][j] = 1e9;
		for (int i = 0; i < 101; ++i)
			D[i][i] = 0;

		int n = 0;
		do{
			if (!a && !b)
				break;
			n = max(n, a);
			n = max(b, n);
			D[a][b] = 1;
		}while (cin >> a >> b);

		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					D[i][j] = min(D[i][j], D[i][k] + D[k][j]);

		int count = 0, sum = 0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if (D[i][j] < 1e9 && D[i][j]) {
					count++;
					sum += D[i][j];
				}

		cout << "Case " << t++ << ": average length between pages = " <<fixed<< setprecision(3)<<((double)sum / count)<<" clicks" << endl;
	}
}