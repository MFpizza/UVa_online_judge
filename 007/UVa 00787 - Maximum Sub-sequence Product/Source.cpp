#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

string mul(string a, string b)
{
	string c;
	c.resize(a.size() * b.size(),'0');
	for (int i = a.size() - 1; i >= 0; i--) {
		for (int j = b.size() - 1; j >= 0; j--) {
			if (a[i] == '-' || b[i] == '-')
				continue;
			c[i * j] += (a[i]-'0') * (b[j]-'0');
		}
	}

	for(int i=c.size()-1;i>=0;i--)
		if (c[i] > '9') {
			int t = c[i] / 10;
			c[i] = c[i] % 10;
			c[i + 1] + t;
		}
	return c;
}

string compar(string a, string b, bool bigger) {
	if (bigger) {
		if (a.size() > b.size())
			return a;
		if (a.size() < b.size())
			return b;
		if (a.size() == b.size())
			for (int i = 0; i < a.size(); i++)
				if (a[i] > b[i])
					return a;
		return b;
	}
	else {
		if (a.size() > b.size())
			return b;
		if (a.size() < b.size())
			return a;
		if (a.size() == b.size())
			for (int i = 0; i < a.size(); i++)
				if (a[i] > b[i])
					return b;
		return a;
	}
}

string findMaxSubArray(vector<string>vec) {
	vector<string>ma(vec.size());
	vector<string>mi(vec.size());
	ma[0] = mi[0] = "1";
	for (int i = 1; i < vec.size(); i++) {
		if (vec[i] == "0") {
			ma[i] = mi[i] = "0";
			continue;
		}
		string mid1 = mul(ma[i-1] ,vec[i]);
		string mid2 = mul(mi[i - 1] , vec[i]);
		ma[i] = compar(vec[i], mid1,true);
		ma[i] = compar(ma[i], mid2,true);
		mi[i] = compar(vec[i], mid1,false);
		mi[i] = compar(mi[i], mid2,false);
	}
	string max2 = ma[1];
	for (int i = 2; i < ma.size(); i++) {
		max2 = compar(max2, ma[i],true);
	}
	return max2;
}
#include <fstream>
int main() {
	string num;
	ofstream out("t.txt");
	vector<string>vec;
	vec.push_back("0");
	while (cin >> num) {
		if (num == "-999999") {
			cout << findMaxSubArray(vec) << endl;
			vec.clear();
			vec.push_back("0");
		}
		else if (num == "-9999999") {
			return 0;
		}
		else
			vec.push_back(num);
	}
}