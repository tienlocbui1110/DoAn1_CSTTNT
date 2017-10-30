#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "MyPolygon.h"
using namespace std;

bool Input(const char* INPUT_FILE, const int ZOOM,int &n, pair<int,int> &startNode, pair<int,int> &endNode, vector<MyPolygon> &control)
{
	// CAU TRUC
	// Dong dau tien : n -> so da giac 
	// Dong thu 2 : 4 chu so, tuong ung voi x_start, y_start, x_end, y_end
	// n dong tiep theo, moi dong la thong tin cua da giac
	//  + Cot dau tien : m -> Chi ra so diem cua da giac
	//  + Cac cot tiep theo, moi cot lan luot la toa do Xi , Yi cua tung diem theo thu tu de tao thanh da giac
	ifstream inp;
	inp.open(INPUT_FILE, ifstream::in);
	if (!inp.is_open())
		return false;
	// Xu li
	inp >> n;
	inp >> startNode.first >> startNode.second >> endNode.first >> endNode.second;
	for (int i = 0; i < n; i++)
	{
		MyPolygon p;
		int m;
		inp >> m;
		for (int j = 0; j < m; j++)
		{
			int tmpX, tmpY;
			inp >> tmpX >> tmpY;
			p.AddPoint(tmpX, tmpY);
		}
		control.push_back(p);
	}
	inp.close();
	return true;
}

void createBuffer(const int width, const int height, char **&buffer)
{
	buffer = new char*[height];

	for (int i = 0; i < height; i++)
		buffer[i] = new char[width];

	// set all to 0

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			buffer[i][j] = 0;
}

void SetColorPolygon(const int COLOR, vector<MyPolygon> &control)
{
	for (int i = 0; i < control.size(); i++)
		control[i].SetColor(COLOR);
}