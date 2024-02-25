#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <STB_IMAGE/stb_image.h>
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"


bool switchPolygonMode = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}


	static int qKeyPreviousState = GLFW_RELEASE;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && qKeyPreviousState == GLFW_RELEASE) {
		switchPolygonMode = !switchPolygonMode;
		(switchPolygonMode) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	qKeyPreviousState = glfwGetKey(window, GLFW_KEY_Q);
}

int main() {
	stbi_set_flip_vertically_on_load(true);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //mowimy o wersji opengl czyli 3.3 (ale piszemy 3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //mowimy ze uzywamy core profile

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL); //tworzymy okno
	if (window == NULL) { //jak sie nie uda usuwamy glfw
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //wlaczamy okno (ale wylaczy sie odrazu)

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { //ladujemy glad zeby móc wogóle i latwiej pisac komendy
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST); //wlacz depth testing z z-buffera

	glViewport(0, 0, 800, 600); //ustawiamy viewport na 800x600
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //na event zmiany okna zmieniamy viewport

	float vertices[] = {
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
- 0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};


	GLuint indices[] = {
		0,1,3,
		1,2,3
	};

	GLfloat texCoords[] = {
		0.0f,0.0f,
		1.0f,0.0f,
		0.5f,1.0f
	};



	VAO vao;
	vao.Bind();
	VBO vbo(vertices, sizeof(vertices));
	//EBO ebo(indices, sizeof(indices));
	vao.LinkVBOTexture(vbo, 0, 1);

	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels,0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	unsigned int texture1;
	glGenTextures(1, &texture1);
	data = stbi_load("lolek.jpg", &width, &height, &nrChannels, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}


	Shader myShader("default.vert", "default.frag");

	
	vao.Unbind();
	vbo.Unbind();
	//ebo.Unbind();
	float lastFrame = glfwGetTime();
	float currentFrame = glfwGetTime();
	float deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	while (!glfwWindowShouldClose(window)) {//render loop - jezeli nie zamykamy okna to zamieniamy bufor i updatujemy input itp
		processInput(window);  //je¿eli wcisnie sie escape to gg ustawiamy window should sclose na true

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myShader.Activate();


		camera.Inputs(window,deltaTime);
		camera.Matrix(90.0f, 0.1f, 100.0f, myShader, "camMatrix");

		/*
		//object to world
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
 
		//view matrix eye matrix camera matrix
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0, 0.0f, -3.0f));

		float aspect = 800.0f / 600.0f;
		float n = 0.1f;
		float f = 100.0f;
		float l = -aspect;
		float r = aspect;
		float b = -1.0f;
		float t = 1.0f;

		float fov = glm::radians(45.0f);
		//glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		glm::mat4 projectionOrth = glm::mat4(2.0f / (r - l) , 0.0f, 0.0f, -(r+l)/(r-l),
											0.0f, 2.0f / (t-b), 0.0f, -(t+b)/(t-b),
											0.0f, 0.0f, -2.0f/(f-n), -(f+n)/(f-n),
											0.0f, 0.0f, 0.0f, 1.0f);

		glm::mat4 projectionPers = glm::mat4(1/(tan(fov/2)*aspect), 0.0f, 0.0f, 0.0f,
											0.0f, 1/(tan(fov/2)), 0.0f, 0.0f,
											0.0f, 0.0f, -(f+n)/(f-n), (-2.0f*f*n) / (f - n),
											0.0f, 0.0f, -1.0f, 0.0f);
		//glm::mat4 projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, 3.0f, 100.0f);

		projectionOrth = glm::transpose(projectionOrth);
		projectionPers = glm::transpose(projectionPers);
		glm::mat4 projection = projectionPers;

		int modelLoc = glGetUniformLocation(myShader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(myShader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projectionLoc = glGetUniformLocation(myShader.ID, "perspective");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		*/

		glUniform1i(glGetUniformLocation(myShader.ID, "Texture1"), 0);
		glUniform1i(glGetUniformLocation(myShader.ID, "Texture2"), 1);
		vao.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	myShader.Delete();
	vbo.Delete();
	//ebo.Delete();
	vao.Delete();
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &texture1);
	
	glfwTerminate();
	return 0;
}

