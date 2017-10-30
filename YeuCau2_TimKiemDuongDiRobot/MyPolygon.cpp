#include <iostream>
#include <vector>
#include <map>
#include "MyPolygon.h"
#include <math.h>

using namespace std;

void MyPolygon::AddPoint(int x, int y)
{
	pair<int, int> tmp;
	tmp.first = x; 
	tmp.second = y;
	m_Points.push_back(tmp);
}

void MyPolygon::AddToBuffer(char **buffer)
{
	for (int i = 0; i < m_Points.size() - 1; i++)
		SetLineToBuffer(m_Points[i], m_Points[i + 1],buffer);

	SetLineToBuffer(m_Points[0], m_Points[m_Points.size()-1], buffer);

}

void MyPolygon::SetLineToBuffer(pair<int,int> point1, pair<int,int> point2, char **buffer)
{
	DivineLineToBuffer(point1, point2, buffer);
}

void MyPolygon::DivineLineToBuffer(pair<int, int> point1, pair<int, int> point2, char **buffer)
{
	if ((point1.first == point2.first) && (point1.second == point2.second))
	{
		buffer[point1.first][point1.second] = m_color;
	}
	else
	{
		pair<int, int> tmp1, tmp2;
		int addX, addY;
		addX = (abs(point1.first - point2.first)) % 2;
		addY = (abs(point1.second - point2.second)) % 2;
		if (point1.first < point2.first)
		{
			tmp1.first = (point1.first + point2.first) / 2;
			tmp2.first = tmp1.first + addX;
		}
		else
		{
			tmp2.first = (point1.first + point2.first) / 2;
			tmp1.first = tmp2.first + addX;
		}

		if (point1.second < point2.second)
		{
			tmp1.second = (point1.second + point2.second) / 2;
			tmp2.second = tmp1.second + addY;
		}
		else
		{
			tmp2.second = (point1.second + point2.second) / 2;
			tmp1.second = tmp2.second + addY;
		}
		

		
		
		DivineLineToBuffer(point1, tmp1, buffer);
		DivineLineToBuffer(tmp2, point2, buffer);
	}
}

void MyPolygon::SetColor(int color)
{
	m_color = color;
}

void MyPolygon::SetZoom(int zoom)
{
	m_zoom = zoom;
}

vector<pair<pair<int,int>, pair<int,int>>> MyPolygon::getAllLine()
{
	vector<pair<pair<int, int>, pair<int, int>>> result;
	
	for (int i = 0; i < m_Points.size() - 1; i++)
	{
		pair<pair<int, int>, pair<int, int>> tmp(m_Points[i], m_Points[i + 1]);
		result.push_back(tmp);
	}
	pair<pair<int, int>, pair<int, int>> tmp(m_Points[m_Points.size() - 1], m_Points[0]);
	result.push_back(tmp);
	return result;
}