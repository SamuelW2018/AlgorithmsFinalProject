#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//P[8][3][3] (8, vector < vector<bool>(3, vector<bool>(3, false)));
vector<vector<vector<bool>>> P = {
{ { false, true, false },{ true, true, true },{ false, true, false } },
{ {true, true, false},{ false, true, false },{ false, true, true } },
{ {true, false, false},{ true, false, false },{ true, true, true } },
{ {true, true, true},{ false, true, false },{ false, true, false } },
{ {false, true, true},{ true, true, false },{ false, true, false } },
{ {false, true, true},{ false, true, false },{ true, true, false } },
{ { true, true, false },{ false, true, true },{ false, true, false}},
{ { true, false, false },{ true, true, false },{ false, true, true } }
};

const int X = 0;
const int Z = 1;
const int V = 2;
const int T = 3;
const int R = 4;
const int S = 5;
const int SEVEN = 6;
const int W = 7;

int chooseBlock(char c)
{
	if (c == 'X')
	{
		return 0;
	}
	else if (c == 'Z')
	{
		return 1;
	}
	else if (c == 'V')
	{
		return 2;
	}
	else if (c == 'T')
	{
		return 3;
	}
	else if (c == 'R')
	{
		return 4;
	}
	else if (c == 'S')
	{
		return 5;
	}
	else if (c == '7')
	{
		return 6;
	}
	else
		return 7;
}

// , [size_x]>, [size_y] , [size_x2]>, [size_y2] size_t size_x2, size_t size_y2
//template <size_t size_x, size_t size_y>
inline void Copy(vector<vector<bool>> d, vector<vector<bool>> s)
{
	for (int i = 0; i < s.size(); i++)
	{
		for (int j = 0; j < s[i].size(); j++)
		{
			d[i][j] = s[i][j];
		}
	}
}


// template <size_t size_x, size_t size_y> , [size_x]>, [size_y]
void print(vector<vector<bool>> d)
{
	for (int i = 0; i < d.size(); i++)
	{
		for (int j = 0; j < d[i].size(); j++)
		{
			cout << d[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

// , [size_x]>, [size_y] , [size_x2]>, [size_y2]
//template <size_t size_x, size_t size_y, size_t size_x2, size_t size_y2>
vector<vector<bool>> addBlock(vector<vector<bool>> block, vector<vector<bool>> state)
{
	int height = 9;

	for (int i = 0; i <= 2; i++)
	{
		if (block[2][i] == true)
		{
			bool nex = true; int h = 10;
			do
			{
				h--;
				nex = state[h][i];
			} while (nex == true && h > 2);
			if (h > height)
			{
				height = h;
			}
		}
	}

	vector<vector<bool>> newState = { {false, false, false},{ false, false, false },{ false, false, false },{ false, false, false },{ false, false, false },{ false, false, false },{ false, false, false },{ false, false, false },{ false, false, false },{ false, false, false } };
	//Copy(newState, state);
	newState = state;

	bool added = true;

	do
	{
		added = true;
		//Copy(newState, state);
		newState = state;
		for (int i = height; i > height - 3; i--)
		{
			for (int j = 0; j <= 2; j++)
			{
				if (block[(i + 2) - height][j] == true)
				{
					if (state[height][j] == true)
						added = false;
					else
						newState[i][j] = block[(i + 2) - height][j];
				}
			}
		}

		if (!added)
		{
			height = height - 1;
		}
	} while (!added && height >= 3);

	if (height < 3)
	{
		return { {true, true, true},{ true, true, true },{ true, true, true },{ true, true, true },{ true, true, true },{ true, true, true },{ true, true, true },{ true, true, true },{ true, true, true },{ true, true, true } };
	}

	return newState;
}

vector<vector<bool>> rotate(vector<vector<bool>> block, int rotate)
{
	vector<vector<bool>> newBlock = block;
	for (int i = 1; i <= rotate; i++)
	{
		vector<vector<bool>> temp(3, vector<bool>(3));
		temp[0][2] = newBlock[0][0];
		temp[1][2] = newBlock[0][1];
		temp[2][2] = newBlock[0][2];
		temp[1][1] = newBlock[1][1];
		temp[2][1] = newBlock[1][2];
		temp[2][0] = newBlock[2][2];
		temp[1][0] = newBlock[2][1];
		temp[0][0] = newBlock[2][0];
		temp[0][1] = newBlock[1][0];
		newBlock = temp;
	}
	return newBlock;
}

vector<vector<bool>> CheckState(vector<vector<bool>> state)
{
	vector<vector<bool>> newState = state;
	for (int i = 0; i < 10; i++)
	{
		if ((newState[i][0] == true) && (newState[i][1] == true) && (newState[i][2] == true))
		{
			for (int j = i; j > 0; j--)
			{
				newState[j][0] = newState[j - 1][0];
				newState[j][1] = newState[j - 1][1];
				newState[j][2] = newState[j - 1][2];
			}
		}
	}
	return newState;
}

bool DFS(map<vector<vector<bool>>, int> stateDist, vector<vector<vector<bool>>> blocks, vector<vector<vector<bool>>> stateSpace, int index)
{
	vector<vector<bool>> state = stateSpace[stateSpace.size() - 1];
	if (state[0][0] == true)
	{
		return false;
	}
	else
	{

	}
}

bool endCheck(vector<vector<vector<bool>>> Space, vector<vector<bool>> state)
{
	if (find(Space.begin(), Space.end(), state) != Space.end())
	{
		return true;
	}
	else
		return false;
}


int main()
{
	vector<int> stateDist;
	vector<vector<vector<bool>>> stateSpace;
	vector<vector<vector<bool>>> blocks;
	string charString;
	cin >> charString;

	for (int i = 0; i < charString.size(); i++)
	{
		vector<vector<bool>> temp = { {false, false, false}, {false, false, false }, {false, false, false} };
		int a = chooseBlock(charString[i]);
		temp = P[a];
		blocks.push_back(temp);
	}
	vector<vector<bool>> startState(10, vector<bool>(3, false)); //= { { false, false, false },{ false, false, false },{ false, false, false },{ false, false, false },{ false, false, false },{ false, false, false },{ false, false, false },{ false, false, false },{ false, false, false },{ false, false, false } };
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 3; j++) {
			startState[i][j] = false;
		}
	}

	//for (int j = 0; j < blocks.size(); j++)
	//{
	//	print(blocks[j]);
	//}
	stateSpace.push_back(startState);


	//cout << stateSpace[0] << endl;
	//cout << blocks[0] << endl;
	//cout << addBlock((bool**)blocks[0], (bool**)stateSpace[0]) << endl;


	bool gameOver = false;
	int index = 0;
	int rounds = 0;
	string check;
	bool cantLose = false;
	vector<vector<vector<bool>>> visited;

	/*vector<vector<bool>> newBlock1 = rotate(blocks[0], 0);
	vector<vector<bool>> newBlock2 = rotate(blocks[0], 1);
	vector<vector<bool>> newBlock3 = rotate(blocks[0], 2);
	vector<vector<bool>> newBlock4 = rotate(blocks[0], 3);
	print(newBlock1);
	print(newBlock2);
	print(newBlock3);
	print(newBlock4);*/

	while (!gameOver && !cantLose)
	{
		vector<vector<bool>> curState(10, vector<bool>(3, false));
		curState = stateSpace[stateSpace.size()-1];
		vector<vector<bool>> block(3, vector<bool>(3, false));
		block = blocks[index];
		vector<vector<bool>> newState = addBlock(block, curState);
		print(newState);
		newState = CheckState(newState);
		print(curState);
		print(newState);
		if (index + 1 >= blocks.size() || index == 19)
			index = 0;
		else
			index++;
		stateSpace.push_back(newState);
		if (newState[0][0] == true)
		{
			gameOver = true;
		}
		else
			rounds++;
	}

	if (cantLose)
		cout << "forever" << endl;
	else
		cout << rounds << endl;

}