#include "application.h"

#include "video.h"

Application::Application() {
	std::cout << "Clasa aplicatie a fost creata ..." << std::endl;
	
	stateIntro = NULL;
	statePlay = NULL;
//	intromusic = NULL;
}

void Application::init() {
	initSDL();
//	initFMOD();
}

void Application::initSDL() {
	if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0) {
		char mesaj[100]; sprintf( mesaj, "Nu am putut initializa SDL: %s", SDL_GetError() );
		throw( std::runtime_error(mesaj) );
	}

    SDL_ShowCursor( SDL_DISABLE );

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 6 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); 
	
    Uint32 video_flags = SDL_WINDOW_OPENGL; // SDL_OPENGLBLIT | SDL_HWSURFACE | full;

	if (( this->window = SDL_CreateWindow( "J.A.S.S - Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, video_flags )) == NULL ) {
		throw( std::runtime_error( "Nu am putut initializa modul video !" ) );
	}
    
    gl_context = SDL_GL_CreateContext( window );

	std::cout << "SDL a fost initailizat cu succes si urmeaza informatii video: " << std::endl;

	// std::cout << " Ecran BPP   : " << SDL_GetVideoSurface()->format->BitsPerPixel << std::endl;
	// std::cout << " Producator  : " << glGetString( GL_VENDOR ) << std::endl;
	// std::cout << " Renderer    : " << glGetString( GL_RENDERER ) << std::endl;
	// std::cout << " Versiune    : " << glGetString( GL_VERSION ) << std::endl;
	// std::cout << " Extensii    : " << glGetString( GL_EXTENSIONS ) << std::endl;

	int valoare;
	
	SDL_GL_GetAttribute( SDL_GL_RED_SIZE, &valoare );
	std::cout << " Componenta rosie " << valoare << " biti" << std::endl;

	SDL_GL_GetAttribute( SDL_GL_GREEN_SIZE, &valoare );
	std::cout << " Componenta verde " << valoare << " biti" << std::endl;

	SDL_GL_GetAttribute( SDL_GL_BLUE_SIZE, &valoare );
	std::cout << " Componenta albastra " << valoare << " biti" << std::endl;

	// SDL_WM_SetCaption( "J.A.S.S - Project", "data\\iconita\\jass.ico" );

	glShadeModel( GL_SMOOTH ); // GL_FLAT

	glClearColor( 0.0, 0.0, 0.0, 0.0 );

	glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );

	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );/* GL_PERSPECTIVE_CORRECTION_HINT ||  GL_LINE_SMOOTH_HINT */
	
	//glPolygonMode( GL_BACK , GL_LINE );

	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );
	
	glEnable( GL_TEXTURE_2D );

	glViewport( 0, 0, width, height );

	Video* video = Video::getVideo();
	video->initFont();

	std::cout << "SDL a fost initializat." << std::endl;
}

//void Application::initFMOD() {
//    if (FSOUND_GetVersion() < FMOD_VERSION) {
//		char mesaj[100]; sprintf( mesaj, "Veriune FMOD inavlida, ar trebui sa fie : %.02f", FMOD_VERSION );
//		throw( std::logic_error( mesaj ) );
//    }
//
//	bool retval = (FSOUND_SetOutput( -1 ) == TRUE);
//	retval &= (FSOUND_SetDriver( 0 ) == TRUE);
//	retval &= (FSOUND_Init(44100, 32, FSOUND_INIT_USEDEFAULTMIDISYNTH) == TRUE);
//
//	if (!retval) {
//		throw( std::runtime_error( "Nu am putut initializa FMOD !" ) );
//	}
//
//	intromusic = FMUSIC_LoadSong( "data\\muzica\\intro.s3m" );
//	if (!intromusic) {
//		throw( std::runtime_error( "Nu am putut incarca data\\muzica\\intro.s3m" ) );
//	}
//	std::cout << "data\\muzica\\intro.s3m a fost incarcat" << std::endl;
//	
//	FMUSIC_PlaySong( intromusic );
//
//	std::cout << "FMOD a fost initializat." << std::endl;
//}

void Application::run() {
	Uint32 miliseconds = 0;
	Uint8 *keystate = NULL;
	State *state = NULL;

	SDL_Event event;

	stateIntro = new StateIntro();
	statePlay = new StatePlay();

	stateIntro->set();
	State::update();

	while( (state = State::get()) ) {
		miliseconds = SDL_GetTicks();

		SDL_PumpEvents();
		keystate = const_cast<Uint8 *>(SDL_GetKeyboardState( NULL ));

		state->execute( miliseconds, keystate );

		if (keystate[SDL_SCANCODE_F10]) State::set( NULL );

		while( SDL_PollEvent( &event ) ) {
			if (event.type == SDL_QUIT) State::set( NULL );
		}

		State::update();
	}
}

Application::~Application() {
	if (statePlay) delete statePlay;
	if (stateIntro) delete stateIntro;
	
//	if (intromusic) {
//		FMUSIC_StopAllSongs();
//		FMUSIC_FreeSong( intromusic );
//	}
//
//	FSOUND_Close();
    
    if (gl_context) {
        SDL_GL_DeleteContext(gl_context);
    }
    
    SDL_DestroyWindow(window);
    
	SDL_Quit();
		
	std::cout << "Aplicatia a fost incheiata." << std::endl;
}