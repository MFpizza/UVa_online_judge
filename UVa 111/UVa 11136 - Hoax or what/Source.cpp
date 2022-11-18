#include <iostream>
#include <set>
using namespace std;

int main() {
	int count, count2,bill;
	multiset<int>::iterator max, min;
	while (cin >> count, count) {
		long long int cost = 0;
		multiset<int> urn;
		for (int z = 0; z < count; z++) {
			cin >> count2;
			for (int a = 0; a < count2; a++)
			{
				cin >> bill;
				urn.insert(bill);
			}
			max = --urn.end(); min = urn.begin();
			cost += *max - *min;
			urn.erase(max); urn.erase(min);
		}
		cout << cost << endl;
	}
}
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2077