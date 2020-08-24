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
	unordered_map<string, vector<node>> graph;
	unordered_map<string, string> parent;
	unordered_map<string, float> dist;
	priority_queue<pair<float, string>, vector<pair<float, string>>, greater<pair<float, string>>> min_heap;

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
		dist[vert] = float(INT_MAX);
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

	min_heap.push({0.0, source});
	dist[source] = 0.0;

	while(!min_heap.empty())
	{
		auto curr = min_heap.top();
		min_heap.pop();

		for(auto i : graph[curr.second])
		{
			if(curr.first + i.w < dist[i.to])
			{
				parent[i.to] = curr.second;
				dist[i.to] = curr.first + i.w;
				min_heap.push({i.w, i.to});
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