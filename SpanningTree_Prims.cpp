#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>  
#include <map>
#include <unordered_set>

using namespace std;

struct Edge {
	int X;
	int Y;
	int Weight;

	Edge(int x, int y, int w) {
		X = x;
		Y = y;
		Weight = w;
	}
};

void g_add(map<int, vector<Edge>>& g, int x, int y, int r) {
	if (g.find(x) == g.end())
		g.insert({ x, vector<Edge>() });

	g[x].push_back(Edge(x, y, r));
}

map<int, vector<Edge>> parseData() {
	int n; //# of nodes
	int m; //# of edges
	int x; //endpoint 1
	int y; //endpont 2
	int r; //weight

	cin >> n >> m;

	map<int, vector<Edge>> g;

	for (int i = 0; i < m; i++)
	{
		cin >> x >> y >> r;
		g_add(g, x, y, r);
		g_add(g, y, x, r);
	}

	return g;
}

Edge getCheapest(map<int, vector<Edge>>& g, unordered_set<int>& x) {
	map<int, vector<Edge>> vertexes;

	Edge min(0, 0, 9999999999);

	for (auto item : x) {
		for (auto e : g[item]) {
			if (min.Weight > e.Weight && x.find(e.Y) == x.end()) {
				min = e;
			}
		}
	}

	return min;
}

int prims(map<int, vector<Edge>>& g, int start) {
	vector<int> nodes;	for (auto it : g) nodes.push_back(it.first);

	unordered_set<int> x;
	vector<Edge> t;
	x.insert(start);

	while (x.size() != nodes.size()) {
		auto e = getCheapest(g, x);

		t.push_back(e);
		x.insert(e.Y);
	}

	int ret = 0;
	for (auto it : t)
		ret += it.Weight;

	return ret;
}


int main() {
	auto g = parseData();

	int start;
	cin >> start;

	auto ret = prims(g, start);
	cout << ret;
}
