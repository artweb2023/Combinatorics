#include "NumberOfTrees.h"

void SetKirgofMatrix(const Matrix& adjacencyMatrix, Matrix& kirgofMatrix)
{
	int size = static_cast<int>(adjacencyMatrix.size());
	kirgofMatrix = Matrix(size, std::vector<double>(size, 0));

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (adjacencyMatrix[i][j] != 0)
			{
				kirgofMatrix[i][j] = -adjacencyMatrix[i][j];
				kirgofMatrix[i][i] += adjacencyMatrix[i][j];
			}
		}
	}
}

void PrintMatrix(const Matrix& matrix)
{
	for (const auto& mat : matrix)
	{
		for (const auto& m : mat)
		{
			std::cout << m << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Matrix GetMinor(const Matrix& kirgofMatrix)
{
	int size = static_cast<int>(kirgofMatrix.size());
	Matrix minor(size - 1, std::vector<double>(size - 1));
	for (int i = 1; i < size; ++i)
	{
		for (int j = 1; j < size; ++j)
		{
			minor[i - 1][j - 1] = kirgofMatrix[i][j];
		}
	}
	return minor;
}

double CalculateDeterminant(Matrix matrix)
{
	int n = static_cast<int>(matrix.size());
	double det = 1.0;

	for (int i = 0; i < n; ++i)
	{
		int maxElemRow = i;
		for (int k = i + 1; k < n; ++k)
		{
			if (std::abs(matrix[k][i]) > std::abs(matrix[maxElemRow][i]))
			{
				maxElemRow = k;
			}
		}
		if (matrix[maxElemRow][i] == 0)
		{
			return 0;
		}
		if (i != maxElemRow)
		{
			std::swap(matrix[i], matrix[maxElemRow]);
			det = -det;
		}
		det *= matrix[i][i];
		for (int k = i + 1; k < n; ++k)
		{
			double factor = matrix[k][i] / matrix[i][i];
			for (int j = i; j < n; ++j)
			{
				matrix[k][j] -= factor * matrix[i][j];
			}
		}
	}
	return det;
}

double GetCountTree(const Matrix& kirgofMatrix)
{
	Matrix minor = GetMinor(kirgofMatrix);
	return std::abs(CalculateDeterminant(minor));
}