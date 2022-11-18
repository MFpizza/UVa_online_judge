#include <iostream>
#include <list>
using namespace std;
int main() {
	int p, c, ulimit, n, t = 1;
	char cmd;
	list<int> mlist;
	while (cin >> p >> c) {
		if (p == 0) break;
		if (p > 1000) ulimit = 1000;
		else ulimit = p;
		mlist.clear();
		for (int i = 1; i <= ulimit; i++) mlist.push_back(i);
		cout << "Case " << t++ << ":" << endl;
		for (int i = 1; i <= c; i++) {
			cin >> cmd;
			if (cmd == 'N') {
				cout << mlist.front() << endl;
				mlist.push_back(mlist.front());
				mlist.pop_front();
			}
			else {
				cin >> n;
				mlist.remove(n);
				mlist.push_front(n);
			}
		}
	}
}
//https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3359