#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include <stb/stb_image.h>
#include "StateManager.h"

#include "Rectangle.h"
#include "VertexHandler.h"

int main()
{
	glfwInit(); //tells opengl to start up

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //only use core profile

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Truss Simulator", NULL, NULL); //create window statement

	if (window == NULL) //if the window fails to create, end the program
	{
		std::cout << "failed to create window :(" << '\n';
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window); //specify which window is being used

	gladLoadGL(); //load glad API

	glViewport(0,0,WIDTH,HEIGHT); // specify bounds of window

	Shader shaderProgram("default.vert", "default.frag");

	VertexHandler vHandler; //empty constructors don't need the "()" part
	Rectangle rect(100.0f, 100.0f, 20.0f, 20.0f);
	Rectangle rect2(50, 50, 50, 50);
	vHandler.addRectangle(rect);
	vHandler.addRectangle(rect2);

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vHandler.vertices);
	EBO EBO1(vHandler.indices);

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//keep number of channels at 4 
	int width, height, channels;
	unsigned char* pixels = stbi_load("images/download.jpg", &width, &height, &channels, 4);
	
	if (pixels == NULL)
	{
		std::cout << "failed to load image" << "\n";
		glfwTerminate();
	}

	/*GLFWimage image;
	image.width = width;
	image.height = height;
	image.pixels = pixels;

	GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);

	glfwSetCursor(window, cursor);*/

	//methods found in "StateManager.h"
	glfwSetMouseButtonCallback(window, mouse_button_callback); 
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetKeyCallback(window, key_callback);
	

	while (!glfwWindowShouldClose(window)) // main loop
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, vHandler.indices.size() * sizeof(GLuint), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); // double buffers
		glfwPollEvents(); //keep this for basic responsiveness
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window); 
	glfwTerminate();
	return 0;
}


