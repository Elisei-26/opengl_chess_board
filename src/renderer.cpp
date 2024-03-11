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

namespace opengles_workspace
{
	const char* vertex_shader_source = "#version 300 es\n"
										"precision lowp float;\n"
										"layout (location = 0) in vec3 a_pos;\n"
										"void main()\n"
										"{\n"
										"	gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);\n"
										"}\0";

	const char* fragment_shader_source = "#version 300 es\n"
										"precision lowp float;\n"
										"out vec4 frag_color;\n"
										"void main()\n"
										"{\n"
										"	frag_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);\n" // black
										"}\n\0";

	const char* fragment_shader_source2 = "#version 300 es\n"
										"precision lowp float;\n"
										"out vec4 frag_color;\n"
										"void main()\n"
										"{\n"
										"	frag_color = vec4(0.0f, 0.69f, 0.69f, 1.0f);\n" // dark cyan
										"}\n\0";
	
	GLuint vertex_shader, fragment_shader, fragment_shader2, shader_program, shader_program2;
	GLfloat vertices1[100000], vertices2[100000];
	int nr_lines = 0, nr_columns = 0;

	void readData() {
		std::ifstream file_in;
		file_in.open("../src/data.txt");
		if (!file_in.is_open()) {
			return;
		}
		std::string line;
		while (std::getline(file_in, line) && nr_columns == 0) { // search first 2 numbers from file
			bool flag_nr_line = false, flag_nr_col = false;
			int nr_aux = 0;
			for (auto i : line) {				// search numbers from string if are there
				if (isdigit(i)) {
					nr_aux = nr_aux * 10 + i - '0';
				} else if (!isdigit(i) && nr_aux != 0 && flag_nr_line == false) {
					flag_nr_line = true;
					nr_lines = nr_aux;
					nr_aux = 0;
				} else if (!isdigit(i) && nr_aux != 0 && flag_nr_col == false) {
					flag_nr_col = true;
					nr_columns = nr_aux;
					nr_aux = 0;
				}
			}
			if (nr_aux != 0 && flag_nr_col == false) {
				nr_columns = nr_aux;
			}
		}
		file_in.close();
	}

	GLFWRenderer::GLFWRenderer(std::shared_ptr<Context> context)
		: mContext(std::move(context))
	{
		vertex_shader = glCreateShader(GL_VERTEX_SHADER); // create vertex shader
		glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL); // 1 is no of strings used for shader
		glCompileShader(vertex_shader);

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER); // create fragment shader
		glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL); // 1 is no of strings used for shader
		glCompileShader(fragment_shader);

		fragment_shader2 = glCreateShader(GL_FRAGMENT_SHADER); // create fragment shader
		glShaderSource(fragment_shader2, 1, &fragment_shader_source2, NULL); // 1 is no of strings used for shader
		glCompileShader(fragment_shader2);

		shader_program = glCreateProgram(); // create shader program
		glAttachShader(shader_program, vertex_shader);
		glAttachShader(shader_program, fragment_shader);
		glLinkProgram(shader_program);

		shader_program2 = glCreateProgram(); // create shader program
		glAttachShader(shader_program2, vertex_shader);
		glAttachShader(shader_program2, fragment_shader2);
		glLinkProgram(shader_program2);

		glDeleteShader(vertex_shader); // delete vertex & fragment shaders
		glDeleteShader(fragment_shader);
		glDeleteShader(fragment_shader2);

		readData();
	}

	void draw(GLuint shader_program, bool clear, int nr_vertices) {
		GLuint VAO, VBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		if (clear) {
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_DYNAMIC_DRAW);
		} else {
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_DYNAMIC_DRAW);
		}

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		if (clear) {
			glClearColor(255.0f, 255.0f, 255.0f, 1.0f); // set background color
			glClear(GL_COLOR_BUFFER_BIT);
		}
		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, nr_vertices * 3);

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shader_program);
	}

	void GLFWRenderer::render() {
		// GL code begin
		glfwInit();

		float x_step = 2.0 / nr_columns, y_step = 2.0 / nr_lines;
		float x = -1.0, y1 = x + x_step, y2 = x + y_step, x_modifier = 0.0, y_modifier = 0.0;
		short vert_ind = 0, half_columns = nr_columns;
		if (nr_columns % 2 == 1) { // if nr of columns is even
			half_columns += 1;
		}
		half_columns = half_columns / 2;
		short double_nr_lines = nr_lines * 2;
		bool flag = true; // used as a switch for case when nr lines is odd
		for (short i = 0; i < double_nr_lines; ++i) {
			for (short j = 0; j < half_columns; ++j) {
				if (i < nr_lines) {
					vertices1[vert_ind++] = x + x_modifier;
					vertices1[vert_ind++] = x + y_modifier;
					vertices1[vert_ind++] = y1 + x_modifier;
					vertices1[vert_ind++] = x + y_modifier;
					vertices1[vert_ind++] = x + x_modifier;
					vertices1[vert_ind++] = y2 + y_modifier;

					vertices1[vert_ind++] = x + x_modifier;
					vertices1[vert_ind++] = y2 + y_modifier;
					vertices1[vert_ind++] = y1 + x_modifier;
					vertices1[vert_ind++] = x + y_modifier;
					vertices1[vert_ind++] = y1 + x_modifier;
					vertices1[vert_ind++] = y2 + y_modifier;
				} else {
					vertices2[vert_ind++] = x + x_modifier;
					vertices2[vert_ind++] = x + y_modifier;
					vertices2[vert_ind++] = y1 + x_modifier;	
					vertices2[vert_ind++] = x + y_modifier;
					vertices2[vert_ind++] = x + x_modifier;
					vertices2[vert_ind++] = y2 + y_modifier;

					vertices2[vert_ind++] = x + x_modifier;
					vertices2[vert_ind++] = y2 + y_modifier;
					vertices2[vert_ind++] = y1 + x_modifier;
					vertices2[vert_ind++] = x + y_modifier;
					vertices2[vert_ind++] = y1 + x_modifier;
					vertices2[vert_ind++] = y2 + y_modifier;
				}
				x_modifier += (2 * x_step);
			}
			x_modifier = 0.0;

			if (i % 2 == 0 && i < nr_lines) {
				x_modifier = x_step;
			} else if (i % 2 == 1 && i > nr_lines - 1) {
                x_modifier = x_step;
            }
			if (i % 2 == 1 && i > nr_lines - 1 && nr_lines % 2 == 1 && flag) { // when nr lines is odd
                x_modifier = 0.0;
				flag = false;
            } else if (!flag) {
				x_modifier = x_step;
				flag = true;
			}
			y_modifier += y_step;
            if (i == nr_lines - 1) {
				vert_ind = 0;
                x = -1.0, y1 = x + x_step, y2 = x + y_step, x_modifier = x_step, y_modifier = 0.0;
            }
		}
		int half_of_squres = (nr_lines * nr_columns) / 2;
		if (half_of_squres == 0) {
			half_of_squres = 1;
		}
		int nr_vertices = half_of_squres * 6;
		draw(shader_program, true, nr_vertices);
		draw(shader_program2, false, nr_vertices);
		
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