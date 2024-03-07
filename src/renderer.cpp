#include <renderer.hpp>
#include <exception.hpp>
#include <memory>
#include <optional>
#include <cassert>
#include <array>
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace opengles_workspace
{

	const char* vertex_shader_source = "#version 330 core\n"
										"layout (location = 0) in vec3 a_pos;\n"
										"void main()\n"
										"{\n"
										"	gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);\n"
										"}\0";

	const char* fragment_shader_source = "#version 330 core\n"
										"out vec4 frag_color;\n"
										"void main()\n"
										"{\n"
										"	frag_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);\n" // black
										"}\n\0";

	const char* fragment_shader_source2 = "#version 330 core\n"
										"out vec4 frag_color;\n"
										"void main()\n"
										"{\n"
										"	frag_color = vec4(0.0f, 0.69f, 0.69f, 1.0f);\n" // dark cyan
										"}\n\0";
	
	GLuint vertex_shader, fragment_shader, fragment_shader2, shader_program, shader_program2;
	GLfloat vertices1[384], vertices2[384];

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
	}

	void draw(GLuint shader_program, bool clear) {
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
		glDrawArrays(GL_TRIANGLES, 0, 192);

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shader_program);
	}

	void GLFWRenderer::render() {
		// GL code begin
		glfwInit();

		// GLfloat vertices1[384], vertices2[384];

		float aux1 = -0.8, aux2 = -0.6, aux3 = 0.0, aux4 = 0.0;
		short vert_ind = 0;
		for (short i = 0; i < 16; ++i) {
			for (short j = 0; j < 4; ++j) {
				if (i < 8) {
					vertices1[vert_ind++] = aux1 + aux3;
					vertices1[vert_ind++] = aux1 + aux4;
					vertices1[vert_ind++] = aux2 + aux3;
					vertices1[vert_ind++] = aux1 + aux4;
					vertices1[vert_ind++] = aux1 + aux3;
					vertices1[vert_ind++] = aux2 + aux4;

					vertices1[vert_ind++] = aux1 + aux3;
					vertices1[vert_ind++] = aux2 + aux4;
					vertices1[vert_ind++] = aux2 + aux3;
					vertices1[vert_ind++] = aux1 + aux4;
					vertices1[vert_ind++] = aux2 + aux3;
					vertices1[vert_ind++] = aux2 + aux4;
				} else {
					vertices2[vert_ind++] = aux1 + aux3;
					vertices2[vert_ind++] = aux1 + aux4;
					vertices2[vert_ind++] = aux2 + aux3;
					vertices2[vert_ind++] = aux1 + aux4;
					vertices2[vert_ind++] = aux1 + aux3;
					vertices2[vert_ind++] = aux2 + aux4;

					vertices2[vert_ind++] = aux1 + aux3;
					vertices2[vert_ind++] = aux2 + aux4;
					vertices2[vert_ind++] = aux2 + aux3;
					vertices2[vert_ind++] = aux1 + aux4;
					vertices2[vert_ind++] = aux2 + aux3;
					vertices2[vert_ind++] = aux2 + aux4;
				}
				aux3 += 0.4;
			}
			aux3 = 0.0;
			if (i % 2 == 0 && i < 8) {
				aux3 = 0.2;
			} else if (i % 2 == 1 && i > 7) {
                aux3 = 0.2;
            }
			aux4 += 0.2;
            if (i == 7) {
				vert_ind = 0;
                aux1 = -0.8, aux2 = -0.6, aux3 = 0.2, aux4 = 0.0;
            }
		}
		draw(shader_program, true);
		draw(shader_program2, false);
		
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

// GLuint VAO, VBO;
		// glGenVertexArrays(1, &VAO);
		// glGenBuffers(1, &VBO);
		// glBindVertexArray(VAO);
		// glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_DYNAMIC_DRAW);
		// glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		// glEnableVertexAttribArray(0);
		// glBindBuffer(GL_ARRAY_BUFFER, 0);
		// glBindVertexArray(0);
		// glClearColor(155.0f, 155.0f, 0.0f, 127.0f); // set background color
		// glClear(GL_COLOR_BUFFER_BIT);
		// glUseProgram(shader_program);
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 192);
		// glDeleteVertexArrays(1, &VAO);
		// glDeleteBuffers(1, &VBO);
		// glDeleteProgram(shader_program);
		// GLuint vao, vbo;
		// glGenVertexArrays(1, &vao);
		// glGenBuffers(1, &vbo);
		// glBindVertexArray(vao);
		// glBindBuffer(GL_ARRAY_BUFFER, vbo);
		// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_DYNAMIC_DRAW);
		// glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		// glEnableVertexAttribArray(0);
		// glBindBuffer(GL_ARRAY_BUFFER, 0);
		// glBindVertexArray(0);
		// glClearColor(155.0f, 155.0f, 0.0f, 127.0f); // set background color
		// glUseProgram(shader_program2);
		// glBindVertexArray(vao);
		// glDrawArrays(GL_TRIANGLES, 0, 192);
		// glDeleteVertexArrays(1, &vao);
		// glDeleteBuffers(1, &vbo);
		// glDeleteProgram(shader_program2);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// glfwInit();
		// GLfloat vertices[768];
		// float aux1 = -0.8, aux2 = -0.6, aux3 = 0.0, aux4 = 0.0;
		// short vert_ind = 0;
		// for (short i = 0; i < 8; ++i) {
		// 	for (short j = 0; j < 4; ++j) {
		// 		vertices[vert_ind++] = aux1 + aux3;
		// 		vertices[vert_ind++] = aux1 + aux4;
		// 		vertices[vert_ind++] = aux2 + aux3;
		// 		vertices[vert_ind++] = aux1 + aux4;
		// 		vertices[vert_ind++] = aux1 + aux3;
		// 		vertices[vert_ind++] = aux2 + aux4;
		// 		vertices[vert_ind++] = aux1 + aux3;
		// 		vertices[vert_ind++] = aux2 + aux4;
		// 		vertices[vert_ind++] = aux2 + aux3;
		// 		vertices[vert_ind++] = aux1 + aux4;
		// 		vertices[vert_ind++] = aux2 + aux3;
		// 		vertices[vert_ind++] = aux2 + aux4;
		// 		aux3 += 0.4;
		// 	}
		// 	aux3 = 0.0;
		// 	if (i % 2 == 0 && i < 8) {
		// 		aux3 = 0.2;
		// 	} else if (i % 2 == 1 && i > 7) {
        //         aux3 = 0.2;
        //     }
		// 	aux4 += 0.2;
        //     if (i == 7) {
        //         aux1 = -0.8, aux2 = -0.6, aux3 = 0.2, aux4 = 0.0;
        //     }
		// }
		// GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER); // create vertex shader
		// glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL); // 1 is no of strings used for shader
		// glCompileShader(vertex_shader);
		// GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER); // create fragment shader
		// glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL); // 1 is no of strings used for shader
		// glCompileShader(fragment_shader);
		// // GLuint fragment_shader2 = glCreateShader(GL_FRAGMENT_SHADER); // create fragment shader
		// // glShaderSource(fragment_shader2, 1, &fragment_shader_source2, NULL); // 1 is no of strings used for shader
		// // glCompileShader(fragment_shader2);
		// GLuint shader_program = glCreateProgram(); // create shader program
		// glAttachShader(shader_program, vertex_shader);
		// glAttachShader(shader_program, fragment_shader);
		// glLinkProgram(shader_program);
		// // GLuint shader_program2 = glCreateProgram(); // create shader program
		// // glAttachShader(shader_program2, vertex_shader);
		// // glAttachShader(shader_program2, fragment_shader2);
		// // glLinkProgram(shader_program2);
		// glDeleteShader(vertex_shader); // delete vertex & fragment shader
		// glDeleteShader(fragment_shader);
		// // glDeleteShader(fragment_shader2);
		// GLuint VAO, VBO;
		// glGenVertexArrays(1, &VAO);
		// glGenBuffers(1, &VBO);
		// glBindVertexArray(VAO);
		// glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
		// glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		// glEnableVertexAttribArray(0);
		// glBindBuffer(GL_ARRAY_BUFFER, 0);
		// glBindVertexArray(0);
		// glClearColor(255.0f, 255.0f, 255.0f, 255.0f); // set background color
		// glClear(GL_COLOR_BUFFER_BIT);
		// glUseProgram(shader_program);
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 384);
		// glDeleteVertexArrays(1, &VAO);
		// glDeleteBuffers(1, &VBO);
		// glDeleteProgram(shader_program);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// glClearColor(1.0f, 0.0f, 0.0f, 0.0f); // set background color
		// glClear(GL_COLOR_BUFFER_BIT);
		// glEnable(GL_COLOR_MATERIAL);
		// glBegin(GL_TRIANGLES);
		// float aux1 = -0.8, aux2 = -0.6, aux3 = 0.0, aux4 = 0.0;
		// glColor3f(0, 0, 0);
		// for (short i = 0; i < 16; ++i) {
		// 	for (short j = 0; j < 4; ++j) {
		// 		glVertex2f(aux1 + aux3, aux1 + aux4);
		// 		glVertex2f(aux2 + aux3, aux1 + aux4);
		// 		glVertex2f(aux1 + aux3, aux2 + aux4);
		// 		glVertex2f(aux1 + aux3, aux2 + aux4);
		// 		glVertex2f(aux2 + aux3, aux1 + aux4);
		// 		glVertex2f(aux2 + aux3, aux2 + aux4);
		// 		aux3 += 0.4;
		// 	}
		// 	aux3 = 0.0;
		// 	if (i % 2 == 0 && i < 8) {
		// 		aux3 = 0.2;
		// 	} else if (i % 2 == 1 && i > 7) {
        //         aux3 = 0.2;
        //     }
		// 	aux4 += 0.2;
        //     if (i == 7) {
        //         glColor3f(255,255,255);
        //         aux1 = -0.8, aux2 = -0.6, aux3 = 0.2, aux4 = 0.0;
        //     }
		// }
        // // margine stanga
		// glColor3f(155,155,155);
        // glVertex2f(-0.9, -0.9);
        // glVertex2f(-0.8, -0.9);
        // glVertex2f(-0.9, 0.9);
		// glVertex2f(-0.8, 0.9);
        // glVertex2f(-0.9, 0.9);
        // glVertex2f(-0.8, -0.9);
        // // marginea de sus
		// glVertex2f(-0.9, 0.8);
        // glVertex2f(-0.9, 0.9);
        // glVertex2f(0.9, 0.9);
		// glVertex2f(0.9, 0.9);
        // glVertex2f(0.9, 0.8);
        // glVertex2f(-0.9, 0.8);
        // // margine dreapta
		// glVertex2f(0.9, 0.9);
        // glVertex2f(0.9, -0.9);
        // glVertex2f(0.8, 0.9);
		// glVertex2f(0.8, 0.9);
        // glVertex2f(0.8, -0.9);
        // glVertex2f(0.9, -0.9);
        // // marginea de jos
		// glVertex2f(-0.9, -0.9);
        // glVertex2f(-0.9, -0.8);
        // glVertex2f(0.9, -0.9);
		// glVertex2f(0.9, -0.9);
        // glVertex2f(0.9, -0.8);
        // glVertex2f(-0.9, -0.8);
        // glEnd();