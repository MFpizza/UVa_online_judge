#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
	int m, n;
	while (cin >> m >> n) {
		vector<int>c(n + 1);
		vector<int>w(n + 1);
		for (int i = 1; i <= n; ++i)
			cin >> c[i] >> w[i];

		if (m > 1800) m += 200;

		vector<int>F(m + 1, 0);
		for (int i = 1; i <= n; i++)
			for (int j = m; j >= c[i]; j--)
				if (w[i] + F[j - c[i]] > F[j])
					F[j] = w[i] + F[j - c[i]];

		int f = m;
		while (f > 0 && F[f] == F[f - 1]) f--;
		if (f <= 2000 && m > 2000)
			cout << F[m - 200] << endl;
		else
			cout << F[m] << endl;
	}
}