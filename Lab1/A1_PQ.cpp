#include <bits/stdc++.h>
#include <string.h>
using namespace std;

stack<string> path;		// stack for path printing.

struct node
{
	string to;
	string road;
	float w;
};

void printG(unordered_map<string, vector<node> > graph)
{
	for(auto i : graph)
	{
		cout << i.first << " : ";
		for(auto j : i.second)
		{
			cout << "[" << j.to << ", " << j.road << ", " << j.w << "]";
		}
		cout << endl;
	}
}

pair<string, float> find_min(unordered_map<string, float> heap)
{
	pair<string, float> m = {"", INT_MAX};
	for(auto i : heap)
	{
		if(i.second <= m.second)
		{
			m = {i.first, i.second};
		}
	}

	return m;
}

void buildStack(string fin, string curr, unordered_map<string, string> parent)
{
	if(curr == fin)
	{
		path.push(curr);
		return;
	}

	path.push(curr);
	buildStack(fin, parent[curr], parent);
}

int main()
{
	unordered_map<string, vector<node> > graph;
	unordered_map<string, string> parent;
	unordered_map<string, float> heap;

	int v, e;
	cout << "Enter the number of Vertices : ";
	cin >> v;
	cout << "Enter the Vertices : \n";
	// initializing the heap and the parent array.
	for(int i=0;i<v;++i)
	{
		string vert;
		cin >> vert;

		parent[vert] = "";
		heap[vert] = float(INT_MAX);
	}

	cout << "\nEnter the number of Edges : " ;
	cin >> e;
	cout << "Enter the Edges : \n";
	for(int i=0;i<e;++i)
	{
		string f, t, r;
		float v;
		cin >> f >> t >> r >> v;

		node temp;
		temp.to = t;
		temp.road = r;
		temp.w = v;

		graph[f].push_back(temp);
	}


	cout << "\nGraph : \n";
	printG(graph);

	string source;
	cout << "\nEnter the Source Node : ";
	cin >> source;

	heap[source] = 0.0;

	pair <string, float> m;

	while(!heap.empty())
	{
		m = find_min(heap);
		heap.erase(m.first);

		if(graph.find(m.first) == graph.end()) continue;

		for(auto i : graph[m.first])
		{
			if(heap.find(i.to) == heap.end()) continue;

			if(heap[i.to] > i.w + m.second)
			{
				heap[i.to] = i.w + m.second;
				parent[i.to] = m.first;
			}
		}
	}

	cout << "\nPath from " << source << " to all the other nodes : \n";
	for(auto i : parent)
	{
		if(i.second == "") continue;

		buildStack(source, i.first, parent);

		// print stack content along with the respective paths.
		while(!path.empty())
		{
			string poped = path.top();
			cout << poped << " ";
			path.pop();

			for(auto j : graph[poped])
			{
				if(!path.empty() && j.to == path.top())
				{
					cout << j.road << " ";
					break;
				}
			}
		}
		cout << endl;
	}

}

/*

INPUT GRAPH

6
A B C D E F
7
A B R1 4
A C R2 6
A D R3 8
B C R5 1
D E R7 3
D F R6 6
F A R4 5
A
*/