#include <headers.h>

/*
	things worth trying to emulate:

	compute:
	https://twitter.com/totallyRonja/status/1287421347749076992
	https://twitter.com/weigert__/status/1290023570056216577

	graphics:
	https://twitter.com/algomystic/status/1306634253153775616
	https://twitter.com/FreyaHolmer/status/1264248161926893568
*/

// settings
double time = 0.0;
double delta = 0.0;
double mousePosX = 0;
double mousePosY = 0;
unsigned int frame = 0;
unsigned int width = 1200;
unsigned int height = 600;

// main is the entry point
int main() 
{
	// initialize glfw, create a window and context, initilize glad
	GLFWwindow* window = initialize();
	if (window == NULL) return -1; // Failed to initialize
	std::cout << "Jupiter is rising bitches..." << std::endl;

	// stb: load images
	stbi_set_flip_vertically_on_load(true);
	int imgWidth, imgHeight, imgNumChannels;
	unsigned char* data = stbi_load("res/textures/container.jpg", &imgWidth, &imgHeight, &imgNumChannels, 0);
	// create texture
	unsigned int texture0;
	glGenTextures(1, &texture0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	// stb: free image from memorysx
	stbi_image_free(data);
	// repeat for second texture
	data = stbi_load("res/textures/awesomeface.png", &imgWidth, &imgHeight, &imgNumChannels, 0);
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	float quad[] = {
		// positions          // colors           // texcoords
		/**/ 0.0, -1.0, 0.0, /**/ 0.0, 0.0, 1.0, /**/ 0.0, 0.0,
		/**/ 0.0,  1.0, 0.0, /**/ 0.0, 1.0, 0.0, /**/ 0.0, 1.0,
		/**/ 1.0,  1.0, 0.0, /**/ 1.0, 1.0, 0.0, /**/ 1.0, 1.0,
		/**/ 1.0, -1.0, 0.0, /**/ 1.0, 0.0, 0.0, /**/ 1.0, 0.0
	};


	unsigned int quadIndices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	
	// Parsing and Creating Shaders
	std::string vsSource = ParseShader("res/shaders/shader.vert");
	std::string fsSource = ParseShader("res/shaders/noise.frag");
	const char* vs = vsSource.c_str();
	const char* fs = fsSource.c_str();
	unsigned int program = CreateShader(vs, fs);

	// coordinate system matrices setup
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// main Loop
	while (!glfwWindowShouldClose(window))
	{
		process(window);

		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//ImGui::ShowDemoWindow();

		// shader uniforms
		int modelID = glGetUniformLocation(program, "model");
		glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
		int viewID = glGetUniformLocation(program, "view");
		glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
		int projID = glGetUniformLocation(program, "projection");
		glUniformMatrix4fv(projID, 1, GL_FALSE, glm::value_ptr(projection));

		// render geometry and gui
		render(window, program, vaoFullQuad);	
	}
	glfwTerminate();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	return 0;
}

GLFWwindow* initialize()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Proto Engine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	//glfwSetWindowPos(window, 0, 0);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}
	return window;
}

// process :: glfwPollEvents
void process(GLFWwindow * window)
{
	frame++;
	delta = glfwGetTime() - time;
	time = glfwGetTime();
	glfwGetCursorPos(window, &mousePosX, &mousePosY);
	//std::cout << "FPS: " << 1.0f / delta << std::endl;
	//std::cout << "Delta Time: " << delta << std::endl;
	//std::cout << "Frame Count: " << frame << std::endl;
	//std::cout << "Elapsed Time: " << time << std::endl;
	//std::cout << "Mouse position X: " << mousePosX << " Y: " << mousePosY << std::endl;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_KP_0) == GLFW_PRESS)
		frame = 0;


	glfwPollEvents();
}

// render :: glfwMakeContextCurrent...glfwSwapBuffers
void render(GLFWwindow* window, unsigned int program, unsigned int vao)
{
	glfwMakeContextCurrent(window);
	glClearColor(0.2f, 0.3f, 0.3f, 0.9f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);
	
	// render your GUI
	ImGui::Begin("Noise Colors");
	static float color1[3] = { 1.0, 0.0, 0.0 };
	static float color2[3] = { 0.0, 1.0, 0.0 };
	static float color3[3] = { 0.0, 0.0, 1.0 };
	ImGui::ColorEdit3("Color 1", color1);
	ImGui::ColorEdit3("Color 2", color2);
	ImGui::ColorEdit3("Color 3", color3);
	int c1ID = glGetUniformLocation(program, "col1");
	int c2ID = glGetUniformLocation(program, "col2");
	int c3ID = glGetUniformLocation(program, "col3");
	glUniform3f(c1ID, color1[0], color1[1], color1[2]);
	glUniform3f(c2ID, color2[0], color2[1], color2[2]);
	glUniform3f(c3ID, color3[0], color3[1], color3[2]);
	ImGui::End();

	int frameID = glGetUniformLocation(program, "frame");
	int timeID = glGetUniformLocation(program, "time");
	int resoID = glGetUniformLocation(program, "reso");
	glUniform1i(frameID, frame);
	glUniform4f(timeID, time, sin(time), sin(time) * 0.5 + 0.5, 0.0);
	glUniform4f(resoID, width, height, 0.2, 0.0);
	glUniform1i(glGetUniformLocation(program, "texture0"), 0);
	glUniform1i(glGetUniformLocation(program, "texture1"), 1);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}

// glfw: whenever the window size changes (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// cherno: parse shader code from a .shader file to a const char*
static std::string ParseShader(const std::string& filepath)
{
	std::string line;
	std::stringstream ss;
	/*std::ifstream noise("res/shaders/noise.glsl");
	while (getline(noise, line))
	{
		ss << line << "\n";
	}*/
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
