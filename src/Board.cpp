#include "Board.h"
#include "Ball.h"
#include "Types.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <memory.h>
#include <vector>
#include <set>

namespace bitsoccer
{
	Board::Board()
		: m_initialized(false)
		, m_width(kBoardWidth)
		, m_height(kBoardHeight)
		, m_posX(0)
		, m_posY(0)
		, m_bricks(0)
		, m_hitSurfaces(0)

	{
	}

	Direction::Type Board::GetOppositeDirection( Direction::Type dir ) const
	{
		if ( dir == Direction::North )
			return Direction::South;
		if ( dir == Direction::South )
			return Direction::North;
		if ( dir == Direction::East )
			return Direction::West;
		if ( dir == Direction::West )
			return Direction::East;
		return Direction::NumDirections;
	}

	u32 Board::GetPossibleColorMoveDirections( u32 row, u32 col, Color::Type playerColor ) const
	{
		u32 moveDirections = 0;
		const Brick* b = GetBrick(row, col);
		for ( u32 i = 0; i < Direction::NumDirections; ++i )
		{
			Direction::Type dir = (Direction::Type)i;
			Color::Type colorDir = b->GetColor( dir );
			if ( colorDir == playerColor || colorDir == Color::Green )
			{
				s32 dRow = dir == Direction::North ? 1 : ( dir == Direction::South ? -1 : 0 );
				s32 dCol = dir == Direction::East  ? 1 : ( dir == Direction::West  ? -1 : 0 );
				if ( ( dRow >= 0 || row > 0 ) && ( dCol >= 0 || col > 0 ) )
				{
					Color::Type colorNeighbour = GetBrick( u32(s32(row)+dRow), u32(s32(col)+dCol) )->GetColor( GetOppositeDirection(dir) );
					if  ( colorNeighbour == colorDir )
					{
						if ( i == Direction::North )
							moveDirections |= MoveDirection::ToNorth;
						if ( i == Direction::South )
							moveDirections |= MoveDirection::ToSouth;
						if ( i == Direction::East )
							moveDirections |= MoveDirection::ToEast;
						if ( i == Direction::West )
							moveDirections |= MoveDirection::ToWest;
					}
				}
			}
		}
		return moveDirections;
	}

	/**
	returns true if the color type can move the ball to the specified row and column
	*/
	bool Board::GetMovePathForColor( const Ball* ball, const u32 row, const u32 col, const Color::Type playerColor) const
	{
		bool foundPath = false;
		std::vector<u32> queueRows;
		std::vector<u32> queueCols;
		std::set<u32> visitedIndicies;
		u32 currRow = ball->GetRow();
		queueRows.push_back(currRow);
		u32 currCol = ball->GetCol();
		queueCols.push_back(currCol);
		u32 currIndex = CalcIndex(currRow,currIndex);
		visitedIndicies.insert(currIndex);
		while ( !queueRows.empty() )
		{
			currRow = queueRows.back();
			queueRows.pop_back();
			currCol = queueCols.back();
			queueCols.pop_back();
			u32 moveDirections = GetPossibleColorMoveDirections(currRow, currCol, playerColor);
			std::cout << "rP: " << currRow << " cP: " << currCol << std::endl;
			std::cout << "moveDir: " << moveDirections << std::endl;
			
			if ( moveDirections & MoveDirection::ToNorth )
			{
				s32 tmpR = currRow + 1;
				s32 tmpC = currCol;
				std::cout << "r: " << tmpR << " c: " << tmpC << std::endl;
				currIndex = CalcIndex((u32)tmpR,(u32)tmpC);
				std::set<u32>::iterator it = visitedIndicies.find(currIndex);
				if ( it == visitedIndicies.end() )
				{
					visitedIndicies.insert(currIndex);
					queueRows.push_back((u32)tmpR);
					queueCols.push_back((u32)tmpC);

					if ( queueRows.back() == row && queueCols.back() == col )
					{
						foundPath = true;
						break;
					}
				}
			}
			if ( moveDirections & MoveDirection::ToSouth )
			{
				s32 tmpR = currRow - 1;
				s32 tmpC = currCol;
				std::cout << "r: " << tmpR << " c: " << tmpC << std::endl;
				currIndex = CalcIndex((u32)tmpR,(u32)tmpC);
				std::set<u32>::iterator it = visitedIndicies.find(currIndex);
				if ( it == visitedIndicies.end() )
				{
					visitedIndicies.insert(currIndex);
					queueRows.push_back((u32)tmpR);
					queueCols.push_back((u32)tmpC);

					if ( queueRows.back() == row && queueCols.back() == col )
					{
						foundPath = true;
						break;
					}
				}
			}
			if ( moveDirections & MoveDirection::ToEast )
			{
				s32 tmpR = currRow;
				s32 tmpC = currCol + 1;
				std::cout << "r: " << tmpR << " c: " << tmpC << std::endl;
				currIndex = CalcIndex((u32)tmpR,(u32)tmpC);
				std::set<u32>::iterator it = visitedIndicies.find(currIndex);
				if ( it == visitedIndicies.end() )
				{
					visitedIndicies.insert(currIndex);
					queueRows.push_back((u32)tmpR);
					queueCols.push_back((u32)tmpC);

					if ( queueRows.back() == row && queueCols.back() == col )
					{
						foundPath = true;
						break;
					}
				}
			}
			if ( moveDirections & MoveDirection::ToWest )
			{
				s32 tmpR = currRow;
				s32 tmpC = currCol - 1;
				std::cout << "r: " << tmpR << " c: " << tmpC << std::endl;
				currIndex = CalcIndex((u32)tmpR,(u32)tmpC);
				std::set<u32>::iterator it = visitedIndicies.find(currIndex);
				if ( it == visitedIndicies.end() )
				{
					visitedIndicies.insert(currIndex);
					queueRows.push_back((u32)tmpR);
					queueCols.push_back((u32)tmpC);

					if ( queueRows.back() == row && queueCols.back() == col )
					{
						foundPath = true;
						break;
					}
				}
			}

		}
		queueRows.clear();
		queueCols.clear();
		visitedIndicies.clear();
		return foundPath;
	}

	u32 Board::GetBrickType( Ball* ball, MoveDirection::Type movableColorDirs, u32 h, u32 w)
	{
		Brick* b = GetBrick(h, w);
		u32 brickType = (u32)BrickMode::Normal;
		Brick* ballBrick = GetBrick( ball->GetRow(), ball->GetCol() );
		
		if	( 
			( movableColorDirs & MoveDirection::ToNorth && h > 0 && w     == ball->GetCol() && h - 1 == ball->GetRow() ) ||
			( movableColorDirs & MoveDirection::ToEast  && w > 0 && w - 1 == ball->GetCol() && h     == ball->GetRow() ) ||
			( movableColorDirs & MoveDirection::ToSouth &&          w     == ball->GetCol() && h + 1 == ball->GetRow() ) ||
			( movableColorDirs & MoveDirection::ToWest  &&          w + 1 == ball->GetCol() && h     == ball->GetRow() )   
			)
			brickType |= (u32)BrickMode::PossibleMove;
		if ( b->IsGoal(Player::Red) )
			brickType |= BrickMode::RedGoal;
		if ( b->IsGoal(Player::Blue) )
			brickType |= BrickMode::BlueGoal;
		return brickType;
	}

	void Board::Draw( Ball* ball, MoveDirection::Type movableColorDirs, Color::Type playerColor )
	{	
		for (u32 w = 0; w < m_width; ++w)
		{
			for (u32 h = 0; h < m_height; ++h)
			{
				Brick* b = GetBrick(h, w);
				u32 brickType = GetBrickType(ball, movableColorDirs, h, w);
				b->Draw( (BrickMode::Type)brickType, playerColor );
			}
		}
	}

	u32 Board::GetNumSurroundingHitSurfaces() const
	{
		return m_width*2+m_height*2;
	}
	Renderer::HitSurface& Board::GetHitSurface( u32 index )
	{
		return m_hitSurfaces[index];
	}
	
	u32 Board::GetNumBricks() const
	{
		return m_width*m_height;
	}
    u32 Board::GetWidth() const
	{
		return m_width;
	}

	u32 Board::GetHeight() const
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

	u32 Board::CalcIndex(u32 rowIndex, u32 colIndex) const
	{
		return m_width*rowIndex + colIndex; 
	}

	void Board::SetupHitSurfaces()
	{
		m_hitSurfaces = (Renderer::HitSurface*)malloc(sizeof(Renderer::HitSurface) * 2 * (m_width + m_height));
		int currentSurface = 0;
		u32 brickSize = Brick::GetSize();

		// Lower buttons
		for (u32 i = 0; i < m_width; ++i)
		{
			m_hitSurfaces[currentSurface].startX = i * (brickSize+Brick::GetMargin()) + m_posX;
			m_hitSurfaces[currentSurface].startY = -(brickSize+Brick::GetMargin()) + m_posY;
			m_hitSurfaces[currentSurface].width = brickSize;
			m_hitSurfaces[currentSurface].height = brickSize;
			m_hitSurfaces[currentSurface].state = HitState::Released;

			Renderer::RegisterHitSurface(&m_hitSurfaces[currentSurface]);

			++currentSurface;
		}

		// Upper buttons
		for (u32 i = 0; i < m_width; ++i)
		{
			m_hitSurfaces[currentSurface].startX = i * (brickSize+Brick::GetMargin()) + m_posX;
			m_hitSurfaces[currentSurface].startY = (m_height) * (brickSize+Brick::GetMargin()) + m_posY;
			m_hitSurfaces[currentSurface].width = brickSize;
			m_hitSurfaces[currentSurface].height = brickSize;
			m_hitSurfaces[currentSurface].state = HitState::Released;

			Renderer::RegisterHitSurface(&m_hitSurfaces[currentSurface]);

			++currentSurface;
		}

		// Left buttons
		for (u32 i = 0; i < m_height; ++i)
		{
			m_hitSurfaces[currentSurface].startX = -(brickSize+Brick::GetMargin()) + m_posX;
			m_hitSurfaces[currentSurface].startY = i * (brickSize+Brick::GetMargin()) + m_posY;
			m_hitSurfaces[currentSurface].width = brickSize;
			m_hitSurfaces[currentSurface].height = brickSize;
			m_hitSurfaces[currentSurface].state = HitState::Released;

			Renderer::RegisterHitSurface(&m_hitSurfaces[currentSurface]);

			++currentSurface;
		}

		// Right buttons
		for (u32 i = 0; i < m_height; ++i)
		{
			m_hitSurfaces[currentSurface].startX = m_width * (brickSize+Brick::GetMargin()) + m_posX;
			m_hitSurfaces[currentSurface].startY = i * (brickSize+Brick::GetMargin()) + m_posY;
			m_hitSurfaces[currentSurface].width = brickSize;
			m_hitSurfaces[currentSurface].height = brickSize;
			m_hitSurfaces[currentSurface].state = HitState::Released;

			Renderer::RegisterHitSurface(&m_hitSurfaces[currentSurface]);

			++currentSurface;
		}
	}

	void Board::SetPosition(u32 x, u32 y)
	{
		m_posX = x; m_posY = y;
		for (u32 i = 0; i < m_height; ++i)
		{
			for ( u32 j = 0; j < m_width; ++j)
			{
				u32 index = CalcIndex(i,j);
				m_bricks[index]->SetBoardOrigin(x, y);
			}
		}
	}

	void Board::Initialize(u32 x, u32 y)
	{
		if (m_bricks == 0)
		{
			m_bricks = (Brick**)malloc(sizeof(Brick*) * m_width * m_height);
			for (u32 i = 0; i < m_height; ++i)
			{
				for ( u32 j = 0; j < m_width; ++j)
				{
					u32 index = CalcIndex(i,j);
					m_bricks[index] = new Brick();
				}
			}
		}

		SetPosition(x, y);
		SetupHitSurfaces();

		m_initialized = true; 
	}

	Brick* Board::GetBrick( u32 row, u32 col )
	{
		u32 index = CalcIndex(row,col);
		if ( index >= GetNumBricks() )
			return 0;
		return m_bricks[index];
	}

	const Brick* Board::GetBrick( u32 row, u32 col ) const
	{
		u32 index = CalcIndex(row,col);
		if ( index >= GetNumBricks() )
			return 0;
		return m_bricks[index];
	}

	Brick* Board::Push( Direction::Type dir, u32 row, u32 col, Brick* brick )
	{
		s32 rowIncrement = dir == Direction::North  ? 1 : ( dir == Direction::South  ? -1 : 0 );
		s32 colIncrement = dir == Direction::East  ? 1 : ( dir == Direction::West ? -1 : 0 );
		u32 numIterations = (u32)abs( (s32)GetWidth()*colIncrement + (s32)GetHeight()*rowIncrement);
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

	Direction::Type Board::GetDirectionFromIndex(u32 index)
	{
		if (index < m_width)						// Lower
			return Direction::North;
		else if (index < 2 * m_width)				// Upper
			return Direction::South;
		else if (index < (2*m_width + m_height))	// Left
			return Direction::East;
		else										// Right
			return Direction::West;
	}


	void Board::GetRowColumnFromIndex(u32 hitSurfaceIndex, u32& row, u32& col)
	{
		u32 index = hitSurfaceIndex;
		if (index < m_width)						// Lower
		{
			row = 0;
			col = index % m_width;
		}
		else if (index < 2 * m_width)				// Upper
		{
			row = m_height - 1;
			col = (index - m_width) % m_width;
		}
		else if (index < (2*m_width + m_height))	// Left
		{
			col = 0;
			row = (index - 2 * m_width) % m_height;
		}
		else										// Right
		{
			col = m_width - 1;
			row = (index - 2*m_width - m_height) % m_height;
		}
	}
	
	Board::~Board()
	{		
		if (m_bricks)
		{
			for (u32 i = 0; i < m_height; ++i)
			{
				for ( u32 j = 0; j < m_width; ++j)
				{
					u32 index = CalcIndex(i,j);
					delete m_bricks[index];
					m_bricks[index] = 0;
				}
			}
		}
		free(m_bricks);

		if (m_hitSurfaces)
		{
			for (int i = 0; i < 2 * m_width * m_height; ++i)
			{
				Renderer::UnregisterHitSurface(&m_hitSurfaces[i]);
			}
		}
		free(m_hitSurfaces);
	}
}
