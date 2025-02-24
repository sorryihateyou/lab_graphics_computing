#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
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

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		-0.91f,  0.60f, 0.0f,    1.0f,1.0f,1.0f,  // top right
		-0.59f, 0.73f, 0.0f,    1.0f,1.0f,0.0f,  // bottom right
		-0.56f, 0.69f, 0.0f,   1.0f,0.0f,1.0f,  // bottom left
		-0.42f,  0.29f, 0.0f,   1.0f,1.0f,0.0f, // top left 
		-0.55f,  0.68f, 0.0f,   1.0f,1.0f,0.0f,
		-0.62f,  0.67f, 0.0f,   1.0f,0.0f,0.0f,
		-0.58f,  0.28f, 0.0f,   1.0f,1.0f,0.0f,
		-0.43f,  0.29f, 0.0f,   1.0f,1.0f,0.0f,
		-0.621f,  0.65f, 0.0f,   1.0f,0.0f,1.0f,
		-0.3653f,  0.094f, 0.0f,   1.0f,1.0f,0.0f,
		-0.4258f,  0.282f, 0.0f,   1.0f,1.0f,0.0f,
		-0.579f,  0.269f, 0.0f,   1.0f,0.0f,0.0f,
		-0.360f,  0.0956f, 0.0f,   1.0f,1.0f,0.0f,
		-0.4169f,  0.2832f, 0.0f,   1.0f,1.0f,0.0f,
		-0.1184f,  0.3121f, 0.0f,   1.0f,0.0f,1.0f,
		-0.3539f,  0.0899f, 0.0f,   1.0f,1.0f,0.0f,
		-0.0550f,  0.0528f, 0.0f,   1.0f,1.0f,0.0f,
		-0.11596f,  0.3073f, 0.0f,   1.0f,0.0f,0.0f,
		0.11356f,  0.2315f, 0.0f,   1.0f,1.0f,0.0f,
		-0.0534f,  0.0534f, 0.0f,   1.0f,1.0f,0.0f,
		-0.11196f,  0.3092f, 0.0f,   1.0f,0.0f,1.0f,
		-0.1089f,  0.3128f, 0.0f,   1.0f,1.0f,0.0f,
		-0.0658f,  0.3492f, 0.0f,   1.0f,1.0f,0.0f,
		0.1072f,  0.2413f, 0.0f,   1.0f,0.0f,0.0f,
		-0.0635f,  0.3548f, 0.0f,   1.0f,1.0f,0.0f,
		-0.1136f,  0.3147f, 0.0f,   1.0f,1.0f,0.0f,
		-0.1674f,  0.5899f, 0.0f,   1.0f,1.0f,1.0f,
		-0.1666f,  0.5942f, 0.0f,   1.0f,1.0f,0.0f,
		0.4077f,  0.7982f, 0.0f,   1.0f,1.0f,0.0f,
		-0.0598f,  0.3592f, 0.0f,   1.0f,0.0f,1.0f,
		-0.0559f,  0.3524f, 0.0f,   1.0f,1.0f,0.0f,
		0.7366f,  0.4721f, 0.0f,   1.0f,1.0f,0.0f,
		0.4113f,  0.7914f, 0.0f,   1.0f,0.0f,0.0f,
		-0.0560f,  0.3462f, 0.0f,   1.0f,1.0f,0.0f,
		0.9189f,  -0.2066f, 0.0f,   1.0f,1.0f,0.0f,
		0.7369f,  0.4671f, 0.0f,   1.0f, 0.0f,1.0f,
		0.2221f,  0.1765f, 0.0f,   1.0f,1.0f,0.0f,
		0.3592f,  0.0878f, 0.0f,   1.0f,1.0f,0.0f,
		0.3054f,  -0.7403f, 0.0f,   1.0f,1.0f,1.0f,
		0.2433f,  -0.7977f, 0.0f,   1.0f,1.0f,0.0f,
		0.3028f,  -0.7485f, 0.0f,   1.0f,1.0f,0.0f,
		0.2149f,  0.1659f, 0.0f,   1.0f,0.0f,1.0f,
		0.2355f,  -0.8027f, 0.0f,   1.0f,1.0f,0.0f,
		0.2354f,  -0.7414f, 0.0f,   1.0f,1.0f,0.0f,
		-0.1773f, -0.7905f, 0.0f,   1.0f,0.0f,1.0f,



	};
	unsigned int indices[] = {  // note that we start from 0!
		3,2,1,// second Triangle
		0,1,3,
		
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        //glPointSize(1);
        //glDrawArrays(GL_POINTS,0,1);
        
        //glDrawArrays(GL_LINES,0,2);
        //glDrawArrays(GL_LINE_LOOP,0,2);
        
        glDrawArrays(GL_TRIANGLES,0,3);
		glDrawArrays(GL_TRIANGLES,3,3);
		glDrawArrays(GL_TRIANGLES,6,3);
		glDrawArrays(GL_TRIANGLES,9,3);
		glDrawArrays(GL_TRIANGLES,12,3);
		glDrawArrays(GL_TRIANGLES,15,3);
		glDrawArrays(GL_TRIANGLES, 18, 3);
		glDrawArrays(GL_TRIANGLES, 21, 3);
		glDrawArrays(GL_TRIANGLES, 24, 3);
		glDrawArrays(GL_TRIANGLES, 27, 3);
		glDrawArrays(GL_TRIANGLES, 30, 3);
		glDrawArrays(GL_TRIANGLES, 33, 3);
		glDrawArrays(GL_TRIANGLES, 36, 3);
		glDrawArrays(GL_TRIANGLES, 39, 3);
		glDrawArrays(GL_TRIANGLES, 42, 3);

		//glDrawArrays(GL_TRIANGLES, 6, 8);
		//glDrawArrays(GL_TRIANGLES,2,3);

        //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0);

        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}