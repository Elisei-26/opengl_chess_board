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

#include <GL/glut.h>
#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library ft;
FT_Face face;

namespace opengles_workspace
{
	Table tetris_table = Table();




	// void initFreeType() 
	// {
	// 	if (FT_Init_FreeType(&ft)) 
	// 	{
	// 		// handle error
	// 	}
	// 	if (FT_New_Face(ft, "../third_party/font/arial.ttf", 0, &face)) 
	// 	{
	// 		// handle error
	// 	}
	// 	FT_Set_Pixel_Sizes(face, 0, 48);
	// }

	// void renderText(const char *text, float x, float y, float scale) 
	// {
	// 	glMatrixMode(GL_MODELVIEW);
	// 	glPushMatrix();
	// 	glLoadIdentity();
	// 	glTranslatef(x, y, 0);
	// 	glScalef(scale, scale, 1);
	// 	FT_GlyphSlot g = face->glyph;
	// 	for (const char *p = text; *p; p++) {
	// 		if (FT_Load_Char(face, *p, FT_LOAD_RENDER)) 
	// 		{
	// 			continue;
	// 		}
	// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
	// 		float x2 = x + g->bitmap_left * scale;
	// 		float y2 = -y - g->bitmap_top * scale;
	// 		float w = g->bitmap.width * scale;
	// 		float h = g->bitmap.rows * scale;
	// 		glBegin(GL_QUADS);
	// 		glTexCoord2f(0, 0); glVertex2f(x2, -y2);
	// 		glTexCoord2f(1, 0); glVertex2f(x2 + w, -y2);
	// 		glTexCoord2f(1, 1); glVertex2f(x2 + w, -y2 - h);
	// 		glTexCoord2f(0, 1); glVertex2f(x2, -y2 - h);
	// 		glEnd();
	// 		x += (g->advance.x >> 6) * scale;
	// 		y += (g->advance.y >> 6) * scale;
	// 	}
	// 	glPopMatrix();
	// }

	// void display() 
	// {
	// 	glClear(GL_COLOR_BUFFER_BIT);
	// 	renderText("Hello, OpenGL!", 100, 100, 1.0f);
	// 	glutSwapBuffers();
	// }



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





		// // glutInit(&argc, argv);
		// glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		// // glutInitWindowSize(800, 600);
		// // glutCreateWindow("OpenGL Text Rendering");
		// glMatrixMode(GL_PROJECTION);
		// glLoadIdentity();
		// // glOrtho(0, 1000, 0, 1000, -1, 1);
		// // glOrtho(0.0f, 1000, 1000, 0.0f, -1.0f, 1.0f);
		// glutDisplayFunc(display);
		// initFreeType();
		// glutMainLoop();






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