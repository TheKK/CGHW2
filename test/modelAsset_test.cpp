#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <glm/glm.hpp>

#include "modelAsset.h"

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
	const std::vector<glm::vec3> kVertice = {
		{-1.000000, -1.000000, 1.000000},
		{-1.000000, -1.000000, -1.000000},
		{1.000000, -1.000000, -1.000000},
		{1.000000, -1.000000, 1.000000},
		{-1.000000, 1.000000, 1.000000},
		{-1.000000, 1.000000, -1.000000},
		{1.000000, 1.000000, -1.000000},
		{1.000000, 1.000000, 1.00000}
	};
	const std::vector<glm::vec3> kVertexNormals = {
		{-1.000000, 0.000000, 0.000000},
		{0.000000, 0.000000, -1.000000},
		{1.000000, 0.000000, 0.000000},
		{0.000000, 0.000000, 1.000000},
		{0.000000, -1.000000, 0.000000},
		{0.000000, 1.000000, 0.000000}
	};

	const std::vector<glm::vec3> kVertexUVs = {
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

TEST(modelAsset_test, constructorDefault)
{
	ModelAsset modelAsset;
	const auto& vertice = modelAsset.getVertice();
	const auto& vertexNormals = modelAsset.getVertexNormals();
	const auto& vertexUVs = modelAsset.getVertexUVs();
	const auto& faces = modelAsset.getFaces();

	ASSERT_EQ(0, vertice.size());
	ASSERT_EQ(0, vertexNormals.size());
	ASSERT_EQ(0, vertexUVs.size());
	ASSERT_EQ(0, faces.size());
}

TEST(modelAsset_test, constructorWithStringArgument)
{
	ModelAsset modelAsset(kTestObjFile);
	const auto& vertice = modelAsset.getVertice();
	const auto& vertexNormals = modelAsset.getVertexNormals();
	const auto& vertexUVs = modelAsset.getVertexUVs();
	const auto& faces = modelAsset.getFaces();

	ASSERT_EQ(kVertice, vertice);
	ASSERT_EQ(kVertexNormals, vertexNormals);
	ASSERT_EQ(kVertexUVs, vertexUVs);
	ASSERT_EQ(kFaces, faces);
}

TEST(modelAsset_test, load)
{
	ModelAsset modelAsset;
	const auto& vertice = modelAsset.getVertice();
	const auto& vertexNormals = modelAsset.getVertexNormals();
	const auto& vertexUVs = modelAsset.getVertexUVs();
	const auto& faces = modelAsset.getFaces();

	ASSERT_EQ(0, modelAsset.load(kTestObjFile));

	ASSERT_EQ(kVertice, vertice);
	ASSERT_EQ(kVertexNormals, vertexNormals);
	ASSERT_EQ(kVertexUVs, vertexUVs);
	ASSERT_EQ(kFaces, faces);
}

TEST(modelAsset_test, clear)
{
	ModelAsset modelAsset(kTestObjFile);
	const auto& vertice = modelAsset.getVertice();
	const auto& vertexNormals = modelAsset.getVertexNormals();
	const auto& vertexUVs = modelAsset.getVertexUVs();
	const auto& faces = modelAsset.getFaces();

	modelAsset.clear();

	ASSERT_EQ(0, vertice.size());
	ASSERT_EQ(0, vertexNormals.size());
	ASSERT_EQ(0, vertexUVs.size());
	ASSERT_EQ(0, faces.size());
}

TEST(modelAsset_test, getVertice)
{
	ModelAsset modelAsset(kTestObjFile);
	const auto& vertice = modelAsset.getVertice();

	ASSERT_TRUE(kVertice == vertice);
}

TEST(modelAsset_test, getVertexNormals)
{
	ModelAsset modelAsset(kTestObjFile);
	const auto& vertexNormals = modelAsset.getVertexNormals();

	ASSERT_TRUE(kVertexNormals == vertexNormals);
}

TEST(modelAsset_test, getVertexUVs)
{
	ModelAsset modelAsset(kTestObjFile);
	const auto& vertexUVs = modelAsset.getVertexUVs();

	ASSERT_TRUE(kVertexUVs == vertexUVs);
}

TEST(modelAsset_test, getFaces)
{
	ModelAsset modelAsset(kTestObjFile);
	const auto& faces = modelAsset.getFaces();

	ASSERT_TRUE(kFaces == faces);
}
