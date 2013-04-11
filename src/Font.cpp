#include "Font.h"

#include <GL/gl.h>
#include <stdio.h>
#include <assert.h>

#ifndef STBTT_malloc
#include <stdlib.h>
#define STBTT_malloc(x,u)  malloc(x)
#define STBTT_free(x,u)    free(x)
#endif

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

namespace bitsoccer
{
	Font::Font()
	: m_cdata(0)
	, m_textureId(0)
	{
	}

	Font::~Font()
	{
		FreeFontImage();
	}

	void Font::FreeRenderingResources()
	{
		if (m_textureId)
		{
			glDeleteTextures(1, &m_textureId);
			m_textureId = 0;
		}
	}

	void Font::FreeFontImage()
	{
		FreeRenderingResources();

		if(m_cdata) free(m_cdata);
	}

	void Font::DrawText(float xpos, float ypos, const char* text) const
	{		
		assert(m_textureId);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// assume orthographic projection with units = screen pixels, origin at top left
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		glBegin(GL_QUADS);
		while (*text) 
		{
			if (*text >= 32 && *text < 128) 
			{
				stbtt_aligned_quad q;
				stbtt_GetBakedQuad(m_cdata, 512,512, *text-32, &xpos, &ypos, &q, 1);
				
				float temp = q.t0;
				q.t0 = q.t1;
				q.t1 = temp;
				glTexCoord2f(q.s0,q.t1); glVertex3f(q.x0,q.y0, 20.0f);
				glTexCoord2f(q.s1,q.t1); glVertex3f(q.x1,q.y0, 20.0f);
				glTexCoord2f(q.s1,q.t0); glVertex3f(q.x1,q.y1, 20.0f);
				glTexCoord2f(q.s0,q.t0); glVertex3f(q.x0,q.y1, 20.0f);
			}
			++text;
		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
	}

	bool Font::LoadFontFromPath(const char* fontTexturePath, int sizeInPixels)
	{
		FreeFontImage();
		printf("Loading font: %s\n", fontTexturePath);

		FILE* file = fopen(fontTexturePath, "rb");
		if (file)
		{
			fseek(file, 0L, SEEK_END);
			int sz = ftell(file);
			fseek(file, 0L, SEEK_SET);

			printf("File '%s' opened successfully. Size: %d kb\n", fontTexturePath, sz / 1024);
			const size_t texture_size = 512;
			u8* bitmap = (u8*)malloc(texture_size*texture_size);
			u8* ttf_buffer = (u8*)malloc((size_t)sz+256);
			m_cdata = (stbtt_bakedchar*)malloc(256*sizeof(stbtt_bakedchar));

			fread(ttf_buffer, 1, sz+16, file);
			if (stbtt_BakeFontBitmap(ttf_buffer,0, (float)sizeInPixels, bitmap, texture_size, texture_size, 32, 255, m_cdata) <= 0)
			{
				printf("The bitmap was too small for the font.\n");
			}

			glGenTextures(1, &m_textureId);
			glBindTexture(GL_TEXTURE_2D, m_textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512,512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			free(bitmap);
			free(ttf_buffer);

			fclose(file);
		}

		return true;
	}
}