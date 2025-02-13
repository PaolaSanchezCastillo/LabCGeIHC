//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>

//glfw include
#include <GLFW/glfw3.h>

// program include
#include "Headers/TimeManager.h"

// Shader include
#include "Headers/Shader.h"

// Model geometric includes

#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
#include "Headers/FirstPersonCamera.h"


//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int screenWidth;
int screenHeight;

GLFWwindow * window;

Shader shader;
std::shared_ptr <FirstPersonCamera> camera(new FirstPersonCamera());

Sphere sphere1(20, 20);
Sphere sphere2(20, 20);
Sphere sphere3(10, 10);
Cylinder cylinder1(20, 20, 0.5, 0.5);
Box box1;
Box box2;
Box box3;


bool sentidobob = true;
float rot1bob = 0.0, rot2 = 0.0, rot3 = 0.0, rot4 = 0.0;
float rot5 = 0.0, rot6 = 0.0, rot7 = 0.0, rot8 = 0.0;
bool exitApp = false;
int lastMousePosX, offSetX = 0;
int lastMousePosY, offSetY = 0;

double deltaTime;

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod);
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);

// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
			glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
			nullptr);

	if (window == nullptr) {
		std::cerr
			<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
			<< std::endl;
		destroy();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");

	//inicializar vao, vbo y ebo //esfera
	sphere1.init();
	//metodo setter que coloca el apumntador al shader que se ocupara
	sphere1.setShader(&shader);
	//metodo setter para poner el color a la esfera
	sphere1.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));

	//inicializar vao, vbo y ebo //esfera
	sphere2.init();
	//metodo setter que coloca el apumntador al shader que se ocupara
	sphere2.setShader(&shader);
	//metodo setter para poner el color a la esfera
	sphere2.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	sphere3.init();
	sphere3.setShader(&shader);
	sphere3.setColor(glm::vec4(0.0, 0.0, 0.0, 1.0));

	cylinder1.init();
	cylinder1.setShader(&shader);
	cylinder1.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));

	box1.init();
	box1.setShader(&shader);
	box1.setColor(glm::vec4(1.0, 0.8, 0.0, 1.0));


	box3.init();
	box3.setShader(&shader);
	box3.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	box2.init();
	box2.setShader(&shader);
	box2.setColor(glm::vec4(0.66, 0.41, 0.24, 1.0));

	camera->setPosition(glm::vec3(2.0, 0.0, 7.0));
}

void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();

	//destruye el vao, vbo, ebo
	sphere1.destroy();
	cylinder1.destroy();
	box1.destroy();

	shader.destroy();
}

void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	offSetX = xpos - lastMousePosX;
	offSetY = ypos - lastMousePosY;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offSetX, offSetY, deltaTime);

	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod) {
	if (state == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication) {
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}

	TimeManager::Instance().CalculateFrameRate(false);
	deltaTime = TimeManager::Instance().DeltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveFrontCamera(true, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveFrontCamera(false, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveRightCamera(false, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveRightCamera(true, deltaTime);
	offSetX = 0;
	offSetY = 0;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)

		sentidobob = false;


	//Brazo derecho 

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && sentidobob)
		rot1bob += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !sentidobob)
		rot1bob -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && sentidobob)
		rot2 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && !sentidobob)
		rot2 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && sentidobob)
		rot3 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && !sentidobob)
		rot3 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && sentidobob)
		rot4 += 0.001;

	sentidobob = false;
	//	Brazo izquierdo


	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && sentidobob)
		rot5 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && !sentidobob)
		rot5 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && sentidobob)
		rot6 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && !sentidobob)
		rot6 -= 0.001;

	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && sentidobob)
		rot7 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && !sentidobob)
		rot7 -= 0.001;

	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && sentidobob)
		rot8 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && !sentidobob)
		rot8 -= 0.001;

	sentidobob = true;




	glfwPollEvents();
	return continueApplication;
}

void applicationLoop() {
	bool psi = true;
	while (psi) {
		psi = processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.01f, 100.0f);
		glm::mat4 view = camera->getViewMatrix(); //glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

		shader.turnOn();

		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));

		glm::mat4 model = glm::mat4(1.0f);


		box1.render(glm::scale(model, glm::vec3(1.0, 1.0, 0.1)));

		//jean
		glm::mat4 p1 = glm::translate(model, glm::vec3(0.0, -0.4, 0.0));
		box2.render(glm::scale(p1, glm::vec3(1.0, 0.2, 0.5)));


		// Camisa
		glm::mat4 c1 = glm::translate(model, glm::vec3(0.0, -0.2, 0.0));
		box3.render(glm::scale(c1, glm::vec3(1.0, 0.2, 0.5)));

		//left arm (Articulación) 
		glm::mat4 j1 = glm::translate(model, glm::vec3(0.5f, 0.0, 0.0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j1, glm::vec3(0.1, 0.1, 0.1)));
		j1 = glm::rotate(j1, rot1bob, glm::vec3(0, 0, 1));
		j1 = glm::rotate(j1, rot2, glm::vec3(0, 1, 0));

		//bone brazo izquierdo 
		glm::mat4 l1 = glm::translate(j1, glm::vec3(0.25, 0.0, 0.0));
		l1 = glm::rotate(l1, glm::radians(90.0f), glm::vec3(0, 0, 0.1));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l1, glm::vec3(0.1, 0.5, 0.1)));


		//Segunda Articulación Brazo igzqierdo
		glm::mat4 j2 = glm::translate(j1, glm::vec3(0.5, 0.0, 0.0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j2, glm::vec3(0.1, 0.1, 0.1)));
		j2 = glm::rotate(j2, rot3, glm::vec3(0.0, 0.0, 1.0));
		j2 = glm::rotate(j2, rot4, glm::vec3(1, 0, 0));


		//bone two
		glm::mat4 l2 = glm::translate(j2, glm::vec3(0.15, 0.0, 0.0));
		l2 = glm::rotate(l2, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.1));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l2, glm::vec3(0.1, 0.25, 0.1)));

		//eyes
		glm::mat4 eye = glm::translate(model, glm::vec3(0.25, 0.25, 0.20));
		sphere2.enableWireMode();
		sphere2.render(glm::scale(eye, glm::vec3(0.2, 0.2, 0.2)));

		glm::mat4 eye2 = glm::translate(model, glm::vec3(-0.25, 0.25, 0.20));
		sphere2.enableWireMode();
		sphere2.render(glm::scale(eye2, glm::vec3(0.2, 0.2, 0.2)));

		glm::mat4 eyei = glm::translate(model, glm::vec3(0.25, 0.25, 0.35));
		sphere3.render(glm::scale(eyei, glm::vec3(0.1, 0.1, 0.2)));

		glm::mat4 eye2i = glm::translate(model, glm::vec3(-0.25, 0.25, 0.35));
		sphere3.render(glm::scale(eye2i, glm::vec3(0.1, 0.1, 0.2)));

		//right arm
		glm::mat4 j3 = glm::translate(model, glm::vec3(-0.5f, 0.0, 0.0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j3, glm::vec3(0.1, 0.1, 0.1)));


		j3 = glm::rotate(j3, rot5, glm::vec3(0, 0, 1));
		j3 = glm::rotate(j3, rot6, glm::vec3(0, 1, 0));

		//bone three
		glm::mat4 l3 = glm::translate(j3, glm::vec3(-0.25, 0.0, 0.0));
		l3 = glm::rotate(l3, glm::radians(90.0f), glm::vec3(0, 0, 0.1));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l3, glm::vec3(0.1, 0.5, 0.1)));

		//second articulation (brazo derecho)
		glm::mat4 j4 = glm::translate(j3, glm::vec3(-0.25, 0.0, 0.0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j4, glm::vec3(0.1, 0.1, 0.1)));
		j4 = glm::rotate(j4, rot7, glm::vec3(0, 0, 1));
		j4 = glm::rotate(j4, rot8, glm::vec3(0, 1, 0));




		//rigth leg
		glm::mat4 j5 = glm::translate(model, glm::vec3(-0.25, -0.5, 0.0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j5, glm::vec3(0.1, 0.1, 0.1)));

		//bome five
		glm::mat4 l5 = glm::translate(j5, glm::vec3(0.0, -0.15, 0.0));
		l5 = glm::rotate(l5, glm::radians(00.0f), glm::vec3(0, 0, 0.1));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l5, glm::vec3(0.1, 0.25, 0.1)));

		//second articulation
		glm::mat4 j6 = glm::translate(j5, glm::vec3(0.0, -0.30, 0.0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j6, glm::vec3(0.1, 0.1, 0.1)));


		//bone six
		glm::mat4 l6 = glm::translate(j5, glm::vec3(0.0, -0.4, 0.0));
		l6 = glm::rotate(l6, glm::radians(00.0f), glm::vec3(0.0, 0.0, -1.1));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l6, glm::vec3(0.1, 0.25, 0.1)));

		//SHOE
		glm::mat4 j11 = glm::translate(j5, glm::vec3(0.0, -0.58, 0.0));
		sphere3.render(glm::scale(j11, glm::vec3(0.1, 0.1, 0.1)));


		//pierna izquierda
		glm::mat4 j7 = glm::translate(model, glm::vec3(0.25, -0.5, 0.0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j7, glm::vec3(0.1, 0.1, 0.1)));

		//hueso seis
		glm::mat4 l7 = glm::translate(j7, glm::vec3(0.0, -0.15, 0.0));
		l7 = glm::rotate(l7, glm::radians(00.0f), glm::vec3(0, 0, 0.1));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l7, glm::vec3(0.1, 0.25, 0.1)));

		//segunda articulacion
		glm::mat4 j8 = glm::translate(j7, glm::vec3(0.0, -0.25, 0.0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j8, glm::vec3(0.1, 0.1, 0.1)));

		//hueso siete
		glm::mat4 l8 = glm::translate(j7, glm::vec3(0.0, -0.4, 0.0));
		l8 = glm::rotate(l8, glm::radians(00.0f), glm::vec3(0.0, 0.0, -1.1));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l8, glm::vec3(0.1, 0.25, 0.1)));

		//zapato
		glm::mat4 j10 = glm::translate(j7, glm::vec3(0.0, -0.58, 0.0));
		sphere3.render(glm::scale(j10, glm::vec3(0.1, 0.1, 0.1)));

		shader.turnOff();

		glfwSwapBuffers(window);
	}
}

int main(int argc, char ** argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}