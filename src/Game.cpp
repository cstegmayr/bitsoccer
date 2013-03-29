#pragma once

#include "Game.h"
#include "Renderer.h"

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
		m_ball->SetPosition(m_board.GetWidth()/2, m_board.GetHeight()/2, m_board);
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
