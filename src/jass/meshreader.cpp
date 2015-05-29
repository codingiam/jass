#include "meshreader.h"

#include <string>
#include <fstream>

MeshReader::MeshReader( char *filename, char* path ) {
	std::string openfile = path;
	openfile += filename;

	fp = fopen( openfile.c_str(), "r" );
}

MeshReader::~MeshReader( ) {
	if (fp) fclose( fp );
}