#include<bits/stdc++.h>
using namespace std;

const int N = 4;

vector<vector<int>> Path;

int graph[N][N] = {
	{0, 10, 15, 20},
	{10, 0, 35, 25},
	{15, 35, 0, 30},
	{20, 25, 20, 0}
};

struct state
{
	int v;
	unordered_set<int> visited;
	state* parent = NULL;

	void setV(int v)
	{
		this->v = v;
	}

	void setParent(state &P)
	{
		parent = &P;
	}

	void setChild(state* P, int v)
	{
		setV(v);
		visited = P->visited;
	}
};

void printPuzzle(int v)
{
	cout << v << " ";
}

int main()
{
	queue<state*> frontier;

	struct state start;
	start.setV(0);

	cout << "Current State = ";
	printPuzzle(start.v);
	cout << endl << endl;

	state* P;

	frontier.push(&start);

	while(!frontier.empty())
	{
		state* curr = new state();
		curr = frontier.front();
		frontier.pop();

		curr->visited.insert(curr->v);

		if(curr->visited.size() == N)
		{
			// create the paths
			P = curr;
			vector<int> temp;
			temp.push_back(0);
			while(P->parent != NULL)
			{
				temp.push_back(P->v);
				P = P->parent;
			}
			temp.push_back(0);
			Path.push_back(temp);
		}


		for(int i=0; i<N; ++i)
		{
			if(curr->visited.find(i) == curr->visited.end())
			{
				struct state* V = new state();

				V->setChild(curr, i);
				V->setParent(*curr);

				frontier.push(V);
			}
		}
	}


	// printing the paths
	cout << "Paths = \n";
	for(auto i : Path)
	{
		for(int j : i)
		{
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;

	// cost calculation
	int pos = 0;
	int min_val = INT_MAX;
	for(int i=0; i<Path.size(); ++i)
	{
		int val = 0;
		for(int j=0; j<Path[i].size()-1; ++j)
		{
			val += graph[Path[i][j]][Path[i][j+1]];
			// cout << graph[Path[i][j]][Path[i][j+1]] << " ";
		}

		if(val < min_val)
		{
			min_val = val;
			pos = i;
		}
	}

	cout << "Minimum at pos = " << pos << " and value = "<< min_val << endl;
	for(auto i : Path[pos])
		cout << i << " -> ";
	cout << endl;
}
