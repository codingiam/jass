#include "ship.h"

#include "application.h"
#include "stateplay.h"
#include "proiectile.h"

#include <cmath>

Ship::Ship(GLfloat xpos, GLfloat ypos, Uint32 id, GLfloat angle) {
	shipId = id;
	this->xpos = xpos;
	this->ypos = ypos;
	this->angle = angle;
	accel = 0.0f;
	speed = 0.0f;
	life = 1.0f;
	energy = 1.0f;
	
	lastTimeACC = 0;
	lastTimeMOV = 0;
	lastTimeROT = 0;
	lastTimeSHO = 0;
}

void Ship::update(Uint32 ticks, Uint8 *keystate) {
	if ((ticks - lastTimeACC) > 150) {
		if (keystate[keys[K_UP]]) {
			accel += 0.055f;
			if (accel > 1.0f) accel = 1.0f;
		}

		if (keystate[keys[K_DOWN]]) {
			accel -= 0.055f;
			if (accel < -1.0f) accel = -1.0f;
		}

		if (accel < 0) {
			accel += 0.025f;
			if (accel > 0.0f) accel = 0.0f;
		}
		
		if (accel > 0) {
			accel -= 0.025f;
			if (accel < 0.0f) accel = 0.0f;
		}

		lastTimeACC = ticks;
	}
    
	if ((ticks - lastTimeROT) > 100) {
		if (keystate[keys[K_LEFT]]) {
			angle += 10.0f;
		}
		
		if (keystate[keys[K_RIGHT]]) {
			angle -= 10.0f;
		}

		if (angle > 360.0f) angle -= 360.0f;
		if (angle < 0.0f) angle += 360.0f;

		lastTimeROT = ticks;
	}

	if ((ticks - lastTimeSHO) > 100) {
		if ((keystate[keys[K_SHOOT]]) && (energy >= 0.15f)) {
			Application *app = Application::getApp();
			StatePlay *play = app->statePlay;

			GLfloat amx = 0.0f, amy = 0.0f;

			amy = - cos( 3.141516f * angle / 180 );
			amx = sin( 3.141516f * angle / 180 );

			Proiectile *proiectil = new Proiectile( xpos + amx, ypos + amy, angle, shipId );
			play->addProiectile( proiectil );

			energy -= 0.15f;
		}

		energy += 0.01f;
		if (energy > 1.0f) energy = 1.0f;

		lastTimeSHO = ticks;
	}
	
	Uint32 diff = ticks - lastTimeMOV;

	if (diff > 100) diff = 100;

	GLfloat amx = 0.0f, amy = 0.0f;

	amy = - cos( 3.141516f * angle / 180 );
	amx = sin( 3.141516f * angle / 180 );

	ypos += accel * 0.25f * (diff / 100) * amy;
	xpos += accel * 0.25f * (diff / 100) * amx;

	if (xpos <= -5.8f) xpos = 5.75f;
	if (xpos >= 5.8f) xpos = -5.75f;

	if (ypos <= -4.5f) ypos = 4.45f;
	if (ypos >= 4.5f) ypos = -4.45f;

	if (diff > 100) {

		lastTimeMOV = ticks;
	}
}

void Ship::setkeys( Uint32 keys[]) {
	memcpy( this->keys, keys, sizeof(Uint32) * 6);
}

int pnpoly(int npol, float *xp, float *yp, float x, float y) {
    int i, j, c = 0;
    for (i = 0, j = npol-1; i < npol; j = i++) {
    if ((((yp[i] <= y) && (y < yp[j])) ||
            ((yp[j] <= y) && (y < yp[i]))) &&
        (x < (xp[j] - xp[i]) * (y - yp[i]) / (yp[j] - yp[i]) + xp[i]))
        c = !c;
    }
    return c;
}

bool Ship::colide( GLfloat x, GLfloat y ) {
	GLfloat amc = 0.0f, ams = 0.0f;

	ams = sin( 3.141516f * angle / 180 );
	amc = cos( 3.141516f * angle / 180 );
	
	GLfloat xp[4], yp[4];

	xp[0] = xpos + (-0.40f) * amc - ( 0.55f) * ams;
	yp[0] = ypos + (-0.40f) * ams + ( 0.55f) * amc;

	xp[1] = xpos + ( 0.40f) * amc - ( 0.55f) * ams;
	yp[1] = ypos + ( 0.40f) * ams + ( 0.55f) * amc;

	xp[2] = xpos + ( 0.40f) * amc - (-0.55f) * ams;
	yp[2] = ypos + ( 0.40f) * ams + (-0.55f) * amc;

	xp[3] = xpos + (-0.40f) * amc - (-0.55f) * ams;
	yp[3] = ypos + (-0.40f) * ams + (-0.55f) * amc;


	bool hit = (pnpoly(4, xp, yp, x, y) == 1);
	if (hit) {
		life -= 0.10f;
		std::cout << life << std::endl;
	}

	return hit;
}