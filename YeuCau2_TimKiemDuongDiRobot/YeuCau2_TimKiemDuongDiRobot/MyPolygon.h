#pragma once
#include <vector>

using namespace std;

class MyPolygon
{
private:
	vector<pair<int, int>> m_Points;
	int m_color;
	int m_zoom;
	void SetLineToBuffer(pair<int, int> point1, pair<int, int> point2, char **buffer);
	void DivineLineToBuffer(pair<int, int> point1, pair<int, int> point2, char **buffer);
public:
	void AddPoint(int x, int y);
	void AddToBuffer(char **buffer);
	void SetColor(int color);
	void SetZoom(int zoom);
	vector<pair<pair<int, int>, pair<int, int>>> getAllLine();
};

