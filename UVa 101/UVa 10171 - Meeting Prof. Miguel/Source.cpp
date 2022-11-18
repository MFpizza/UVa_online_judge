#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int nodeNum;
	while (cin >> nodeNum, nodeNum) {
		char a, b, c, d, from, end;
		vector<vector<int>>wY(26, vector<int>(26, 1000000));
		vector<vector<int>>wOld(26, vector<int>(26, 1000000));
		for (int i = 0; i < nodeNum; i++) {
			cin >> a >> b >> c >> d;
			if (a == 'Y')
				if (b == 'U') {
					cin >> wY[c - 'A'][d - 'A'];
				}
				else {
					cin >> wY[c - 'A'][d - 'A'];
					wY[d - 'A'][c - 'A'] = wY[c - 'A'][d - 'A'];
				}
			else
				if (b == 'U') {
					cin >> wOld[c - 'A'][d - 'A'];
				}
				else {
					cin >> wOld[c - 'A'][d - 'A'];
					wOld[d - 'A'][c - 'A'] = wOld[c - 'A'][d - 'A'];
				}
		}

		for (int i = 0; i < 26; i++)
			wY[i][i] = wOld[i][i] = 0;

		for (int k = 0; k < 26; k++)
			for (int i = 0; i < 26; i++)
				for (int j = 0; j < 26; j++) {
					wY[i][j] = min(wY[i][j], wY[i][k] + wY[k][j]);
					wOld[i][j] = min(wOld[i][j], wOld[i][k] + wOld[k][j]);
				}

		cin >> from >> end;

		int mi = 1000000;
		vector<int>eq;

		for (int i = 0; i < 26; i++)
		{
			if (mi > wY[from - 'A'][i] + wOld[end - 'A'][i]) {
				mi = wY[from - 'A'][i] + wOld[end - 'A'][i];
				eq.clear();
				eq.push_back(i);
			}
			else if (mi == wY[from - 'A'][i] + wOld[end - 'A'][i])
				eq.push_back(i);
		}

		if (mi == 1000000)
			cout << "You will never meet.\n";
		else {
			cout << mi;
			for (int i = 0; i < eq.size(); i++) {
				end = eq[i] + 'A';
				cout << " " << end;
			}
			cout << endl;
		}
	}
}