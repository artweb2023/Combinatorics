﻿/*
Алгоритм поднять-в-начало:
	- занести все v э V | {s, t} (кроме исток и сток) в односвязный список
	- пройдемся по списку и выполним DISCHARGE от каждой вершины
		- при этом, если в результате DISCHARGE(v) R(v) увеличилось,
			то поместим v в начало списка и начнем заново
		- если дошли до конца, то завершаем работу

*/
#include "MaxFlowFinder.h"
#include <cassert>

void MaxFlowFinder::InitializePreflow()
{
	height.resize(network->NumberOfVertices());
	overflow.resize(network->NumberOfVertices());
	edgePosition.resize(network->NumberOfVertices());

	height.assign(height.size(), 0);
	height[network->GetFlowSource()] = network->NumberOfVertices();

	overflow.assign(overflow.size(), 0);
	for (VertexNumber vertex = 0; vertex < network->NumberOfVertices(); ++vertex)
	{
		for (EdgeNumber edge : network->EdgesFrom(vertex))
		{
			network->UpdateEdgeFlow(edge, -network->GetEdgeFlow(edge));
		}
	}
	for (EdgeNumber edge : network->EdgesFrom(network->GetFlowSource()))
	{
		network->UpdateEdgeFlow(edge, network->GetEdgeCapacity(edge));
		overflow[network->GetEdgeTarget(edge)] += network->GetEdgeCapacity(edge);
		overflow[network->GetFlowSource()] -= network->GetEdgeCapacity(edge);
	}

	edgePosition.assign(edgePosition.size(), 0);

	list.clear();
	for (VertexNumber vertex = 0; vertex < network->NumberOfVertices(); ++vertex)
	{
		if (vertex != network->GetFlowSource() && vertex != network->GetFlowTarget())
		{
			list.push_back(vertex);
		}
	}
}

void MaxFlowFinder::Push(EdgeNumber edge)
{
	VertexNumber from = network->GetEdgeSource(edge);
	VertexNumber to = network->GetEdgeTarget(edge);

	assert(overflow[from] > 0);
	assert(network->GetEdgeCapacity(edge) - network->GetEdgeFlow(edge));
	assert(height[from] == 1 + height[to]);

	int delta = std::min(network->GetEdgeCapacity(edge) - network->GetEdgeFlow(edge), overflow[from]);
	network->UpdateEdgeFlow(edge, delta);
	overflow[from] -= delta;
	overflow[to] += delta;
}

void MaxFlowFinder::Relabel(VertexNumber vertex)
{
	VertexNumber minimumHeight = height[vertex];

	for (EdgeNumber edge : network->EdgesFrom(vertex))
	{
		if (!(network->GetEdgeCapacity(edge) - network->GetEdgeFlow(edge)))
		{
			continue;
		}
		VertexNumber to = network->GetEdgeTarget(edge);
		assert(height[to] >= height[vertex]);
		minimumHeight = std::min(minimumHeight, height[to]);
	}

	height[vertex] = 1 + minimumHeight;
}

void MaxFlowFinder::Discharge(VertexNumber vertex)
{
	while (overflow[vertex] > 0)
	{
		if (edgePosition[vertex] >= network->EdgesFrom(vertex).size())
		{
			Relabel(vertex);
			edgePosition[vertex] = 0;
			continue;
		}

		EdgeNumber edge = network->EdgesFrom(vertex)[edgePosition[vertex]];
		VertexNumber to = network->GetEdgeTarget(edge);
		if (network->GetEdgeCapacity(edge) - network->GetEdgeFlow(edge)
			&& height[vertex] == 1 + height[to])
		{
			Push(edge);
		}
		else
		{
			++edgePosition[vertex];
		}
	}
}

MaxFlowFinder& MaxFlowFinder::GetInstance()
{
	static MaxFlowFinder instance;
	return instance;
}

int MaxFlowFinder::FindMaximumFlow(Network* network)
{
	this->network = network;

	InitializePreflow();

	auto listIterator = list.begin();
	while (listIterator != list.end())
	{
		VertexNumber vertex = *listIterator;
		VertexNumber previousHeight = height[vertex];

		Discharge(vertex);

		if (height[vertex] > previousHeight)
		{
			list.erase(listIterator);
			list.push_front(vertex);
			listIterator = list.begin();
		}
		else
		{
			++listIterator;
		}
	}

	return -overflow[network->GetFlowSource()];
}

void MaxFlowFinder::PrintMaxFlowAsMatrix()
{
	this->network->PrintEdgesAsMatrix();
}