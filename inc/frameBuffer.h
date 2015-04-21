#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H
#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <SDL2/SDL_opengl.h>

#include "texture.h"

typedef uint8_t clearBitField;
#define COLOR_BUFFER_BIT 0x01
#define DEPTH_BUFFER_BIT 0x02

class FrameBuffer
{
public:
	FrameBuffer(uint32_t width, uint32_t height);
	FrameBuffer(const FrameBuffer& other);
	FrameBuffer& operator=(const FrameBuffer& other);
	~FrameBuffer();

	void drawPixel(uint32_t x, uint32_t y);
	void drawPixel(float x, float y);

	void clear(clearBitField bits);

	void upload();

	void setDrawColor(glm::vec4& color) { drawColor_ = color; }
	void setClearColor(glm::vec4& color) { clearColor_ = color; }

	glm::vec4 drawColor() const { return drawColor_; }
	glm::vec4 clearColor() const { return clearColor_; }
private:
	uint32_t width_, height_;
	GLuint texture_;

	PixelTexture pixelTexture_;
	DepthTexture depthTexture_;

	glm::vec4 drawColor_;
	glm::vec4 clearColor_;
};

#endif /* FRAME_BUFFER_H */
