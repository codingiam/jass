#if !defined(MESH_H)
#define MESH_H

#include "material.h"

#include <vector>

class Mesh {
public:
	Mesh();
	~Mesh();
	void loadMeshObj(char *filename, char *path = (char *) "./");
	void display();
private:
	void processCmdObj(char *cmd, char *params);
	void loadMaterialObj(char *filename);
	void processFace(char *face);
private:
	char *path, *filename;
	std::vector<Material*> materials;
	std::vector<GLfloat*> verticies;
	std::vector<GLdouble*> tcoords;
	std::vector<GLfloat*> normals;
	GLuint mesh;
};

#endif