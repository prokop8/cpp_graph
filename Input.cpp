#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Input.h"
#include <iterator>
#include <algorithm>
#include <stack>

bool Graph::ProcessLine(const std::string& line, std::vector<vertex>& v)
{
	bool flag=false;
	std::istringstream ss(line);
	if (line.length()==0)
		return false;
	for (unsigned k = 0; k < line.length(); k++)
	{
		if (line[k] == ' ') flag=true;
	}
	if (flag==false)
	{
		double hlp;
		ss >> hlp;
		if (hlp<=1)
			return false;
		v.resize(hlp);
	}
	else
	{
		int hlp1, hlp2;
        double hlp3;
		ss >> hlp1 >> hlp2 >> hlp3;
		v[hlp1].in.push_back(edge(&v[hlp1], &v[hlp2], hlp3));
		v[hlp1].number = hlp1;
		v[hlp2].in.push_back(edge(&v[hlp2], &v[hlp1], hlp3));
		v[hlp2].number = hlp2;
	}
	return true;
}

void Graph::FindCycles()
{
	for (int i = 0; i < v.size();i++)
		if(v[i].visited==false)
			dfs(&v[i], 1);
	printCycles();
}

void Graph::ShowGraph()
{
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i].number << endl;
}

void Graph::ReadGraph()
{
	bool flaga = true;
	while (cin)
	{
		string line;
		getline(cin, line);
		flaga = ProcessLine(line, v);
		if (flaga == false)
			break;
	}
}

void Graph::ReadGraph_test(int i)
{
	bool flaga = true;
	if (i == 1)
	{
		string line = "4";
		flaga = ProcessLine(line, v);
		line = "1 0 12.3";
		flaga = ProcessLine(line, v);
		line = "0 2 10";
		flaga = ProcessLine(line, v);
		line = "1 2 2.4";
		flaga = ProcessLine(line, v);
		line = "2 3 1.1";
		flaga = ProcessLine(line, v);
		line = "3 0 5.0";
		flaga = ProcessLine(line, v);
	}
	else if (i == 2)
	{
		string line = "6";
		flaga = ProcessLine(line, v);
		line = "0 1 1";
		flaga = ProcessLine(line, v);
		line = "0 2 1";
		flaga = ProcessLine(line, v);
		line = "1 2 1";
		flaga = ProcessLine(line, v);
		line = "3 4 1";
		flaga = ProcessLine(line, v);
		line = "3 5 1";
		flaga = ProcessLine(line, v);
		line = "4 5 1";
		flaga = ProcessLine(line, v);
	}
	else if (i == 3)
	{
		string line = "6";
		flaga = ProcessLine(line, v);
		line = "0 1 1";
		flaga = ProcessLine(line, v);
		line = "0 3 1";
		flaga = ProcessLine(line, v);
		line = "1 2 1";
		flaga = ProcessLine(line, v);
		line = "2 3 1";
		flaga = ProcessLine(line, v);
		line = "3 4 1";
		flaga = ProcessLine(line, v);
		line = "4 5 1";
		flaga = ProcessLine(line, v);
		line = "2 5 1";
		flaga = ProcessLine(line, v);
	}
	else if (i == 4)
	{
		string line = "4";
		flaga = ProcessLine(line, v);
		line = "0 1 1";
		flaga = ProcessLine(line, v);
		line = "0 3 1";
		flaga = ProcessLine(line, v);
		line = "0 2 1";
		flaga = ProcessLine(line, v);
		line = "1 2 1";
		flaga = ProcessLine(line, v);
		line = "1 3 1";
		flaga = ProcessLine(line, v);
		line = "2 3 1";
		flaga = ProcessLine(line, v);
	}
	else if (i == 5)
	{
		string line = "2";
		flaga = ProcessLine(line, v);
		line = "0 1 1";
		flaga = ProcessLine(line, v);
	}
	else if (i == 6)
	{
		string line = "2";
		flaga = ProcessLine(line, v);
	}
}


void Graph::dfs(vertex* v,int c)
{
	cycle.push_back(*v);
	v->visited = true;
	if (v->color == 0)
	{
		for (int i = 0; i < v->in.size(); i++)
		{
			v->color = c;
			dfs(v->in[i].to, 1+c%2);
		}
		v->color = 0;
	}
	else if(v->color==1+c%2)
	{
		std::vector<vertex> t;
		for (int i = cycle.size() - 1; i >= 0; i--)
		{
			if (v->number == cycle[i].number && i!=cycle.size()-1)
				break;
			t.push_back(cycle[i]);
		}
		addCycle(t);
	}
	cycle.pop_back();
}

void Graph::addCycle(std::vector<vertex> cyc)
{
	for (auto v = fcycle.begin(); v != fcycle.end();v++)
	{
		if (eq(cyc, *v))
			return;
	}
	j++;
	fcycle.push_back(cyc);
}

bool Graph::eq(std::vector<vertex> a, std::vector<vertex> b)
{
	if (a.size() != b.size())
		return false;
	int n = a.size();
	for (int i = 0; i < n; ++i)
	{
		if (a == b)
			return true;
		move(b);
	}
	reverse(b.begin(), b.end());
	for (int i = 0; i < n; ++i)
	{
		if (a == b)
			return true;
		move(b);
	}
	return false;
}

void Graph::move(std::vector<vertex>& a)
{
	vertex tmp;
	tmp = a[0];
	a.erase(a.begin());
	a.push_back(tmp);
}

void Graph::printCycles()
{
	for (int i = 0; i < fcycle.size(); i++)
	{
		double suma = 0;
		for (int m = 0; m < fcycle[i].size(); m++)
		{
			if (m < fcycle[i].size() - 1)
				suma += FindEdge(&fcycle[i][m], &fcycle[i][m + 1]);
			std::cout << fcycle[i][m].number;
		}
		suma += FindEdge(&fcycle[i][fcycle[i].size()-1], &fcycle[i][0]);
		std::cout << fcycle[i][0].number;
		std::cout << " " << suma;
		std::cout << std::endl;
	}
}

double Graph::FindEdge(vertex* a, vertex* b)
{
	for (int i = 0; i < a->in.size(); i++)
	{
		for (int j = 0; j < b->in.size(); j++)
		{
			if (a->in[i].from == b->in[j].to && a->in[i].to == b->in[j].from)
				return a->in[i].weight;
		}
	}
	return 0;
}

void test()
{
	Graph a;
	Graph b;
	Graph c;
	Graph d;
	Graph e;
	Graph f;
	std::cout << "Graf z zadania" << std::endl;
	a.ReadGraph_test(1);
	a.FindCycles();
	std::cout << "Rozlaczny graf" << std::endl;
	b.ReadGraph_test(2);
	b.FindCycles();
	std::cout << "Graf bez nieparzystych cykli" << std::endl;
	c.ReadGraph_test(3);
	c.FindCycles();
	std::cout << "Graf K4" << std::endl;
	d.ReadGraph_test(4);
	d.FindCycles();
	std::cout << "Graf ktory ma 2 wierzcholki polaczone" << std::endl;
	e.ReadGraph_test(5);
	e.FindCycles();
	std::cout << "Graf ktory ma 2 wierzcholki rozlaczne" << std::endl;
	f.ReadGraph_test(6);
	f.FindCycles();

}

