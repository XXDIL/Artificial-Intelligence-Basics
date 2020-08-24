#include<bits/stdc++.h>
#include<math.h>
using namespace std;

struct state
{
	vector<int> mat;
	state* parent = NULL;

	void setState(vector<int>& m)
	{
		mat.insert(mat.end(), m.begin(), m.end());
	}

	void setParent(state &P)
	{
		parent = &P;
	}

	void set1(state* P, int dia)
	{
		setState(P->mat);
		mat[2] ^= 1;

		if(dia == 1)		// 1C
		{
			mat[1] -= 1;
		}
		else if(dia == 2)	// 2C
		{
			mat[1] -= 2;
		}
		else if(dia == 3)	// 1M
		{
			mat[0] -= 1;
		}
		else if(dia == 4)	// 2M
		{
			mat[0] -= 2;
		}
		else				// 1C1M
		{
			mat[0] -= 1;
			mat[1] -= 1;
		}
	}	

	void set2(state* P, int dia)
	{
		setState(P->mat);
		mat[2] ^= 1;
		
		if(dia == 1)		// 1C
		{
			mat[1] += 1;
		}
		else if(dia == 2)	// 2C
		{
			mat[1] += 2;
		}
		else if(dia == 3)	// 1M
		{
			mat[0] += 1;
		}
		else if(dia == 4)	// 2M
		{
			mat[0] += 2;
		}
		else				// 1C1M
		{
			mat[0] += 1;
			mat[1] += 1;
		}
	}
};

void printPuzzle(vector<int> puzzle)
{
	for(int i=0; i<3; ++i)
	{
		cout << puzzle[i] << "  ";
	}
	cout << endl;
}

int main()
{
	vector<int> puzzle{3, 3, 1};

	vector<int> goal{0, 0, 0};

	queue<state*> frontier;
	set<vector<int>> closed;

	struct state start;
	start.setState(puzzle);

	cout << "Current State = \n";
	printPuzzle(start.mat);
	cout << endl;

	frontier.push(&start);
	state* P;

	// int z = 1;
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

		struct state* C = new state();
		struct state* CC = new state();
		struct state* M = new state();
		struct state* MM = new state();
		struct state* CM = new state();

		int currm = curr->mat[0];
		int currc = curr->mat[1];

		if(curr->mat[2] == 1)
		{
			if(currc-1 >= 0 && (currm == 3 || currm == currc-1 || currm == 0))		// 1C
			{
				C->set1(curr, 1);
				if(closed.find(C->mat) == closed.end())
				{
					C->setParent(*curr);
					frontier.push(C);
				}
			}

			if(currc-2 >= 0 && (currm == 3 || currm == currc-2 || currm == 0))		// 2C
			{
				CC->set1(curr, 2);
				if(closed.find(CC->mat) == closed.end())
				{
					CC->setParent(*curr);
					frontier.push(CC);
				}
			}

			if(currm-1 >= 0 && (currm-1 == 0 || currm-1 == currc))		// 1M
			{
				M->set1(curr, 3);
				if(closed.find(M->mat) == closed.end())
				{
					M->setParent(*curr);
					frontier.push(M);
				}
			}

			if(currm-2 >= 0 && (currm-2 == 0 || currm-2 == currc))		// 2M
			{
				MM->set1(curr, 4);
				if(closed.find(MM->mat) == closed.end())
				{
					MM->setParent(*curr);
					frontier.push(MM);
				}
			}

			if(currc-1 >= 0 && currm-1 >= 0 && (currm-1 == 0 || currm-1 == currc-1))		//1C1M
			{
				CM->set1(curr, 5);
				if(closed.find(CM->mat) == closed.end())
				{
					CM->setParent(*curr);
					frontier.push(CM);
				}
			}
		}
		else
		{
			if(currc+1 <= 3 && (currm == 3 || currm == currc+1 || currm == 0))		// 1C
			{
				C->set2(curr, 1);
				if(closed.find(C->mat) == closed.end())
				{
					C->setParent(*curr);
					frontier.push(C);
				}
			}

			if(currc+2 <= 3 && (currm == 3 || currm == currc+2 || currm == 0))		// 2C
			{
				CC->set2(curr, 2);
				if(closed.find(CC->mat) == closed.end())
				{
					CC->setParent(*curr);
					frontier.push(CC);
				}
			}

			if(currm+1 <= 3 && (currm+1 == 3 || currm+1 == currc))		// 1M
			{
				M->set2(curr, 3);
				if(closed.find(M->mat) == closed.end())
				{
					M->setParent(*curr);
					frontier.push(M);
				}
			}

			if(currm+2 <= 3 && (currm+2 == 3 || currm+2 == currc))		// 2M
			{
				MM->set2(curr, 4);
				if(closed.find(MM->mat) == closed.end())
				{
					MM->setParent(*curr);
					frontier.push(MM);
				}
			}

			if(currc+1 <= 3 && currm+1 <= 3 && (currm+1 == 3 || currm+1 == currc+1))		//1C1M
			{
				CM->set2(curr, 5);
				if(closed.find(CM->mat) == closed.end())
				{
					CM->setParent(*curr);
					frontier.push(CM);
				}
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
		if(P->mat[2] == 0)
			cout << "\t\t";
		printPuzzle(P->mat);
		cout << "------------------------\n";
		path.pop();
	}
}
