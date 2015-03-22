#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <array>
#include <vector>
#include <glm/glm.hpp>

class ObjLoader
{
public:
	ObjLoader();
	ObjLoader(const std::string& filePath);

	int load(const std::string& filePath);
	void clear();

	const std::vector<glm::vec3>& getVertice() const;
	const std::vector<glm::vec3>& getVertexNormals() const;
	const std::vector<glm::vec3>& getVertexUVs() const;
	const std::vector<std::array<std::array<uint32_t, 3>, 3>>&
		getFaces() const;
private:
	std::vector<glm::vec3> vertice;
	std::vector<glm::vec3> vertexNormals;
	std::vector<glm::vec3> vertexUVs;
	std::vector<std::array<std::array<uint32_t, 3>, 3>> faces;
};

#endif /* OBJLOADER_H */
