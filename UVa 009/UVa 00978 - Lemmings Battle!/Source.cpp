#include <iostream>
#include <set>
#include <vector>
using namespace std;
#include <stdio.h>

int main() {
	int power, BF, SG, SB, cas;
	multiset<int> GP, BP;
	vector<int> gw, bw;
	multiset<int>::iterator it, fit;
	cin >> cas;
	while (cas--) {
		GP.clear(); BP.clear();
		cin >> BF >> SG >> SB;
		for (int i = 0; i < SG; i++)
		{
			cin >> power;
			GP.insert(power);
		}
		for (int i = 0; i < SB; i++)
		{
			cin >> power;
			BP.insert(power);
		}
		while (BP.size() > 0 && GP.size() > 0) {
			gw.clear(); bw.clear();
			for (int i = 0; i < BF; i++) {
				it = --BP.end(), fit = --GP.end();
				if (*it > * fit)
					bw.push_back(*it - *fit);
				else if (*fit > * it)
					gw.push_back(*fit - *it);
				BP.erase(it); GP.erase(fit);

				if (BP.size() == 0 || GP.size() == 0)
					break;
			}
			for (int i = 0; i < gw.size(); i++)
				GP.insert(gw[i]);
			for (int i = 0; i < bw.size(); i++)
				BP.insert(bw[i]);
		}
		if (!BP.empty() && GP.empty()) {
			cout << "blue wins\n";
			for (it = --BP.end(); it != BP.begin(); --it)
				cout << *it << "\n";
			cout << *it << "\n";
		}
		else if (BP.empty() && !GP.empty()) {
			cout << "green wins\n";
			for (it = --GP.end(); it != GP.begin(); --it)
				cout << *it << "\n";
			cout << *it << "\n";
		}
		else
			cout << "green and blue died\n";
		if (cas) printf("\n");
	}
}