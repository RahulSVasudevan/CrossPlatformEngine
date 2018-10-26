#include "stdafx.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game() {
	//Necessary?
	gameObjects.clear();
	meshes.clear();
}

void Game::Init()
{
}

void Game::Draw()
{
	renderer->DrawQuad();

}
