#pragma once
#include <memory>
#include <optional>
#include <context.hpp>
#include <polled_object.hpp>


#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "../include/Table.hpp"

namespace opengles_workspace
{
	class GLFWRenderer : public PolledObject//, public Table
	{
	public:
		GLFWRenderer(std::shared_ptr<Context> context);

		~GLFWRenderer() = default;

		void render();

		bool poll() override;


		void create_shaders();
		const void set_buffers();

	private:
		const char* _vertex_shader_source = R"(
											#version 300 es
											layout (location = 0) in vec3 aPos;

											void main() {
												gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
											}
										)";

		const char* _fragment_shader_source = R"(
											#version 300 es
											out highp vec4 FragColor;

											void main() {
												FragColor = vec4(1.0, 0.5, 0.2, 1.0);
											}
										)";

		GLuint _vertex_shader, _fragment_shader, _shader_program;
		GLuint _VBO, _VAO;

		std::shared_ptr<Context> mContext;
		GLFWwindow* window() const { return static_cast<GLFWwindow*>(mContext->window()); }
	};
}