#include "Game.h"
#include "Renderer.h"

namespace bitsoccer
{
	Game::Game()
	{
		m_mixer  =  new MixerRandom();
		m_ball   = new Ball();
		m_looseBrick = new Brick();
		m_looseBrick->SetColor(Direction::North,Color::Green);
		m_looseBrick->SetColor(Direction::East ,Color::Red);
		m_looseBrick->SetColor(Direction::South,Color::Green);
		m_looseBrick->SetColor(Direction::West ,Color::Blue);
	}

	void Game::Initialize()
	{
		m_board.Initialize();
		m_mixer->Mix(m_board);
		m_ball->SetPosition(m_board.GetWidth()/2, m_board.GetHeight()/2, m_board);
	}

	u32 Game::PushBoard(Direction::Type dir, u32 row, u32 col)
	{
		m_looseBrick = m_board.Push(dir,row,col,m_looseBrick);
		// returns which directions that are availible to move to
		u32 movableDirections = m_ball->getMoveDirections(m_board);

		return movableDirections;

	}

	void Game::Draw()
	{
		m_board.Draw();
	}

	Game::~Game()
	{
		delete m_mixer;
		delete m_ball;
	}


}
