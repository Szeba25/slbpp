#include "Shader.h"

const std::string Shader::getSource(const std::string& fileName) {
	// Get source from file stream
	std::ifstream file(fileName);

	if (file.is_open() && file.good()) {
		std::cout << "OK: File opened " << fileName << std::endl;
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		return buffer.str();
	} else {
		std::cout << "ERROR: Unable to open file " << fileName << std::endl;
		return "";
	}
}

void Shader::checkCompileStatus(const unsigned int& shader) {
	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "ERROR: Shader compilation failed!" << std::endl << infoLog << std::endl;
	} else {
		std::cout << "OK: Shader compilation successful!" << std::endl;
	}
}

void Shader::checkProgramLinkStatus() {
	int success;
	char infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cout << "ERROR: Program link failed!" << std::endl << infoLog << std::endl;
	} else {
		std::cout << "OK: Program link successful!" << std::endl;
	}
}

Shader::Shader(const std::string& vertexName, const std::string& fragmentName) {
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const std::string vertexSource = getSource(vertexName);
	const GLchar* vertexSourceCstr = vertexSource.c_str();
	glShaderSource(vertexShader, 1, &vertexSourceCstr, nullptr);
	glCompileShader(vertexShader);
	checkCompileStatus(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const std::string fragmentSource = getSource(fragmentName);
	const GLchar* fragmentSourceCstr = fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentSourceCstr, nullptr);
	glCompileShader(fragmentShader);
	checkCompileStatus(fragmentShader);

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	checkProgramLinkStatus();

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(program);
	std::cout << "OK: Shader program deleted!" << std::endl;
}

void Shader::use() {
	glUseProgram(program);
}
