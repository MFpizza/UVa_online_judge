#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int main() {
	int count, num, snowflakes;
	ofstream out("out.txt");
	cin >> count;
	while (count--) {
		set<int> set1;
		cin >> num;
		int ma = 0;
		vector<int> vec;
		for (int i = 0; i < num; i++)
		{
			cin >> snowflakes;
			if (set1.count(snowflakes) == 1) {
				set1.clear();
				unsigned int b=vec.size();
				while (--b)
					if (vec[b] == snowflakes)
						break;
				for (; b < vec.size(); b++)
					set1.insert(vec[b]);
			}
			vec.push_back(snowflakes);
			set1.insert(snowflakes);

			ma = max(ma, (int)set1.size());
		}
		cout << ma << endl;
	}
}
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2619