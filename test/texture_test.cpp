#include <gtest/gtest.h>

#include "texture.h"

TEST(texture_test, constructWithZero)
{
	ASSERT_NO_THROW(Texture<int>(0, 0));
}

TEST(texture_test, constructWithNonzero)
{
	ASSERT_NO_THROW(Texture<int>(30, 23));
}

TEST(texture_test, constructWithNegtive)
{
	ASSERT_ANY_THROW(Texture<int>(-30, 23));
}

TEST(texture_test, setDataAt)
{
	Texture<int> tex(2, 10);

	tex.at(1, 1) = 123;

	ASSERT_EQ(123, tex.at(1, 1));
}

TEST(texture_test, getDataThatOutOfRange)
{
	Texture<int> tex(2, 10);

	ASSERT_ANY_THROW(tex.at(123, 32));
}

TEST(texture_test, widthGetter)
{
	Texture<int> tex(15, 3);

	ASSERT_EQ(15, tex.width());
}

TEST(texture_test, heightGetter)
{
	Texture<int> tex(15, 3);

	ASSERT_EQ(3, tex.height());
}
