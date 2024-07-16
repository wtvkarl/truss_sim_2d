#ifndef VBO_CLASS_H
#define VBO_CLASS_H 

#include <glad/glad.h>
#include <vector>

class VBO
{
	public:
		GLuint ID;

		std::vector <GLfloat> vertexData;

		VBO();
		VBO(std::vector<GLfloat> vertices);

		void updateVertexData(std::vector<GLfloat> newData);
		void Bind();
		void Unbind();
		void Delete();

};

#endif // VBO_CLASS_H
