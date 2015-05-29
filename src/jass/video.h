#if !defined(VIDEO_H)
#define VIDEO_H

#include "main.h"

typedef GLint vertex2i[2];
typedef GLfloat vertex3f[3];

class Video {
	Video();
	Video(Video &) { }
    Video & operator= (Video &);
public:
	static Video * getVideo() {
		static Video video;

		return &video;
	}
public:
	void init2DScene( int width, int height );
	void init3DScene( int width, int height );
	void initFont();
	void print( GLint x, GLint y, char *string, int set = 1 );
	SDL_Surface* loadTexture( char* name );
	void makeTexture( SDL_Surface* surface, GLuint &texture );
	void drawTexture(int x, int y, int w, int h, GLuint texture, GLfloat yamount = 0.0f );
	void getNormal(vertex3f v0, vertex3f v1, vertex3f v2, vertex3f &normal);
public:
	~Video();
public:
	GLuint fontTexture;
	GLuint base;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	enum { rmask = 0xff000000, gmask = 0x00ff0000, bmask = 0x0000ff00, amask = 0x000000ff };
#else
	enum { rmask = 0x000000ff, gmask = 0x0000ff00, bmask = 0x00ff0000, amask = 0xff000000 };
#endif
};

#endif