#if !defined(STATEPLAY_H)
#define STATEPLAY_H

#include "state.h"
#include "main.h"
#include "mesh.h"
#include "ship.h"
#include "proiectile.h"
#include <vector>

class StatePlay : public State {
	GLuint bgSpace;
	GLuint bgHealthbar;
	GLuint bgBoard;
	std::vector<Proiectile*> proiectile;
public:
	StatePlay();
	~StatePlay();
	void execute( Uint32 ticks, Uint8* keystate );
	void addProiectile( Proiectile* proiectil );
protected:
	void activate();
	void deactivate();
private:
	Mesh* ship;
	Ship* nava1;
	Ship* nava2;
};

#endif