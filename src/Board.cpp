#include "Board.h"
namespace bitsoccer
{
	Board::Board()
	{
		m_width  = kBoardWidth;
		m_heigth = kBoardHeight;
	}
<<<<<<< HEAD:Board.cpp
	
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

	void Board::Initialize()
	{ 
=======

	void Board::Initialize()
	{
>>>>>>> a433352657e109ea9a34a43b0d535c2f809f6203:src/Board.cpp
	}
	
	Board::~Board()
	{
	}
}
