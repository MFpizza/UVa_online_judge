#include <iostream>
#include <vector>
using namespace std;

int main(){
	int cas;
	cin >> cas;
	while (cas--) {
		vector<vector<int>>dp(302, vector<int>(302, 100000));

		int num, end;
		cin >> num >> end;
		vector<int>old(num);
		vector<int>newP(num);
		for (int i = 0; i < num; i++) {
			cin >> old[i] >> newP[i];
			dp[old[i]][newP[i]] = 1;
		}

		for (int i = 0; i < num; ++i) //preprocesser
			for (int j = old[i]; j <= end; ++j)
				for (int k = newP[i]; k <= end; ++k)
					if (dp[j][k] > dp[j - old[i]][k - newP[i]] + 1)
						dp[j][k] = dp[j - old[i]][k - newP[i]] + 1;

		int max = 100000;
		for (int i = 0; i <= end; ++i)
			for (int j = 0; j <= end; ++j)
				if (i * i + j * j == end * end && max > dp[i][j])
					max = dp[i][j];

		if (max == 100000)
			cout << "not possible\n";
		else
			cout << max << endl;
	}	
}