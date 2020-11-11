#pragma once
#include <glad/include/glad/glad.h>
#include <glfw/include/GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// prototype functions
GLFWwindow* initialize();
void process(GLFWwindow * window);
void render(GLFWwindow* window, unsigned int program, unsigned int vao);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
std::string ParseShader(const std::string& filepath);
unsigned int CompileShader(unsigned int type, const char* shaderSource);
unsigned int CreateShader(const char*& vertexShader, const char*& fragmentShader);