#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>


#define WINDOW_HIGHT 800
#define WINDOW_WIDTH 800
#define WINDOW_TITLE "Golf World"
#define BOTTOM_LEFT_CORD 0,0
#define TOP_RIGHT_CORD WINDOW_WIDTH, WINDOW_HIGHT
#define SCREEN_BACKGROUND_COLOR 0.07f, 0.13f, 0.17f, 1.0f

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

	// Tells openGL what area to render
	// Input: Bottom left corner coordinates, Top right corner coordinates
	glViewport(BOTTOM_LEFT_CORD, TOP_RIGHT_CORD);


	// Specifies the rgb color in the color buffer to applay new color on the screen
	glClearColor(SCREEN_BACKGROUND_COLOR);
	// Cleans the back buffer (color) and assign the new color into it
	// GL_COLOR_BUFFER_BIT indecates the color buffer is enabled for color writing
	glClear(GL_COLOR_BUFFER_BIT);

	// Now we have the back buffer with the color we want and the
	// front buffer with the defult color.
	// In order to refrese the color we want to swap between the buffers
	// (back buffer and from buffer) and see the new wanted color

	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Termianate GLFW before ending the program
	glfwTerminate();
	return 0;
}