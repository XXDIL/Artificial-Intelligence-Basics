/*
	Assuming that we accept only {0, T}
*/

#include<bits/stdc++.h>
#include<math.h>
using namespace std;

int M=6, N=3, T=4;
// M = J1 max
// N = J2 max
// T = target

struct state
{
	vector<int> mat;
	state* parent = NULL;

	void setMat(vector<int>& A)
	{
		mat.insert(mat.end(), A.begin(), A.end());
	}

	void setParent(state &P)
	{
		parent = &P;
	}

	void setChild(state* P, int dia)
	{
		setMat(P->mat);

		if(dia == 1)		// Fill X
		{
			mat[0] = M;
		}
		else if(dia == 2)	// Fill Y
		{
			mat[1] = N;
		}
		else if(dia == 3)	// Empty X
		{
			mat[0] = 0;
		}
		else if(dia == 4)	// Empth Y
		{
			mat[1] = 0;
		}
		else if(dia == 5)	// X to Y
		{
			int d = min(mat[0], N-mat[1]);
			mat[0] -= d;
			mat[1] += d;
		}
		else				// Y to X
		{
			int d = min(mat[1], M-mat[0]);
			mat[0] += d;
			mat[1] -= d;
		}
	}
};

void printPuzzle(vector<int>& puzzle)
{
	cout << puzzle[0] << "\t" << puzzle[1] << endl;
}

int main()
{
	vector<int> puzzle{0,0};

	vector<int> goal{0, T};

	queue<state*> frontier;
	set<vector<int>> closed;

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
			c = 1;
			P = curr;
			cout << "There is a way ...\n";
			break;
		}

		struct state* FX = new state();
		struct state* FY = new state();
		struct state* EX = new state();
		struct state* EY = new state();
		struct state* XtoY = new state();
		struct state* YtoX = new state();


		if(curr->mat[0] != M)						// Fill X
		{
			FX->setChild(curr, 1);
			if(closed.find(FX->mat) == closed.end())
			{
				FX->setParent(*curr);
				frontier.push(FX);
			}
		}

		if(curr->mat[1] != N)						// Fill Y
		{
			FY->setChild(curr, 2);
			if(closed.find(FY->mat) == closed.end())
			{
				FY->setParent(*curr);
				frontier.push(FY);
			}
		}
		if(curr->mat[0] != 0)						// Empty X
		{
			EX->setChild(curr, 3);
			if(closed.find(EX->mat) == closed.end())
			{
				EX->setParent(*curr);
				frontier.push(EX);
			}
		}
		if(curr->mat[1] != 0)						// Empty Y
		{
			EY->setChild(curr, 4);
			if(closed.find(EY->mat) == closed.end())
			{
				EY->setParent(*curr);
				frontier.push(EY);
			}
		}
		if(curr->mat[0] > 0 && curr->mat[1] < N)	// X to Y
		{
			XtoY->setChild(curr, 5);
			if(closed.find(XtoY->mat) == closed.end())
			{
				XtoY->setParent(*curr);
				frontier.push(XtoY);
			}
		}
		if(curr->mat[1] > 0 && curr->mat[0] < M)	// Y to X
		{
			YtoX->setChild(curr, 6);
			if(closed.find(YtoX->mat) == closed.end())
			{
				YtoX->setParent(*curr);
				frontier.push(YtoX);
			}
		}
	}

	if(c == 0)
	{
		cout << "This is not possible !"<< endl;
		return 0;
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
		cout << "----------\n";
		path.pop();
	}
}
