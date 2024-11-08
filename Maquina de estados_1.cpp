/*                                           Jim�nez Hern�ndez Diana            318051363
*
*		      	Pr�ctica 10: Animaci�n por m�quina de estados       Fecha de entrega: 25 de octubre de 2024*/
#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void Animation();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,2.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



glm::vec3 Light1 = glm::vec3(0);
//Anim
float rotBall = 0.0f;
bool AnimBall = false;
bool AnimDog = false;
float rotDog = 0.0f;
int dogAnim = 0;
float FLegs = 0.0f;
float RLegs = 0.0f;
float head = 0.0f;
float tail = 0.0f;
glm::vec3 dogPos (0.0f,0.0f,0.0f);
float dogRot = 0.0f;
bool step = false;
bool dirz = false;
bool dirx = false;
bool diag = false;



// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Animacion maquina de estados:Jimenez Hernandez Diana", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
	
	//models
	
	Model Piso((char*)"Models/piso_bosque.obj");
	Model Casa((char*)"Models/abandoned_cottage.obj");
	Model Casa1((char*)"Models/Old House 2 3D Models.obj");
	Model Arbol((char*)"Models/Gledista_Triacanthos.obj");
	Model Arbol1((char*)"Models/Gledista_Triacanthos_2.obj");
	Model Arbol2((char*)"Models/Gledista_Triacanthos_3.obj");
	/*Model Piso((char*)"Models/piso_bosque.obj");
	Model Piso((char*)"Models/piso_bosque.obj");
	Model Piso((char*)"Models/piso_bosque.obj");
	Model Piso((char*)"Models/piso_bosque.obj");
	Model Piso((char*)"Models/piso_bosque.obj");*/

	



	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		Animation();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
		// OpenGL options
		glEnable(GL_DEPTH_TEST);

		
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		
	

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

        glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"),0.6f,0.6f,0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"),0.3f, 0.3f, 0.3f);


		// Point light 1
	    glm::vec3 lightColor;
		lightColor.x= abs(sin(glfwGetTime() *Light1.x));
		lightColor.y= abs(sin(glfwGetTime() *Light1.y));
		lightColor.z= sin(glfwGetTime() *Light1.z);

		
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x,lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x,lightColor.y,lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"),0.075f);


		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));
		

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);

	
		
		//Carga de modelo 
        view = camera.GetViewMatrix();	
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.002f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-2.2f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.002f));
		modelTemp= model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa1.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-2.8f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.002f));
		modelTemp = model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa1.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-2.14f, 0.0f, -1.5f));
		model = glm::scale(model, glm::vec3(0.002f));
		modelTemp = model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa1.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-2.16f, 0.0f, -1.5f));
		model = glm::scale(model, glm::vec3(0.002f));
		modelTemp = model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa1.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.6f, 0.0f, -1.5f));
		model = glm::scale(model, glm::vec3(0.002f));
		modelTemp = model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa1.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.5f));
		model = glm::scale(model, glm::vec3(0.002f));
		modelTemp = model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa1.Draw(lightingShader);


		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(2.2f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.002f));
		modelTemp = model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa1.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(2.9f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.002f));
		modelTemp = model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa1.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(2.9f, 0.0f, -1.5f));
		model = glm::scale(model, glm::vec3(0.002f));
		modelTemp = model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa1.Draw(lightingShader);
		
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(2.5f, 0.0f, -1.5f));
		model = glm::scale(model, glm::vec3(0.002f));
		modelTemp = model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa1.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, -1.5f));
		model = glm::scale(model, glm::vec3(0.002f));
		modelTemp = model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa1.Draw(lightingShader);


		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.2f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.02f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Arbol.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.6f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.02f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Arbol1.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(1.2f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.02f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Arbol1.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(1.6f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.02f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Arbol.Draw(lightingShader);

		//model = glm::mat4(1);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//////Body
		//modelTemp= model = glm::translate(model, dogPos);
		//modelTemp= model = glm::rotate(model, glm::radians(dogRot), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//DogBody.Draw(lightingShader);
		////Head
		//model = modelTemp;
		//model = glm::translate(model, glm::vec3(0.0f, 0.093f, 0.208f));
		//model = glm::rotate(model, glm::radians(head), glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//HeadDog.Draw(lightingShader);
		////Tail 
		//model = modelTemp;
		//model = glm::translate(model, glm::vec3(0.0f, 0.026f, -0.288f));
		//model = glm::rotate(model, glm::radians(tail), glm::vec3(0.0f, 0.0f, -1.0f)); 
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		//DogTail.Draw(lightingShader);
		////Front Left Leg
		//model = modelTemp;
		//model = glm::translate(model, glm::vec3(0.112f, -0.044f, 0.074f));
		//model = glm::rotate(model, glm::radians(FLegs), glm::vec3(-1.0f, 0.0f, 0.0f)); 
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//F_LeftLeg.Draw(lightingShader);
		////Front Right Leg
		//model = modelTemp; 
		//model = glm::translate(model, glm::vec3(-0.111f, -0.055f, 0.074f));
		//model = glm::rotate(model, glm::radians(FLegs), glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//F_RightLeg.Draw(lightingShader);
		////Back Left Leg
		//model = modelTemp; 
		//model = glm::translate(model, glm::vec3(0.082f, -0.046, -0.218)); 
		//model = glm::rotate(model, glm::radians(RLegs), glm::vec3(1.0f, 0.0f, 0.0f)); 
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		//B_LeftLeg.Draw(lightingShader);
		////Back Right Leg
		//model = modelTemp; 
		//model = glm::translate(model, glm::vec3(-0.083f, -0.057f, -0.231f));
		//model = glm::rotate(model, glm::radians(RLegs), glm::vec3(-1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//B_RightLeg.Draw(lightingShader); 


		//model = glm::mat4(1);
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		//model = glm::rotate(model, glm::radians(rotBall), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	 //   Ball.Draw(lightingShader); 
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);
	

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[0]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		
		glBindVertexArray(0);



		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_Y])
	{
		pointLightPositions[0].y += 0.01f;
	}

	if (keys[GLFW_KEY_H])
	{
		pointLightPositions[0].y -= 0.01f;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z -= 0.1f;
	}
	if (keys[GLFW_KEY_J])
	{
		pointLightPositions[0].z += 0.01f;
	}
	
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(0.2f, 0.8f, 1.0f);
			
		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}
	}
	if (keys[GLFW_KEY_N])
	{
		AnimBall = !AnimBall;
		
	}
	if (keys[GLFW_KEY_B])
	{
		dogAnim = !dogAnim;


	}
	
}
void Animation() {
	if (AnimBall)
	{
		rotBall += 0.4f;
		//printf("%f", rotBall);
	}
	
	if (AnimDog)
	{
		rotDog -= 0.6f;
		//printf("%f", rotBall);
	}
	if (dogAnim == 1) { //Walk animation
		if (dogPos.z <= 2.2 and dirz==false and diag==false) {
			if (!step) {
				RLegs += 0.03f;
				FLegs += 0.03f;
				head += 0.03f;
				tail += 0.03f;
				if (RLegs > 15.0f) {
					step = true;
				}
			}
			else {
				RLegs -= 0.03f;
				FLegs -= 0.03f;
				head -= 0.03f;
				tail -= 0.03f;
				if (RLegs < -15.0f) {
					step = false;
				}
			}
			dogPos.z += 0.0001;
			//printf("%f", dogPos.z);
		}
		else
		{
			if (dogRot <= 90) { // gira
				if (!step) {
					RLegs += 0.03f;
					FLegs += 0.03f;
					head += 0.03f;
					tail += 0.03f;
					if (RLegs > 15.0f) {
						step = true;
					}
				}
				else {
					RLegs -= 0.03f;
					FLegs -= 0.03f;
					head -= 0.03f;
					tail -= 0.03f;
					if (RLegs < -15.0f) {
						step = false;
					}
				}
				dogRot += 0.01;
				//printf("%f   ", dogRot);
			}
			else {
				dirz = true;
				//Walk right
				
				if (dogPos.x <= 2.0 and dirx==false and diag==false) {
					if (!step) {
						RLegs += 0.03f;
						FLegs += 0.03f;
						head += 0.03f;
						tail += 0.03f;
						if (RLegs > 15.0f) {
							step = true;
						}
					}
					else {
						RLegs -= 0.03f;
						FLegs -= 0.03f;
						head -= 0.03f;
						tail -= 0.03f;
						if (RLegs < -15.0f) {
							step = false;
						}
					}
					dogPos.x += 0.0001;
					//printf("%f", dogPos.z);
				}
				else {
					
					if (dogRot <= 180) { // gira hacia atras
						if (!step) {
							RLegs += 0.03f;
							FLegs += 0.03f;
							head += 0.03f;
							tail += 0.03f;
							if (RLegs > 15.0f) {
								step = true;
							}
						}
						else {
							RLegs -= 0.03f;
							FLegs -= 0.03f;
							head -= 0.03f;
							tail -= 0.03f;
							if (RLegs < -15.0f) {
								step = false;
							}
						}
						dogRot += 0.01;
						//printf("%f   ", dogRot);
					}
					else {//camina hacia atr�s
						if (dogPos.z >= -2.1 and dirz==true and diag==false) {
							if (!step) {
								RLegs += 0.03f;
								FLegs += 0.03f;
								head += 0.03f;
								tail += 0.03f;
								if (RLegs > 15.0f) {
									step = true;
								}
							}
							else {
								RLegs -= 0.03f;
								FLegs -= 0.03f;
								head -= 0.03f;
								tail -= 0.03f;
								if (RLegs < -15.0f) {
									step = false;
								}
							}
							dogPos.z -= 0.0001;
							//printf("%f   ", dogPos.z);
						}
						else {
							if (dogRot <= 320) { // gira hacia la diagonal
								if (!step) {
									RLegs += 0.03f;
									FLegs += 0.03f;
									head += 0.03f;
									tail += 0.03f;
									if (RLegs > 15.0f) {
										step = true;
									}
								}
								else {
									RLegs -= 0.03f;
									FLegs -= 0.03f;
									head -= 0.03f;
									tail -= 0.03f;
									if (RLegs < -15.0f) {
										step = false;
									}
								}
								dogRot += 0.01;
								//printf("%f   ", dogRot);
							}
							else {
								dirz = false;
								dirx = true;
								diag = true;
								//printf("%f   ", dogPos.x);
								//printf("%d ",dirx);
								//printf("%f   ", dogPos.z);
								if (dogPos.z <= 0.0 and dirz == false and dogPos.x >= 0.0 and dirx == true and diag == true) {
									if (!step) {
										RLegs += 0.03f;
										FLegs += 0.03f;
										head += 0.03f;
										tail += 0.03f;
										if (RLegs > 15.0f) {
											step = true;
										}
									}
									else {
										RLegs -= 0.03f;
										FLegs -= 0.03f;
										head -= 0.03f;
										tail -= 0.03f;
										if (RLegs < -15.0f) {
											step = false;
										}
									}
									dogPos.z += 0.0001;
									dogPos.x -= 0.0001;
	
								}
								else {
									if (dogRot <= 360) { // gira hacia adelante
										if (!step) {
											RLegs += 0.03f;
											FLegs += 0.03f;
											head += 0.03f;
											tail += 0.03f;
											if (RLegs > 15.0f) {
												step = true;
											}
										}
										else {
											RLegs -= 0.03f;
											FLegs -= 0.03f;
											head -= 0.03f;
											tail -= 0.03f;
											if (RLegs < -15.0f) {
												step = false;
											}
										}
										dogRot += 0.01;
										//printf("%f   ", dogRot);
									}
									else {
										dirz = false;
										dirx = false;
										diag = false;
										dogRot = 0.0;
									}
								}
							}
						}


					}

				}

			}
			
		}
		
		
		
	}
	
	
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}