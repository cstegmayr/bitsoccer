#include "Board.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
//#include <iostream>
#include <memory.h>

namespace bitsoccer
{
	Board::Board()
		: m_initialized(false)
		, m_width(kBoardWidth)
		, m_height(kBoardHeight)
		, m_bricks(0)
		, m_hitSurfaces(0)

	{
	}

	void Board::Draw()
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		int maxSize = m_width > m_height ? m_width : m_height;
		float scale = 32.0f + 2.0f; // pixels wide

		glBegin(GL_TRIANGLES);
		{
			for (u32 w = 0; w < m_width; ++w)
			{
				for (u32 h = 0; h < m_height; ++h)
				{
					float posX = (w+1) * scale;
					float posY = (h+1) * scale;

					GetBrick(w, h)->Draw(posX+1.0f, posY, scale-2.0f);
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
		return m_width*colIndex +rowIndex; 
	}

	void Board::SetupHitSurfaces()
	{
		m_hitSurfaces = (Renderer::HitSurface*)malloc(sizeof(Renderer::HitSurface) * 2 * (m_width + m_height));
		int maxSize = m_width > m_height ? m_width : m_height;
		int brickWidth = 32 + 2;

		int currentSurface = 0;

		// Lower buttons
		for (u32 i = 0; i < m_width; ++i)
		{
			m_hitSurfaces[currentSurface].startX = (i+1)*brickWidth+1;
			m_hitSurfaces[currentSurface].startY = 0;
			m_hitSurfaces[currentSurface].width = brickWidth-2;
			m_hitSurfaces[currentSurface].height = brickWidth-2;
			m_hitSurfaces[currentSurface].state = HitState::Released;

			Renderer::RegisterHitSurface(&m_hitSurfaces[currentSurface]);

			++currentSurface;
		}

		// Upper buttons
		for (u32 i = 0; i < m_width; ++i)
		{
			m_hitSurfaces[currentSurface].startX = (i+1) * brickWidth+1;
			m_hitSurfaces[currentSurface].startY = (m_height+1) * brickWidth;
			m_hitSurfaces[currentSurface].width = brickWidth-2;
			m_hitSurfaces[currentSurface].height = brickWidth-2;
			m_hitSurfaces[currentSurface].state = HitState::Released;

			Renderer::RegisterHitSurface(&m_hitSurfaces[currentSurface]);

			++currentSurface;
		}

		// Left buttons
		for (u32 i = 0; i < m_height; ++i)
		{
			m_hitSurfaces[currentSurface].startX = 1;
			m_hitSurfaces[currentSurface].startY = (i+1) * brickWidth;
			m_hitSurfaces[currentSurface].width = brickWidth-2;
			m_hitSurfaces[currentSurface].height = brickWidth-2;
			m_hitSurfaces[currentSurface].state = HitState::Released;

			Renderer::RegisterHitSurface(&m_hitSurfaces[currentSurface]);

			++currentSurface;
		}

		// Right buttons
		for (u32 i = 0; i < m_height; ++i)
		{
			m_hitSurfaces[currentSurface].startX = (m_width+1) * brickWidth+1;
			m_hitSurfaces[currentSurface].startY = (i+1) * brickWidth;
			m_hitSurfaces[currentSurface].width = brickWidth-2;
			m_hitSurfaces[currentSurface].height = brickWidth-2;
			m_hitSurfaces[currentSurface].state = HitState::Released;

			Renderer::RegisterHitSurface(&m_hitSurfaces[currentSurface]);

			++currentSurface;
		}
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

		SetupHitSurfaces();

		m_initialized = true; 
	}

	Brick* Board::GetBrick( u32 row, u32 col )
	{
		u32 index = CalcIndex(row,col);
		if ( index >= GetSize() )
			return 0;
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
			brick->NotifyPosition(row + rowIncrement*i,col + colIncrement*i);
			brick = tmp;
		}
		return brick;
	}
	
	Board::~Board()
	{
		free(m_bricks);
		free(m_hitSurfaces);
	}
}
