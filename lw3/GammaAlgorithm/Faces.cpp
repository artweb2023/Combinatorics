#include "Faces.h"

namespace
{
	std::string vectorToString(const std::vector<int>& vec)
	{
		std::string res = "[";
		for (size_t i = 0; i < vec.size(); ++i)
		{
			res += std::to_string(vec[i]);
			if (i < vec.size() - 1)
			{
				res += ", ";
			}
		}
		res += "]";
		return res;
	}
}

Faces::Faces(const Face& interior, const std::vector<int>& external)
{
	if (!interior.empty() && !external.empty())
	{
		this->m_interior = interior;
		this->m_external = external;
		m_size = static_cast<int>(interior.size()) + static_cast<int>(external.size());
	}
	else
	{
		m_size = 0;
	}
}

Face Faces::getInterior() const
{
	return m_interior;
}

std::vector<int> Faces::getExternal() const
{
	return m_external;
}

std::string Faces::toString() const
{
	std::string result = "Faces size = " + std::to_string(m_size) + "\nExternal face:\n";
	result += vectorToString(m_external) + "\nInterior faces:\n";
	for (const auto& face : m_interior)
	{
		result += vectorToString(face) + "\n";
	}
	return result;
}
