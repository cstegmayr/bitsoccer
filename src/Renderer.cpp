#include "Renderer.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

namespace bitsoccer
{
	namespace Renderer
	{	
		static int s_width = 800;
		static int s_heigth = 800;
		HitSurface* s_surfaces[128];
		s32 s_numHitSurfaces;

		void GLFWCALL reshape( int w, int h )
		{
			int minSize = w < h ? w : h;
			s_width = w;
			s_heigth = h;
			glViewport( 0, 0, (GLsizei)w, (GLsizei)h );

			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);

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

			printf("Mouse x: %d y: %d transformed y: ", x, y);

			y = s_width - y;

			printf("%d\n", y);

			for (int i = 0; i < s_numHitSurfaces; ++i)
			{
				HitSurface* hs = s_surfaces[i];
				if (Inside(hs, x, y))
				{					
					hs->state = action == GLFW_PRESS ? HitState::Hold : (hs->state == HitState::Hold ? HitState::Pressed : HitState::Released);
				}
			}
		}
		
		void RegisterHitSurface(HitSurface* surface)
		{
			s_surfaces[s_numHitSurfaces++] = surface;
		}

		void SetupView(int w, int h)
		{
			reshape(w,h);			
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		}

		void Initialize(int argc, const char** argv)
		{
			if (!glfwInit())
			{
				fprintf( stderr, "Failed to initialize GLFW\n" );
				exit( EXIT_FAILURE );
			}
			
			glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
			if( !glfwOpenWindow( s_width, s_heigth, 8, 8, 8, 8, 16, 0, GLFW_WINDOW ) )
			{
				fprintf( stderr, "Failed to open GLFW window\n" );
				glfwTerminate();
				exit( EXIT_FAILURE );
			}
			

			glfwSetWindowTitle( "Bit Soccer" );
			glfwSetWindowSizeCallback( reshape );
			glfwSetMouseButtonCallback( mouseButtonCallback );
			glfwEnable( GLFW_STICKY_KEYS );
			glfwSwapInterval( 1 );
			glfwSetTime( 0.0 );

			SetupView(s_width, s_heigth);
		}

		bool IsRunning()
		{			
			return glfwGetWindowParam( GLFW_OPENED ) == GL_TRUE;
		}

		void Terminate()
		{			
			glfwTerminate();
		}
		
		void DrawCallback()
		{
			glFlush();
			glfwSwapBuffers();
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			glBegin(GL_TRIANGLES);
			for (int i = 0; i < s_numHitSurfaces; ++i)
			{
				HitSurface* hs = s_surfaces[i];
				float x, y, w, h;
				MapFromScreen(hs->startX, hs->startY, x, y);
				MapFromScreenScale(hs->width, hs->height, w, h);

				if (hs->state == HitState::Released)
				{
					glColor3f(1.0f, 1.0f, 0.0f);
				}
				else
				{
					glColor3f(1.0f, 0.0, 0.0);
				}
				
				glVertex2f(x, y);
				glVertex2f(x, y+h);
				glVertex2f(x+w, y);
				glVertex2f(x+w, y);
				glVertex2f(x, y+h);
				glVertex2f(x+w, y+h);

				if (hs->state == HitState::Pressed)
					hs->state = HitState::Released;
			}
			glEnd();
		}
	}
}
