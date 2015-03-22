#include <fstream>
#include <cstdio>
#include <string>

#include "modelAsset.h"

ModelAsset::ModelAsset()
{
}

ModelAsset::ModelAsset(const std::string& filePath)
{
	load(filePath);
}

int
ModelAsset::load(const std::string& filePath)
{
	std::ifstream fd(filePath, std::ios::in);
	std::string lineBuffer;

	std::array<float, 3> floatTmp;
	std::array<std::array<uint32_t, 3>, 3> uintTmp;

	if (!fd.good())
		return -1;

	clear();

	while (std::getline(fd, lineBuffer)) {
		if (sscanf(lineBuffer.c_str(), "v %f %f %f",
			   &floatTmp[0], &floatTmp[1], &floatTmp[2])) {

			vertice.emplace_back(floatTmp[0],
					     floatTmp[1],
					     floatTmp[2]);

		} else if (sscanf(lineBuffer.c_str(), "vn %f %f %f",
				  &floatTmp[0], &floatTmp[1], &floatTmp[2])) {

			vertexNormals.emplace_back(floatTmp[0],
						   floatTmp[1],
						   floatTmp[2]);

		} else if (sscanf(lineBuffer.c_str(), "vt %f %f %f",
				  &floatTmp[0], &floatTmp[1], &floatTmp[2])) {

			vertexUVs.emplace_back(floatTmp[0],
					       floatTmp[1],
					       floatTmp[2]);

		} else if (sscanf(lineBuffer.c_str(),
				  "f %u/%u/%u %u/%u/%u %u/%u/%u",
				  &uintTmp[0][0], &uintTmp[0][1], &uintTmp[0][2],
				  &uintTmp[1][0], &uintTmp[1][1], &uintTmp[1][2],
				  &uintTmp[2][0], &uintTmp[2][1], &uintTmp[2][2])) {

			faces.push_back(uintTmp);
		}
	}

	return 0;
}

void
ModelAsset::clear()
{
	vertice.clear();
	vertexNormals.clear();
	faces.clear();
}

const std::vector<glm::vec3>&
ModelAsset::getVertice() const
{
	return vertice;
}

const std::vector<glm::vec3>&
ModelAsset::getVertexNormals() const
{
	return vertexNormals;
}

const std::vector<glm::vec3>&
ModelAsset::getVertexUVs() const
{
	return vertexUVs;
}

const std::vector<std::array<std::array<uint32_t, 3>, 3>>&
ModelAsset::getFaces() const
{
	return faces;
}
