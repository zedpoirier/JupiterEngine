#pragma once
#include <glad/include/glad/glad.h>
#include <glfw/include/GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


// prototype functions
void processInput(GLFWwindow* window);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
std::string ParseShader(const std::string& filepath);
unsigned int CompileShader(unsigned int type, const char* shaderSource);
unsigned int CreateShader(const char*& vertexShader, const char*& fragmentShader);