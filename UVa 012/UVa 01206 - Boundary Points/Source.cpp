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
void Graham_scan() {
	vector<point>ans;
	ans.push_back(map[0]);
	ans.push_back(map[1]);
	ans.push_back(map[2]);
	for (int i = 3; i < map.size(); i++) {
		while (ans.size() >= 2 && (wai_g(ans[ans.size() - 2], ans[ans.size() - 1], map[i]) <= 0))
			ans.pop_back();
		ans.push_back(map[i]);
	}
	for (int i = map.size() - 1, t = ans.size(); i >= 0; i--) {

		while (ans.size() >= t && (wai_g(ans[ans.size() - 2], ans[ans.size() - 1], map[i]) <= 0))
			ans.pop_back();
		ans.push_back(map[i]);
	}
	
	cout <<fixed<< setprecision(3) << "(" << ans[0].x << "," << ans[0].y << ")";
	for (int i = 1; i < ans.size(); i++) {
		cout  << " (" << setprecision(3) << ans[i].x << "," << setprecision(3) << ans[i].y << ")";
	}
	cout << endl;
}
#include <sstream>
int main() {
	string s;
	char a;
	double c, d;
	while (getline(cin, s)) {
		if (s == "")
			break;
		map.clear();
		stringstream aa(s);
		while (aa >> a >> c >> a >> d >> a) {
			point nP;
			nP.x = c;
			nP.y = d;
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
		Graham_scan();
	}
}