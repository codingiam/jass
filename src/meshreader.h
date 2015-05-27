#if !defined(MESHREADER_H)
#define MESHREADER_H

#include <cstdio>

class MeshReader {
	FILE* fp;
public:
	MeshReader( char* filename, char* path = (char *) "./" );
	~MeshReader( );
};

#endif