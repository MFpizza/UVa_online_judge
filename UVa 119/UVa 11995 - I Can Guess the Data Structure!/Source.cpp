#include <stack>
#include <queue>
#include <iostream>
using namespace std;

int main() {
	int n;
	while (cin >> n) {
		stack<int> stac;
		queue<int> que;
		priority_queue<int> pque;
		bool stackPossible = true, queuePossible = true, priorityPossible = true;
		while (n--) {
			int cas, second;
			cin >> cas >> second;
			if (cas == 1) {
				if (stackPossible)
					stac.push(second);
				if (queuePossible)
					que.push(second);
				if (priorityPossible)
					pque.push(second);
			}
			else {
				if (stackPossible)
				{
					if (stac.empty() || stac.top() != second)
						stackPossible = false;
					else
						stac.pop();
				}
				if (queuePossible)
				{
					if (que.empty() || que.front() != second)
						queuePossible = false;
					else
						que.pop();
				}
				if (priorityPossible)
				{
					if (pque.empty() || pque.top() != second)
						priorityPossible = false;
					else
						pque.pop();
				}
			}
		}

		if (!stackPossible && !queuePossible && !priorityPossible)
			cout << "impossible\n";
		else if ((stackPossible && queuePossible) ||
			(stackPossible && priorityPossible) ||
			(queuePossible && priorityPossible))
			cout << "not sure\n";
		else if (stackPossible)
			cout << "stack\n";
		else if (queuePossible)
			cout << "queue\n";
		else
			cout << "priority queue\n";
	}
}