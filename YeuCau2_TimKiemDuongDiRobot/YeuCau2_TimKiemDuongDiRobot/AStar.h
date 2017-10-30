#pragma once

void AStarBFS(char **buffer, const int MAX_WIDTH, const int MAX_HEIGHT, pair<int, int> startNode, pair<int, int> endNode, map<pair<int, int>, pair<int, int>> &trace);