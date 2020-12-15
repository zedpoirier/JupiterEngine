#include <headers.h>

/*
	things worth trying:

	compute:
	https://twitter.com/totallyRonja/status/1287421347749076992
	https://twitter.com/weigert__/status/1290023570056216577

	graphics:
	https://twitter.com/algomystic/status/1306634253153775616
	https://twitter.com/FreyaHolmer/status/1264248161926893568

	save to file:
	https://stackoverflow.com/questions/3191978/how-to-use-glut-opengl-to-render-to-a-file
	http://netpbm.sourceforge.net/doc/ppm.html#:~:text=The%20PPM%20format%20is%20a%20lowest%20common%20denominator%20color%20image%20file%20format.&text=For%20example%2C%20%22PPM%20using%20the,also%20called%20%22portable%20pixmaps.%22
	https://eklitzke.org/rendering-videos-from-opengl
	
	raymarching:
	http://jamie-wong.com/2016/07/15/ray-marching-signed-distance-functions/#the-raymarching-algorithm
	https://www.youtube.com/watch?v=Cfe5UQ-1L9Q&t=3233s
*/

// settings
DemoType type = FULLSCREEN;
bool showGUI = false;
float time = 0.0;
double delta = 0.0;
double mousePosX = 0;
double mousePosY = 0;
unsigned int frame = 0;
unsigned int width = 980;
unsigned int height = 540;
float xRot = 0.0;
float zRot = 0.0;
float rotSpeed = 2.0;
float PI = 3.1415;
glm::vec3 controllerPos = glm::vec3(0.0f);

// matrices
glm::mat4 view;
glm::mat4 model;
glm::mat4 projection;

// camera
Camera cam = Camera(glm::vec3(0.0f, 0.0f, 10.0f));
float lastX = width / 2.0f;
float lastY = height / 2.0f;
bool firstMouse = true;

float quad[] = {
	// positions          // colors           // texcoords
	/**/ -1.0, -1.0, 0.0, /**/ 0.0, 0.0, 1.0, /**/ 0.0, 0.0,
	/**/ -1.0,  1.0, 0.0, /**/ 0.0, 1.0, 0.0, /**/ 0.0, 1.0,
	/**/  1.0,  1.0, 0.0, /**/ 1.0, 1.0, 0.0, /**/ 1.0, 1.0,
	/**/  1.0, -1.0, 0.0, /**/ 1.0, 0.0, 0.0, /**/ 1.0, 0.0
};

unsigned int quadIndices[] = {
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
};

float cube[] = {
	// positions          // texcoords
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

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
	// openGL function and settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// setup for FULLSCREEN render
	unsigned int vaoFullQuad;
	glGenVertexArrays(1, &vaoFullQuad);
	glBindVertexArray(vaoFullQuad);
	unsigned int vboFullQuad;
	glGenBuffers(1, &vboFullQuad);
	glBindBuffer(GL_ARRAY_BUFFER, vboFullQuad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	unsigned int eboFullQuad;
	glGenBuffers(1, &eboFullQuad);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboFullQuad);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);
	std::string vsSource = ParseShader("res/shaders/fullscreen.vert");
	std::vector<std::string> fsSourcePaths = { "res/shaders/noise.glsl", "res/shaders/sdf.glsl", "res/shaders/noise.frag" };
	std::string fsSource = ParseShader(fsSourcePaths);
	const char* vs = vsSource.c_str();
	const char* fs = fsSource.c_str();
	unsigned int program = CreateShader(vs, fs);

	// setup for CUBES render
	unsigned int vaoCube;
	glGenVertexArrays(1, &vaoCube);
	glBindVertexArray(vaoCube);
	unsigned int vboCube;
	glGenBuffers(1, &vboCube);
	glBindBuffer(GL_ARRAY_BUFFER, vboCube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	std::string vsSource2 = ParseShader("res/shaders/shader.vert");
	std::string fsSource2 = ParseShader("res/shaders/shader.frag");
	const char* vs2 = vsSource2.c_str();
	const char* fs2 = fsSource2.c_str();
	unsigned int program2 = CreateShader(vs2, fs2);

	// setup for RAYMARCH render
	std::string vsSource3 = ParseShader("res/shaders/raymarching.vert");
	std::vector<std::string> fsSourcePaths3 = { "res/shaders/noise.glsl", "res/shaders/sdf.glsl", "res/shaders/raymarching.frag" };
	std::string fsSource3 = ParseShader(fsSourcePaths3);
	const char* vs3 = vsSource3.c_str();
	const char* fs3 = fsSource3.c_str();
	unsigned int program3 = CreateShader(vs3, fs3);

	// setup for PADDLE render
	std::string vsSource4 = ParseShader("res/shaders/raymarching.vert");
	std::vector<std::string> fsSourcePaths4 = { "res/shaders/noise.glsl", "res/shaders/sdf.glsl", "res/shaders/paddle.frag" };
	std::string fsSource4 = ParseShader(fsSourcePaths4);
	const char* vs4 = vsSource4.c_str();
	const char* fs4 = fsSource4.c_str();
	unsigned int program4 = CreateShader(vs4, fs4);

	// setup for PARTICLES render
	std::string vsSource5 = ParseShader("res/shaders/shader.vert");
	std::vector<std::string> fsSourcePaths5 = { "res/shaders/noise.glsl", "res/shaders/sdf.glsl", "res/shaders/particles.frag" };
	std::string fsSource5 = ParseShader(fsSourcePaths5);
	const char* vs5 = vsSource5.c_str();
	const char* fs5 = fsSource5.c_str();
	unsigned int program5 = CreateShader(vs5, fs5);


	// main Loop
	while (!glfwWindowShouldClose(window))
	{
		process(window);

		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// render geometry and gui based on DemoType
		switch (type)
		{
		case FULLSCREEN:
			renderFULLSCREEN(window, program, vaoFullQuad);
			break;
		case CUBES:
			renderCUBES(window, program2, vaoCube);
			break;
		case RAYMARCH:
			renderRAYMARCH(window, program3, vaoFullQuad);
			break;
		case PADDLE:
			renderRAYMARCH(window, program4, vaoFullQuad);
			break;
		case PARTICLES:
			renderPARTICLES(window, program5, vaoFullQuad);
			break;
		}
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
	glfwSetWindowPos(window, 300, 300);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);


	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	glfwSetKeyCallback(window, key_callback);
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

	// camera movement
	float cameraSpeed = 2.5f * delta; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.ProcessKeyboard(FORWARD, delta);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.ProcessKeyboard(BACKWARD, delta);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.ProcessKeyboard(LEFT, delta);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.ProcessKeyboard(RIGHT, delta);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cam.ProcessKeyboard(UP, delta);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cam.ProcessKeyboard(DOWN, delta);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		zRot += delta * rotSpeed;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		zRot -= delta * rotSpeed;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		xRot += delta * rotSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		xRot -= delta * rotSpeed;

	xRot = std::clamp(xRot, -3.1415f / 3.0f, 3.1415f / 3.0f);
	zRot = std::clamp(zRot, -3.1415f / 3.0f, 3.1415f / 3.0f);

	glfwPollEvents();
}

// render :: glfwMakeContextCurrent...glfwSwapBuffers
void renderFULLSCREEN(GLFWwindow* window, unsigned int program, unsigned int vao)
{
	glfwMakeContextCurrent(window);
	glClearColor(0.2f, 0.3f, 0.3f, 0.9f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	
	// color uniforms for gui test and nosie shader
	static float color1[3] = { 1.0, 0.0, 0.0 };
	static float color2[3] = { 0.0, 1.0, 0.0 };
	static float color3[3] = { 0.0, 0.0, 1.0 };
	int c1ID = glGetUniformLocation(program, "col1");
	int c2ID = glGetUniformLocation(program, "col2");
	int c3ID = glGetUniformLocation(program, "col3");
	glUniform3f(c1ID, color1[0], color1[1], color1[2]);
	glUniform3f(c2ID, color2[0], color2[1], color2[2]);
	glUniform3f(c3ID, color3[0], color3[1], color3[2]);

	// common uniforms
	int frameID = glGetUniformLocation(program, "frame");
	int timeID = glGetUniformLocation(program, "time");
	int resoID = glGetUniformLocation(program, "reso");
	glUniform1i(frameID, frame);
	glUniform1f(timeID, time);
	glUniform2f(resoID, width, height);
	glUniform1i(glGetUniformLocation(program, "texture0"), 0);
	glUniform1i(glGetUniformLocation(program, "texture1"), 1);

	// shader matrix uniforms
	view = cam.GetViewMatrix();
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0, 0.0, 5.0));
	projection = glm::perspective(glm::radians(cam.Zoom), (float)(width / height), 0.1f, 100.0f);
	int viewID = glGetUniformLocation(program, "view");
	int modelID = glGetUniformLocation(program, "model");
	int projID = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projID, 1, GL_FALSE, glm::value_ptr(projection));

	// camera uniforms
	int camPosID = glGetUniformLocation(program, "camPos");
	int camFrontID = glGetUniformLocation(program, "camFront");
	glUniform3f(camPosID, cam.Position.x, cam.Position.y, cam.Position.z);
	glUniform3f(camFrontID, cam.Front.x, cam.Front.y, cam.Front.z);
	
	// bind vao and render elements
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// render your GUI
	if (showGUI)
	{
		// setup GUI
		ImGui::Begin("Noise Colors");
		ImGui::ColorEdit3("Color 1", color1);
		ImGui::ColorEdit3("Color 2", color2);
		ImGui::ColorEdit3("Color 3", color3);
		ImGui::End();
	}
	// render GUI
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}

// render :: glfwMakeContextCurrent...glfwSwapBuffers
void renderCUBES(GLFWwindow* window, unsigned int program, unsigned int vao)
{
	glfwMakeContextCurrent(window);
	glClearColor(0.2f, 0.3f, 0.3f, 0.9f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);

	// shader matrix uniforms
	view = cam.GetViewMatrix();
	model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
	projection = glm::perspective(glm::radians(cam.Zoom), (float)(width / height), 0.1f, 100.0f);
	int viewID = glGetUniformLocation(program, "view");
	int modelID = glGetUniformLocation(program, "model");
	int projID = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projID, 1, GL_FALSE, glm::value_ptr(projection));
	
	// common uniforms
	int frameID = glGetUniformLocation(program, "frame");
	int timeID = glGetUniformLocation(program, "time");
	int resoID = glGetUniformLocation(program, "reso");
	glUniform1i(frameID, frame);
	glUniform1f(timeID, time);
	glUniform2f(resoID, width, height);
	glUniform1i(glGetUniformLocation(program, "texture0"), 0);
	glUniform1i(glGetUniformLocation(program, "texture1"), 1);


	glBindVertexArray(vao);
	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		// calculate the model matrix for each object and pass it to shader before drawing
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		if ((i + 1) % 2 == 0)
			angle = glfwGetTime() * 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
	
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// render your GUI
	if (showGUI)
	{
		// setup GUI
		ImGui::Begin("Camera Properties");
		// camera pos, camera front?, cam up, zoom,
		float position[3] = { cam.Position.x, cam.Position.y, cam.Position.z};
		float front[3] = { cam.Front.x, cam.Front.y, cam.Front.z};
		float up[3] = { cam.Up.x, cam.Up.y, cam.Up.z};
		ImGui::InputFloat3("Position", position, 2);
		ImGui::InputFloat3("Front", front, 2);
		ImGui::InputFloat3("Up", up, 2);
		ImGui::InputFloat("Zoom(FOV)", &cam.Zoom);
		ImGui::End();
	}
	// render GUI
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	glfwSwapBuffers(window);
}

// render :: glfwMakeContextCurrent...glfwSwapBuffers
void renderRAYMARCH(GLFWwindow* window, unsigned int program, unsigned int vao)
{
	glfwMakeContextCurrent(window);
	glClearColor(0.2f, 0.3f, 0.3f, 0.9f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);

	// common uniforms
	int frameID = glGetUniformLocation(program, "frame");
	int timeID = glGetUniformLocation(program, "time");
	int resoID = glGetUniformLocation(program, "reso");
	glUniform1i(frameID, frame);
	glUniform1f(timeID, time);
	glUniform2f(resoID, width, height);
	glUniform1i(glGetUniformLocation(program, "texture0"), 0);
	glUniform1i(glGetUniformLocation(program, "texture1"), 1);

	// camera uniforms
	int camPosID = glGetUniformLocation(program, "camPos");
	int camFrontID = glGetUniformLocation(program, "camFront");
	glUniform3f(camPosID, cam.Position.x, cam.Position.y, cam.Position.z);
	glUniform3f(camFrontID, cam.Front.x, cam.Front.y, cam.Front.z);


	// bind vao and render elements
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// render your GUI
	if (showGUI)
	{
		// setup GUI
		ImGui::Begin("Raymarch Properties");
		ImGui::Text("FPS: %.0f", 1.0f / delta);
		float position[3] = { cam.Position.x, cam.Position.y, cam.Position.z };
		float front[3] = { cam.Front.x, cam.Front.y, cam.Front.z };
		ImGui::InputFloat3("Position", position, 2);
		ImGui::InputFloat3("Front", front, 2);
		ImGui::End();
	}
	// render GUI
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}

// render :: glfwMakeContextCurrent...glfwSwapBuffers
void renderPARTICLES(GLFWwindow* window, unsigned int program, unsigned int vao)
{
	glfwMakeContextCurrent(window);
	glClearColor(0.1f, 0.1f, 0.3f, 0.9f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);

	// shader matrix uniforms
	view = cam.GetViewMatrix();
	projection = glm::perspective(glm::radians(cam.Zoom), (float)(width / height), 0.1f, 100.0f);
	int viewID = glGetUniformLocation(program, "view");
	int modelID = glGetUniformLocation(program, "model");
	int projID = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projID, 1, GL_FALSE, glm::value_ptr(projection));

	// common uniforms
	int frameID = glGetUniformLocation(program, "frame");
	int timeID = glGetUniformLocation(program, "time");
	int resoID = glGetUniformLocation(program, "reso");
	glUniform1i(frameID, frame);
	glUniform1f(timeID, time);
	glUniform2f(resoID, width, height);
	glUniform1i(glGetUniformLocation(program, "texture0"), 0);
	glUniform1i(glGetUniformLocation(program, "texture1"), 1);


	glBindVertexArray(vao);
	for (unsigned int i = 0; i < 15; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		glm::vec3 pos = glm::vec3(sin(i), cos(i), i - 2.0f);
		model = glm::translate(model, pos * 0.5f);
		model = glm::rotate(model, glm::radians(20.0f * (i+1)), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(3.0, 3.0, 1.0));
		glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));

		// bind vao and render elements
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	// render your GUI
	if (showGUI)
	{
		// setup GUI
		ImGui::Begin("Camera Properties");
		// camera pos, camera front?, cam up, zoom,
		float position[3] = { cam.Position.x, cam.Position.y, cam.Position.z };
		float front[3] = { cam.Front.x, cam.Front.y, cam.Front.z };
		float up[3] = { cam.Up.x, cam.Up.y, cam.Up.z };
		ImGui::InputFloat3("Position", position, 2);
		ImGui::InputFloat3("Front", front, 2);
		ImGui::InputFloat3("Up", up, 2);
		ImGui::InputFloat("Zoom(FOV)", &cam.Zoom);
		ImGui::End();
	}
	// render GUI
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}

// glfw: whenever the window size changes (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	cam.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	cam.ProcessMouseScroll(yoffset);
}

// glfw: whenever a key is pressed a single time "BUTTONDOWN" 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		showGUI = !showGUI;
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		type = FULLSCREEN;
		// tell GLFW to capture our mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		type = CUBES;
		// tell GLFW to capture our mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS)
	{
		type = RAYMARCH;
		// tell GLFW to capture our mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS)
	{
		type = PADDLE;
		// tell GLFW to capture our mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (key == GLFW_KEY_5 && action == GLFW_PRESS)
	{
		type = PARTICLES;
		// tell GLFW to capture our mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

// cherno: parse shader code from a .shader file to a const char*
static std::string ParseShader(const std::string filepath)
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

// cherno: parse shader code from a .shader file to a const char* customized to take in multiple shader sources
static std::string ParseShader(const std::vector<std::string> filepaths)
{
	int count = filepaths.size();
	std::string line;
	std::string result;
	for (int i = 0; i < count; i++)
	{
		//std::cout << "parsing shader file " << i + 1 << " of " << count << " files..." << std::endl;
		int n = 0;
		std::stringstream ss;
		std::ifstream stream(filepaths[i]);
		while (getline(stream, line))
		{
			if (i > 0 && n == 0)
			{
				n++;
				continue;
			}
			ss << line << "\n";
			n++;

		}
		result += ss.str();
	}
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