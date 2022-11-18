#include <stack>
#include <queue>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
int updown, drive;
struct node {
	int data;
	queue<int> cap;
};

struct car {
	stack<int> cap;
	int state;
};

bool em(vector<node>&map, car &Car) {
	bool end = true;
	for (int i = 0; i < map.size(); i++)
		if (map[i].cap.size() != 0)
		{
			end = false;
			break;
		}
	if (Car.cap.size() != 0) end = false;
	return end;
}

int main() {
	ofstream out("o.txt");
	int cas;
	cin >> cas;
	while (cas--) {
		updown = drive = 0;
		int nodenum, carCapcity, nodeCapcity;
		cin >> nodenum >> carCapcity >> nodeCapcity;
		vector<node> map;
		for (int i = 0; i < nodenum; i++) {
			node n;
			n.data = i + 1;
			int num, goods;
			cin >> num;
			while (num--) {
				cin >> goods;
				n.cap.push(goods);
			}
			map.push_back(n);
		}
		car Car;
		Car.state = 0;
		while (1) {
			while (!Car.cap.empty() ) { //卸貨
				if (map[Car.state].cap.size() == nodeCapcity) {
					while (!Car.cap.empty()&&Car.cap.top() == map[Car.state].data) {
						Car.cap.pop();
						updown++;
					}
					break;
				}
				updown++;
				int tem = Car.cap.top();
				Car.cap.pop();
				if (tem != map[Car.state].data) {
					map[Car.state].cap.push(tem);
				}
			}
			while (Car.cap.size() < carCapcity && map[Car.state].cap.size() != 0) { //上貨
				updown++;
				int tem = map[Car.state].cap.front();
				map[Car.state].cap.pop();
				Car.cap.push(tem);
			}
			if (em(map, Car)) break; //全空?
			drive++; //開車
			Car.state++;
			Car.state %= nodenum;
		}
		cout << 2 * drive + updown << endl;
	}
}