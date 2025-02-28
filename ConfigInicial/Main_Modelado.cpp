/*
Diego Adri�n Del Razo S�nchez
26 de febrero de 2025
Pr�ctica 4
319114939
*/



#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado geometrico Diego Del Razo", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificaci�n de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {
		//Parte Blanca (cuerpo)
		-0.5f, -0.5f, 0.5f, 255.0f, 255.0f,255.0f,//Front
		0.5f, -0.5f, 0.5f,  255.0f, 255.0f,255.0f,
		0.5f,  0.5f, 0.5f,  255.0f, 255.0f,255.0f,
		0.5f,  0.5f, 0.5f,  255.0f, 255.0f,255.0f,
		-0.5f,  0.5f, 0.5f, 255.0f, 255.0f,255.0f,
		-0.5f, -0.5f, 0.5f, 255.0f, 255.0f,255.0f,
		
	    -0.5f, -0.5f,-0.5f, 255.0f, 255.0f,255.0f,//Back
		 0.5f, -0.5f,-0.5f, 255.0f, 255.0f,255.0f,
		 0.5f,  0.5f,-0.5f, 255.0f, 255.0f,255.0f,
		 0.5f,  0.5f,-0.5f, 255.0f, 255.0f,255.0f,
	    -0.5f,  0.5f,-0.5f, 255.0f, 255.0f,255.0f,
	    -0.5f, -0.5f,-0.5f, 255.0f, 255.0f,255.0f,
		
		 0.5f, -0.5f,  0.5f,  255.0f, 255.0f,255.0f,
		 0.5f, -0.5f, -0.5f,  255.0f, 255.0f,255.0f,
		 0.5f,  0.5f, -0.5f,  255.0f, 255.0f,255.0f,
		 0.5f,  0.5f, -0.5f,  255.0f, 255.0f,255.0f,
		 0.5f,  0.5f,  0.5f,  255.0f, 255.0f,255.0f,
		 0.5f,  -0.5f, 0.5f, 255.0f, 255.0f,255.0f,
      
		-0.5f,  0.5f,  0.5f,  255.0f, 255.0f,255.0f,
		-0.5f,  0.5f, -0.5f,  255.0f, 255.0f,255.0f,
		-0.5f, -0.5f, -0.5f,  255.0f, 255.0f,255.0f,
		-0.5f, -0.5f, -0.5f,  255.0f, 255.0f,255.0f,
		-0.5f, -0.5f,  0.5f,  255.0f, 255.0f,255.0f,
		-0.5f,  0.5f,  0.5f,  255.0f, 255.0f,255.0f,
		
		-0.5f, -0.5f, -0.5f, 255.0f, 255.0f,255.0f,
		0.5f, -0.5f, -0.5f,  255.0f, 255.0f,255.0f,
		0.5f, -0.5f,  0.5f,  255.0f, 255.0f,255.0f,
		0.5f, -0.5f,  0.5f,  255.0f, 255.0f,255.0f,
		-0.5f, -0.5f,  0.5f, 255.0f, 255.0f,255.0f,
		-0.5f, -0.5f, -0.5f, 255.0f, 255.0f,255.0f,
		
		-0.5f,  0.5f, -0.5f, 255.0f, 255.0f,255.0f,
		0.5f,  0.5f, -0.5f,  255.0f, 255.0f,255.0f,
		0.5f,  0.5f,  0.5f,  255.0f, 255.0f,255.0f,
		0.5f,  0.5f,  0.5f,  255.0f, 255.0f,255.0f,
		-0.5f,  0.5f,  0.5f, 255.0f, 255.0f,255.0f,
		-0.5f,  0.5f, -0.5f, 255.0f, 255.0f,255.0f,


		//Parte morada (cabello)
		-0.5f, -0.5f, 0.5f, 0.8f, 0.6f,1.0f,//Front
		0.5f, -0.5f, 0.5f,  0.8f, 0.6f,1.0f,
		0.5f,  0.5f, 0.5f,  0.8f, 0.6f,1.0f,
		0.5f,  0.5f, 0.5f,  0.8f, 0.6f,1.0f,
		-0.5f,  0.5f, 0.5f, 0.8f, 0.6f,1.0f,
		-0.5f, -0.5f, 0.5f, 0.8f, 0.6f,1.0f,

		-0.5f, -0.5f,-0.5f, 0.8f, 0.6f,1.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.8f, 0.6f,1.0f,
		 0.5f,  0.5f,-0.5f, 0.8f, 0.6f,1.0f,
		 0.5f,  0.5f,-0.5f, 0.8f, 0.6f,1.0f,
		-0.5f,  0.5f,-0.5f, 0.8f, 0.6f,1.0f,
		-0.5f, -0.5f,-0.5f, 0.8f, 0.6f,1.0f,

		 0.5f, -0.5f,  0.5f,  0.8f, 0.6f,1.0f,
		 0.5f, -0.5f, -0.5f,  0.8f, 0.6f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.8f, 0.6f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.8f, 0.6f,1.0f,
		 0.5f,  0.5f,  0.5f,  0.8f, 0.6f,1.0f,
		 0.5f,  -0.5f, 0.5f, 0.8f, 0.6f,1.0f,

		-0.5f,  0.5f,  0.5f,  0.8f, 0.6f,1.0f,
		-0.5f,  0.5f, -0.5f,  0.8f, 0.6f,1.0f,
		-0.5f, -0.5f, -0.5f,  0.8f, 0.6f,1.0f,
		-0.5f, -0.5f, -0.5f,  0.8f, 0.6f,1.0f,
		-0.5f, -0.5f,  0.5f,  0.8f, 0.6f,1.0f,
		-0.5f,  0.5f,  0.5f,  0.8f, 0.6f,1.0f,

		-0.5f, -0.5f, -0.5f, 0.8f, 0.6f,1.0f,
		0.5f, -0.5f, -0.5f,  0.8f, 0.6f,1.0f,
		0.5f, -0.5f,  0.5f,  0.8f, 0.6f,1.0f,
		0.5f, -0.5f,  0.5f,  0.8f, 0.6f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.8f, 0.6f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.8f, 0.6f,1.0f,

		-0.5f,  0.5f, -0.5f, 0.8f, 0.6f,1.0f,
		0.5f,  0.5f, -0.5f,  0.8f, 0.6f,1.0f,
		0.5f,  0.5f,  0.5f,  0.8f, 0.6f,1.0f,
		0.5f,  0.5f,  0.5f,  0.8f, 0.6f,1.0f,
		-0.5f,  0.5f,  0.5f, 0.8f, 0.6f,1.0f,
		-0.5f,  0.5f, -0.5f, 0.8f, 0.6f,1.0f,

		//Parte morada claro (cabello)
		-0.5f, -0.5f, 0.5f, 0.95f, 0.85f,1.0f,//Front
		0.5f, -0.5f, 0.5f,  0.95f, 0.85f,1.0f,
		0.5f,  0.5f, 0.5f,  0.95f, 0.85f,1.0f,
		0.5f,  0.5f, 0.5f,  0.95f, 0.85f,1.0f,
		-0.5f,  0.5f, 0.5f, 0.95f, 0.85f,1.0f,
		-0.5f, -0.5f, 0.5f, 0.95f, 0.85f,1.0f,

		-0.5f, -0.5f,-0.5f, 0.95f, 0.85f,1.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.95f, 0.85f,1.0f,
		 0.5f,  0.5f,-0.5f, 0.95f, 0.85f,1.0f,
		 0.5f,  0.5f,-0.5f, 0.95f, 0.85f,1.0f,
		-0.5f,  0.5f,-0.5f, 0.95f, 0.85f,1.0f,
		-0.5f, -0.5f,-0.5f, 0.95f, 0.85f,1.0f,

		 0.5f, -0.5f,  0.5f, 0.95f, 0.85f,1.0f,
		 0.5f, -0.5f, -0.5f, 0.95f, 0.85f,1.0f,
		 0.5f,  0.5f, -0.5f, 0.95f, 0.85f,1.0f,
		 0.5f,  0.5f, -0.5f, 0.95f, 0.85f,1.0f,
		 0.5f,  0.5f,  0.5f, 0.95f, 0.85f,1.0f,
		 0.5f,  -0.5f, 0.5f, 0.95f, 0.85f,1.0f,

		-0.5f,  0.5f,  0.5f, 0.95f, 0.85f,1.0f,
		-0.5f,  0.5f, -0.5f, 0.95f, 0.85f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.95f, 0.85f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.95f, 0.85f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.95f, 0.85f,1.0f,
		-0.5f,  0.5f,  0.5f, 0.95f, 0.85f,1.0f,

		-0.5f, -0.5f, -0.5f, 0.95f, 0.85f,1.0f,
		0.5f, -0.5f, -0.5f, 0.95f, 0.85f,1.0f,
		0.5f, -0.5f,  0.5f, 0.95f, 0.85f,1.0f,
		0.5f, -0.5f,  0.5f, 0.95f, 0.85f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.95f, 0.85f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.95f, 0.85f,1.0f,

		-0.5f,  0.5f, -0.5f, 0.95f, 0.85f,1.0f,
		0.5f,  0.5f, -0.5f, 0.95f, 0.85f,1.0f,
		0.5f,  0.5f,  0.5f, 0.95f, 0.85f,1.0f,
		0.5f,  0.5f,  0.5f, 0.95f, 0.85f,1.0f,
		-0.5f,  0.5f,  0.5f, 0.95f, 0.85f,1.0f,
		-0.5f,  0.5f, -0.5f, 0.95f, 0.85f,1.0f,

		//Color hueso (cuerno)
			-0.5f, -0.5f, 0.5f, 0.96f, 0.91f, 0.76f,//Front
			0.5f, -0.5f, 0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, 0.5f, 0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, 0.5f, 0.5f, 0.96f, 0.91f, 0.76f,
			-0.5f, 0.5f, 0.5f, 0.96f, 0.91f, 0.76f,
			-0.5f, -0.5f, 0.5f, 0.96f, 0.91f, 0.76f,

			-0.5f, -0.5f, -0.5f, 0.96f, 0.91f, 0.76f,//Back
			0.5f, -0.5f, -0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, 0.5f, -0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, 0.5f, -0.5f, 0.96f, 0.91f, 0.76f,
			-0.5f, 0.5f, -0.5f, 0.96f, 0.91f, 0.76f,
			-0.5f, -0.5f, -0.5f, 0.96f, 0.91f, 0.76f,

			0.5f, -0.5f, 0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, -0.5f, -0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, 0.5f, -0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, 0.5f, -0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, 0.5f, 0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, -0.5f, 0.5f, 0.96f, 0.91f, 0.76f,

			-0.5f, 0.5f, 0.5f, 0.96f, 0.91f, 0.76f,
			-0.5f, 0.5f, -0.5f, 0.96f, 0.91f, 0.76f,
			-0.5f, -0.5f, -0.5f, 0.96f, 0.91f, 0.76f,
			-0.5f, -0.5f, -0.5f, 0.96f, 0.91f, 0.76f,
			-0.5f, -0.5f, 0.5f, 0.96f, 0.91f, 0.76f,
			-0.5f, 0.5f, 0.5f, 0.96f, 0.91f, 0.76f,

			-0.5f, -0.5f, -0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, -0.5f, -0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, -0.5f, 0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, -0.5f, 0.5f, 0.96f, 0.91f, 0.76f,
			-0.5f, -0.5f, 0.5f, 0.96f, 0.91f, 0.76f,
			-0.5f, -0.5f, -0.5f, 0.96f, 0.91f, 0.76f,

			-0.5f, 0.5f, -0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, 0.5f, -0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, 0.5f, 0.5f, 0.96f, 0.91f, 0.76f,
			0.5f, 0.5f, 0.5f, 0.96f, 0.91f, 0.76f,
			-0.5f, 0.5f, 0.5f, 0.96f, 0.91f, 0.76f,
			-0.5f, 0.5f, -0.5f, 0.96f, 0.91f, 0.76f,

			//Color durazno (nariz y patas)
			-0.5f, -0.5f, 0.5f, 0.98f, 0.72f, 0.68f,//Front
			0.5f, -0.5f, 0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, 0.5f, 0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, 0.5f, 0.5f, 0.98f, 0.72f, 0.68f,
			-0.5f, 0.5f, 0.5f, 0.98f, 0.72f, 0.68f,
			-0.5f, -0.5f, 0.5f, 0.98f, 0.72f, 0.68f,

			-0.5f, -0.5f, -0.5f, 0.98f, 0.72f, 0.68f,//Back
			0.5f, -0.5f, -0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, 0.5f, -0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, 0.5f, -0.5f, 0.98f, 0.72f, 0.68f,
			-0.5f, 0.5f, -0.5f, 0.98f, 0.72f, 0.68f,
			-0.5f, -0.5f, -0.5f, 0.98f, 0.72f, 0.68f,

			0.5f, -0.5f, 0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, -0.5f, -0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, 0.5f, -0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, 0.5f, -0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, 0.5f, 0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, -0.5f, 0.5f, 0.98f, 0.72f, 0.68f,

			-0.5f, 0.5f, 0.5f, 0.98f, 0.72f, 0.68f,
			-0.5f, 0.5f, -0.5f, 0.98f, 0.72f, 0.68f,
			-0.5f, -0.5f, -0.5f, 0.98f, 0.72f, 0.68f,
			-0.5f, -0.5f, -0.5f, 0.98f, 0.72f, 0.68f,
			-0.5f, -0.5f, 0.5f, 0.98f, 0.72f, 0.68f,
			-0.5f, 0.5f, 0.5f, 0.98f, 0.72f, 0.68f,

			-0.5f, -0.5f, -0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, -0.5f, -0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, -0.5f, 0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, -0.5f, 0.5f, 0.98f, 0.72f, 0.68f,
			-0.5f, -0.5f, 0.5f, 0.98f, 0.72f, 0.68f,
			-0.5f, -0.5f, -0.5f, 0.98f, 0.72f, 0.68f,

			-0.5f, 0.5f, -0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, 0.5f, -0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, 0.5f, 0.5f, 0.98f, 0.72f, 0.68f,
			0.5f, 0.5f, 0.5f, 0.98f, 0.72f, 0.68f,
			-0.5f, 0.5f, 0.5f, 0.98f, 0.72f, 0.68f,
			-0.5f, 0.5f, -0.5f, 0.98f, 0.72f, 0.68f,

			//Color durazno obscuro (fosas nasales)
			-0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,//Front
			0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,

			-0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,//Back
			0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,

			0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,

			-0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,

			-0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,

			-0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,

			//Color durazno obscuro (fosas nasales)
			-0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,//Front
			0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,

			-0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,//Back
			0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,

			0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,

			-0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,

			-0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, -0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, -0.5f, -0.5f, 0.80f, 0.45f, 0.35f,

			-0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.35f,
			-0.5f, 0.5f, -0.5f, 0.80f, 0.45f, 0.35f,

			//Color turquesa (contorno)
			-0.5f, -0.5f, 0.5f, 0.0f, 0.8f, 0.75f,//Front
			0.5f, -0.5f, 0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, 0.5f, 0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, 0.5f, 0.5f, 0.0f, 0.8f, 0.75f,
			-0.5f, 0.5f, 0.5f, 0.0f, 0.8f, 0.75f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.8f, 0.75f,

			-0.5f, -0.5f, -0.5f, 0.0f, 0.8f, 0.75f,//Back
			0.5f, -0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
			-0.5f, 0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.8f, 0.75f,

			0.5f, -0.5f, 0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, -0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, 0.5f, 0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, -0.5f, 0.5f, 0.0f, 0.8f, 0.75f,

			-0.5f, 0.5f, 0.5f, 0.0f, 0.8f, 0.75f,
			-0.5f, 0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.8f, 0.75f,
			-0.5f, 0.5f, 0.5f, 0.0f, 0.8f, 0.75f,

			-0.5f, -0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, -0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, -0.5f, 0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, -0.5f, 0.5f, 0.0f, 0.8f, 0.75f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.8f, 0.75f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.8f, 0.75f,

			-0.5f, 0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, 0.5f, 0.5f, 0.0f, 0.8f, 0.75f,
			0.5f, 0.5f, 0.5f, 0.0f, 0.8f, 0.75f,
			-0.5f, 0.5f, 0.5f, 0.0f, 0.8f, 0.75f,
			-0.5f, 0.5f, -0.5f, 0.0f, 0.8f, 0.75f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.7f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);


		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);

		//   model = glm::mat4(1.0f);
		   //model = glm::scale(model, glm::vec3(3.5f, 0.35f, 2.0f));// Ancho, grosor, profundidad
		   //model = glm::translate(model, glm::vec3(0.0f, 0.6f, 0.0f));
		   //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		   //glDrawArrays(GL_TRIANGLES, 0, 36);

		   //model = glm::mat4(1.0f);
		   //model = glm::scale(model, glm::vec3(2.0f, 0.2f, 1.5f));// Ancho, grosor, profundidad
		   //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		   //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		   //glDrawArrays(GL_TRIANGLES, 0, 36);
		   //
		   ////Pata 1
		   //model = glm::mat4(1.0f);
		   //model = glm::scale(model, glm::vec3(0.25f, 0.6f, 0.3f));// Ancho, grosor, profundidad
		   //model = glm::translate(model, glm::vec3(3.5f, -0.6f, 1.9f));
		   //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		   //glDrawArrays(GL_TRIANGLES, 0, 36);

		   ////Pata 2
		   //model = glm::mat4(1.0f);
		   //model = glm::scale(model, glm::vec3(0.25f, 0.6f, 0.3f));// Ancho, grosor, profundidad
		   //model = glm::translate(model, glm::vec3(-3.5f, -0.6f, 1.9f));
		   //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		   //glDrawArrays(GL_TRIANGLES, 0, 36);

		   ////Pata 3
		   //model = glm::mat4(1.0f);
		   //model = glm::scale(model, glm::vec3(0.25f, 0.6f, 0.3f));// Ancho, grosor, profundidad
		   //model = glm::translate(model, glm::vec3(3.5f, -0.6f, -1.9f));
		   //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		   //glDrawArrays(GL_TRIANGLES, 0, 36);


		   ////Pata 4
		   //model = glm::mat4(1.0f);
		   //model = glm::scale(model, glm::vec3(0.25f, 0.6f, 0.3f));// Ancho, grosor, profundidad
		   //model = glm::translate(model, glm::vec3(-3.5f, -0.6f, -1.9f));
		   //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		   //glDrawArrays(GL_TRIANGLES, 0, 36);


		   //Unicornio en Voxel Art
		   //Cuerpo
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(0.2f, -0.6f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		////Cabeza
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-0.4f, 0.3f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Patas
		//Pata delantera derecha
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.6f, 0.4f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-0.978f, -2.3f, -0.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Pata delantera izquierda
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.6f, 0.4f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-0.978f, -2.3f, 0.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Pata trasera derecha
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.6f, 0.4f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(2.979f, -2.3f, -0.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Pata trasera izquierda
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.6f, 0.4f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(2.979f, -2.3f, 0.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Alas
		//Ala derecha
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(2.979f, 0.0f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(1.7482f, 0.9f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.6f, 0.2f, 0.2f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(1.32f, 1.8f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Ala izquierda
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(2.979f, 0.0f, -2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(1.7482f, 0.9f, -2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.6f, 0.2f, 0.2f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(1.32f, 1.8f, -2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Orejas
		//Oreja derecha
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.5f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-0.4f, 1.8f, -1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Oreja izquierda
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.5f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-0.4f, 1.8f, 1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cabello
		// //morado claro
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.7f, 0.125f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-0.15f, 8.44f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 110);

		//morado fuerte
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.9f, 0.2f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-0.15f, 4.45f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);

		//morado fuerte
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.256f, 1.235f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(1.0f, 0.3f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);

		//morado claro
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.9f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(3.0f, 0.3f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 110);

		//morado fuerte
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.7f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(4.0f, 0.3f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);

		//morado claro
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.4f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(5.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 110);

		//morado fuerte
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.2f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(6.0f, -0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);

		//Cola
		//morado fuerte
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.256f, 0.2f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(5.5f, -0.3f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);

		//morado fuerte
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.24f, 0.7f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(6.5f, -0.45f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);

		//morado fuerte
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(4.1f, -3.5f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);

		//morado claro
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(4.7f, -2.45f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 110);

		//morado claro
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(9.95f, -1.64f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 110);

		//morado claro
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.2f, 0.3f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(7.3f, -3.78f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 110);

		//Cuerno
		//Color hueso
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.12f, 0.5f, 0.1f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-0.15f, 2.7f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		//Color hueso
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.12f, 0.2f, 0.1f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-0.6f, 5.7f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		//Herraduras
		//herradura delantera derecha
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.4f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-0.978f, -8.8f, -0.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 180);

		//herradura delantera izquierda
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.4f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-0.978f, -8.8f, 0.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 180);

		//herradura trasera derecha
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.4f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(2.979f, -8.8f, -0.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 180);

		//herradura trasera izquierda
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.4f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(2.979f, -8.8f, 0.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 180);


		//Nariz
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.6f, 0.8f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-3.5f, 0.2f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 180);

		//Fosas nasales
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-7.7f, 0.3f, 0.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 180, 216);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-7.7f, 0.3f, -0.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 180, 216);

		//Contorno alas
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.25f));// Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(2.125f, 0.35f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

				
		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.004f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.004f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.004f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.004f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.004f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.004f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.025f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.025f;
 }


