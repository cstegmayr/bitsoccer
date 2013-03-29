#pragma once

#include "Game.h"

namespace bitsoccer
{
	Game::Game()
	{
		m_mixer  =  new MixerRandom();
		m_ball   = new Ball();
	}

	void Game::Initialize()
	{
		m_board.Initialize();
		m_mixer->Mix(m_board);
		m_ball->SetPosition(m_board.getWidth()/2,m_board.getHeight()/2,m_board);
	}

	void Game::Draw()
	{
	}

	Game::~Game()
	{
		delete m_mixer;
		delete m_ball;
	}


}
