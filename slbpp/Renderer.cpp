#include "Renderer.h"

Renderer::Renderer() {
	// Set the viewport to match the window size.
	glViewport(0, 0, 1280, 720);

	// Create shaders.
	int success;
	char infoLog[512];

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertexSource = "#version 330 core\nlayout (location = 0) in vec3 aPos;\n\nvoid main() {\n    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\n";
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "Vertex shader compilation failed!\n" << infoLog << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragmentSource = "#version 330 core\nout vec4 FragColor;\n\nvoid main() {\n    FragColor = vec4(1.0f, 0.3f, 0.7f, 1.0f);\n}\n";
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "Fragment shader compilation failed!\n" << infoLog << std::endl;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "Shader program linking failed!\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Initialize test vertices.
	vertices = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	// Set up VBO and VAO.

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Renderer::~Renderer() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Renderer::clear() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::test() {
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// Unnecessary to unbind every time!
	//glBindVertexArray(0);
}

void Renderer::resize(int width, int height) {
	glViewport(0, 0, width, height);
}
