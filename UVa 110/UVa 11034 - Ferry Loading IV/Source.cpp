#include <iostream>
#include <queue>
using namespace std;

int main() {
	int cas;
	cin >> cas;
	while (cas--) {
		int count = 0;
		queue<int> right;
		queue<int> left;
		int boat = 0, boatSize, line;
		bool boatAtRight = false;
		cin >> boatSize >> line;
		boatSize *= 100;
		while (line--) {
			int num;
			string s;
			cin >> num >> s;
			if (s == "right")
				right.push(num);
			else
				left.push(num);
		}
		while (!right.empty() || !left.empty()) {
			queue<int>& cur = (boatAtRight) ? right : left;
			while (!cur.empty() && boat < boatSize) {
				int tem = cur.front();
				if (boat + tem > boatSize) break;
				boat += tem;
				cur.pop();
			}
			count++;
			boatAtRight = !boatAtRight;
			boat = 0;
		}
		cout << count << endl;
	}
}