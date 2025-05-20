#include "MainGame.h"
#include <cstdlib>
#include <ctime>
#include "ImageLoader.h"



MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	witdh = 800;
	height = 600;
	gameState = GameState::PLAY;
	init();
	sprites.push_back(new Sprite());
	sprites.back()->init(-1, -1, 1, 1, "Images/lock.png");
	sprites.push_back(new Sprite());
	sprites.back()->init(0, -1, 1, 1, "Images/lock.png");
	//sprite.init(-1, -1, 1, 1,"Images/lock.png");
	update();
}

void MainGame::init()
{
	SDL_Init(SDL_INIT_HAPTIC | SDL_INIT_CAMERA | SDL_INIT_EVENTS);
	window = SDL_CreateWindow("Hola", witdh, height, SDL_WINDOW_OPENGL);

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
	
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.4f, 1.0f, 1.0f);

	_tex1 = ImageLoader::loadPNG("Images/img1.png");
	_tex2 = ImageLoader::loadPNG("Images/img2.png");
	_tex3 = ImageLoader::loadPNG("Images/img3.png");
	_tex4 = ImageLoader::loadPNG("Images/img4.png");

	_pos1 = glm::vec2(650,450);
	_pos2 = glm::vec2(20,450);
	_pos3 = glm::vec2(680,50);
	_pos4 = glm::vec2(50,50);
	initShaders();
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_EVENT_MOUSE_MOTION:
			inputManager.setMouseCoords(event.motion.x, event.motion.y);
			//cout << "posicion x " << event.motion.x << " posicion y " 
				//			<< event.motion.y << endl;
			break;
		case SDL_EVENT_KEY_DOWN:
			inputManager.pressKey(event.key.key);
			break;
		case SDL_EVENT_KEY_UP:
			inputManager.releaseKey(event.key.key);
			break;
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();
}

void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		processInput();
		draw();
	}
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	time += 0.02;
	program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	GLuint textureLocation = program.getUniformLocation("myImage");
	glUniform1i(textureLocation, 0);
	for (size_t i = 0; i < sprites.size(); i++)
	{
		sprites[i]->draw();
	}
	program.unuse();
	SDL_GL_SwapWindow(window);
}
