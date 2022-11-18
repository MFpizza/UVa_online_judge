#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int cas,t=1,nodeNum,RoadNum,a,b;
	cin >> cas;
	while (cas--) {
		cin >> nodeNum>>RoadNum;
		vector<vector<int>>D(nodeNum, vector<int>(nodeNum, 101));
		for (int i = 0; i < RoadNum; i++) {
			cin >> a >> b;
			D[a][b] = D[b][a] = 1;
		}
		for (int i = 0; i < nodeNum; i++) 
			D[i][i] = 0;
		
		cin >> a >> b;
		for (int k = 0; k < nodeNum; k++)
			for (int i = 0; i < nodeNum; i++)
				for (int j = 0; j < nodeNum; j++)
					D[i][j] = min(D[i][j], D[i][k] + D[k][j]);

		int ma = 0;
		for (int k = 0; k < nodeNum; k++)
			ma = max(ma, D[a][k] + D[k][b]);
		cout << "Case " << t++ << ": " << ma << endl;
	}
}