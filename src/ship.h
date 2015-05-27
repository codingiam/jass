#if !defined(SHIP_H)
#define SHIP_H

#include "main.h"

class Ship {
	enum { K_UP = 0, K_DOWN, K_LEFT, K_RIGHT, K_SHOOT, K_SHIELD };
	GLfloat angle;
	GLfloat xpos, ypos;
	GLfloat accel, speed;
	GLfloat life;
	GLfloat energy;
	GLuint shipId;
	Uint32 lastTimeACC;
	Uint32 lastTimeMOV;
	Uint32 lastTimeROT;
	Uint32 lastTimeSHO;
	Uint32 keys[6];
public:
	Ship(GLfloat xpos, GLfloat ypos, Uint32 id, GLfloat angle);
	void update(Uint32 ticks, Uint8 *keystate);
	void getPosition(GLfloat &x, GLfloat &y, GLfloat &angle) { x = xpos; y = ypos; angle = this->angle; };
	void setkeys( Uint32 keys[]);
	bool colide( GLfloat x, GLfloat y);
	GLfloat getLife() { return life; };
};

#endif