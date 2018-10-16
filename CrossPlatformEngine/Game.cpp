#include "stdafx.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game() {
	delete[] gameObjects;
	delete[] meshes;
}

void Game::Init()
{
}

void Game::Draw()
{
	renderer->DrawQuad();

}
