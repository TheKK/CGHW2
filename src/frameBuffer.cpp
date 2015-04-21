#include <algorithm>
#include <limits>

#include "frameBuffer.h"

namespace
{
	const double kMaxDepth = std::numeric_limits<double>::max();
}

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height):
	width_(width), height_(height),
	pixelTexture_(width_, height_),
	depthTexture_(width_, height_)
{
	struct Pixel* rawDataPtr = pixelTexture_.data();

	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_,
		     0, GL_RGBA8, GL_UNSIGNED_BYTE,
		     (GLvoid*) rawDataPtr);

	glBindTexture(GL_TEXTURE_2D, 0);
}

FrameBuffer::FrameBuffer(const FrameBuffer& other):
	width_(other.width_), height_(other.height_),
	pixelTexture_(other.pixelTexture_),
	depthTexture_(other.depthTexture_)
{
	struct Pixel* rawDataPtr = pixelTexture_.data();

	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_,
		     0, GL_RGBA8, GL_UNSIGNED_BYTE,
		     (GLvoid*) rawDataPtr);

	glBindTexture(GL_TEXTURE_2D, 0);
}

FrameBuffer& 
FrameBuffer::operator=(const FrameBuffer& other)
{
	struct Pixel* rawDataPtr = pixelTexture_.data();

	width_ = other.width_;
	height_ = other.height_;
	pixelTexture_ = other.pixelTexture_;
	depthTexture_ = other.depthTexture_;

	glBindTexture(GL_TEXTURE_2D, texture_);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_,
		     0, GL_RGBA8, GL_UNSIGNED_BYTE,
		     (GLvoid*) rawDataPtr);

	glBindTexture(GL_TEXTURE_2D, 0);

	return *this;
}

FrameBuffer::~FrameBuffer()
{
	glDeleteTextures(1, &texture_);
}

void 
FrameBuffer::drawPixel(uint32_t x, uint32_t y)
{
	if (glm::clamp<uint32_t>(x, 0, width_ - 1) != x ||
	    glm::clamp<uint32_t>(y, 0, height_ - 1) != y)
		return;

	struct Pixel p = {
		.r = (uint8_t) std::roundf(drawColor_.r * 255.f),
		.g = (uint8_t) std::roundf(drawColor_.r * 255.f),
		.b = (uint8_t) std::roundf(drawColor_.r * 255.f),
		.a = (uint8_t) std::roundf(drawColor_.r * 255.f)
	};

	pixelTexture_.at(x, y) = p;
}

void 
FrameBuffer::drawPixel(float x, float y)
{
	uint32_t pixelX = std::roundf(((x + 1.f) / 2.f) * (float) width_);
	uint32_t pixelY = std::roundf(((y + 1.f) / 2.f) * (float) height_);

	drawPixel(pixelX, pixelY);
}

void
FrameBuffer::clear(clearBitField bits)
{
	if ((bits & COLOR_BUFFER_BIT) != 0) {
		struct Pixel p = {
			.r = (uint8_t) std::roundf(drawColor_.r * 255.f),
			.g = (uint8_t) std::roundf(drawColor_.r * 255.f),
			.b = (uint8_t) std::roundf(drawColor_.r * 255.f),
			.a = (uint8_t) std::roundf(drawColor_.r * 255.f)
		};

		std::fill(pixelTexture_.begin(), pixelTexture_.end(), p);
	}

	if ((bits & DEPTH_BUFFER_BIT) == 1) {
		std::fill(depthTexture_.begin(), depthTexture_.end(), kMaxDepth);
	}
}

void
FrameBuffer::upload()
{
	glBindTexture(GL_TEXTURE_2D, texture_);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_,
			GL_RGBA, GL_UNSIGNED_BYTE,
			(GLvoid*) pixelTexture_.data());

	glEnable(GL_TEXTURE_2D);

	// draw a point with texture
	glBindTexture(GL_TEXTURE_2D, texture_);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f( 1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f( 1.0f,  1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(-1.0f,  1.0f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}
