#pragma once

#include "ReadFromFile.h"
#include "stdafx.h"

using Face = std::vector<std::vector<int>>;

class Faces
{
public:
	Faces(const Face& interior, const std::vector<int>& external);
	Face getInterior() const;
	std::vector<int> getExternal() const;
	std::string toString() const;
private:
	Face m_interior;
	std::vector<int> m_external;
	int m_size;
};
