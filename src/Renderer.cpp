#include "Renderer.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

namespace bitsoccer
{
	namespace Renderer
	{	
		void GLFWCALL reshape( int w, int h )
		{
			int minSize = w < h ? w : h;
			glViewport( 0, 0, (GLsizei)minSize, (GLsizei)minSize );

			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();

			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
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

			if( !glfwOpenWindow( 400, 400, 8, 8, 8, 8, 16, 0, GLFW_WINDOW ) )
			{
				fprintf( stderr, "Failed to open GLFW window\n" );
				glfwTerminate();
				exit( EXIT_FAILURE );
			}
			

			glfwSetWindowTitle( "Bit Soccer" );
			glfwSetWindowSizeCallback( reshape );
			glfwEnable( GLFW_STICKY_KEYS );
			glfwSwapInterval( 1 );
			glfwSetTime( 0.0 );

			SetupView(400, 400);
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
		}

		void KeyCallback() {}
	}
}
