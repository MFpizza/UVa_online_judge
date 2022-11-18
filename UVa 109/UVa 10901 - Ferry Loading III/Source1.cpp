#include <queue>
#include <climits>
#include <iostream>
using namespace std;

int main() {
	int cas;
	cin >> cas;
	while (cas--) {
		int time[10001];
		bool side[10001]; // 0=right 1=left
		int car[10001];
		int bS, min, line;
		cin >> bS >> min >> line;
		for (int i = 0; i < line; i++) {
			string s;
			cin >> car[i] >> s; 
			side[i] = (s == "left");
		}
		bool AtLeft = true;
		queue<int> right,left,boat;
		int ca = 0,arriveTime=INT_MAX;

		while (ca < line|| (!boat.empty()||!right.empty()||!left.empty())) {
			if (ca<line && car[ca] <= arriveTime) {
				(side[ca] ? left : right).push(ca);
				if (arriveTime == INT_MAX) arriveTime = car[ca];
				ca++;
			}
			else {
				while (!boat.empty()) {
					time[boat.front()] = arriveTime;
					boat.pop();
				}
				if (right.empty() && left.empty()) 
					arriveTime = INT_MAX;
				else {
					queue<int>& cur = (AtLeft) ? left : right;
					while (!cur.empty() && boat.size() < bS) {
						boat.push(cur.front());
						cur.pop();
					}
					AtLeft = !AtLeft;
					arriveTime += min;
				}
			}
		}
		for (int i = 0; i < line; i++)
			cout << time[i] << endl;
		
		if (cas) cout << endl;
	}
}