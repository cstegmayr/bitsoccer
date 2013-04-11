#include "Game.h"
#include "Renderer.h"

#include <stdio.h>
#include <stdlib.h>

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
		m_ball->SetPosition( m_board.GetHeight()/2,m_board.GetWidth()/2, m_board);
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
#if 0
		{
			static int frame = 0;
			static double total_time = 0.0;
			total_time += dt;
			++frame;

			double fps = frame / total_time;
			Vec3 color(1.0f, 1.0f, 1.0f);
			Renderer::rprintf(0, 8, color, "%.1f\n", fps);

			if (total_time > 1.0)
			{
				frame = 1;
				total_time = dt;
			}
		}
#endif

		// If brick is pressed => Rotate it
		if (m_looseBrick->IsPressed())
		{
			printf("Pressed the loose brick\n");
			m_looseBrick->RotateCW();
		}

		// Update state machine
		switch (m_state)
		{
		case PlayState::PlayerRedPush:
		case PlayState::PlayerBluePush:
			UpdatePushState();
			break;
		case PlayState::PlayerRedMove:
		case PlayState::PlayerBlueMove:
			UpdateMoveState();
			break;
		default:
			printf("Player state not implemented\n");
			abort();
		}
	}

	/**
	returns Color::Green if the game is in push state. Othrewise returns color of player that is supposed to move the ball.
	*/
	Color::Type Game::GetMovePlayerColor( const bool includePushState )
	{
		Color::Type playerColor = Color::Green;
		if ( m_state == PlayState::PlayerRedMove || ( includePushState && m_state == PlayState::PlayerRedPush ) )
			playerColor = Color::Red;
		else if ( m_state == PlayState::PlayerBlueMove || ( includePushState && m_state == PlayState::PlayerBluePush ) )
			playerColor = Color::Blue;
		return playerColor;
	}

	void Game::Draw()
	{
			
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glBegin(GL_TRIANGLES);
		{
			Color::Type playerColor = GetMovePlayerColor(false);
			MoveDirection::Type moveDir = (MoveDirection::Type)m_ball->GetMovableColorDirections( m_board, playerColor );
			
			playerColor = GetMovePlayerColor(true);
			m_board.Draw(m_ball, moveDir, playerColor );
			m_looseBrick->NotifyPosition(0, m_board.GetWidth() + 2);
			
			m_looseBrick->Draw( BrickMode::Normal, playerColor );
			m_ball->Draw( m_board );
		}
		glEnd();
		glPopMatrix();
	}


	//////////////////////////////////////////////////////////////////////////////////////
	// PRIVATE METHODS 
	//////////////////////////////////////////////////////////////////////////////////////

	void Game::UpdatePushState()
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

			}
			else
			{
				for ( u32 col = 0; col < m_board.GetWidth(); ++col )
				{
					bool doBreak = false;
					for ( u32 row = 0; row < m_board.GetHeight(); ++row )
					{
						Brick* b = m_board.GetBrick(row,col);
						if ( b->IsPressed() ) 
						{
							foundSurface = 1; // notify that the player rotates a brick instead of pushing the board
							b->RotateCW();
						}
					}
					if ( doBreak )
						break;
				}
			}

			if ( foundSurface >= 0 )
			{				// change play state
				if ( m_state == PlayState::PlayerRedPush )
				{
					m_state = PlayState::PlayerRedMove;
					u32 movableDirections = m_ball->GetMovableColorDirections(m_board, Color::Red);
					if ( movableDirections == 0 )
					{
						//There is nowhere to go for player red
						m_state = PlayState::PlayerBluePush;
					}
				}
				else if ( m_state == PlayState::PlayerBluePush )
				{
					m_state = PlayState::PlayerBlueMove;
					u32 movableDirections = m_ball->GetMovableColorDirections(m_board, Color::Blue);
					if ( movableDirections == 0 )
					{
						//There is nowhere to go for player blue
						m_state = PlayState::PlayerRedPush;
					}
				}
			}
	}

	void Game::UpdateMoveState()
	{
		for ( u32 col = 0; col < m_board.GetWidth(); ++col )
			{
				bool doBreak = false;
				for ( u32 row = 0; row < m_board.GetHeight(); ++row )
				{
					Brick* b = m_board.GetBrick(row,col);
					if ( b->IsPressed() ) 
					{
						Color::Type playerColor = m_state == PlayState::PlayerRedMove ? Color::Red : Color::Blue;
						//u32 movableDirections = m_ball->GetMovableColorDirections(m_board, playerColor);
						//u32 brickType = m_board.GetBrickType(m_ball, (MoveDirection::Type)movableDirections, row, col);

						if (m_board.GetMovePathForColor(m_ball, row, col, playerColor)) //if ( brickType & BrickMode::PossibleMove )
						{
							m_ball->SetPosition(row,col,m_board);
							if ( playerColor == Color::Red )
								m_state = PlayState::PlayerBluePush;
							else
								m_state = PlayState::PlayerRedPush;
							doBreak = true;
							break;
						}
						
					}
				}
				if ( doBreak )
					break;
			}
	}

}
