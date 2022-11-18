#include<iostream>
#include <vector>
using namespace std;
void sort1(vector<int>& Knight, vector<int>& dragon) {
	for (int i = 0; i < Knight.size(); i++) {
		for (int j = 0; j < Knight.size(); j++) {
			if (Knight[i] < Knight[j]) {
				int tem = Knight[i];
				Knight[i] = Knight[j];
				Knight[j] = tem;
			}
		}
	}
	for (int i = 0; i < dragon.size(); i++) {
		for (int j = 0; j < dragon.size(); j++) {
			if (dragon[i] < dragon[j]) {
				int tem = dragon[i];
				dragon[i] = dragon[j];
				dragon[j] = tem;
			}
		}
	}
}
#include <fstream>
int main() {
	int HeadNum, knight;
	ofstream out("o.txt");
	while (cin >> HeadNum >> knight) {
		if (HeadNum == 0 && knight == 0)
			break;
		vector<int> dragon;
		int tem;
		while (HeadNum--) {
			cin >> tem;
			dragon.push_back(tem);
		}
		vector<int>Knight;
		while (knight--) {
			cin >> tem;
			Knight.push_back(tem);
		}
		sort1(Knight, dragon);
		int kill = 0, pay = 0;
		int siz = (Knight.size() > dragon.size()) ? Knight.size() : dragon.size();
		for (int i = 0, j = 0;;) {
			if (i == Knight.size() || j == dragon.size())
				break;
			if (Knight[i] >= dragon[j]) {
				pay += Knight[i];
				kill++, i++, j++;
			}
			else {
				i++;
			}
		}
		if (kill == dragon.size())
			cout << pay << endl;
		else
			cout << "Loowater is doomed!\n";
	}
}