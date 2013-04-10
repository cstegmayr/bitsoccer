#pragma once

#include "Types.h"
#include <GL/glfw.h>


#ifndef STBTT_malloc
#include <stdlib.h>
#define STBTT_malloc(x,u)  malloc(x)
#define STBTT_free(x,u)    free(x)
#endif
#include <stb_truetype.h>


namespace bitsoccer
{
	class Font
	{
	public:
		Font();
		~Font();

		/// Loads a png image of the bitmap font
		bool LoadFontFromPath(const char* fontTexturePath, int sizeInPixels);
		/// Gets the height in pixels of the specified character
		int GetCharHeight(char c) const { return 0;}
		/// Gets the width in pixels of the specified character
		int GetCharWidth(char c) const { return 0;}
		/// Draws text on screen at current raster position
		void DrawText(float xpos, float ypos, const char* text) const;

	private:
		void FreeRenderingResources();
		void FreeFontImage();
		void InitRendering();

		GLFWimage m_fontImage;
		stbtt_bakedchar* m_cdata;
		u32 m_textureId;
	};

}
