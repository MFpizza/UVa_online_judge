#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
//http://unfortunatedog.blogspot.com/2013/07/168-theseus-and-minotaur.html ½Ķ

struct Node {
	char data;
	vector<Node*> adj;
	bool light;
};

void dfs(vector<Node*> map, char TheseusPoint, char MinotaurPoint, int pC) {
	Node* T = map[TheseusPoint-'A'], * M = map[MinotaurPoint-'A'];
	int count = 0;
	while (1) { //開始追逐戰
		Node* tem = M;//紀錄Minotaur 在移動前的位置
		bool MDied = true; //如果Minotaur 沒位置能移動 也就是被卡死會=true
		for (int i = 0; i < M->adj.size(); i++) { //對所有Minotaur的鄰居
			if (M->adj[i] != T && M->adj[i]->light == false) { //找到第一個可以過去(不是Theseus所在的位置 跟 沒有放蠟燭) 的點
				M = M->adj[i]; //Minotaur網可以過去的點移動過去
				MDied = false; //Minotaur 沒被困死 所以她活下來 所以MinotaurDied = false
				break; //他只會找第一個可以移動過去的點 所以不用找其他可以過去的點
			}
		}
		if (MDied) { //Minotaur 被困死 輸出他被困死的位置
			cout << '/' << M->data << endl;
			break;
		}
		T = tem; //讓Theseus 移動到 Minotaur 移動前所在的位置
		count++; //代表 Theseus 移動的次數++
		if (count % pC == 0) { //如果移動的次數是 放蠟燭數量的倍數
			T->light = true; //放蠟燭
			cout << T->data << " "; //輸出蠟燭所在的位置
		}
	}
}

int main() {
	string s;
	vector<Node* > map;
	while (cin >> s) {
		if (s == "#") break;
		map.clear();
		for (int i = 0; i < 26; i++) {
			Node* newNode = new Node;
			newNode->data = i + 'A';
			newNode->light = false;
			map.push_back(newNode);
		}
		char ch;
		char TheseusPoint, MinotaurPoint;
		int PutCandleNum;
		for (int i = 0; i < s.size(); i++) {
			ch = s[i];
			Node* Nodeptr = map[ch - 'A'];
			while (s[i] != ';') {
				if (s[i] != ':' && s[i] != ch) {
					Nodeptr->adj.push_back(map[s[i] - 'A']);
				}
				i++;
				if (s[i] == '.') break;
			}
			if (s[i] == '.') break;
		}
		cin >> MinotaurPoint >> TheseusPoint >> PutCandleNum;
		dfs(map, TheseusPoint, MinotaurPoint, PutCandleNum);
	}
}