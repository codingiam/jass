#if !defined(MATERIAL_H)
#define MATERIAL_H

#include "main.h"

class Material {
	enum  { MAT_AMBIENT = 1, MAT_DIFFUSE = 2, MAT_SPECULAR = 4, MAT_SHINESS = 8, MAT_TEXTURE = 16 };
public:
	Material();
	~Material();
public:
	void loadMaterial(char *filename, char *path = (char *) "./");
	const char * getName() { return name; }
	void useMaterial();
private:
	void processCmdMat(char *cmd, char *params);
private:
	char *path, *filename;
	char name[50];
	
	unsigned short format;
	GLfloat matAmbient[3], matDiffuse[3], matSpecular[3], matShiness;
public:
	GLuint matTexture;
};

#endif