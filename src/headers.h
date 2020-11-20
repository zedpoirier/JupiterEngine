#pragma once
#include <glad/include/glad/glad.h>
#include <glfw/include/GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <Camera.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

enum DemoType {
	FULLSCREEN,
	CUBES,
	RAYMARCH
};


// prototype functions
GLFWwindow* initialize();
void process(GLFWwindow * window);
void renderFULLSCREEN(GLFWwindow* window, unsigned int program, unsigned int vao);
void renderCUBES(GLFWwindow* window, unsigned int program, unsigned int vao);
void renderRAYMARCH(GLFWwindow* window, unsigned int program, unsigned int vao);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
std::string ParseShader(const std::string filepath);
std::string ParseShader(const std::string filepaths[]);
unsigned int CompileShader(unsigned int type, const char* shaderSource);
unsigned int CreateShader(const char*& vertexShader, const char*& fragmentShader);