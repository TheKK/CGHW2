#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include <stdexcept>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <glm/glm.hpp>

class TextureExcepttion: public std::runtime_error
{
public:
	TextureExcepttion(const std::string& msg):
		std::runtime_error("[Texture] " + msg) {}
};

class TextureOutOfMemoryException: public TextureExcepttion
{
public:
	TextureOutOfMemoryException():
		TextureExcepttion("Out of memory") {}
};

template <typename T>
class Texture : public std::vector<T>
{
public:
	Texture(uint32_t w, uint32_t h):
		std::vector<T>(w * h),
		width_(w), height_(h) {}

	T& at(uint32_t x, uint32_t y)
	{ return std::vector<T>::at(offset_(x, y)); }

	uint32_t width() const { return width_; }
	uint32_t height() const { return height_; }
private:
	uint32_t width_, height_; 

	uint32_t offset_(uint32_t x, uint32_t y) { return width_ * y + x; }
};

struct Pixel {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

typedef Texture<double> DepthTexture;
typedef Texture<struct Pixel> PixelTexture;

#endif /* TEXTURE_H */
