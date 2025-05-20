#pragma once
#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include "Sprite.h"
#include "GLSProgram.h"
#include "InputManager.h"
#include "Camera2D.h"
#include <vector>
#include "GLTexture.h"
#include <glm/glm.hpp>
using namespace std;
enum class GameState {
	PLAY,EXIT
};
class MainGame
{
private:
	GLTexture _tex1, _tex2, _tex3, _tex4;
	glm::vec2 _pos1, _pos2, _pos3, _pos4;
	int witdh;
	int height;
	InputManager inputManager;
	Camera2D camera2D;
	float time = 0;
	Sprite sprite;
	vector<Sprite*> sprites;
	GLSProgram program;
	SDL_Window* window;
	void init();
	void processInput();
	void initShaders();
public:
	MainGame();
	~MainGame();
	GameState gameState;
	void run();
	void update();
	void draw();
};

