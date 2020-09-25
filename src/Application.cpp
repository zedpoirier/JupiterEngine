#include <glad/include/glad/glad.h>
#include <glfw/include/GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
//std::string vertexShaderSourceString;
//std::string fragmentShaderSourceString;

// prototype functions
int SetupGLFW();
void processInput(GLFWwindow* window);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
const char* ParseShader(const std::string& filepath);
unsigned int CompileShader(unsigned int type, const char* shaderSource);
//unsigned int CreateShader(const std::string& vertexShader);
//unsigned int CreateShader(const std::string& fragmentShader);
unsigned int CreateShader(const char*& vertexShader, const char*& fragmentShader);

// main is the entry point
int main() 
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw: create a window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Proto Engine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	SetupGLFW();
	// glad: load all OpenGl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// exercise 1: two triangles
	// exercise 2: 2 VAOs and VBOs
	// exercise 3: 2 shader programs
	float triangle1[] = {
		-0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	float triangle2[] = {
		0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	// simple quad with indices
	float quad[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int quadIndices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// vao and vbo 1
	unsigned int VAO1;
	glGenVertexArrays(1, &VAO1);
	glBindVertexArray(VAO1);
	unsigned int VBO1;
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
	// vertex attribute linking
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// vao and vbo 2
	unsigned int VAO2;
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);
	unsigned int VBO2;
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
	// vertex attribute linking
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// element buffer object for quad - uses indices
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);


	std::cout << "Jupiter is rising bitches..." << std::endl;
	std::cout << "Fucking Test == " << std::endl;
	const char* vertexShaderSource = ParseShader("src\res\BasicVertex.shader");
	const char* fragmentShaderSource = ParseShader("src\res\FragmentVertex.shader");
	const char* fragmentShaderTwoSource = ParseShader("src\res\YellowFragment.shader");
	std::cout << "vertexShaderSource == " << vertexShaderSource << std::endl;
	std::cout << "fragmentShaderSource == " << fragmentShaderSource << std::endl;
	std::cout << "fragmentShaderTwoSource == " << fragmentShaderTwoSource << std::endl;
	vertexShaderSource =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
	fragmentShaderTwoSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(0.9f, 0.8f, 0.2f, 1.0f);\n"
		"}\0";

	std::cout << "vertexShaderSource == " << vertexShaderSource << std::endl;
	std::cout << "fragmentShaderSource == " << fragmentShaderSource << std::endl;
	std::cout << "fragmentShaderTwoSource == " << fragmentShaderTwoSource << std::endl;

	unsigned int shaderProgram = CreateShader(vertexShaderSource, fragmentShaderSource);
	unsigned int shaderProgramTwo = CreateShader(vertexShaderSource, fragmentShaderTwoSource);
	
	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgramTwo);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

// glfw: whenever the window size changes (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// glfw: process all input pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// cherno: parse shader code from a .shader file to a const char*
static const char* ParseShader(const std::string& filepath)
{
	const char* result;
	std::string line;
	std::stringstream ss;
	std::ifstream stream(filepath);
	while (getline(stream, line))
	{
		ss << line << "\n";
	}
	result = ss.str().c_str();
	return result;
}

// cherno: compile Shader
static unsigned int CompileShader(unsigned int type, const char* shaderSource)
{
	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &shaderSource, NULL);
	glCompileShader(id);

	// error checking
	int result;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		std::cout << "ALSO POOP" << std::endl;
	}

	return id;
}

// Create shader program
static unsigned int CreateShader(const char*& vertexShader, const char*& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	// error checking
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM-TWO::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}

// All the GLFW setup window stuff
int SetupGLFW()
{
	return 1;
}