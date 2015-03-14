#include <gtest/gtest.h>
#include <vector>
#include <array>

#include "../objLoader.h"

/*
 * mtllib cube.mtl
 * o Cube_Cube.001
 * v -1.000000 -1.000000 1.000000
 * v -1.000000 -1.000000 -1.000000
 * v 1.000000 -1.000000 -1.000000
 * v 1.000000 -1.000000 1.000000
 * v -1.000000 1.000000 1.000000
 * v -1.000000 1.000000 -1.000000
 * v 1.000000 1.000000 -1.000000
 * v 1.000000 1.000000 1.000000
 * vn -1.000000 0.000000 0.000000
 * vn 0.000000 0.000000 -1.000000
 * vn 1.000000 0.000000 0.000000
 * vn 0.000000 0.000000 1.000000
 * vn 0.000000 -1.000000 0.000000
 * vn 0.000000 1.000000 0.000000
 * usemtl None
 * s off
 * f 6//1 2//1 1//1
 * f 7//2 3//2 2//2
 * f 8//3 4//3 3//3
 * f 5//4 1//4 4//4
 * f 2//5 3//5 4//5
 * f 7//6 6//6 5//6
 * f 5//1 6//1 1//1
 * f 6//2 7//2 2//2
 * f 7//3 8//3 3//3
 * f 8//4 5//4 4//4
 * f 1//5 2//5 4//5
 * f 8//6 7//6 5//6
 */

namespace
{
	const std::string kTestObjFile = "testObj.obj";
	const std::vector<std::array<float, 3>> kVertice = {
		{{-1.000000, -1.000000, 1.000000}},
		{{-1.000000, -1.000000, -1.000000}},
		{{1.000000, -1.000000, -1.000000}},
		{{1.000000, -1.000000, 1.000000}},
		{{-1.000000, 1.000000, 1.000000}},
		{{-1.000000, 1.000000, -1.000000}},
		{{1.000000, 1.000000, -1.000000}},
		{{1.000000, 1.000000, 1.00000}}
	};
	const std::vector<std::array<float, 3>> kVertexNormals = {
		{{-1.000000, 0.000000, 0.000000}},
		{{0.000000, 0.000000, -1.000000}},
		{{1.000000, 0.000000, 0.000000}},
		{{0.000000, 0.000000, 1.000000}},
		{{0.000000, -1.000000, 0.000000}},
		{{0.000000, 1.000000, 0.000000}}
	};
	const std::vector<std::array<std::array<uint32_t, 2>, 3>> kFaces = {
		{{{{6, 1}}, {{2, 1}}, {{1, 1}}}},
		{{{{7, 2}}, {{3, 2}}, {{2, 2}}}},
		{{{{8, 3}}, {{4, 3}}, {{3, 3}}}},
		{{{{5, 4}}, {{1, 4}}, {{4, 4}}}},
		{{{{2, 5}}, {{3, 5}}, {{4, 5}}}},
		{{{{7, 6}}, {{6, 6}}, {{5, 6}}}},
		{{{{5, 1}}, {{6, 1}}, {{1, 1}}}},
		{{{{6, 2}}, {{7, 2}}, {{2, 2}}}},
		{{{{7, 3}}, {{8, 3}}, {{3, 3}}}},
		{{{{8, 4}}, {{5, 4}}, {{4, 4}}}},
		{{{{1, 5}}, {{2, 5}}, {{4, 5}}}},
		{{{{8, 6}}, {{7, 6}}, {{5, 6}}}}
	};
}

TEST(objLoader_test, constructorDefault)
{
	ObjLoader objLoader;
	const auto& vertice = objLoader.getVertice();
	const auto& vertexNormals = objLoader.getVertexNormals();
	const auto& faces = objLoader.getFaces();

	ASSERT_EQ(0, vertice.size());
	ASSERT_EQ(0, vertexNormals.size());
	ASSERT_EQ(0, faces.size());
}

TEST(objLoader_test, constructorWithStringArgument)
{
	ObjLoader objLoader(kTestObjFile);
	const auto& vertice = objLoader.getVertice();
	const auto& vertexNormals = objLoader.getVertexNormals();
	const auto& faces = objLoader.getFaces();

	ASSERT_EQ(kVertice.size(), vertice.size());
	ASSERT_EQ(kVertexNormals.size(), vertexNormals.size());
	ASSERT_EQ(kFaces.size(), faces.size());
}

TEST(objLoader_test, load)
{
	ObjLoader objLoader;
	const auto& vertice = objLoader.getVertice();
	const auto& vertexNormals = objLoader.getVertexNormals();
	const auto& faces = objLoader.getFaces();

	ASSERT_EQ(objLoader.load(kTestObjFile), 0);

	ASSERT_EQ(kVertice.size(), vertice.size());
	ASSERT_EQ(kVertexNormals.size(), vertexNormals.size());
	ASSERT_EQ(kFaces.size(), faces.size());
}

TEST(objLoader_test, clear)
{
	ObjLoader objLoader(kTestObjFile);
	const auto& vertice = objLoader.getVertice();
	const auto& vertexNormals = objLoader.getVertexNormals();
	const auto& faces = objLoader.getFaces();

	objLoader.clear();

	ASSERT_EQ(0, vertice.size());
	ASSERT_EQ(0, vertexNormals.size());
	ASSERT_EQ(0, faces.size());
}

TEST(objLoader_test, getVertice)
{
	ObjLoader objLoader(kTestObjFile);
	const auto& vertice = objLoader.getVertice();

	ASSERT_TRUE(kVertice == vertice);
}

TEST(objLoader_test, getVertexNormals)
{
	ObjLoader objLoader(kTestObjFile);
	const auto& vertexNormals = objLoader.getVertexNormals();

	ASSERT_TRUE(kVertexNormals == vertexNormals);
}

TEST(objLoader_test, getFaces)
{
	ObjLoader objLoader(kTestObjFile);
	const auto& faces = objLoader.getFaces();

	ASSERT_TRUE(kFaces == faces);
}
