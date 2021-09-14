#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	// ID refrence for the Vertex Array Object
	GLuint ID;
	// Constractor that generates a VAO ID
	VAO();

	// Links a VBO Attribute to the VAO usingg a certin latout
	void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};

#endif