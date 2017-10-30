#include <iostream>
#include <vector>
#include <map>

#include "graphics.h"
#pragma comment(lib, "graphics.lib")

using namespace std;

void DrawToConsole(int width, int height, int x_top, int y_top, char **buffer)
{
	for (int i = x_top; i < width; i++)
		for (int j = y_top; j < height; j++)
			putpixel(i, j, buffer[i][j]);
}