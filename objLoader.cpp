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

const std::vector<std::array<std::array<uint32_t, 2>, 3>>&
ObjLoader::getFaces() const
{
	return faces;
}
