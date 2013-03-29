#include "Board.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>

namespace bitsoccer
{
	Board::Board()
	{
		m_width  = kBoardWidth;
		m_height = kBoardHeight;
		m_initialized = false;
	}

	void Board::Draw()
	{		
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		int maxSize = m_width > m_height ? m_width : m_height;
		float scale = 2.0f / (float)(maxSize+2);

		glBegin(GL_TRIANGLES);
		{
			for (u32 w = 0; w < m_width; ++w)
			{
				for (u32 h = 0; h < m_height; ++h)
				{
					float posX = (w+1) * scale - 1.0f;
					float posY = (h+1) * scale - 1.0f;

					GetBrick(w, h)->Draw(posX+scale*0.01f, posY, scale*0.98f);
				}
			}
		}
		glEnd();

		glPopMatrix();
	}
	
	u32 Board::GetSize()
	{
		return m_width*m_height;
	}
    u32 Board::GetWidth()
	{
		return m_width;
	}

	u32 Board::GetHeight()
	{
		return m_height;
	}

	bool Board::SetWidth( u32 width )
	{
		if ( m_initialized )
			return false; 
		m_width = width;
		return true;
	}

	bool Board::SetHeight( u32 height )
	{
		if ( m_initialized )
			return false;
		m_height = height;
		return true;
	}

	u32 Board::CalcIndex(u32 rowIndex, u32 colIndex)
	{
		return m_width*rowIndex + colIndex; 
	}

	void Board::Initialize()
	{
		m_bricks = (Brick**)malloc(sizeof(Brick*) * m_width * m_height);
		for (u32 i = 0; i < m_width; ++i)
		{
			for ( u32 j = 0; j < m_height; ++j)
			{
				u32 index = CalcIndex(i,j);
				m_bricks[index] = new Brick();
			}
		}


		m_hitSurfaces = (Renderer::HitSurface*)malloc(sizeof(Renderer::HitSurface*) * 2 * (m_width + m_height));
		int maxSize = m_width > m_height ? m_width : m_height;
		float scale = 2.0f / (float)(maxSize+2);

		// Upper buttons
		for (u32 i = 0; i < m_width; ++i)
		{			
			int x, y, scaleX, scaleY;
			Renderer::MapToScreen((float)(i+1) * scale - 1.0f, 1.0f - scale, x, y);
			Renderer::MapToScreenScale(scale, scale, scaleX, scaleY);
			m_hitSurfaces[i].startX = x;
			m_hitSurfaces[i].startY = y;
			m_hitSurfaces[i].width = scaleX;
			m_hitSurfaces[i].height = scaleY;
			m_hitSurfaces[i].state = HitState::Released;

			Renderer::RegisterHitSurface(&m_hitSurfaces[i]);
		}

		// Lower buttons
		for (u32 i = 0; i < m_width; ++i)
		{			
			int x, y, scaleX, scaleY;
			Renderer::MapToScreen((float)(i+1) * scale - 1.0f, -1.0f, x, y);
			Renderer::MapToScreenScale(scale, scale, scaleX, scaleY);
			m_hitSurfaces[i+m_width].startX = x;
			m_hitSurfaces[i+m_width].startY = y;
			m_hitSurfaces[i+m_width].width = scaleX;
			m_hitSurfaces[i+m_width].height = scaleY;
			m_hitSurfaces[i+m_width].state = HitState::Released;

			Renderer::RegisterHitSurface(&m_hitSurfaces[i+m_width]);
		}

		m_initialized = true; 
	}

	Brick* Board::GetBrick( u32 row, u32 col )
	{
		u32 index = CalcIndex(row,col);
		if ( index >= GetSize() )
			return nullptr;
		return m_bricks[index];
	}

	Brick* Board::Push( Direction::Type dir, u32 row, u32 col, Brick* brick )
	{
		s32 rowIncrement = dir == Direction::East  ? 1 : ( dir == Direction::West  ? -1 : 0 );
		s32 colIncrement = dir == Direction::North ? 1 : ( dir == Direction::South ? -1 : 0 );
		u32 numIterations = (u32)abs( (s32)GetWidth()*rowIncrement + (s32)GetHeight()*colIncrement);
		for ( u32 i = 0; i < numIterations; ++i ) 
		{			
			u32 index = CalcIndex(row + rowIncrement*i,col + colIncrement*i);
			
			Brick* tmp = m_bricks[index];
			m_bricks[index] = brick;
			brick = tmp;
		}
		return brick;
	}
	
	Board::~Board()
	{
	}
}
