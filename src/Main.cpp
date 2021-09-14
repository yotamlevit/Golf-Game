#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"EBO.h"
#include"VAO.h"
#include"VBO.h"

// Const
#define WINDOW_HIGHT 800
#define WINDOW_WIDTH 800
#define WINDOW_TITLE "Golf World"
#define BOTTOM_LEFT_CORD 0,0
#define TOP_RIGHT_CORD WINDOW_WIDTH, WINDOW_HIGHT
#define SCREEN_BACKGROUND_COLOR 0.07f, 0.13f, 0.17f, 1.0f
//#define SCREEN_BACKGROUND_COLOR 0.00f, 0.2f, 0.2f, 1.0f
#define SCREEN_SECONDERY_COLOR 0.00f, 0.2f, 0.2f, 1.0f


// Vertices coordinates
GLfloat vertices[] =
{
	//	COORDINATES		/	   COLORS	   //	TexCoord		  //
	-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // Lower left corner
	-0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  0.0f, 1.0f,  // Upper left corner
	 0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  // Upper right corner
	 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f   // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper left triangle
	0, 3, 2  // Lower right triangle
};



int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// Windows Settings
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	// Input: hight, width, Window name, is full screen, not importent
	window = glfwCreateWindow(WINDOW_HIGHT, WINDOW_WIDTH, WINDOW_TITLE, NULL, NULL);
	// Error check if the window fails to create
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	// Tells openGL what area to render
	// Input: Bottom left corner coordinates, Top right corner coordinates
	glViewport(BOTTOM_LEFT_CORD, TOP_RIGHT_CORD);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called ""scale
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture

	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load("D:\Yotam\Code\Golf-Game\src\pop_cat.png", &widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f}
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1f(tex0Uni, 0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// Specifies the rgb color in the color buffer to applay new color on the screen
		glClearColor(SCREEN_BACKGROUND_COLOR);

		// Cleans the back buffer (color) and assign the new color into it
		// GL_COLOR_BUFFER_BIT indecates the color buffer is enabled for color writing
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Assigns a valur to the uniform; NOTE: Must alwats be done after activatin the Shader Program
		glUniform1f(uniID, 0.0f);
		glBindTexture(GL_TEXTURE_2D, texture);
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Now we have the back buffer with the color we want and the
		// front buffer with the defult color.
		// In order to refrese the color we want to swap between the buffers
		// (back buffer and from buffer) and see the new wanted color

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &texture);
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Termianate GLFW before ending the program
	glfwTerminate();
	return 0;
}