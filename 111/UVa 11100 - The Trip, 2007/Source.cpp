#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

int main() {
	int n;
	ofstream out("o.txt");
	int tem = 1;
	while (cin >> n, n) {
		if (tem != 1)
			cout << endl;
		int* arr = new int[n];
		int* siz = new int[n]();
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}
		int ma = 0;
		sort(arr, arr + n);

		siz[0] = 1;
		for (int i = 1,j=0; i < n; i++) {
			if (arr[i] != arr[i - 1]) {
				j++;
			}
			siz[j]++;
		}

		for (int i = 0; i < n; i++) 
			if (siz[i] > ma)
				ma = siz[i];
		

		vector<queue<int>> vec;
		for (int i = 0; i < ma; i++) {
			queue<int> sta;
			vec.push_back(sta);
		}
		for (int i = 0; i < n; i++) {
			int tem = i;
			tem %= ma;
			vec[tem].push(arr[i]);
		}
		cout << ma<<endl;
		for (int i = 0; i < vec.size(); i++) {
			while (!vec[i].empty()) {
				cout << vec[i].front();
				vec[i].pop();
				if (!vec[i].empty())
					cout << " ";
			}
			cout << endl;
		}
		tem++;
	}
}