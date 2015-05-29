#if !defined(APPLICATION_H)
#define APPLICATION_H

#include "state.h"
#include "stateintro.h"
#include "stateplay.h"
#include "main.h"

class Application {
	Application();
	Application(Application &) { }
    Application & operator= (Application &);
public:
	static Application* getApp() {
		static Application app;

		return &app;
	}
	
	void run();
	void init();
private:
	void initSDL();
	void initFMOD();
//	FMUSIC_MODULE* intromusic;

public:
	~Application();
	enum { width = 800, height = 600, full = 0 };

public:
	StateIntro* stateIntro;
	StatePlay* statePlay;
    SDL_Window *window;
    SDL_GLContext gl_context;
};

#endif