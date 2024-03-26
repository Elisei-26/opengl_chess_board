#include <renderer.hpp>
#include <exception.hpp>
#include <memory>
#include <optional>
#include <cassert>
#include <array>
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"
#include "read_file.hpp"
#include <unistd.h>

#include <../third_party/glm/glm.hpp>
#include <../third_party/glm/gtc/matrix_transform.hpp>
#include <../third_party/glm/gtc/type_ptr.hpp>

namespace opengles_workspace
{
	const char* vertexShaderSource = R"(
										#version 300 es
										layout (location = 0) in vec3 aPos;

										void main() {
											gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
										}
									)";

	const char* fragmentShaderSource = R"(
											#version 300 es
											out highp vec4 FragColor;

											void main() {
												FragColor = vec4(1.0, 0.5, 0.2, 1.0);
											}
										)";
	float vertices[] = {
		-0.25f, -1.0f, 0.0f,
		0.25f, -1.0f, 0.0f,
		-0.25f,  -0.5f, 0.0f,
		-0.25f,  -0.5f, 0.0f,
		0.25f, -1.0f, 0.0f,
		0.25f, -0.5f, 0.0f
	};

	float speed = 0.0f;
	GLuint vertexShader, fragmentShader, shaderProgram;
	int nr_frames = 0;
	GLuint VBO, VAO;

	void create_shaders() 
	{
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		glUseProgram(shaderProgram);

		glDeleteShader(vertexShader); // delete vertex & fragment shaders
		glDeleteShader(fragmentShader);
	}

	void set_buffers() 
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	GLFWRenderer::GLFWRenderer(std::shared_ptr<Context> context)
		: mContext(std::move(context))
	{
		create_shaders();
		set_buffers();
	}

	void change_vertices_coordonates(char ax) 
	{
		int vertices_leng = sizeof(vertices)/sizeof(float);
		int start = (ax == 'x') ? 0 : 1;

		for (int i = start; i < vertices_leng; i += 3) 
		{
			vertices[i] += speed;
		}

		for (int i = start; i < vertices_leng; i += 3)
		{ 
			if (vertices[i] >= 1.0f || vertices[i] <= -1.0f) 
			{
				speed *= -1.0f;
				i = vertices_leng;
			}
		}
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_UP && action == GLFW_REPEAT) 
		{
			if (speed < 0) {
				speed *= -1.0f;
			}
			change_vertices_coordonates('y');
		}
		else if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
		{
			if (speed > 0) {
				speed *= -1.0f;
			}
			change_vertices_coordonates('y');
		} 
		else if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
		{
			if (speed > 0) {
				speed *= -1.0f;
			}
			change_vertices_coordonates('x');
		} 
		else if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
		{
			if (speed < 0) {
				speed *= -1.0f;
			}
			change_vertices_coordonates('x');
		}

	}

	void GLFWRenderer::render() 
	{
		// GL code begin
		glfwInit();

		glfwSetKeyCallback(window(), key_callback);
		
		ReadFile reader = ReadFile();
		int nr_frames = reader.read_file("../src/data.txt");
		speed = (float)1 / nr_frames;

		while (!glfwWindowShouldClose(window())) {
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(shaderProgram);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			glfwSwapBuffers(window());
			glfwPollEvents();

			key_callback;
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);

		glfwTerminate();
		
		// GL code end
		glfwSwapBuffers(window());
	}

	bool GLFWRenderer::poll() {
		if (glfwWindowShouldClose(window())) {
			return false;
		}
		return true;
	}
}