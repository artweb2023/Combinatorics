#pragma once

#include "Faces.h"
#include "ReadFromFile.h"
#include "stdafx.h"

class Graph
{
public:
	Graph(const AdjMatrix& matrix);
	Graph(int size);
	std::string toString() const;
	void addEdge(int u, int v);
	bool containsEdge(int u, int v) const;
	Faces* getPlanarLaying();
private:
	bool dfsCycle(std::vector<int>& result, std::vector<int>& used, int parent, int v);
	void dfsSegments(std::vector<int>& used, const std::vector<bool>& laidVertexes, Graph& result, int v);
	std::vector<Graph> getSegments(const std::vector<bool>& laidVertexes, const std::vector<std::vector<bool>>& edges);
	void dfsChain(std::vector<int>& used, std::vector<bool>& laidVertexes, std::vector<int>& chain, int v);
	std::vector<int> getChain(std::vector<bool>& laidVertexes);
	std::vector<int> getCycle();
	static void layChain(std::vector<std::vector<bool>>& result, std::vector<int>& chain, bool cyclic);
	bool isFaceContainsSegment(const std::vector<int>& face, const Graph& segment, const std::vector<bool>& laidVertexes);
	std::vector<int> calcNumOfFacesContainedSegments(const AdjMatrix& intFaces, const std::vector<int>& extFace,
		const std::vector<Graph>& segments, const std::vector<bool>& laidVertexes, AdjMatrix& destFaces);
	AdjMatrix m_matrix;
	int m_size = 0;
};