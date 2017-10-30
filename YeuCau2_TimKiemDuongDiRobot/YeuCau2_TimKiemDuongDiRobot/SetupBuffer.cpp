#include <vector>
#include <map>

#include "MyPolygon.h"

using namespace std;

void SetupBuffer(char **buffer, vector<MyPolygon> &control)
{
	for (int i = 0; i < control.size(); i++)
		control[i].AddToBuffer(buffer);
}