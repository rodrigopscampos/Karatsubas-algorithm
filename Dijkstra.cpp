#include <iostream>
#include<vector>
#include <list>
#include <map>
#include <algorithm>
#include <queue>
#include <string>
#include <fstream>
#include <unordered_set>
#include <stack>
#include <unordered_set>
#include <set>

using namespace std;

struct Node {
	int N;
	map<int, int> adjacents;

	Node() {}
	Node(int n) {
		N = n;
	}

	void addAdjacent(int v, int weight) {
		auto it = adjacents.find(v);
		if (it == adjacents.end()) {
			adjacents.insert({ v, weight });
		}
		else {
			if (it->second > weight) {
				it->second = weight;
			}
		}
	}
};

unordered_set<int> getNodes(const int n) {
	unordered_set<int> ret;
	for (int i = 0; i <= n; i++)
		ret.insert(i);

	return ret;
}

int getMin(const vector<int>& D, const unordered_set<int>& unvisited) {
	int min = D[*unvisited.begin()];
	int ret = *unvisited.begin();

	for (auto it : unvisited) {
		if (D[it] < min) {
			min = D[it];
			ret = it;
		}
	}

	return ret;
}

//n: number of edges (from 1 to n)
//graph: graph adjacent list representation
//s: the vertex to calculate the distance from
vector<int> dijkstra(int n, map<int, Node>& graph, int s) {
	int INF = (int)1e9;
	vector<int> D(n + 1, INF); //Dist From A
	D[s] = 0;

	unordered_set<int> unvisited = getNodes(n);

	while (unvisited.size() > 0) {
		int u = getMin(D, unvisited);

		for (auto next : graph[u].adjacents) {
			int v = next.first;
			int weight = next.second;

			if (unvisited.find(v) != unvisited.end()) {
				if (D[u] + weight < D[v]) {
					D[v] = D[u] + weight;
				}
			}
		}

		unvisited.erase(u);
	}

	return D;
}

int main()
{
	int n;

	cin >> n;

	map<int, Node> graph;
	for (int i = 1; i <= n; i++)
		graph.insert({ i, Node(i) });

	int v, u, w, count;
	for (int i = 1; i <= n; i++) {

		cin >> u;
		cin >> count;

		for (int j = 0; j < count; j++) {
			cin >> v;
			cin >> w;

			graph[u].addAdjacent(v, w);
			graph[v].addAdjacent(u, w);
		}
	}

	auto result = dijkstra(n, graph, 1);

	for (int i = 1; i < result.size(); i++)
		cout << i << " : " << result[i] << "\n";

	return 0;
}
