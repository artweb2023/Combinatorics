#include "Network.h"
#include <algorithm>
#include <iostream>

NetworkFlow::NetworkFlow(int vertices)
	: m_size(vertices)
	, m_capacity(vertices, std::vector<int>(vertices, 0))
	, m_flow(vertices, std::vector<int>(vertices, 0))
	, m_height(vertices, 0)
	, m_excess(vertices, 0)
	, m_seen(vertices, 0)
{
}

void NetworkFlow::addEdge(int u, int v, int cap)
{
	m_capacity[u][v] = cap;
}

int NetworkFlow::maxFlow(int source, int sink)
{
	m_height[source] = m_size;
	m_excess[source] = INT_MAX;
	for (int v = 0; v < m_size; ++v)
	{
		if (v != source)
		{
			push(source, v);
		}
	}
	while (!m_excessVertices.empty())
	{
		int u = m_excessVertices.front();
		m_excessVertices.pop();
		if (u != source && u != sink)
		{
			discharge(u);
		}
	}
	int maxflow = 0;
	for (int i = 0; i < m_size; ++i)
	{
		maxflow += m_flow[source][i];
	}
	return maxflow;
}

Matrix NetworkFlow::getFlow() const
{
	return m_flow;
}

void NetworkFlow::PrintNetwork(const Matrix& flow) const
{
	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			if (flow[i][j] > 0)
			{
				std::cout << flow[i][j] << " ";
			}
			else
			{
				std::cout << " - ";
			}
		}
		std::cout << std::endl;
	}
}

// проталкивание потока
void NetworkFlow::push(int u, int v)
{
	int delta = std::min(m_excess[u], m_capacity[u][v] - m_flow[u][v]);
	m_flow[u][v] += delta;
	m_flow[v][u] -= delta;
	m_excess[u] -= delta;
	m_excess[v] += delta;
	if (delta && m_excess[v] > 0 && v != 0 && v != m_size - 1)
	{
		m_excessVertices.push(v);
	}
}

// помечаем вершину
void NetworkFlow::relabel(int u)
{
	int minHeight = INT_MAX;
	for (int v = 0; v < m_size; ++v)
	{
		if (m_capacity[u][v] - m_flow[u][v] > 0)
		{
			minHeight = std::min(minHeight, m_height[v]);
			m_height[u] = minHeight + 1;
		}
	}
}
// разгрузка
void NetworkFlow::discharge(int u)
{
	while (m_excess[u] > 0)
	{
		if (m_seen[u] < m_size)
		{
			int v = m_seen[u];
			if (m_capacity[u][v] - m_flow[u][v] > 0 && m_height[u] > m_height[v])
			{
				push(u, v);
			}
			else
			{
				++m_seen[u];
			}
		}
		else
		{
			relabel(u);
			m_seen[u] = 0;
		}
	}
}
