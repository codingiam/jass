#if !defined(PROIECTILE_H)
#define PROIECTILE_H

#include "main.h"

class Proiectile {
	GLfloat angle;
	Uint32 lastUpdate;
	Uint32 lifetime;
public:
	GLuint owner;
	GLfloat xpos, ypos;
public:
	bool sterge;
	Proiectile( GLfloat xpos, GLfloat ypos, GLfloat angle, GLuint owner );
	void update( Uint32 ticks );
	void getPos( GLfloat &x, GLfloat &y ) { x = xpos; y = ypos; };
};

#endif