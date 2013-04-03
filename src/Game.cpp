#include "Game.h"
#include "Renderer.h"

namespace bitsoccer
{
	Game::Game()
	: m_board()
	, m_mixer(new MixerRandom())
	, m_ball(new Ball())
	, m_looseBrick(new Brick())
	, m_state(PlayState::PlayerRedPush)
	, m_animationCounter(0)
	{
		m_looseBrick->SetColor(Direction::North,Color::Green);
		m_looseBrick->SetColor(Direction::East ,Color::Red);
		m_looseBrick->SetColor(Direction::South,Color::Green);
		m_looseBrick->SetColor(Direction::West ,Color::Blue);
	}

	Game::~Game()
	{
		delete m_mixer;
		delete m_ball;
		delete m_looseBrick;
	}

	PlayState::Type Game::GetState() const
	{
		return m_state;
	}

	bool Game::IsAnimating() const
	{
		return m_animationCounter > 0;
	}

	void Game::Initialize()
	{
		m_board.Initialize(64, 64);
		m_looseBrick->SetBoardOrigin(64, 64);
		m_mixer->Mix(m_board);
		m_ball->SetPosition(m_board.GetWidth()/2, m_board.GetHeight()/2, m_board);
	}

	u32 Game::PushBoard(Direction::Type dir, u32 row, u32 col)
	{
		m_looseBrick = m_board.Push(dir,row,col,m_looseBrick);
		// returns which directions that are availible to move to
		u32 movableDirections = m_ball->GetChangedDirections(m_board);

		return movableDirections;

	}

	void Game::Update(double dt)
	{
		//Check surrounding hit surfaces for mouse picks
		if ( m_state == PlayState::PlayerRedPush || m_state == PlayState::PlayerBluePush )
		{
			s32 foundSurface = -1;
			for ( u32 i = 0; i < m_board.GetNumSurroundingHitSurfaces(); ++i )
			{
				if ( m_board.GetHitSurface(i).state == HitState::Pressed )
				{
					foundSurface = i;
					break;
				}
			}
			if ( foundSurface >= 0 )
			{
				// calc from direction
				Direction::Type dir = m_board.GetDirectionFromIndex((u32)foundSurface);
				// calc index on board
				u32 row, col;
				m_board.GetRowColumnFromIndex((u32)foundSurface,row,col);

				// push the board
				PushBoard( dir, row, col );

				// change play state
				if ( m_state == PlayState::PlayerRedPush )
					m_state = PlayState::PlayerRedMove;

				else if ( m_state == PlayState::PlayerBluePush )
					m_state = PlayState::PlayerBlueMove;

			}
		}
		else
		{
			for ( u32 col = 0; col < m_board.GetWidth(); ++col )
			{
				for ( u32 row = 0; row < m_board.GetHeight(); ++row )
				{
					Brick* b = m_board.GetBrick(row,col);
					if ( b->IsPressed() ) 
					{
						
					}
				}
			}
		
		}
	}

	void Game::Draw()
	{
			
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glBegin(GL_TRIANGLES);
		{
			Color::Type playerColor = m_state == PlayState::PlayerRedMove ? Color::Red : ( m_state == PlayState::PlayerBlueMove ? Color::Blue : Color::Green);
			m_board.Draw(m_ball, (MoveDirection::Type)m_ball->GetMovableColorDirections( m_board, playerColor ) );
			m_looseBrick->NotifyPosition(0, m_board.GetWidth() + 2);
			m_looseBrick->Draw( BrickMode::Normal );
			m_ball->Draw( m_board );
		}
		glEnd();
		glPopMatrix();
	}


}
