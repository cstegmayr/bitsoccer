#pragma once

#include "Types.h"

#include <GL/glfw.h>
#include <GL/gl.h>

namespace bitsoccer
{
	class Font;
	class Vec3;

	namespace Renderer
	{
		struct HitSurface
		{
			int startX, startY, width, height;
			HitState::Type state;
		};

		void MapToScreen(float x, float y, int& screenX, int& screenY);
		void MapToScreenScale(float width, float height, int& screenWidth, int& screenHeight);
		void MapFromScreenScale(int screenWidth, int screenHeight, float& width, float& height);
		void MapFromScreen(int screenX, int screenY, float& x, float& y);
		void Initialize();

		void RegisterHitSurface(HitSurface* surface);
		void UnregisterHitSurface(HitSurface* surface);

		void DrawCallback();
		void Terminate();
		bool IsRunning();

		int rprintf(int x, int y, const Vec3& color, const char* format, ...);
		int rprintf(int x, int y, const char* format, ...);
		Font* GetFont();

	}
}
