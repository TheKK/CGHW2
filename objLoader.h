#include <string>
#include <array>
#include <vector>

class ObjLoader
{
public:
	ObjLoader();
	ObjLoader(const std::string& filePath);

	int load(const std::string& filePath);
	void clear();

	const std::vector<std::array<float, 3>>& getVertice() const;
	const std::vector<std::array<float, 3>>& getVertexNormals() const;
	const std::vector<std::array<std::array<uint32_t, 2>, 3>>&
		getFaces() const;
private:
	std::vector<std::array<float, 3>> vertice;
	std::vector<std::array<float, 3>> vertexNormals;
	std::vector<std::array<std::array<uint32_t, 2>, 3>> faces;
};
