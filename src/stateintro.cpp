#include "stateintro.h"
#include "video.h"
#include "application.h"

const char* introText[] = {
	"  Acest joc este proiectul nostru pentru cursul de grafica.",
	"Sper ca va v-a face placere sa-l jucati si bineintles sa ne",
	"dati o nota pe masura efortului.",
	"  Scopul jocului este sa scapati cu nava intacta din batalie. ",
	" ",
	"  Si acuma urmeaza tastele:",
	"END"
};

StateIntro::StateIntro() {
	bgSpace = 0;
	bgIntro = 0;
	bgAction = 0;

	ticksTitle = 0;
	ticksAction = 0;
	ticksIntroText = 0;
	
	speedTitle = 1 * 1000;
	speedAction = 2 * 1000;
	speedIntroText = 10 * 1000;

	sizeIntroText = 242;
/*
	for(int i = 0; (strcmp(introText[i], "END") != 0) ;i++) {
		sizeIntroText += (Uint32) strlen(introText[i]);
	}
*/

	Video* video = Video::getVideo();
	//std::cout << video->fontTexture << std::endl;

	SDL_Surface* tmp = video->loadTexture( (char *) "data/texturi/introbg.png" );
	video->makeTexture( tmp, bgSpace );
	SDL_FreeSurface( tmp );

	tmp = video->loadTexture( (char *) "data/texturi/title.png" );
	video->makeTexture( tmp, bgIntro );
	SDL_FreeSurface( tmp );

	tmp = video->loadTexture( (char *) "data/texturi/action.png" );
	video->makeTexture( tmp, bgAction );
	SDL_FreeSurface( tmp );

	if (!(bgSpace) || !(bgIntro) || !(bgAction)) {
		throw( std::runtime_error( "Nu am putut crea texturile pentru 'stateintro'." ) );
	}
}

StateIntro::~StateIntro() {
	if (bgSpace) glDeleteTextures( 1, &bgSpace );
	if (bgIntro) glDeleteTextures( 1, &bgSpace );
	if (bgAction) glDeleteTextures( 1, &bgAction );
}

void StateIntro::activate() {
	ticksTitle = 0;
	ticksAction = 0;
	ticksIntroText = 0;
}

void StateIntro::deactivate() {
}

void StateIntro::execute( Uint32 ticks, Uint8 *keystate ) {
	Video* video = Video::getVideo();

	if (ticksTitle == 0) ticksTitle = ticks;
	if (ticksAction == 0) ticksAction = ticks;
	if (ticksIntroText == 0) ticksIntroText = ticks;
	
	float alphaTitle = (float) (ticks - ticksTitle) / (float) speedTitle;
	float blueAction = (float) (ticks - ticksAction) / (float) speedAction;
	float positionText = (float) (ticks - ticksIntroText) / (float) speedIntroText;

	if (alphaTitle >= 1.0f) alphaTitle = 1.0f;
	if (blueAction >= 1.0f) ticksAction += speedAction;
	if (positionText >= 1.0f) positionText = 1.0f;

	Application* app = Application::getApp();

	glClear( GL_COLOR_BUFFER_BIT ); 
	video->init2DScene( app->width, app->height );
	
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	video->drawTexture( 0, 0, app->width, app->height, bgSpace );

	glColor4f( 1.0f, 1.0f, 1.0f, alphaTitle );
	video->drawTexture( 272, 8, 256, 64, bgIntro );

	glColor4f( 1.0f, 1.0f - blueAction, blueAction, 1.0f );
	video->drawTexture( 262, 440, 276, 64, bgAction );

	glColor3f( 1.0f, 1.0f, 1.0f );
	
	Uint32 showTo = (Uint32) (sizeIntroText * positionText);
	Uint32 marime = 0;
	char buffer[100];
	Uint32 shown = 0;
 	for(int i = 0; showTo; i++) {
		if (strcmp(introText[i], "END") == 0) break;
		marime = (int) strlen(introText[i]);
		if (marime > showTo) marime = showTo;
		strncpy( buffer, introText[i], marime);buffer[marime] = 0;
		showTo -= marime;
		video->print( 90, 105 + 20 * i, buffer );
	}

    SDL_GL_SwapWindow( Application::getApp()->window );

	if (keystate[SDL_SCANCODE_SPACE]) app->statePlay->set();
}