#pragma once
#include <queue>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

class NetworkFlow
{
public:
	NetworkFlow(int vertices);
	void addEdge(int u, int v, int cap);
	int maxFlow(int source, int sink);
	Matrix getFlow() const;
	void PrintNetwork(const Matrix& flow) const;
private:
	void push(int u, int v);
	void relabel(int u);
	void discharge(int u);
	int m_size;
	Matrix m_capacity;
	Matrix m_flow;
	std::vector<int> m_height;
	std::vector<int> m_excess;
	std::vector<int> m_seen;
	std::queue<int> m_excessVertices;
};