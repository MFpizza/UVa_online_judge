#include <queue>
#include <string>
#include <iostream>
#include <map>
using namespace std;

struct Node {
	int x, time,period;
	Node(int _x, int _y,int _z) {
		x = _x; time = _y;  period = _z;
	}
	bool operator<(const Node &b)const {
		if (time == b.time) 
			return x > b.x;
		return time > b.time;
	}
};

int main() {
	string s;
	priority_queue<Node> que;
	while (cin >> s) {
		if (s == "#")
			break;
		int num, period;
		cin >> num >> period;
		Node node(num, period, period);
		que.push(node);
	}
	int cas;
	cin >> cas;

	while (cas--) {
		Node n = que.top(); que.pop();
		cout << n.x << endl;
		n.time += n.period;
		que.push(n);
	}
}
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3644