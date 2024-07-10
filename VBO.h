#ifndef VBO_CLASS_H
#define VBO_CLASS_H 

#include <glad/glad.h>
#include <vector>

class VBO
{
	public:
		GLuint ID;
		VBO(std::vector<GLfloat>& vertices);

		void Bind();
		void Unbind();
		void Delete();

};

#endif // VBO_CLASS_H
