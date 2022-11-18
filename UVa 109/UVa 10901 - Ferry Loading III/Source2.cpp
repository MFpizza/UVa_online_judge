#include <iostream>
#include <queue>
#include <climits>
using namespace std;

int events[10000];
int tim[10000];
bool side[10000]; //1¥Nªíleft 0 right

int main() {
	int cas;
	cin >> cas;
	while (cas--) {
		int bS, min, lin;
		cin >> bS >> min >> lin;
		for (int i = 0; i < lin; i++) {
			string s;
			cin >> events[i] >> s;
			side[i] = s == "left";
		}
		bool Atleft = true;
		int curevent = 0, arriveTime = INT_MAX;
		queue<int> boat, right, left;

		while (curevent < lin || arriveTime != INT_MAX) {
			if (curevent < lin && events[curevent] <= arriveTime) {
				(side[curevent] ? left : right).push(curevent);
				if (arriveTime == INT_MAX) arriveTime = events[curevent];
				curevent++;
			}
			else {
				while (!boat.empty()) {
					tim[boat.front()] = arriveTime;
					boat.pop();
				}
				if (right.empty() && left.empty())
					arriveTime = INT_MAX;
				else {
					queue<int>& cur = Atleft ? left : right;
					while (!cur.empty() && boat.size() < bS) {
						boat.push(cur.front());
						cur.pop();
					}
					arriveTime += min;
					Atleft = !Atleft;
				}
			}
		}
		for (int i = 0; i < lin; i++) {
			cout << tim[i] << endl;
		}
		if (cas) cout << endl;
	}
}