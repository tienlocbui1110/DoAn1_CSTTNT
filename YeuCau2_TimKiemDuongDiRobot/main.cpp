#include <iostream>
#include <vector>
#include <map>

#include "graphics.h"
#pragma comment(lib, "graphics.lib")

#include "MyPolygon.h"
#include "input.h"
#include "SetupBuffer.h"
#include "Drawing.h"
#include "AStar.h"

#define INPUT_FILE "input.txt"
#define MAX_WIDTH  5000
#define MAX_HEIGHT 5000
#define ZOOM_SCALE 15
#define THICK 3
#define WIN_WIDTH_SIZE 1600
#define WIN_HEIGHT_SIZE 900
#define COLOR GREEN

void SolutionPrintOne(char **buffer, map<pair<int, int>, pair<int, int>> &trace, pair<int, int> startNode, pair<int, int> endNode, vector<MyPolygon> control);
using namespace std;

int main()
{	
	//int gd = DETECT, gm;
	//initgraph(&gd, &gm, "c:\\tc\\bgi");

	//int x1 = 10, y1 = 10;
	//int x2 = 11, y2 = 11;
	//line(x1, y1, x2, y2);
	
	//getch();
	//closegraph();
	int n;
	char **buffer;
	vector<MyPolygon> control;
	pair<int, int> startNode, endNode;
	map<pair<int, int>, pair<int, int>> trace;
	bool check = Input(INPUT_FILE,ZOOM_SCALE, n, startNode, endNode, control);
	if (check == false)
	{
		cout << "LOI FILE\n";
		getch();
		return 0;
	}
	// xu li
	createBuffer(MAX_WIDTH/ZOOM_SCALE, MAX_HEIGHT/ZOOM_SCALE, buffer);
	SetColorPolygon(COLOR, control);
	SetupBuffer(buffer, control);
	trace[endNode] = pair<int, int>(-1, -1);
	// Find path with A*
	AStarBFS(buffer, MAX_WIDTH / ZOOM_SCALE, MAX_HEIGHT / ZOOM_SCALE, startNode, endNode, trace);
	SolutionPrintOne(buffer, trace, startNode,endNode, control);
	getch();
	delete[] buffer;
	return 0;
}

void DrawMyLine(pair<int, int> point1, pair<int, int>point2, const int zoom)
{
	line(point1.first*zoom, point1.second*zoom, point2.first*zoom, point2.second*zoom);
}

void DrawNode(pair<int, int> point, const int zoom)
{
	pair<int, int> tmp1 = point;
	pair<int, int> tmp2 = point;
	tmp1.first -= 1; tmp1.second -= 1; tmp2.first += 1; tmp2.second -= 1;
	DrawMyLine(tmp1, tmp2, zoom);
	tmp1 = tmp2; tmp2.second += 2;
	DrawMyLine(tmp1, tmp2, zoom);
	tmp1 = tmp2; tmp2.first -= 2;
	DrawMyLine(tmp1, tmp2, zoom);
	tmp1 = tmp2; tmp2.second -= 2;
	DrawMyLine(tmp1, tmp2, zoom);
 }

void DrawAllPoly(vector<MyPolygon> control)
{
	for (int i = 0; i < control.size(); i++)
	{
		vector<pair<pair<int, int>, pair<int, int>>> allLine = control[i].getAllLine();
		for (int j = 0; j < allLine.size(); j++)
		{
			DrawMyLine(allLine[j].first, allLine[j].second, ZOOM_SCALE);
		}
	}
}

void DrawTemplate(pair<int, int> startNode, pair<int, int> endNode, vector<MyPolygon> control)
{
	setcolor(WHITE);
	DrawNode(startNode, ZOOM_SCALE);
	setcolor(YELLOW);
	DrawNode(endNode, ZOOM_SCALE);
	setcolor(GREEN);
	DrawAllPoly(control);
}

void SolutionPrintOne(char **buffer, map<pair<int, int>, pair<int, int>> &trace, pair<int,int> startNode, pair<int,int> endNode, vector<MyPolygon> control)
{
	initwindow(WIN_WIDTH_SIZE, WIN_HEIGHT_SIZE);
	cout << "Dang ve hinh hoc...";
	// set line style
	setlinestyle(SOLID_LINE, 1, THICK);
	//DrawToConsole(MAX_WIDTH / ZOOM_SCALE, MAX_HEIGHT / ZOOM_SCALE, 0, 0, buffer);
	// Ve bang ham co san
	DrawTemplate(startNode, endNode, control);
	// Ve diem dau va diem cuoi
		
	//	DrawMyLine(, ZOOM_SCALE);
	
	cout << "\nDa ve xong. Bat dau tim duong di...";
	// In Duong di
	// 
	int PathColor = RED;
	vector<pair<int, int>> goGoGo;
	if (trace[endNode] == pair<int, int>(-1, -1))
	{
		cout << "\nKhong tim duoc duong di.";
		return;
	}
	if (endNode == startNode)
		return;
	pair<int, int> endNodeTemp = endNode;
	while (endNodeTemp != startNode)
	{
		goGoGo.push_back(endNodeTemp);
		endNodeTemp = trace[endNodeTemp];
	}
	goGoGo.push_back(startNode);

	reverse(goGoGo.begin(), goGoGo.end());

	vector<pair<int, int>>::iterator it = goGoGo.begin();

	// set color
	setcolor(RED);
	while (it + 1  != goGoGo.end())
	{
		// Xu li ve
		vector<pair<int, int>>::iterator next = it + 1;
		DrawMyLine((*it), (*next), ZOOM_SCALE);
		
		delay(100);
		it++;
	}

	cout << "\n Da den dich.";
}
