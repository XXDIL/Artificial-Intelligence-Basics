#include<bits/stdc++.h>
#include<math.h>
using namespace std;

struct state
{
	vector<vector<int>> mat;
	state* parent = NULL;

	void setMat(vector<vector<int>>& A)
	{
		mat.insert(mat.end(), A.begin(), A.end());
	}

	void setParent(state &P)
	{
		parent = &P;
	}

	void setChild(state* P, pair<int, int> b, int dia)
	{
		setMat(P->mat);
		// cout << "---------------------------------------------\n";
		int i = b.first;
		int j = b.second;

		if(dia == 1)		// Up
		{
			mat[i][j] = mat[i-1][j];
			mat[i-1][j] = -1;
		}
		else if(dia == 2)	// Down
		{
			mat[i][j] = mat[i+1][j];
			mat[i+1][j] = -1;
		}
		else if(dia == 3)	// Left
		{
			mat[i][j] = mat[i][j-1];
			mat[i][j-1] = -1;
		}
		else				// Right
		{
			mat[i][j] = mat[i][j+1];
			mat[i][j+1] = -1;
		}
	}
};

pair<int, int> findBlank(vector<vector<int>>& A)
{
	pair<int, int> blank;

	for(int i=0; i<3; ++i)
		for(int j=0; j<3; ++j)
			if(A[i][j] == -1) blank = {i, j};

	return blank;
}

void printPuzzle(vector<vector<int>>& puzzle)
{
	for(int i=0; i<3; ++i)
	{
		for(int j=0; j<3; ++j)
		{
			if(puzzle[i][j] == -1) cout << "_\t";
			else cout << puzzle[i][j] << "\t";
		}
		cout << endl;
	}
}

int main()
{
	vector<vector<int>> puzzle{
		{1, 2, 5},
		{3, 4, -1},
		{6, 7, 8}
	};

	vector<vector<int>> goal{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, -1}
	};

	queue<state*> frontier;
	set<vector<vector<int>>> closed;

	struct state start;
	start.setMat(puzzle);

	cout << "Current State = \n";
	printPuzzle(start.mat);

	frontier.push(&start);
	state* P;

	int c = 0;
	while(!frontier.empty())
	{
		state* curr = new state();
		curr = frontier.front();
		frontier.pop();

		closed.insert(curr->mat);

		if(curr->mat == goal)
		{
			P = curr;
			cout << "There is a way ...\n";
			break;
		}

		struct state* U = new state();
		struct state* D = new state();
		struct state* L = new state();
		struct state* R = new state();

		pair<int, int> blank = findBlank(curr->mat);

		if(blank.first > 0)				// Up
		{
			U->setChild(curr, blank, 1);
			if(closed.find(U->mat) == closed.end())
			{
				U->setParent(*curr);
				frontier.push(U);
			}
		}

		if(blank.first < 2)				// Down
		{
			D->setChild(curr, blank, 2);
			if(closed.find(D->mat) == closed.end())
			{
				D->setParent(*curr);
				frontier.push(D);
			}
		}
		if(blank.second > 0)				// Left
		{
			L->setChild(curr, blank, 3);
			if(closed.find(L->mat) == closed.end())
			{
				// cout << "left";
				L->setParent(*curr);
				frontier.push(L);
			}
		}
		if(blank.second < 2)				// Right
		{
			R->setChild(curr, blank, 4);
			if(closed.find(R->mat) == closed.end())
			{
				R->setParent(*curr);
				frontier.push(R);
			}
		}
		c++;
	}

	// printing the path
	stack<state*> path;
	while(P->parent != NULL)
	{
		path.push(P);
		P = P->parent;
	}
	path.push(P);

	while(!path.empty())
	{
		P = path.top();
		printPuzzle(P->mat);
		cout << "-------------------\n";
		path.pop();
	}
}
