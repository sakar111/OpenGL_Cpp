#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

//#define GLM_FORCE_CTOR_INIT

#include "Renderer.h"
#include "VertexBuffer.h"
//#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
//#include "Texture.h"
#include "Camera.h"
//#include "Material.h"
#include "Light.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtx/string_cast.hpp>
#include "Model.h"


#define WIDTH 1920
#define HEIGHT 1080


GLFWwindow* window;


int initialization();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void do_movement();

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void set_camera(glm::vec3 carPos, float theta);


const glm::vec3 cameraPos = glm::vec3(-50.0f, 50.0f, 50.0f);
const glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//const glm::vec3 cameraFront = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
const float fov = 45.0f;
const float yaw = 0.0f;
const float pitch = 0.0f;
const float keystroke_speed = 50.0f;
const float mouse_sensitivity = 0.50f;

Camera camera(cameraPos, cameraFront, worldUp, fov, yaw, pitch, keystroke_speed, mouse_sensitivity);



bool keys[1024];
float deltaTime = 0.0f;

bool firstMouse = true;
float lastX;
float lastY;


int main(void)
{
	if (initialization() == -1)
		return -1;

	Model SunModel("res/models/sun/sun.obj");

	Shader SunShader("res/shaders/LightingSource.shader");
	glm::mat4 light_model(1.0);
	light_model = glm::translate(light_model, Lights::Sun.Position);
	light_model = glm::scale(light_model, glm::vec3(10.0f));
	SunShader.Bind();
	SunShader.SetUniformMat4f("model", light_model);
	SunShader.SetUniform3f("lightColor", Lights::Sun.Color);


	Model envModel("res/models/env/env.obj");

	float env_rotate = 0.0f;//-90.0f;
	Shader EnvShader("res/shaders/Model.shader");
	EnvShader.Bind();
	glm::mat4 env_model(1.0);
	env_model = glm::rotate(env_model, glm::radians(env_rotate), glm::vec3(0.0f, 1.0f, 0.0f));
	env_model = glm::scale(env_model, glm::vec3(5.0f, 5.0f, 5.0f));
	EnvShader.SetUniformMat4f("model", env_model);
	EnvShader.SetUniformLight("light", Lights::Sun);
	glm::mat3 transpose_inverse_env_model = glm::transpose(glm::inverse(env_model));
	EnvShader.SetUniformMat3f("transpose_inverse_model", transpose_inverse_env_model);








	Model Chevrolet("res/models/chevrolet_camaro_ss/Chevrolet_Camaro_SS_High.obj");
	Shader ChevroletShader("res/shaders/Model.shader");
	glm::vec3 ChevroletPos(6.0f, 2.80f, -167.0f);
	float ChevroletAngle = 0.0f;
	glm::mat4 chevrolet_model(1.0f);
	chevrolet_model = glm::translate(chevrolet_model, ChevroletPos);
	ChevroletShader.Bind();
	ChevroletShader.SetUniformMat4f("model", chevrolet_model);
	ChevroletShader.SetUniformLight("light", Lights::Sun);



	Model Camioneta("res/models/camioneta/camioneta_High.obj");
	Shader CamionetaShader("res/shaders/Model.shader");
	glm::vec3 CamionetaPos(6.0f, 3.35f, -88.0f);
	float CamionetaAngle = 0.0f;
	glm::mat4 camioneta_model(1.0f);
	camioneta_model = glm::translate(camioneta_model, CamionetaPos);
	CamionetaShader.Bind();
	CamionetaShader.SetUniformMat4f("model", camioneta_model);
	CamionetaShader.SetUniformLight("light", Lights::Sun);



	Model Toyota("res/models/25-vaz-2108/Ba3 2108.obj");
	Shader ToyotaShader("res/shaders/Model.shader");
	glm::vec3 ToyotaPos(-8.5f, 0.35f, 167.0f);
	float ToyotaAngle = -90.0f;
	glm::mat4 toyota_model(1.0f);
	toyota_model = glm::translate(toyota_model, ToyotaPos);
	toyota_model = glm::scale(toyota_model, glm::vec3(1.40f, 1.40f, 1.40f));
	toyota_model = glm::rotate(toyota_model, glm::radians(ToyotaAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	ToyotaShader.Bind();
	ToyotaShader.SetUniformMat4f("model", toyota_model);
	ToyotaShader.SetUniformLight("light", Lights::Sun);





	Model Bus("res/models/bus/BUS.obj");
	Shader BusShader("res/shaders/Model.shader");
	glm::vec3 BusPos(-11.0f, 8.35f, 127.0f);
	float BusAngle = 90.0f;
	glm::mat4 bus_model(1.0f);
	bus_model = glm::translate(bus_model, BusPos);
	bus_model = glm::scale(bus_model, glm::vec3(2.50f, 2.50f, 2.50f));
	bus_model = glm::rotate(bus_model, glm::radians(BusAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	BusShader.Bind();
	BusShader.SetUniformMat4f("model", bus_model);
	BusShader.SetUniformLight("light", Lights::Sun);


	Renderer renderer;

	glEnable(GL_DEPTH_TEST);

	float lastFrame = 0.0f;
	float currentFrame = 0.0f;

	float theta = 180.0f;

	while (glfwWindowShouldClose(window) == 0)
	{
		glm::vec3 sky_color(72.0f, 119.0f, 167.0f);
		renderer.Clear(sky_color);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		CamionetaPos.z += deltaTime * 20.0f;
		ToyotaPos.x -= deltaTime * 15.0f;
		BusPos.x += deltaTime * 6.0f;

		if (CamionetaPos.z >= 184.0f)
		{
			camioneta_model = glm::translate(camioneta_model, glm::vec3(0.0f, 0.0f, -CamionetaPos.z - 150.0f));
			CamionetaPos.z = -150.0f;
		}
			

		if (ToyotaPos.x <= -245.0f)
		{
			toyota_model = glm::translate(toyota_model, glm::vec3(-ToyotaPos.x - 0.0f, 0.0f, 0.0f));
			ToyotaPos.x = 0.0f;
		}
			
		
		if (BusPos.x >= 104.0f)
		{
			bus_model = glm::translate(bus_model, glm::vec3(-BusPos.x -30.0f, 0.0f, 0.0f));
			BusPos.x = -30.0f;
		}

		std::cout << ChevroletPos.z << std::endl;
			

		camioneta_model = glm::translate(camioneta_model, glm::vec3(0.0f, 0.0f, deltaTime * 20.0f));
		toyota_model = glm::translate(toyota_model, glm::vec3(-deltaTime * 15.0f, 0.0f, 0.0f));
		bus_model = glm::translate(bus_model, glm::vec3(deltaTime * 6.0f, 0.0f, 0.0f));



		float distance = deltaTime * 50.0f;
		float turnAngle = 1.0f;

		if (keys[GLFW_KEY_UP])
		{
			ChevroletPos.z -= distance * cos(glm::radians(theta));
			ChevroletPos.x -= distance * sin(glm::radians(theta));
			if (abs(ChevroletPos.x) < 8.50f && abs(ChevroletPos.z) < 170.0f)
				chevrolet_model = glm::translate(chevrolet_model, glm::vec3(sin(glm::radians(ChevroletAngle)) * distance, 0.0f, /*ChevroletAngle / abs(ChevroletAngle) **/ cos(glm::radians(ChevroletAngle)) * distance));
			else
			{
				ChevroletPos.z += distance * cos(glm::radians(theta));
				ChevroletPos.x += distance * sin(glm::radians(theta));
			}
		}
		if (keys[GLFW_KEY_LEFT])
		{
			theta += turnAngle;
			chevrolet_model = glm::rotate(chevrolet_model, glm::radians(turnAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (keys[GLFW_KEY_RIGHT])
		{
			theta -= turnAngle;
			chevrolet_model = glm::rotate(chevrolet_model, glm::radians(-turnAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (keys[GLFW_KEY_DOWN])
		{
			ChevroletPos.z += distance * cos(glm::radians(theta));
			ChevroletPos.x += distance * sin(glm::radians(theta));
			if (abs(ChevroletPos.x) < 8.50f && abs(ChevroletPos.z) < 170.0f)
				chevrolet_model = glm::translate(chevrolet_model, glm::vec3(-sin(glm::radians(ChevroletAngle)) * distance, 0.0f,/* ChevroletAngle /abs(ChevroletAngle)* */ -cos(glm::radians(ChevroletAngle)) * distance));
			else
			{
				ChevroletPos.z -= distance * cos(glm::radians(theta));
				ChevroletPos.x -= distance * sin(glm::radians(theta));
			}
		}

		if (keys[GLFW_KEY_PAGE_UP])
		{
			ChevroletPos.y += 0.1f;
			chevrolet_model = glm::translate(chevrolet_model, glm::vec3(0.0f, 0.1f, 0.0f));
		}

		if (keys[GLFW_KEY_PAGE_DOWN])
		{
			ChevroletPos.y -= 0.1f;
			chevrolet_model = glm::translate(chevrolet_model, glm::vec3(0.0f, -0.1f, 0.0f));
		}

		std::cout <<glm::to_string(ChevroletPos) << std::endl;

		ChevroletShader.Bind();
		ChevroletShader.SetUniformMat4f("model", chevrolet_model);
		ChevroletShader.SetUniformMat3f("transpose_inverse_model", glm::transpose(glm::inverse(chevrolet_model)));

		CamionetaShader.Bind();
		CamionetaShader.SetUniformMat4f("model", camioneta_model);
		CamionetaShader.SetUniformMat3f("transpose_inverse_model", glm::transpose(glm::inverse(camioneta_model)));

		ToyotaShader.Bind();
		ToyotaShader.SetUniformMat4f("model", toyota_model);
		ToyotaShader.SetUniformMat3f("transpose_inverse_model", glm::transpose(glm::inverse(toyota_model)));

		BusShader.Bind();
		BusShader.SetUniformMat4f("model", bus_model);
		BusShader.SetUniformMat3f("transpose_inverse_model", glm::transpose(glm::inverse(bus_model)));

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Fov), (float)WIDTH / (float)HEIGHT, 0.1f, 500.0f);
		
		SunShader.Bind();
		SunShader.SetUniformMat4f("view", view);
		SunShader.SetUniformMat4f("projection", projection);
		
		glm::vec3 viewPos = camera.Position + camera.Front;

		EnvShader.Bind();
		EnvShader.SetUniform3f("viewPos", viewPos);
		EnvShader.SetUniformMat4f("view", view);
		EnvShader.SetUniformMat4f("projection", projection);


		ChevroletShader.Bind();
		ChevroletShader.SetUniform3f("viewPos", viewPos);
		ChevroletShader.SetUniformMat4f("view", view);
		ChevroletShader.SetUniformMat4f("projection", projection);

		CamionetaShader.Bind();
		CamionetaShader.SetUniform3f("viewPos", viewPos);
		CamionetaShader.SetUniformMat4f("view", view);
		CamionetaShader.SetUniformMat4f("projection", projection);

		ToyotaShader.Bind();
		ToyotaShader.SetUniform3f("viewPos", viewPos);
		ToyotaShader.SetUniformMat4f("view", view);
		ToyotaShader.SetUniformMat4f("projection", projection);

		BusShader.Bind();
		BusShader.SetUniform3f("viewPos", viewPos);
		BusShader.SetUniformMat4f("view", view);
		BusShader.SetUniformMat4f("projection", projection);

		SunModel.Draw(SunShader);
		envModel.Draw(EnvShader);
		Chevrolet.Draw(ChevroletShader);
		Camioneta.Draw(CamionetaShader);
		Toyota.Draw(ToyotaShader);
		Bus.Draw(BusShader);
	

		if (keys[GLFW_KEY_ENTER])
			camera.mouse_enable = false;
		else if (keys[GLFW_KEY_M])
			camera.mouse_enable = true;
		if (camera.mouse_enable)
			do_movement();
		else
			set_camera(ChevroletPos, theta);

		if (keys[GLFW_KEY_ESCAPE])
			glfwSetWindowShouldClose(window, GL_TRUE);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


int initialization()
{
	if (!glfwInit())
	{
		std::cout << "Error initializing glfw" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "CAR COLLISION SIMULATION", glfwGetPrimaryMonitor(), NULL);
	if (!window)
	{
		std::cout << "Self Driving Car Simulator" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);	// make current window the Opengl rendering context

	glfwSwapInterval(1);	//synchronizing with monitor frequency i.e 60Hz

	if (glewInit() != GLEW_OK)	// glewInit() should be called after a valid OpenGL rendering context is created
		std::cout << "Error while initializing glew" << std::endl;

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	std::cout << glGetString(GL_VERSION) << std::endl;	// print opengl version and graphics card version

	glfwSetKeyCallback(window, key_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetScrollCallback(window, scroll_callback);

	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}


void do_movement()
{
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(Camera_Movement::forward, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(Camera_Movement::backward, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(Camera_Movement::left, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(Camera_Movement::right, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;
	
	if(camera.mouse_enable)
		camera.ProcessMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void set_camera(glm::vec3 carPos, float theta)
{
	float camera_distance = 15.0f;
	float camera_height = 5.0f;
	camera.Position.x = carPos.x + camera_distance * sin(glm::radians(theta));
	camera.Position.y = carPos.y + camera_height;
	camera.Position.z = carPos.z + camera_distance * cos(glm::radians(theta));

	camera.Front = carPos;
}