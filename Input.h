#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stack>

using namespace std;

struct edge;
struct vertex
{
	std::vector<edge> in;
	int color = 0;
	int number = 0;
	bool operator==(vertex a) const
	{
		return number == a.number;
	}
	bool visited = false;
};

struct edge
{
	vertex* from;
	vertex* to;
	double weight;
	edge(vertex* from,vertex* to, double wei) :from(from), to(to), weight(wei) {};
};


class Graph
{
	void addCycle(std::vector<vertex>);
	std::vector<vertex> cycle;
	std::vector<vertex> v;
	std::vector<std::vector<vertex>> fcycle;
	int j = 0;
	void dfs(vertex*, int);
	void move(std::vector<vertex>& a);
	void printCycles();
	bool eq(std::vector<vertex> a, std::vector<vertex> b);
public:
	Graph() {};
	~Graph() {};
	double FindEdge(vertex* a, vertex* b);
	void FindCycles();
	void ShowGraph();
	void ReadGraph();
	void ReadGraph_test(int i);
	bool ProcessLine(const std::string& line, std::vector<vertex>& v);
};

void test();





