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

	GLuint vertexShader, fragmentShader, shaderProgram;
	GLuint VBO, VAO;
	Table tetris_table;

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
		glBufferData(GL_ARRAY_BUFFER, tetris_table.get_vertices_array().size() * sizeof(float), tetris_table.get_vertices_array().data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	GLFWRenderer::GLFWRenderer(std::shared_ptr<Context> context)
		: mContext(std::move(context))
	{
		tetris_table = Table();
		create_shaders();
		set_buffers();
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
	{
		if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
		{
			tetris_table.move_shape_down(tetris_table.get_axis_y_speed() * 3.0f);
		}
		else if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		{
			tetris_table.move_shape_to_right();
		}
		else if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		{
			tetris_table.move_shape_to_left();
		} 
		else if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
		{
			tetris_table.rotate_shape();
		}
	}

	void GLFWRenderer::render() 
	{
		glfwInit();
		glfwSetKeyCallback(window(), key_callback);

		ReadFile reader = ReadFile();
		tetris_table.set_nr_frames(reader.read_file("../src/data.txt"));
		tetris_table.set_axis_y_speed();
		while (!glfwWindowShouldClose(window()) && !tetris_table.game_over()) 
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, tetris_table.get_vertices_length() / 3);
			glfwSwapBuffers(window());
			glfwPollEvents();
			tetris_table.move_shape_down(tetris_table.get_axis_y_speed());
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, tetris_table.get_vertices_array().size() * sizeof(float), tetris_table.get_vertices_array().data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);
		std::cout << tetris_table.get_score() << "\n";

		glfwSwapBuffers(window());
	}

	bool GLFWRenderer::poll() 
	{
		if (glfwWindowShouldClose(window())) 
		{
			return false;
		}
		return true;
	}
}