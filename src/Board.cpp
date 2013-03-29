#include "Board.h"
#include "Renderer.h"

namespace bitsoccer
{
	Board::Board()
	{
		m_width  = kBoardWidth;
		m_height = kBoardHeight;
	}

	void Board::Draw()
	{		
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		int maxSize = m_width > m_height ? m_width : m_height;
		float scale = 2.0f / (float)(maxSize+2);
		float step = scale / 2.0f;
		//glTranslatef(-1.0f, -1.0f, 0.0f);

		glBegin(GL_TRIANGLES);
		{
			for (u32 w = 0; w < m_width; ++w)
			{
				for (u32 h = 0; h < m_height; ++h)
				{
					float posX = (w+1) * scale - 1.0f;
					float posY = (h+1) * scale - 1.0f;
					
					glColor3f(posX*0.5f + 0.5f, posY*0.5f + 0.5f, 0.0f);

					m_board[w][h].Draw(posX, posY, scale);
				}
			}
		}
		glEnd();

		glPopMatrix();
	}
	
	u32 Board::getSize()
	{
		return m_width*m_height;
	}
    u32 Board::getWidth()
	{
		return m_width;
	}

	u32 Board::getHeight()
	{
		return m_height;
	}

	void Board::Initialize( const MixerBase* mixer )
	{ 
	}
	
	Board::~Board()
	{
	}
}
