#include "Graph.h"

Graph::Graph(const AdjMatrix& matrix)
	:m_matrix(matrix)
	, m_size(static_cast<int>(matrix.size()))
{
}

Graph::Graph(int size)
	:m_size(size)
	, m_matrix(size, std::vector<int>(size, 0))
{
}

std::string Graph::toString() const
{
	std::string result;
	for (int i = 0; i < m_size; ++i)
	{
		for (int j = i + 1; j < m_size; ++j)
		{
			if (m_matrix[i][j] == 1)
			{
				result += std::to_string(i) + " ---> " + std::to_string(j) + "\n";
			}
		}
	}
	return result;
}

void Graph::addEdge(int u, int v)
{
	m_matrix[u][v] = 1;
	m_matrix[v][u] = 1;
}

bool Graph::containsEdge(int u, int v) const
{
	return m_matrix[u][v] == 1;
}


bool Graph::dfsCycle(std::vector<int>& result, std::vector<int>& used, int parent, int v)
{
	used[v] = 1;
	for (int i = 0; i < m_size; ++i)
	{
		if (i == parent || m_matrix[v][i] == 0)
		{
			continue;
		}
		if (used[i] == 0)
		{
			result.push_back(v);
			if (dfsCycle(result, used, v, i))
			{
				return true;
			}
			else
			{
				result.pop_back();
			}
		}
		else if (used[i] == 1)
		{
			result.push_back(v);
			std::vector<int> cycle;
			for (size_t j = 0; j < result.size(); ++j)
			{
				if (result[j] == i)
				{
					cycle.insert(cycle.end(), result.begin() + j, result.end());
					result = cycle;
					return true;
				}
			}
			return true;
		}
	}
	used[v] = 2;
	return false;
}

std::vector<int> Graph::getCycle()
{
	std::vector<int> cycle;
	std::vector<int> used(m_size, 0);
	if (dfsCycle(cycle, used, -1, 0))
	{
		return cycle;
	}
	else
	{
		return std::vector<int>();
	}
}

/*
	Поиск связных компонент графа G - G', дополненного ребрами из G,
	один из концов которых принадлежит связной компоненте, а другой G'
 */
void Graph::dfsSegments(std::vector<int>& used, const std::vector<bool>& laidVertexes, Graph& result, int v)
{
	used[v] = 1;
	for (int i = 0; i < m_size; ++i)
	{
		if (m_matrix[v][i] == 1)
		{
			result.addEdge(v, i);
			if (used[i] == 0 && !laidVertexes[i])
			{
				dfsSegments(used, laidVertexes, result, i);
			}
		}
	}
}

std::vector<Graph> Graph::getSegments(const std::vector<bool>& laidVertexes, const std::vector<std::vector<bool>>& edges)
{
	std::vector<Graph> segments;
	for (int i = 0; i < m_size; ++i)
	{
		for (int j = i + 1; j < m_size; ++j)
		{
			if (m_matrix[i][j] == 1 && !edges[i][j] && laidVertexes[i] && laidVertexes[j])
			{
				Graph t(m_size);
				t.addEdge(i, j);
				segments.push_back(t);
			}
		}
	}
	std::vector<int> used(m_size, 0);
	for (int i = 0; i < m_size; ++i)
	{
		if (used[i] == 0 && !laidVertexes[i])
		{
			Graph res(m_size);
			dfsSegments(used, laidVertexes, res, i);
			segments.push_back(res);
		}
	}
	return segments;
}

void Graph::dfsChain(std::vector<int>& used, std::vector<bool>& laidVertexes, std::vector<int>& chain, int v)
{
	used[v] = 1;
	chain.push_back(v);
	for (int i = 0; i < m_size; i++)
	{
		if (m_matrix[v][i] == 1 && used[i] == 0)
		{
			if (!laidVertexes[i])
			{
				dfsChain(used, laidVertexes, chain, i);
			}
			else
			{
				chain.push_back(i);
			}
			return;
		}
	}
}

std::vector<int> Graph::getChain(std::vector<bool>& laidVertexes)
{
	std::vector<int> result;
	std::vector<int> used(m_size, 0);
	for (int i = 0; i < m_size; i++)
	{
		if (laidVertexes[i])
		{
			bool inGraph = false;
			for (int j = 0; j < m_size; j++)
			{
				if (containsEdge(i, j))
					inGraph = true;
			}
			if (inGraph)
			{
				dfsChain(used, laidVertexes, result, i);
				break;
			}
		}
	}
	return result;
}

//Укладка цепи, описание матрицы смежности
void Graph::layChain(std::vector<std::vector<bool>>& result, std::vector<int>& chain, bool cyclic)
{
	for (int i = 0; i < chain.size() - 1; i++)
	{
		result[chain[i]][chain[i + 1]] = true;
		result[chain[i + 1]][chain[i]] = true;
	}
	if (cyclic)
	{
		result[chain[0]][chain[chain.size() - 1]] = true;
		result[chain[chain.size() - 1]][chain[0]] = true;
	}
}

//Проверка на то, что данный сегмент содержится в данной грани
bool Graph::isFaceContainsSegment(const std::vector<int>& face, const Graph& segment, const std::vector<bool>& laidVertexes)
{
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			if (segment.containsEdge(i, j))
			{
				if ((laidVertexes[i] && std::find(face.begin(), face.end(), i) == face.end()) ||
					(laidVertexes[j] && std::find(face.begin(), face.end(), j) == face.end()))
				{
					return false;
				}
			}
		}
	}
	return true;
}

//Считаем число граней, вмещающих данные сегмент
std::vector<int> Graph::calcNumOfFacesContainedSegments(
	const AdjMatrix& intFaces,
	const std::vector<int>& extFace,
	const std::vector<Graph>& segments,
	const std::vector<bool>& laidVertexes,
	AdjMatrix& destFaces)
{
	std::vector<int> count(segments.size(), 0);
	destFaces.resize(segments.size());
	for (size_t i = 0; i < segments.size(); i++)
	{
		for (const auto& face : intFaces)
		{
			if (isFaceContainsSegment(face, segments[i], laidVertexes))
			{
				destFaces[i] = face;
				count[i]++;
			}
		}
		if (isFaceContainsSegment(extFace, segments[i], laidVertexes))
		{
			destFaces[i] = extFace;
			count[i]++;
		}
	}
	return count;
}

Faces* Graph::getPlanarLaying()
{
	// Если граф одновершинный, то возвращаем две грани
	if (m_size == 1)
	{
		std::vector<std::vector<int>> faces;
		std::vector<int> outerFace = { 0 };
		faces.push_back(outerFace);
		faces.push_back(outerFace);
		return new Faces(faces, outerFace);
	}
	// Ищем цикл, если его нет, то граф не соответствует условиям алгоритма
	std::vector<int> cycle = getCycle();
	if (cycle.empty())
	{
		return nullptr;
	}
	// Списки граней
	std::vector<std::vector<int>> intFaces;
	std::vector<int> extFace = cycle;
	intFaces.push_back(cycle);
	intFaces.push_back(extFace);
	// Массивы уже уложенных вершин и рёбер соответственно
	std::vector<bool> laidVertexes(m_size, false);
	std::vector<std::vector<bool>> laidEdges(m_size, std::vector<bool>(m_size, false));
	for (int i : cycle)
	{
		laidVertexes[i] = true;
	}
	// Укладываем найденный цикл
	layChain(laidEdges, cycle, true);
	// Второй шаг алгоритма
	while (true)
	{
		std::vector<Graph> segments = getSegments(laidVertexes, laidEdges);
		// Если нет сегментов, то граф - найденный простой цикл => планарный
		if (segments.empty())
		{
			break;
		}
		// Массив граней, в которые будут уложены соответствующие сегменты
		AdjMatrix destFaces(segments.size());
		std::vector<int> count = calcNumOfFacesContainedSegments(intFaces, extFace, segments, laidVertexes, destFaces);
		int mi = 0;
		for (size_t i = 1; i < segments.size(); ++i)
		{
			if (count[i] < count[mi])
			{
				mi = static_cast<int>(i);
			}
		}
		// Если существует сегмент 𝑆, для которого |G(𝑆)|=0, то граф не планарный, конец;
		if (count[mi] == 0)
		{
			return nullptr;
		}
		else
		{
			// Укладка выбранного сегмента
			std::vector<int> chain = segments[mi].getChain(laidVertexes);
			// Помечаем вершины цепи как уложенные
			for (int i : chain)
			{
				laidVertexes[i] = true;
			}
			// Укладываем соответствующие рёбра цепи
			layChain(laidEdges, chain, false);
			// Целевая грань, куда будет уложен выбранный сегмент
			std::vector<int> face = destFaces[mi];
			// Новые грани, порожденные разбиением грани face выбранным сегментом
			std::vector<int> face1, face2;
			// Ищем номера контактных вершин цепи
			int contactFirst = 0, contactSecond = 0;
			for (size_t i = 0; i < face.size(); ++i)
			{
				if (face[i] == chain[0])
				{
					contactFirst = static_cast<int>(i);
				}
				if (face[i] == chain.back())
				{
					contactSecond = static_cast<int>(i);
				}
			}
			// Находим обратную цепь
			std::vector<int> reverseChain = chain;
			std::reverse(reverseChain.begin(), reverseChain.end());
			size_t faceSize = face.size();
			if (face != extFace)
			{  // Если целевая грань не внешняя
				if (contactFirst < contactSecond)
				{
					face1.insert(face1.end(), chain.begin(), chain.end());
					for (size_t i = (contactSecond + 1) % faceSize; i != contactFirst; i = (i + 1) % faceSize)
					{
						face1.push_back(face[i]);
					}
					face2.insert(face2.end(), reverseChain.begin(), reverseChain.end());
					for (size_t i = (contactFirst + 1) % faceSize; i != contactSecond; i = (i + 1) % faceSize)
					{
						face2.push_back(face[i]);
					}
				}
				else
				{
					face1.insert(face1.end(), reverseChain.begin(), reverseChain.end());
					for (size_t i = (contactFirst + 1) % faceSize; i != contactSecond; i = (i + 1) % faceSize)
					{
						face1.push_back(face[i]);
					}
					face2.insert(face2.end(), chain.begin(), chain.end());
					for (size_t i = (contactSecond + 1) % faceSize; i != contactFirst; i = (i + 1) % faceSize)
					{
						face2.push_back(face[i]);
					}
				}
				// Удаляем целевую грань и добавляем порожденные грани в множество внутренних граней
				auto it = std::find(intFaces.begin(), intFaces.end(), face);
				if (it != intFaces.end())
				{
					intFaces.erase(it);
				}
				//Добавляем порожденные грани в множество внутренних граней
				intFaces.push_back(face1);
				intFaces.push_back(face2);
			}
			else
			{  // Если целевая грань совпала с внешней
				std::vector<int> newOuterFace;
				if (contactFirst < contactSecond)
				{
					newOuterFace.insert(newOuterFace.end(), chain.begin(), chain.end());
					for (size_t i = (contactSecond + 1) % faceSize; i != contactFirst; i = (i + 1) % faceSize)
					{
						newOuterFace.push_back(face[i]);
					}
					face2.insert(face2.end(), chain.begin(), chain.end());
					for (size_t i = (contactSecond - 1 + faceSize) % faceSize; i != contactFirst; i = (i - 1 + faceSize) % faceSize)
					{
						face2.push_back(face[i]);
					}
				}
				else
				{
					newOuterFace.insert(newOuterFace.end(), reverseChain.begin(), reverseChain.end());
					for (size_t i = (contactFirst + 1) % faceSize; i != contactSecond; i = (i + 1) % faceSize)
					{
						newOuterFace.push_back(face[i]);
					}
					face2.insert(face2.end(), reverseChain.begin(), reverseChain.end());
					for (size_t i = (contactFirst - 1 + faceSize) % faceSize; i != contactSecond; i = (i - 1 + faceSize) % faceSize)
					{
						face2.push_back(face[i]);
					}
				}
				// Удаляем старые, добавляем новые
				auto it = std::find(intFaces.begin(), intFaces.end(), extFace);
				if (it != intFaces.end()) {
					intFaces.erase(it);
				}
				intFaces.push_back(newOuterFace);
				intFaces.push_back(face2);
				extFace = newOuterFace;
			}
		}
	}
	return new Faces(intFaces, extFace);
}