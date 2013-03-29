#pragma once

#include "Game.h"
#include "Renderer.h"

namespace bitsoccer
{
	Game::Game()
	{
	}

	void Game::Initialize()
	{
	}

	void Game::Draw()
	{
		m_board.Draw();
	}

	Game::~Game()
	{
	}
}
