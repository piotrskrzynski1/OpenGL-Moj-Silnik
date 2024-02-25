
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
	GLuint ID;
	VAO();

	void LinkVBO(VBO& VBO, GLuint layout);
	void LinkVBOColor(VBO& VBO, GLuint layout1, GLuint layout2);
	void LinkVBOColorTexture(VBO& VBO, GLuint layout1, GLuint layout2, GLuint layout3);
	void LinkVBOTexture(VBO& VBO, GLuint layout1, GLuint layout2);
	void Bind();
	void Unbind();
	void Delete();
};
#endif