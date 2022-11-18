#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int cas;
	cin >> cas;
	for(int i=0;i<cas;i++){
		int monNum, price;
		cin >> price >> monNum;
		vector<int>mon(monNum);
		for (int i = 0; i < monNum; i++)
			cin >> mon[i];

		sort(mon.begin(),mon.end());
		
		vector<int>dp(10001, 99999);
		dp[0] = 0;

		for (int i = 0; i < mon.size(); i++) {
			for (int j = 10000; j >= mon[i];j--) {
				int num= min(dp[j], dp[j - mon[i]] + 1);
				dp[j] = num;
			}
		}

		for(int i=price;i<10001;i++)
			if (dp[i] != 99999) {
				cout << i << " " << dp[i] << endl;
				break;
			}
	}
}