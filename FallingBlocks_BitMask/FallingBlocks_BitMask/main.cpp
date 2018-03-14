#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h> 

using namespace std;
unsigned long Tblock = 0x1D2;
unsigned long Xblock = 0x0BA;
unsigned long Rblock = 0x0F2;
unsigned long Sblock = 0x0D6;
unsigned long Zblock = 0x193;
unsigned long Vblock = 0x127;
unsigned long SEVblock = 0x19A;
unsigned long Wblock = 0x133;
unsigned long beginState = 0x000;
unsigned long death = 0x200000;
int maxDepth = 0;
vector<vector<unsigned long>> maxVisitation;

vector<vector<unsigned long>> blocks = { { 0x1D2,4 },{ 0x0BA,1 },{ 0x0F2,4 },{ 0x0D6,2 },{ 0x193,2 },{ 0x127,4 },{ 0x19A,4 },{ 0x133,4 } };
vector<vector<unsigned long>> blockList;

int chooseBlock(char c)
{
	if (c == 'T')
	{
		return 0;
	}
	else if (c == 'X')
	{
		return 1;
	}
	else if (c == 'R')
	{
		return 2;
	}
	else if (c == 'S')
	{
		return 3;
	}
	else if (c == 'Z')
	{
		return 4;
	}
	else if (c == 'V')
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

void Print(unsigned long block, int h) {
	for (int i = h-1; i >= 0; i--) {
		for (int j = 2; j >= 0; j--) {
			unsigned long checkD = pow((int)2, (int)j);
			unsigned long bit = ((block >> (3 * i)) & checkD) >> j;
			cout << bit;
		}
		//unsigned long bit1 = ((Tblock>>(3 * i)) & 1);
		//unsigned long bit2 = ((Tblock >> (3 * i)) & 2)>>1;
		//unsigned long bit3 = ((Tblock >> (3 * i)) & 4) >> 2;
		//cout << bit1 << bit2 << bit3 << endl;
		//unsigned long checkD = i*2;
		//unsigned long bit = ((Tblock) & checkD);
		cout << endl;
	}
	cout << endl;
}

unsigned long addBlock(unsigned long block, unsigned long state) {
	unsigned long nexState = 0x000;
	for (int i = 7; i >= 0; i--) {
		unsigned long nState = state + (block << (3 * i));
		unsigned long checkBlock = ((nState >> (3 * i))&block);
		if (checkBlock == block) {
			nexState = nState;
		}
		else {
			break;
		}

	}
	//Print(nexState, 10);
	return(nexState);
}

unsigned long clearRows(unsigned long state) {
	unsigned long line = 0x7;
	unsigned long clrState = state;
	for (int i = 9; i >= 0; i--) {
		unsigned long checkBlock = ((clrState >> (3 * i))&line);
		if (checkBlock == line) {
			unsigned long upwards = clrState >> (3 * (i + 1));
			clrState = (clrState ^ (upwards << (3 * (i + 1))));
			clrState = (clrState ^ (line << (3 * i)));
			clrState = clrState + (upwards << (3 * i));
		}
		//Print(clrState, 10);
		//cout << endl;
	}
	return clrState;
}

unsigned long rotate(unsigned long block, int r) {
	for (int i = 0; i < r; i++) {
		unsigned long rblock = 0x000;
		rblock += (block&(0x084)) >> 2;
		rblock += (block&(0x042)) << 2;
		rblock += (block&(0x020)) >> 4;
		rblock += (block&(0x008)) << 4;
		rblock += (block&(0x100)) >> 6;
		rblock += (block&(0x001)) << 6;
		rblock += (block&(0x010));
		block = rblock;
	}
	return block;

}

unsigned long dfs(int depth, int pos, unsigned long state, vector<vector<unsigned long>> visited) {
	unsigned long answer;
	//unsigned long answer1;
	//unsigned long answer2;
	//unsigned long answer3;
	//unsigned long answer4;
	if (state >= death) {
		if ((depth > maxDepth) && (maxDepth != -1)) {//checks if it is not forever and we have found a depth further than before
			if (maxDepth != -1) {
				maxDepth = depth;
				maxVisitation = visited;

				//cout << maxDepth << endl;
			}
		}
		return death;
	}
	int nexPos;
	if (pos == (blockList.size() - 1)) {
		/*if (find(visited.begin(), visited.end(), state) != visited.end()) {//checks if state has been visited (checks for cycle)
			maxDepth = -1;
			return death;
		}
		else {*/
		nexPos = 0;

		//}
	}
	else {
		nexPos = pos + 1;
	}
	for (int i = 0; i < blockList[pos][1]; i++) {
		//cout << "Depth is: " << depth <<endl;
		//Print(state, 10);
		unsigned long nexBlock = rotate(blockList[pos][0], i);
		//cout << "Rotate is: " << i << endl;
		//Print(nexBlock, 3);
		unsigned long nexState = clearRows(addBlock(nexBlock, state));
		vector<unsigned long> curVis = { nexState,(unsigned long)pos };
		if ((find(visited.begin(), visited.end(), curVis) != visited.end()) || maxDepth == -1) {//checks if state has been visited (checks for cycle)
			if (maxDepth != -1) {
				maxVisitation = visited;
				maxVisitation.push_back(curVis);
			}
			maxDepth = -1;
			return death;
		}
		else {
			visited.push_back(curVis);
		}

		answer = dfs(depth + 1, nexPos, nexState, visited);
		visited.pop_back();
	}
	return answer;
}

int main()
{

	vector<vector<unsigned long>> stateSpace;
	string charString;
	cin >> charString;

	for (int i = 0; i < charString.size(); i++)
	{
		int a = chooseBlock(charString[i]);
		vector<unsigned long> temp = blocks[a];
		blockList.push_back(temp);
	}

	vector<unsigned long> beginer = { beginState,21 };
	stateSpace.push_back(beginer);
	/*
	unsigned long fstate;
	if (blockList.size() == 1) {
		for (int i = 0; i < blockList[0][1]; i++)
			fstate = dfs(1, 0, clearRows(rotate(blockList[0][0], i)), stateSpace);
	}
	else {
		for (int i = 0; i < blockList[0][1]; i++)
			fstate = dfs(1, 1, clearRows(rotate(blockList[0][0], i)), stateSpace);
	}

	cout << maxDepth << endl;

	for (int i = 0; i < maxVisitation.size(); i++){
		cout << "Added Block: "<< (int)maxVisitation[i][1]<<endl;
		if (i == 0) {
			Print(0x000, 3);
		}
		else {
			Print(blockList[(int)maxVisitation[i][1]][0], 3);
		}
		Print(maxVisitation[i][0], 10);

	}

	*/
	unsigned int state = 0x000;
	while (true) {
		cout << "Current State" << endl;
		Print(state, 10);
		cout << "Which Block would you like to place? ";
		char input;
		cin>>input;
		cout << endl << "How many times would you like to rotate that block?(0,1,2,3) ";
		unsigned long r;
		cin >> r;
		state = addBlock(rotate(blocks[chooseBlock(input)][0],r), state);
		cout << "Placed" << endl;
		Print(state, 10);
		cout << endl;
		state = clearRows(state);
		
		cout << endl;
		
		if (state > 0x1FFFFF) {
			  cout << "Game Over";
			  break;
		}
	}/**/



	//for (int i = 0; i < 8; i++) {
	//	for (int j = 0; j < blocks[i][1]; j++) {
	//		Print(rotate(blocks[i][0], j), 3);
	//		cout << endl;
	//	}
	//	cout << endl << endl;
	//}
	//Print(line, 2);
	/*unsigned long state = addBlock(blocks[4], blocks[5]);
	

	Print(state, 10);
	cout << endl;
	state = clearRows(state);
	Print(state,10);
	state = addBlock(0x1c9, state);
	cout << endl;
	Print(state, 10);
	cout << endl;
	state = clearRows(state);
	Print(state, 10);*/

	
	
	
	//Print(Tblock, 10);
	
	//cout << bit << endl;
}