#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <climits>
#include <math.h>
#include <fstream>
using namespace std;
ofstream out("o.txt");
struct point {
	double x, y;
};
vector<point> map;
double wai_g(point p0, point a, point b) {
	return ((a.x - p0.x) * (b.y - p0.y) - (a.y - p0.y) * (b.x - p0.x));
}

double pathLong(point a, point b) {
	return pow(b.x - a.x, 2) + pow(b.y - a.y, 2);
}

bool compareAngel(point a, point b) {
	int c = wai_g(map[0], a, b);
	return c > 0 || (c == 0 && pathLong(map[0], a) < pathLong(map[0], b));
}
#include <iomanip>
void Graham_scan(double l) {
	vector<point>ans;
	ans.push_back(map[0]);
	ans.push_back(map[1]);
	ans.push_back(map[2]);

	for (int i = 3; i < map.size(); i++) {
		while (ans.size() >= 2 && (wai_g(ans[ans.size() - 2], ans[ans.size() - 1], map[i]) <= 0))
			ans.pop_back();
		ans.push_back(map[i]);
	}

	double ans2 = 0;
	for (int i = 0; i < ans.size() - 1; i++)
		ans2 += sqrt(pathLong(ans[i], ans[i + 1]));
	if (ans2 > l)
		cout << fixed << setprecision(5) << ans2 << endl;
	else
		cout << fixed << setprecision(5) << l << endl;
}
#include <sstream>
int main() {
	string s;
	char a;
	double c, d;
	int cas;
	cin >> cas;
	while (cas--) {
		map.clear();
		int l, noNum;
		cin >> l >> noNum;
		while (noNum--) {
			point nP;
			cin >> nP.x >> nP.y;
			map.push_back(nP);
		}
		int miniY = INT_MAX, miniX = INT_MAX, No = map.size();
		for (int i = 0; i < map.size(); i++) {
			if (map[i].y < miniY || (map[i].y == miniY && map[i].x < miniX)) {
				miniX = map[i].x;
				miniY = map[i].y;
				No = i;
			}
		}
		point temp = map[No];
		map[No] = map[0];
		map[0] = temp;
		sort(map.begin() + 1, map.end(), compareAngel);

		map.push_back(map[0]);
		if (map.size() >= 3)
			Graham_scan(l);
		else
			cout << fixed << setprecision(5) << l << endl;
	}
}