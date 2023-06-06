#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;
struct MapNode {
	string name;
	int x, y;
};
class Graph {
private:
	vector<MapNode> nodes;
	unordered_map<int, vector<pair<int, int>>> adj_;
public:
	void addNode(string name, int x, int y);
	void addEdge(int u, int v, int w);
	int shortestPath(int u, int v);
	MapNode getNode(int idx);
};
void guide();