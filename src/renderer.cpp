#include <renderer.hpp>
#include <exception.hpp>
#include <memory>
#include <optional>
#include <cassert>
#include <array>
#include <glad/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"
#include "read_file.hpp"
#include <unistd.h>

namespace opengles_workspace
{
	Table tetris_table = Table();

	void GLFWRenderer::create_shaders() 
	{
		this->_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(this->_vertex_shader, 1, &this->_vertex_shader_source, nullptr);
		glCompileShader(this->_vertex_shader);

		this->_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(this->_fragment_shader, 1, &this->_fragment_shader_source, nullptr);
		glCompileShader(this->_fragment_shader);

		this->_shader_program = glCreateProgram();
		glAttachShader(this->_shader_program, this->_vertex_shader);
		glAttachShader(this->_shader_program, this->_fragment_shader);
		glLinkProgram(this->_shader_program);
		glUseProgram(this->_shader_program);

		glDeleteShader(_vertex_shader); // delete vertex & fragment shaders
		glDeleteShader(_fragment_shader);
	}

	void GLFWRenderer::set_buffers() 
	{
		glGenVertexArrays(1, &this->_VAO);
		glGenBuffers(1, &this->_VBO);

		glBindVertexArray(this->_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
		glBufferData(GL_ARRAY_BUFFER, tetris_table.get_vertices_array().size() * sizeof(float), tetris_table.get_vertices_array().data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	GLFWRenderer::GLFWRenderer(std::shared_ptr<Context> context)
		: mContext(std::move(context))
	{
		this->create_shaders();
		this->set_buffers();
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
			glUseProgram(this->_shader_program);
			glBindVertexArray(this->_VAO);
			glDrawArrays(GL_TRIANGLES, 0, tetris_table.get_vertices_length() / 3);
			glfwSwapBuffers(window());
			glfwPollEvents();
			tetris_table.move_shape_down(tetris_table.get_axis_y_speed());
			glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
			glBufferData(GL_ARRAY_BUFFER, tetris_table.get_vertices_array().size() * sizeof(float), tetris_table.get_vertices_array().data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		glDeleteVertexArrays(1, &this->_VAO);
		glDeleteBuffers(1, &this->_VBO);
		glDeleteProgram(this->_shader_program);
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