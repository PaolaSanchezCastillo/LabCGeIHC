#define _USE_MATH_DEFINES

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

//Descomentar
#include "Headers/Texture.h"

int screenWidth;
int screenHeight;

GLFWwindow * window;

Shader shader;
//shader del texturizado
Shader shaderTexture;

std::shared_ptr<FirstPersonCamera> camera(new FirstPersonCamera());

Sphere sphere1(20, 20);
Sphere sphere2(20, 20);
Sphere sphere3(20, 20);
Cylinder cylinder1(20, 20, 0.5, 0.5);
Cylinder cylinder2(20, 20, 0.5, 0.5);
Box box1;
Box box2;
Box box3; //añadimos esto Para el cubo 




//COCA COLA

Cylinder coca1(20, 20, 0.5, 0.5);
Cylinder coca2(20, 20, 0.5, 0.5);
Cylinder coca3(20, 20, 0.5, 0.5);






//Bob Esponja

Sphere sphere1bob(20, 20);
Sphere sphere2bob(20, 20);
Sphere sphere3bob(10, 10);
Cylinder cylinder1bob(20, 20, 0.5, 0.5);
Box box1bob;
Box box2bob;
Box box3bob;

// Descomentar buffer del texturizado
GLuint textureID1, textureID2, textureID3;
GLuint textureID1BOB, textureID2BOB, textureID3BOB, textureID4, textureID5, textureID6, textureID7;;


bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;

float rot0 = 0.0, dz = 0.0;

float rot1bob = 0.0, rot2 = 0.0, rot3 = 0.0, rot4 = 0.0;
bool sentidobob = true;
float rot5 = 0.0, rot6 = 0.0, rot7 = 0.0, rot8 = 0.0;


double deltaTime;

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow* window, int key, int scancode, int action,
	int mode);
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
	//Descomentar
	shaderTexture.initialize("../Shaders/texturizado.vs", "../Shaders/texturizado.fs");


	//shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");

	/// PARA EL CUBO

	box3.init();
	box3.setShader(&shaderTexture);

	//COCA COLA

	coca1.init();
	coca1.setShader(&shaderTexture);
	coca1.setColor(glm::vec4(0.3, 0.3, 1.0, 1.0));

	coca2.init();
	coca2.setShader(&shaderTexture);

	coca3.init();
	coca3.setShader(&shaderTexture);




	//inicializar vao, vbo y ebo //esfera
	sphere1bob.init();
	//metodo setter que coloca el apumntador al shader que se ocupara
	sphere1bob.setShader(&shader);
	//metodo setter para poner el color a la esfera
	sphere1bob.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));

	//inicializar vao, vbo y ebo //esfera
	sphere2bob.init();
	//metodo setter que coloca el apumntador al shader que se ocupara
	sphere2bob.setShader(&shader);
	//metodo setter para poner el color a la esfera
	sphere2bob.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	sphere3bob.init();
	sphere3bob.setShader(&shader);
	sphere3bob.setColor(glm::vec4(0.0, 0.0, 0.0, 1.0));

	cylinder1bob.init();
	cylinder1bob.setShader(&shader);
	cylinder1bob.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));

	box1bob.init();
	box1bob.setShader(&shaderTexture);
	box1bob.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));


	box3bob.init();
	box3bob.setShader(&shader);
	box3bob.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	box2bob.init();
	box2bob.setShader(&shader)

		;
	box2bob.setColor(glm::vec4(0.66, 0.41, 0.24, 1.0));


	// Inicializar los buffers VAO, VBO, EBO
	sphere1.init();
	// Método setter que colocar el apuntador al shader
	sphere1.setShader(&shader);
	//Setter para poner el color de la geometria
	sphere1.setColor(glm::vec4(0.3, 0.3, 1.0, 1.0));

	// Inicializar los buffers VAO, VBO, EBO
	sphere2.init();
	// Método setter que colocar el apuntador al shader
	sphere2.setShader(&shader);
	//Setter para poner el color de la geometria
	sphere2.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	cylinder1.init();
	cylinder1.setShader(&shaderTexture);
	cylinder1.setColor(glm::vec4(0.3, 0.3, 1.0, 1.0));

	cylinder2.init();
	cylinder2.setShader(&shaderTexture);

	box1.init();
	//settea el shader a utilizar
	box1.setShader(&shaderTexture);
	box1.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
	camera->setPosition(glm::vec3(0.0, 0.0, 4.0));

	box2.init();
	//settea el shader a utilizar
	box2.setShader(&shader);

	sphere3.init();
	sphere3.setShader(&shader);

	// Descomentar
	//definimos el tamanio de la imagen 
	int imageWidth, imageHeight;
	//definimos la textura a utilizar
	///TEXTURA PARA EL BOB ESPONJA Y EL CUADRO

	Texture texture1("../Textures/sponge.jpg");
	//carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)

	FIBITMAP *bitmap = texture1.loadImage();

	//convertimos el mapa de bits en una arreglo unidiemnsional de tipo unsigned
	unsigned char *data = texture1.convertToData(bitmap, imageWidth,
		imageHeight);
	//creando la textura con id 1
	glGenTextures(1, &textureID1BOB);
	//enlazar esa textura a un tipo de textura de 2d
	glBindTexture(GL_TEXTURE_2D, textureID1BOB);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//verifica si se pudo abrir la textura
	if (data) {
		//tranferir los dtos de la imagen a memoria
		//pararametros; tipos de textura, niveles de bit maps, formato interno de opengl, ancho, alto, bitmap, 
		//formato interno de la imagen, típo de dtao, apuntador  a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		//genera los niveles del mimap opengl es el encargado de realizarlo
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	//libera la memoria de la textura
	texture1.freeImage(bitmap);



	// CUBOOOO


	//definimos la textura 2 a utilizar
	Texture texture2("../Textures/water.jpg");
	//carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = texture2.loadImage();
	//convertimos el mapa de bits en una arreglo unidiemnsional de tipo unsigned
	data = texture2.convertToData(bitmap, imageWidth,
		imageHeight);
	//creando la textura con id 1
	glGenTextures(1, &textureID2);
	//enlazar esa textura a un tipo de textura de 2d
	glBindTexture(GL_TEXTURE_2D, textureID2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//verifica si se pudo abrir la textura
	if (data) {
		//tranferir los dtos de la imagen a memoria
		//pararametros; tipos de textura, niveles de bit maps, formato interno de opengl, ancho, alto, bitmap, 
		//formato interno de la imagen, típo de dtao, apuntador  a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		//genera los niveles del mimap opengl es el encargado de realizarlo
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	//libera la memoria de la textura
	texture2.freeImage(bitmap);



	// Definiendo la textura a utilizar
	Texture texture4("../Textures/sponge.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture4.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture4.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID4);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID4);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture4.freeImage(bitmap);




	//TEXTURAS PARA LA COCA COLA





}
	
void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	// --------- IMPORTANTE ----------
	// Eliminar los shader y buffers creados.

	// Destrucción de los VAO, EBO, VBO
	sphere1.destroy();
	cylinder1.destroy();
	box1.destroy();
	

	shader.destroy();



	//destruye el vao, vbo, ebo  BOB MIO 
	sphere1bob.destroy();
	cylinder1bob.destroy();
	box1bob.destroy();

	shader.destroy();
}

void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action,
	int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
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
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offsetX, offsetY, 0.01);
	offsetX = 0;
	offsetY = 0;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		sentidobob = false;

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && sentidobob)
		rot1bob += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !sentidobob)
		rot1bob -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		rot2 += 0.001;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		rot2 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && sentidobob)
		rot3 += 0.001;
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && sentidobob)
		rot4 += 0.001;


	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot0 = 0.0001;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot0 = -0.0001;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		dz = 0.0001;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		dz = -0.0001;

	sentidobob = true;

	glfwPollEvents();
	return continueApplication;
}

void applicationLoop() {
	bool psi = true;

	glm::mat4 model = glm::mat4(1.0f);
	float offX = 0.0;
	float angle = 0.0;
	float ratio = 5.0;


	while (psi) {
		psi = processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)screenWidth / (float)screenHeight, 0.01f, 100.0f);
		glm::mat4 view = camera->getViewMatrix();

		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));
		// Settea la matriz de vista y projection al nuevo shader
		shaderTexture.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(view));

		

		model = glm::translate(model, glm::vec3(0, 0, dz));
		model = glm::rotate(model, rot0, glm::vec3(0, 1, 0));
		//box1.enableWireMode();
		//Descomentar
		// Usamos la textura ID 1
		glBindTexture(GL_TEXTURE_2D, textureID1BOB);
		box1bob.render(glm::scale(model, glm::vec3(1.0, 1.0, 0.1)));
		//Descomentar
		// No utilizar ninguna textura
		glBindTexture(GL_TEXTURE_2D, 0);



		glm::mat4 modelCylinder = glm::mat4(1.0);
		modelCylinder = glm::translate(modelCylinder, glm::vec3(-3.0, 0.0, 0.0));
		shaderTexture.setFloat("offsetX", 0);
		
		modelCylinder = glm::translate(modelCylinder, glm::vec3(-4.0, 0.0, 1.0)); //COCA-COLA
		glBindTexture(GL_TEXTURE_2D, textureID4);
		coca3.render(0, coca3.getSlices() * coca3.getStacks() * 6,
			modelCylinder);

		glBindTexture(GL_TEXTURE_2D, textureID5);	//TAPA SUPERIOR COCA COLA
		coca2.render(cylinder2.getSlices() * coca2.getStacks() * 6,
			coca2.getSlices() * 3,
			modelCylinder);

		glBindTexture(GL_TEXTURE_2D, textureID6); //TAPA INFERIOR COCA COLA
		coca2.render(cylinder2.getSlices() * coca2.getStacks() * 6 + coca2.getSlices() * 3,
			coca2.getSlices() * 3,
			modelCylinder);

		//COCA_COLA

	

		



		//jean
		glm::mat4 p1 = glm::translate(model, glm::vec3(0.0, -0.4, 0.0));
		box2bob.render(glm::scale(p1, glm::vec3(1.0, 0.2, 0.5)));


		// Camisa
		glm::mat4 c1 = glm::translate(model, glm::vec3(0.0, -0.2, 0.0));
		box3bob.render(glm::scale(c1, glm::vec3(1.0, 0.2, 0.5)));

		//left arm (Articulación) 
		glm::mat4 j1 = glm::translate(model, glm::vec3(0.5f, 0.0, 0.0));
		sphere1bob.enableWireMode();
		sphere1bob.render(glm::scale(j1, glm::vec3(0.1, 0.1, 0.1)));
		j1 = glm::rotate(j1, rot1bob, glm::vec3(0, 0, 1));
		j1 = glm::rotate(j1, rot2, glm::vec3(0, 1, 0));

		//bone brazo izquierdo 
		glm::mat4 l1 = glm::translate(j1, glm::vec3(0.25, 0.0, 0.0));
		l1 = glm::rotate(l1, glm::radians(90.0f), glm::vec3(0, 0, 0.1));
		cylinder1bob.enableWireMode();
		cylinder1bob.render(glm::scale(l1, glm::vec3(0.1, 0.5, 0.1)));


		//Segunda Articulación Brazo igzqierdo
		glm::mat4 j2 = glm::translate(j1, glm::vec3(0.5, 0.0, 0.0));
		sphere1bob.enableWireMode();
		sphere1bob.render(glm::scale(j2, glm::vec3(0.1, 0.1, 0.1)));
		j2 = glm::rotate(j2, rot3, glm::vec3(0.0, 0.0, 1.0));
		j2 = glm::rotate(j2, rot4, glm::vec3(1, 0, 0));


		//bone two
		glm::mat4 l2 = glm::translate(j2, glm::vec3(0.15, 0.0, 0.0));
		l2 = glm::rotate(l2, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.1));
		cylinder1bob.enableWireMode();
		cylinder1bob.render(glm::scale(l2, glm::vec3(0.1, 0.25, 0.1)));

		//eyes
		glm::mat4 eye = glm::translate(model, glm::vec3(0.25, 0.25, 0.20));
		sphere2bob.enableWireMode();
		sphere2bob.render(glm::scale(eye, glm::vec3(0.2, 0.2, 0.2)));

		glm::mat4 eye2 = glm::translate(model, glm::vec3(-0.25, 0.25, 0.20));
		sphere2bob.enableWireMode();
		sphere2bob.render(glm::scale(eye2, glm::vec3(0.2, 0.2, 0.2)));

		glm::mat4 eyei = glm::translate(model, glm::vec3(0.25, 0.25, 0.35));
		sphere3bob.render(glm::scale(eyei, glm::vec3(0.1, 0.1, 0.2)));

		glm::mat4 eye2i = glm::translate(model, glm::vec3(-0.25, 0.25, 0.35));
		sphere3bob.render(glm::scale(eye2i, glm::vec3(0.1, 0.1, 0.2)));

		//right arm
		glm::mat4 j3 = glm::translate(model, glm::vec3(-0.5f, 0.0, 0.0));
		sphere1bob.enableWireMode();
		sphere1bob.render(glm::scale(j3, glm::vec3(0.1, 0.1, 0.1)));


		j3 = glm::rotate(j3, rot5, glm::vec3(0, 0, 1));
		j3 = glm::rotate(j3, rot6, glm::vec3(0, 1, 0));

		//bone three
		glm::mat4 l3 = glm::translate(j3, glm::vec3(-0.25, 0.0, 0.0));
		l3 = glm::rotate(l3, glm::radians(90.0f), glm::vec3(0, 0, 0.1));
		cylinder1bob.enableWireMode();
		cylinder1bob.render(glm::scale(l3, glm::vec3(0.1, 0.5, 0.1)));

		//second articulation (brazo derecho)
		glm::mat4 j4 = glm::translate(j3, glm::vec3(-0.25, 0.0, 0.0));
		sphere1bob.enableWireMode();
		sphere1bob.render(glm::scale(j4, glm::vec3(0.1, 0.1, 0.1)));
		j4 = glm::rotate(j4, rot7, glm::vec3(0, 0, 1));
		j4 = glm::rotate(j4, rot8, glm::vec3(0, 1, 0));




		//rigth leg
		glm::mat4 j5 = glm::translate(model, glm::vec3(-0.25, -0.5, 0.0));
		sphere1bob.enableWireMode();
		sphere1bob.render(glm::scale(j5, glm::vec3(0.1, 0.1, 0.1)));

		//bome five
		glm::mat4 l5 = glm::translate(j5, glm::vec3(0.0, -0.15, 0.0));
		l5 = glm::rotate(l5, glm::radians(00.0f), glm::vec3(0, 0, 0.1));
		cylinder1bob.enableWireMode();
		cylinder1bob.render(glm::scale(l5, glm::vec3(0.1, 0.25, 0.1)));

		//second articulation
		glm::mat4 j6 = glm::translate(j5, glm::vec3(0.0, -0.30, 0.0));
		sphere1bob.enableWireMode();
		sphere1bob.render(glm::scale(j6, glm::vec3(0.1, 0.1, 0.1)));


		//bone six
		glm::mat4 l6 = glm::translate(j5, glm::vec3(0.0, -0.4, 0.0));
		l6 = glm::rotate(l6, glm::radians(00.0f), glm::vec3(0.0, 0.0, -1.1));
		cylinder1bob.enableWireMode();
		cylinder1bob.render(glm::scale(l6, glm::vec3(0.1, 0.25, 0.1)));

		//SHOE
		glm::mat4 j11 = glm::translate(j5, glm::vec3(0.0, -0.58, 0.0));
		sphere3bob.render(glm::scale(j11, glm::vec3(0.1, 0.1, 0.1)));


		//pierna izquierda
		glm::mat4 j7 = glm::translate(model, glm::vec3(0.25, -0.5, 0.0));
		sphere1bob.enableWireMode();
		sphere1bob.render(glm::scale(j7, glm::vec3(0.1, 0.1, 0.1)));

		//hueso seis
		glm::mat4 l7 = glm::translate(j7, glm::vec3(0.0, -0.15, 0.0));
		l7 = glm::rotate(l7, glm::radians(00.0f), glm::vec3(0, 0, 0.1));
		cylinder1bob.enableWireMode();
		cylinder1bob.render(glm::scale(l7, glm::vec3(0.1, 0.25, 0.1)));

		//segunda articulacion
		glm::mat4 j8 = glm::translate(j7, glm::vec3(0.0, -0.25, 0.0));
		sphere1bob.enableWireMode();
		sphere1bob.render(glm::scale(j8, glm::vec3(0.1, 0.1, 0.1)));

		//hueso siete
		glm::mat4 l8 = glm::translate(j7, glm::vec3(0.0, -0.4, 0.0));
		l8 = glm::rotate(l8, glm::radians(00.0f), glm::vec3(0.0, 0.0, -1.1));
		cylinder1bob.enableWireMode();
		cylinder1bob.render(glm::scale(l8, glm::vec3(0.1, 0.25, 0.1)));

		//zapato
		glm::mat4 j10 = glm::translate(j7, glm::vec3(0.0, -0.58, 0.0));
		sphere3bob.render(glm::scale(j10, glm::vec3(0.1, 0.1, 0.1)));



		///CUBO



		glm::mat4 cubeTextureModel = glm::mat4(1.0);
		cubeTextureModel = glm::translate(cubeTextureModel , glm::vec3(3.0, 2.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(cubeTextureModel);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (angle > 2 * M_PI)
			angle = 0.0;
		else
			angle += 0.0001;

		shader.turnOff();

		dz = 0;
		rot0 = 0;
		offX += 0.001;

		glfwSwapBuffers(window);
	}
}

int main(int argc, char ** argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}

//tarea mapear todas las caras del cubo