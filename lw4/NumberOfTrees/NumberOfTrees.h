#pragma once
#include "ReadFromFile.h"


void SetKirgofMatrix(const Matrix& adjacencyMatrix, Matrix& kirgofMatrix);
double CalculateDeterminant(Matrix matrix);
double GetCountTree(const Matrix& kirgofMatrix);
void PrintMatrix(Matrix& matrix);
Matrix GetMinor(const Matrix& kirgofMatrix);