#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include "Camera.h"

#pragma region model data
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

//unsigned int indices[] = {  // note that we start from 0!
//	0, 1, 2,   // first triangle
//	2, 3, 0    // second triangle
//};


#pragma endregion

#pragma region input declare
float lastX , lastY;
bool firstMouse = true;

float moveSpeed = 0.01f;
float moveAccelerate = 4.0f;
float mouseSpeed = 0.001f;

#pragma endregion

#pragma region camera
//instantiate camera
//Camera cam(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));
Camera cam(glm::vec3(0, 0, 3.0f), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));

#pragma endregion


void myInput(GLFWwindow *window)
{
	//Exit Game
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float tempMoveSpeed = moveSpeed;

	//Camera Move
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		tempMoveSpeed *= moveAccelerate;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.Position += tempMoveSpeed * cam.Forward;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.Position -= tempMoveSpeed * cam.Forward;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.Position -= tempMoveSpeed * cam.Right;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.Position += tempMoveSpeed * cam.Right;

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cam.Position.y += tempMoveSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cam.Position.y -= tempMoveSpeed;

}

void myLoadTexture(unsigned int texBuffer, const char* textureName,GLint internalFormat) {

	glGenTextures(1, &texBuffer);
	glActiveTexture(GL_TEXTURE0 + texBuffer - 1);

	glBindTexture(GL_TEXTURE_2D, texBuffer);

	int width, height, nrChannel;
	unsigned char *data = stbi_load(textureName, &width, &height, &nrChannel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void ShaderFunction(Shader shader) {
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shader.ID, "ourColor");
	shader.use();
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	
	if (firstMouse == true) {
		
		lastX = xpos;
		lastY = ypos;

		firstMouse = false;
	}
	
	float deltaX = xpos - lastX;
	float deltaY = ypos - lastY;

	lastX = xpos;
	lastY = ypos;
	
	deltaX *= mouseSpeed;
	deltaY *= mouseSpeed;
	 
	cam.ProcessMouseMovement(deltaX, deltaY);
}


int main() {

	#pragma region open window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	//Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "MyOpenGLWindow", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("Init GLEW failed");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);

	#pragma endregion


	#pragma region gl setting...

	//cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	//open cull back
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/

	//Line mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//z buffert
	glEnable(GL_DEPTH_TEST);
	#pragma endregion


	#pragma region loadModel use VAO, VBO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/




	// VBO顶点属性位置
	//参数n * sizeof(float)，每隔n个属性为一组
	//(void*)(n * sizeof(float))，组内偏移量
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// VBO颜色属性位置
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	// VBO贴图属性位置
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// VBO法线属性位置
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(3);

	#pragma endregion


	#pragma region texture
	stbi_set_flip_vertically_on_load(true);

	/*unsigned int texBufferA = 1;
	myLoadTexture(texBufferA, "container.jpg", GL_RGB);*/


	/*unsigned int texBufferB = 2;
	myLoadTexture(texBufferB, "awesomeface.png", GL_RGBA);*/

	unsigned int texBufferC = 3;
	myLoadTexture(texBufferC, "container2.png", GL_RGBA);

	unsigned int texBufferD = 4;
	myLoadTexture(texBufferD, "container2_specular.png", GL_RGBA);

	#pragma endregion
	

	#pragma region matrix declare

	#pragma region MVP matrixes
	//矩阵默认是单位矩阵，0.99及更高默认零矩阵
	//如果同时出现，务必按照translate -> rotate -> scale的顺序;

	glm::mat4 modelMat;
	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0, 0));
	glm::mat4 viewMat;
	//projection：以相机为原点移动物体，然后投影
	glm::mat4 projMat;
	//投射角度、长宽、近平面、远平面
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	#pragma endregion
	
	glm::mat4 transform;

	#pragma endregion

	
	
	Shader test = Shader("VertexSourceCode.vert", "FragmentSourceCode.frag");

	

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		
		// input
		myInput(window);

		//Background clear
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		#pragma region VAO setting
		//set material -> texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texBufferC);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texBufferD);

		//set texture to model
		glBindVertexArray(VAO);
		#pragma endregion
		


		

		#pragma region shader and draw call

		//set material -> shader
		ShaderFunction(test);
		test.use();

		#pragma region loop matrix

		viewMat = cam.GetViewMatrix();

		glUniformMatrix4fv(glGetUniformLocation(test.ID, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
		glUniformMatrix4fv(glGetUniformLocation(test.ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniformMatrix4fv(glGetUniformLocation(test.ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(test.ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		#pragma endregion


		//glUniform1i(glGetUniformLocation(test.ID, "myTextureA"), 0);
		//glUniform1i(glGetUniformLocation(test.ID, "myTextureB"), 1);

		//position
		glUniform3f(glGetUniformLocation(test.ID, "light.position"), 10.0f, 10.0f, -5.0f);
		glUniform3f (glGetUniformLocation(test.ID, "viewPos"),cam.Position.x, cam.Position.y, cam.Position.z);

		//system color
		glUniform3f(glGetUniformLocation(test.ID, "light.color"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(test.ID, "light.ambient"), 0.2f, 0.2f, 0.2f);

		//object color
		glUniform1i(glGetUniformLocation(test.ID, "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(test.ID, "material.specular"), 1);
		glUniform1f(glGetUniformLocation(test.ID, "material.glossPower"),256.0f);

		//draw call
		glDrawArrays(GL_TRIANGLES, 0, 36);

		#pragma endregion


		//clean up and prepare next render loop
		glfwSwapBuffers(window);
		//check keyboard
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;

}