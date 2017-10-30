#pragma once

using namespace std;

bool Input(const char* INPUT_FILE, const int ZOOM, int &n, pair<int, int> &startNode, pair<int, int> &endNode, vector<MyPolygon> &control);
void createBuffer(const int width, const int height, char **&buffer);

void SetColorPolygon(const int COLOR, vector<MyPolygon> &control);