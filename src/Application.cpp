#include <headers.h>

// settings
bool SQUARE = false;
const unsigned int SCR_WIDTH = 500;
const unsigned int SCR_HEIGHT = 500;

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
	// glad: load all OpenGl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

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

	float quad[] = {
		-0.9, -0.9, 0.0,
		-0.9, 0.9, 0.0,
		0.9, 0.9, 0.0,
		0.9, -0.9, 0.0
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

	// setup vertex array object
	unsigned int vaoFullQuad;
	glGenVertexArrays(1, &vaoFullQuad);
	glBindVertexArray(vaoFullQuad);
	// build and bind vertex buffer object to array object
	unsigned int vboFullQuad;
	glGenBuffers(1, &vboFullQuad);
	glBindBuffer(GL_ARRAY_BUFFER, vboFullQuad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
	// build and bind element buffer object to array object
	unsigned int eboFullQuad;

	glGenBuffers(1, &eboFullQuad);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboFullQuad);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);
	// set the vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Parsing Shader Sources
	std::string vertexShaderSourceString = ParseShader("res/shaders/BasicVertex.shader");
	const char* vertexShaderSource = vertexShaderSourceString.c_str();
	std::string fragmentShaderSourceString = ParseShader("res/shaders/BasicFragment.shader");
	const char* fragmentShaderSource = fragmentShaderSourceString.c_str();
	std::string fragmentShaderTwoSourceString = ParseShader("res/shaders/FragYellow.shader");
	const char* fragmentShaderTwoSource = fragmentShaderTwoSourceString.c_str();
	std::string shapesShaderSourceString = ParseShader("res/shaders/Shapes.shader");
	const char* shapesShaderSource = shapesShaderSourceString.c_str();
	// Creating Shaders
	unsigned int shaderProgram = CreateShader(vertexShaderSource, fragmentShaderSource);
	unsigned int shaderProgramTwo = CreateShader(vertexShaderSource, fragmentShaderTwoSource);
	unsigned int fullScreenQuadProgram = CreateShader(vertexShaderSource, shapesShaderSource);
	
	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		// glfw:: process input
		processInput(window);

		// glad: process render
		// processRender();

		// glad: render background
		glClearColor(0.2f, 0.3f, 0.3f, 0.9f);
		glClear(GL_COLOR_BUFFER_BIT);
		// glad: render custom shader quad
		glUseProgram(fullScreenQuadProgram);
		glBindVertexArray(vaoFullQuad);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glad: render orange triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glad: render yellow triangle
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
static std::string ParseShader(const std::string& filepath)
{
	std::string line;
	std::stringstream ss;
	std::ifstream stream(filepath);
	while (getline(stream, line))
	{
		ss << line << "\n";
	}
	std::string result = ss.str();
	return result;
}

// cherno: compile single shader (vertex or fragment only for now)
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

// cherno: create shader program and compile shaders
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