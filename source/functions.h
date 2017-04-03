#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>
#include <stdlib.h>

void visualizer(std::vector< std::vector<bool> > &fullChartVector, int rows, int keys);

std::vector<int> generateChord(int numberOfNotes, int keys, std::vector<int> &avoid);

void createChart(std::vector< std::vector<bool> > &fullChartVector, int numberOfGenerations, std::vector<int> numberOfNotes, int keys, int anchor_limit);

#endif // !FUNCTIONS_H
