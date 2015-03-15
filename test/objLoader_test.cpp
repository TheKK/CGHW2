#include <gtest/gtest.h>
#include <vector>
#include <array>

/* TODO Fix this in Makefile */
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
 * f 6/0/1 2/0/1 1/0/1
 * f 7/0/2 3/0/2 2/0/2
 * f 8/0/3 4/0/3 3/0/3
 * f 5/0/4 1/0/4 4/0/4
 * f 2/0/5 3/0/5 4/0/5
 * f 7/0/6 6/0/6 5/0/6
 * f 5/0/1 6/0/1 1/0/1
 * f 6/0/2 7/0/2 2/0/2
 * f 7/0/3 8/0/3 3/0/3
 * f 8/0/4 5/0/4 4/0/4
 * f 1/0/5 2/0/5 4/0/5
 * f 8/0/6 7/0/6 5/0/6
 */

namespace
{
	const std::string kTestObjFile = "test/testObj.obj";
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

	const std::vector<std::array<float, 3>> kVertexUVs = {
	};

	const std::vector<std::array<std::array<uint32_t, 3>, 3>> kFaces = {
		{{{{6, 0, 1}}, {{2, 0, 1}}, {{1, 0, 1}}}},
		{{{{7, 0, 2}}, {{3, 0, 2}}, {{2, 0, 2}}}},
		{{{{8, 0, 3}}, {{4, 0, 3}}, {{3, 0, 3}}}},
		{{{{5, 0, 4}}, {{1, 0, 4}}, {{4, 0, 4}}}},
		{{{{2, 0, 5}}, {{3, 0, 5}}, {{4, 0, 5}}}},
		{{{{7, 0, 6}}, {{6, 0, 6}}, {{5, 0, 6}}}},
		{{{{5, 0, 1}}, {{6, 0, 1}}, {{1, 0, 1}}}},
		{{{{6, 0, 2}}, {{7, 0, 2}}, {{2, 0, 2}}}},
		{{{{7, 0, 3}}, {{8, 0, 3}}, {{3, 0, 3}}}},
		{{{{8, 0, 4}}, {{5, 0, 4}}, {{4, 0, 4}}}},
		{{{{1, 0, 5}}, {{2, 0, 5}}, {{4, 0, 5}}}},
		{{{{8, 0, 6}}, {{7, 0, 6}}, {{5, 0, 6}}}}
	};
}

TEST(objLoader_test, constructorDefault)
{
	ObjLoader objLoader;
	const auto& vertice = objLoader.getVertice();
	const auto& vertexNormals = objLoader.getVertexNormals();
	const auto& vertexUVs = objLoader.getVertexUVs();
	const auto& faces = objLoader.getFaces();

	ASSERT_EQ(0, vertice.size());
	ASSERT_EQ(0, vertexNormals.size());
	ASSERT_EQ(0, vertexUVs.size());
	ASSERT_EQ(0, faces.size());
}

TEST(objLoader_test, constructorWithStringArgument)
{
	ObjLoader objLoader(kTestObjFile);
	const auto& vertice = objLoader.getVertice();
	const auto& vertexNormals = objLoader.getVertexNormals();
	const auto& vertexUVs = objLoader.getVertexUVs();
	const auto& faces = objLoader.getFaces();

	ASSERT_EQ(kVertice, vertice);
	ASSERT_EQ(kVertexNormals, vertexNormals);
	ASSERT_EQ(kVertexUVs, vertexUVs);
	ASSERT_EQ(kFaces, faces);
}

TEST(objLoader_test, load)
{
	ObjLoader objLoader;
	const auto& vertice = objLoader.getVertice();
	const auto& vertexNormals = objLoader.getVertexNormals();
	const auto& vertexUVs = objLoader.getVertexUVs();
	const auto& faces = objLoader.getFaces();

	ASSERT_EQ(0, objLoader.load(kTestObjFile));

	ASSERT_EQ(kVertice, vertice);
	ASSERT_EQ(kVertexNormals, vertexNormals);
	ASSERT_EQ(kVertexUVs, vertexUVs);
	ASSERT_EQ(kFaces, faces);
}

TEST(objLoader_test, clear)
{
	ObjLoader objLoader(kTestObjFile);
	const auto& vertice = objLoader.getVertice();
	const auto& vertexNormals = objLoader.getVertexNormals();
	const auto& vertexUVs = objLoader.getVertexUVs();
	const auto& faces = objLoader.getFaces();

	objLoader.clear();

	ASSERT_EQ(0, vertice.size());
	ASSERT_EQ(0, vertexNormals.size());
	ASSERT_EQ(0, vertexUVs.size());
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

TEST(objLoader_test, getVertexUVs)
{
	ObjLoader objLoader(kTestObjFile);
	const auto& vertexUVs = objLoader.getVertexUVs();

	ASSERT_TRUE(kVertexUVs == vertexUVs);
}

TEST(objLoader_test, getFaces)
{
	ObjLoader objLoader(kTestObjFile);
	const auto& faces = objLoader.getFaces();

	ASSERT_TRUE(kFaces == faces);
}
