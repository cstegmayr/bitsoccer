#include "Renderer.h"
#include "Font.h"
#include "Vec3.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

namespace bitsoccer
{
	namespace Renderer
	{	
		static int s_width = 600;
		static int s_height = 600;
		HitSurface* s_surfaces[256];
		s32 s_numHitSurfaces;
		static Font s_fnt;

		void GLFWCALL reshape( int w, int h )
		{
			s_width = w;
			s_height = h;
			glViewport( 0, 0, (GLsizei)w, (GLsizei)h );

			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			glOrtho(0.0, (GLdouble)w, (GLdouble)h, 0.0, -64.0, 1.0);

			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		}

		void MapToScreen(float x, float y, int& screenX, int& screenY)
		{
			screenX = (int)x;
			screenY = (int)y;
		}

		void MapFromScreen(int screenX, int screenY, float& x, float& y)
		{
			x = (float)screenX;
			y = (float)screenY;
		}

		
		void MapToScreenScale(float width, float height, int& screenWidth, int& screenHeight)
		{
			screenWidth = (int)width;
			screenHeight = (int)height;
		}

		void MapFromScreenScale(int screenWidth, int screenHeight, float& width, float& height)
		{
			width = (float)screenWidth;
			height = (float)screenHeight;
		}

		bool Inside(HitSurface* hs, int x, int y)
		{
			return (x >= hs->startX) && (x <= hs->startX + hs->width) && (y >= hs->startY) && (y <= hs->startY + hs->height);
		}

		void GLFWCALL mouseButtonCallback(int button, int action)
		{
			if (button != GLFW_MOUSE_BUTTON_1)
				return;

			int x, y;
			glfwGetMousePos(&x, &y);

			for (int i = 0; i < s_numHitSurfaces; ++i)
			{
				HitSurface* hs = s_surfaces[i];
				if (action != GLFW_PRESS)
				{
					hs->state = hs->state == HitState::Hold ? HitState::Pressed : HitState::Released;
				}
				else if (Inside(hs, x, y))
				{					
					hs->state = HitState::Hold;
				}
			}
		}
		
		void RegisterHitSurface(HitSurface* surface)
		{
			assert(s_numHitSurfaces < 255);
			s_surfaces[s_numHitSurfaces++] = surface;
		}

		void UnregisterHitSurface(HitSurface* surface)
		{
			for (int i = 0; i < s_numHitSurfaces; ++i)
			{
				if (s_surfaces[i] == surface)
				{
					s_surfaces[i] = s_surfaces[--s_numHitSurfaces];
					return;
				}
			}
		}

		void SetupView(int w, int h)
		{
			reshape(w,h);			
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		}

		void Initialize()
		{
			if (!glfwInit())
			{
				fprintf( stderr, "Failed to initialize GLFW\n" );
				exit( EXIT_FAILURE );
			}
			
			//glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
			if( !glfwOpenWindow( s_width, s_height, 8, 8, 8, 8, 16, 0, GLFW_WINDOW ) )
			{
				fprintf( stderr, "Failed to open GLFW window\n" );
				glfwTerminate();
				exit( EXIT_FAILURE );
			}
			

			glfwSetWindowTitle( "Bit Soccer" );
			glfwSetWindowSizeCallback( reshape );
			glfwSetMouseButtonCallback( mouseButtonCallback );
			glfwEnable( GLFW_STICKY_KEYS );
			glfwEnable( GLFW_STICKY_MOUSE_BUTTONS );
			glfwSwapInterval( 1 );
			glfwSetTime( 0.0 );

			SetupView(s_width, s_height);

			glEnable(GL_DEPTH_TEST);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glEnable(GL_TEXTURE_2D);
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			glEnable(GL_POLYGON_SMOOTH);

			
			//s_fnt.LoadFontFromPath("sheldon_12x6.tga");
			s_fnt.LoadFontFromPath("ProFontWindows.ttf", 12);
		}

		bool IsRunning()
		{			
			return glfwGetWindowParam( GLFW_OPENED ) == GL_TRUE;
		}

		void Terminate()
		{			
			glfwTerminate();
		}

		Font* GetFont()
		{
			return &s_fnt;
		}

		static char s_printfBuf[1024];
		int rprintf(int x, int y, const Vec3& color, const char* format, ...)
		{
			va_list ap;
			va_start(ap, format);
			int res = vsnprintf(s_printfBuf, 1024, format, ap);
			va_end(ap);

			if (res > 0)
			{
				glColor3f(color.r, color.g, color.b);
				s_fnt.DrawText((float)x, (float)y, s_printfBuf);
			}
			return res;
		}

		int rprintf(int x, int y, const char* format, ...)
		{
			va_list ap;
			va_start(ap, format);
			int res = vsnprintf(s_printfBuf, 1024, format, ap);
			va_end(ap);

			if (res > 0)
			{
				glColor3f(1.0f, 1.0f, 1.0f);
				s_fnt.DrawText((float)x, (float)y, s_printfBuf);
			}
			return res;
		}
		
		void DrawCallback()
		{

			glBegin(GL_TRIANGLES);
			for (int i = 0; i < s_numHitSurfaces; ++i)
			{
				HitSurface* hs = s_surfaces[i];
				if (hs->state != HitState::Released)
				{
					u32 x = hs->startX, y = hs->startY, w = hs->width, h = hs->height;
					glColor4f(1.0f, 1.0, 1.0, 0.5f);
					glVertex3i(x, y, 10);
					glVertex3i(x, y+h, 10);
					glVertex3i(x+w, y, 10);
					glVertex3i(x+w, y, 10);
					glVertex3i(x, y+h, 10);
					glVertex3i(x+w, y+h, 10);

					if (hs->state == HitState::Pressed)
						hs->state = HitState::Released;
				}
			}
			glEnd();

			glFlush();
			glfwSwapBuffers();
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		}
	}
}
