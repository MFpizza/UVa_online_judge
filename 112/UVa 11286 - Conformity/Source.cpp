#include <iostream>
#include <sstream>
#include <map>
using namespace std;
int main() {
	int count;
	while (cin >> count, count) {
		map<string, int> m;
		for (int i = 0; i < count; i++) { 
			int a[5];
			for (int j = 0; j < 5; j++)
				cin >> a[j];
			for (int k = 0; k < 5; k++) //把課表的五堂課作排列
				for (int j = 0; j < 4; j++)
					if (a[j] > a[j + 1])
					{
						int tem = a[j];
						a[j] = a[j + 1];
						a[j + 1] = tem;
					}
			stringstream ss;
			for (int k = 0; k <5; k++) //倒過來轉成string 放進map
				ss << a[k];

			string input; 
			ss >> input;
			m[input]++;
		}
		int max = m.begin()->second,count=0; //尋找最多人選的課表跟最高人票選課表的總選擇人數(可能有同樣多人 不同課表的可能 所有課表的選擇人數要加起來)
		for (map<string, int>::iterator it = m.begin()++; it != m.end(); it++) {
			if (max < it->second) {
				max = it->second;
				count = max;
			}
			else if (max == it->second)
				count += it->second;
		}
		cout << count << endl; //最高票選的所有選擇人數
	}
}