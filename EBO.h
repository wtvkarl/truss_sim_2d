#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class EBO
{
public:
	GLuint ID;

	std::vector<GLuint> indexData;

	EBO();
	EBO(std::vector<GLuint>& indices);

	void updateIndexData(std::vector<GLuint> newIndexData);
	void Bind();
	void Unbind();
	void Delete();

};


#endif