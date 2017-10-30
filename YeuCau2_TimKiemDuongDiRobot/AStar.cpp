#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <ctime>

#define BREAK 10

using namespace std;

float CaculateDistance(int x1, int y1, int x2, int y2);
void AddNodeToOpenList(vector<pair<pair<int, int>, float>> &openList, int x, int y, float f);
vector<pair<pair<int, int>, float>>::iterator findMinF(vector<pair<pair<int, int>, float>> &openList, pair<int, int> &presentNode);
void InitializeExpand(pair<int, int> expand[], pair<int, int> presentNode);
bool checkConditionExpand(pair<int, int> &futureNode, const int MAX_WIDTH, const int MAX_HEIGHT, char **buffer, int positionOfExpand);
float CaculateDistance(pair<int, int> point1, pair<int, int> point2);

void AStarBFS(char **buffer, const int MAX_WIDTH, const int MAX_HEIGHT, pair<int,int> startNode, pair<int,int> endNode, map<pair<int, int>, pair<int, int>> &trace)
{
	clock_t startTime = clock();
	clock_t timePassed;
	clock_t testTime;
	double secondsPassed;
	int dem = 0;

	vector<pair<pair<int, int>,float>> openList;
	vector <pair<int, int>> storageOpenNode;
	map<pair<int, int>, float> goneDistance;
	map<pair<int, int>, bool> isMarked;

	// push start node to open list and goneDistance 
	AddNodeToOpenList(openList, startNode.first, startNode.second, 0.0);
	storageOpenNode.push_back(startNode);
	while (!openList.empty())
	{
		// TIMER
		testTime = clock();
		timePassed = testTime - startTime;
		secondsPassed = timePassed / (double)CLOCKS_PER_SEC;
		if (secondsPassed - dem > 1)
		{
			dem++;
			cout << "Time remaining: " << BREAK - dem << endl;
		}
		if (dem == BREAK)
			return;

		//declare
		pair<int, int> presentNode;
		vector<pair<pair<int, int>, float>>::iterator position;

		// Find min f = g(x) + h(x)
		position = findMinF(openList, presentNode);

		// Pop minF from openList
		openList.erase(position);
		isMarked[presentNode] = true;
		if (presentNode == endNode)
			return;
		// Declare 8 position to expand
		pair<int, int> expand[8];
		InitializeExpand(expand, presentNode);
		// check condition for each one
		for (int i = 0; i < 8; i++)
		{
			if (checkConditionExpand(expand[i], MAX_WIDTH, MAX_HEIGHT, buffer, i) && !isMarked[expand[i]])
			{
				// Chua mo node
				if (find(storageOpenNode.begin(), storageOpenNode.end(), expand[i]) == storageOpenNode.end())
				{
					// save
					storageOpenNode.push_back(expand[i]);
					// 
					pair<pair<int, int>, float > tmp;
					tmp.first = expand[i];
					goneDistance[expand[i]] = goneDistance[presentNode] + CaculateDistance(presentNode, expand[i]);
					tmp.second = goneDistance[expand[i]] + CaculateDistance(expand[i], endNode);
					openList.push_back(tmp);
					trace[expand[i]] = presentNode;
				}
				else // Da mo node
				{
					// Tim node da mo
					for (vector<pair<pair<int, int>, float>>::iterator it = openList.begin(); it != openList.end(); it++)
					{
						if ((*it).first == expand[i])
						{
							float distanceTmp = goneDistance[presentNode] + CaculateDistance(presentNode, expand[i]);
							float fAStarTmp = distanceTmp + CaculateDistance(expand[i], endNode);
							if ((*it).second > fAStarTmp)
							{
								(*it).second = fAStarTmp;
								goneDistance[expand[i]] = distanceTmp;
								trace[expand[i]] = presentNode;
							}
						}
					}
				}
			}
		}
	}
}

bool checkConditionExpand(pair<int, int> &futureNode, const int MAX_WIDTH, const int MAX_HEIGHT, char **buffer, int positionOfExpand)
{
	// out of size
	if (futureNode.first < 0 || futureNode.second < 0 || futureNode.first >= MAX_WIDTH || futureNode.second >= MAX_HEIGHT)
		return false;
	if (buffer[futureNode.first][futureNode.second] > 0)
		return false;
	// check position
	if (positionOfExpand == 0 && (buffer[futureNode.first][futureNode.second + 1] > 0 && buffer[futureNode.first + 1][futureNode.second] > 0))
		return false;
	if (positionOfExpand == 2 && (buffer[futureNode.first-1][futureNode.second] > 0 && buffer[futureNode.first][futureNode.second + 1] > 0))
		return false;
	if (positionOfExpand == 5 && (buffer[futureNode.first][futureNode.second - 1] > 0 && buffer[futureNode.first + 1][futureNode.second]> 0))
		return false;
	if (positionOfExpand == 7 && (buffer[futureNode.first][futureNode.second - 1] > 0 && buffer[futureNode.first - 1][futureNode.second] > 0))
		return false;
	return true;
}

void InitializeExpand(pair<int, int> expand[], pair<int, int> presentNode)
{
	expand[0].first = presentNode.first - 1; expand[0].second = presentNode.second - 1;
	expand[1].first = presentNode.first; expand[1].second = presentNode.second - 1;
	expand[2].first = presentNode.first + 1; expand[2].second = presentNode.second - 1;
	expand[3].first = presentNode.first - 1; expand[3].second = presentNode.second;
	expand[4].first = presentNode.first + 1; expand[4].second = presentNode.second;
	expand[5].first = presentNode.first - 1; expand[5].second = presentNode.second + 1;
	expand[6].first = presentNode.first; expand[6].second = presentNode.second + 1;
	expand[7].first = presentNode.first + 1; expand[7].second = presentNode.second + 1;
}

void AddNodeToOpenList(vector<pair<pair<int, int>, float>> &openList, int x, int y, float f)
{
	pair<pair<int, int>, float> tmpBeginOL;
	tmpBeginOL.first.first = x;
	tmpBeginOL.first.second = y;
	tmpBeginOL.second = f;
	openList.push_back(tmpBeginOL);
}

vector<pair<pair<int, int>, float>>::iterator findMinF(vector<pair<pair<int, int>, float>> &openList, pair<int, int> &presentNode)
{
	vector<pair<pair<int, int>, float>>::iterator result;
	float minF = 999999999;
	for (vector<pair<pair<int, int>, float>>::iterator it = openList.begin(); it != openList.end(); it++)
	{
		if ((*it).second < minF)
		{
			result = it;
			minF = (*it).second;
		}
	}

	// result
	presentNode = (*result).first;
	return result;
}

float CaculateDistance(int x1, int y1, int x2, int y2)
{
	int tmp1 = (x1 - x2)*(x1 - x2);
	int tmp2 = (y1 - y2)*(y1 - y2);
	return sqrt((float)(tmp1 + tmp2));
}

float CaculateDistance(pair<int,int> point1, pair<int,int> point2)
{
	int tmp1 = (point1.first - point2.first)*(point1.first - point2.first);
	int tmp2 = (point1.second - point2.second)*(point1.second - point2.second);
	return sqrt((float)(tmp1 + tmp2));
}