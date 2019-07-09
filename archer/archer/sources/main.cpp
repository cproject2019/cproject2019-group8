#include <iostream>


#include "../Include/camera.h"
#include "../Include/resource_manager.h"
#include "../Include/game.h"

void key_callback(GLFWwindow* window,int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;
Game archer(SCREEN_WIDTH, SCREEN_HEIGHT);

double xpos = 0.0f;//to get the cursor, it must be double
double ypos = 0.0f;


int main(int argc, char* argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Archer", nullptr, nullptr);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	archer.State = GAME_ACTIVE;
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	archer.Init();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{	
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwGetCursorPos(window, &xpos, &ypos);
		archer.xpos = (float)xpos;
		archer.ypos = (float)ypos;
		archer.Update(deltaTime);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		archer.Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	archer.~Game();
	return 0;
}

void key_callback(GLFWwindow* window,int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			archer.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			archer.Keys[key] = GL_FALSE;
	}
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	archer.Width = width;
	archer.Height = height;
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		archer.Leftmouse= TRUE;
	else
		archer.Leftmouse = FALSE;
}