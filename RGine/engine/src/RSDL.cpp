/*
 * RSDL.cpp
 *
 *  Created on: Jan 05, 2011
 *      Author: Ricardo Bustamante de Queiroz
 *      e-mail: ricardobqueiroz@gmail.com
 *
 *  @section DESCRIPTION
 *  RSDL is the class that interacts with directly with sdl
 */

#include "RSDL.h"

#include <list>
using namespace std;

RSDL::RSDL() {
	width = 560;
	height = 400;
	bpp = 32;
	quit = false;
}

RSDL::~RSDL() {
}

/*
 * Init all subsystems
 */
bool RSDL::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetVideoMode(width, height, bpp, SDL_OPENGL | SDL_RESIZABLE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_WM_SetCaption("Ricardo's Engine!", NULL);
	opengl_init();
	atexit(SDL_Quit);
	return (true);
}

void RSDL::render_begin() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void RSDL::render_end() {
	SDL_GL_SwapBuffers();
}

//Set OpenGL state
bool RSDL::opengl_init() {
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	opengl_resize();
	return (true);
}

//Set OpenGL Projection Matrix
void RSDL::opengl_resize() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	glOrtho(0.0, width, 0.0, height, -2000, 1000);
	//glFrustum (-width/20,width/20, -height/20,height/20, 50,6000);
	glMatrixMode(GL_TEXTURE);
	//texture
	glMatrixMode(GL_MODELVIEW);
}

//Init the timer
void RSDL::timer_init() {
	timer_startTicks = 0;
	timer_pausedTicks = 0;
	timer_paused = false;
	timer_started = false;
}

//Start the timer
void RSDL::timer_start() {
	timer_started = true;
	timer_paused = false;
	timer_startTicks = SDL_GetTicks();
}

//Stop the timer
void RSDL::timer_stop() {
	timer_started = false;
	timer_paused = false;
}

//Pause the timer
void RSDL::timer_pause() {
	if ((timer_started == true) && (timer_paused == false)) {
		timer_paused = true;
		timer_pausedTicks = SDL_GetTicks() - timer_startTicks;
	}
}

//Unpause the timer
void RSDL::timer_unpause() {
	if (timer_paused == true) {
		timer_paused = false;
		timer_startTicks = SDL_GetTicks() - timer_pausedTicks;
		timer_pausedTicks = 0;
	}
}

//Get the number of ticks passed since start
int RSDL::timer_getTicks() {
	if (timer_started == true) {
		if (timer_paused == true) {
			return (timer_pausedTicks);
		} else {
			return (SDL_GetTicks() - timer_startTicks);
		}
	}
	return (0);
}

//Delay if frame ended up too early
void RSDL::timer_delay() {
	if (timer_getTicks() < 1000 / fps) {
		SDL_Delay((1000 / fps) - timer_getTicks());
	}
}

//Tells the game if sdl has finished it's operation or issued a quit command
bool RSDL::finished() {
	return (quit);
}

MouseStruct RSDL::mouse() {
	return (mouse_);
}

KeyStruct RSDL::key(int kID) {
	return (key_[kID]);
}

void RSDL::key_reset() {
	list<int>::iterator it;
	for (it = key_mod.begin(); it != key_mod.end(); it++) {
		key_[(*it)].up = false;
		key_[(*it)].down = false;
	}
	key_mod.clear();
}

void RSDL::mouse_reset() {
	mouse_.left.up = false;
	mouse_.left.down = false;

	mouse_.right.up = false;
	mouse_.right.down = false;

	mouse_.middle.up = false;
	mouse_.middle.down = false;

	mouse_.wheeldown.up = false;
	mouse_.wheeldown.down = false;

	mouse_.wheelup.up = false;
	mouse_.wheelup.down = false;

	mouse_.speed.set(0, 0);
}

void RSDL::input() {
	key_reset();
	//resetar estado do mouse
	mouse_reset();
	//agora detecta possiveis teclas
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEMOTION:
			mouse_.speed.set(event.button.x - mouse_.position.x(),
					event.button.y - mouse_.position.y());

			mouse_.position.set(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN: {
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				mouse_.left.isDown = true;
				mouse_.left.down = true;
				break;
			case SDL_BUTTON_RIGHT:
				mouse_.right.isDown = true;
				mouse_.right.down = true;
				break;
			case SDL_BUTTON_MIDDLE:
				mouse_.middle.isDown = true;
				mouse_.middle.down = true;
				break;
			case SDL_BUTTON_WHEELUP:
				mouse_.wheelup.isDown = true;
				mouse_.wheelup.down = true;
				break;
			case SDL_BUTTON_WHEELDOWN:
				mouse_.wheeldown.isDown = true;
				mouse_.wheeldown.down = true;
				break;
			default:
				break;
			}
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				mouse_.left.isDown = false;
				mouse_.left.up = true;
				break;
			case SDL_BUTTON_RIGHT:
				mouse_.right.isDown = false;
				mouse_.right.up = true;
				break;
			case SDL_BUTTON_MIDDLE:
				mouse_.middle.isDown = false;
				mouse_.middle.up = true;
				break;
			case SDL_BUTTON_WHEELUP:
				mouse_.wheelup.isDown = false;
				mouse_.wheelup.up = true;
				break;
			case SDL_BUTTON_WHEELDOWN:
				mouse_.wheeldown.isDown = false;
				mouse_.wheeldown.up = true;
				break;
			default:
				break;
			}
			break;
		}
		case SDL_KEYDOWN:
			key_[event.key.keysym.sym].down = true;
			key_[event.key.keysym.sym].isDown = true;
			key_mod.push_back(event.key.keysym.sym);
			break;

		case SDL_KEYUP:
			key_[event.key.keysym.sym].up = true;
			key_[event.key.keysym.sym].isDown = false;
			key_mod.push_back(event.key.keysym.sym);
			break;
		default:
			break;
		}
	}
}

int RSDL::getHeight() {
	return (height);
}

int RSDL::getWidth() {
	return (width);
}
