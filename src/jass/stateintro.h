#if !defined(STATEINTRO_H)
#define STATEINTRO_H

#include "state.h"
#include "main.h"

class StateIntro : public State {
	GLuint bgSpace;
	GLuint bgIntro;
	GLuint bgAction;
public:
	StateIntro();
	~StateIntro();
	void execute( Uint32 ticks, Uint8* keystate );
protected:
	void activate();
	void deactivate();
private:
	Uint32 ticksTitle;
	Uint32 ticksAction;
	Uint32 ticksIntroText;

	Uint32 speedTitle;
	Uint32 speedAction;
	Uint32 speedIntroText;

	Uint32 sizeIntroText;
};

#endif