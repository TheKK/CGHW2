#include <fstream>
#include <cstdio>
#include <string>

#include "objLoader.h"

ObjLoader::ObjLoader()
{
}

ObjLoader::ObjLoader(const std::string& filePath)
{
	load(filePath);
}

int
ObjLoader::load(const std::string& filePath)
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

			vertice.push_back(floatTmp);

		} else if (sscanf(lineBuffer.c_str(), "vn %f %f %f",
				  &floatTmp[0], &floatTmp[1], &floatTmp[2])) {

			vertexNormals.push_back(floatTmp);

		} else if (sscanf(lineBuffer.c_str(), "vt %f %f %f",
				  &floatTmp[0], &floatTmp[1], &floatTmp[2])) {

			vertexUVs.push_back(floatTmp);

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
ObjLoader::clear()
{
	vertice.clear();
	vertexNormals.clear();
	faces.clear();
}

const std::vector<std::array<float, 3>>& 
ObjLoader::getVertice() const
{
	return vertice;
}

const std::vector<std::array<float, 3>>& 
ObjLoader::getVertexNormals() const
{
	return vertexNormals;
}

const std::vector<std::array<float, 3>>& 
ObjLoader::getVertexUVs() const
{
	return vertexUVs;
}

const std::vector<std::array<std::array<uint32_t, 3>, 3>>&
ObjLoader::getFaces() const
{
	return faces;
}
