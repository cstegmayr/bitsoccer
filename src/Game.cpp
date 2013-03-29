#pragma once

#include "Game.h"

namespace bitsoccer
{
	Game::Game()
	{
		m_mixer  =  new MixerRandom();
	}

	void Game::Initialize()
	{
		m_mixer->mix(m_board);
	}

	void Game::Draw()
	{
	}

	Game::~Game()
	{
		delete m_mixer;
	}


}
