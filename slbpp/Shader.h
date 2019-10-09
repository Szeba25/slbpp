#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader {
private:
	unsigned int program;

	const std::string getSource(const std::string &fileName);
	void checkCompileStatus(const unsigned int& shader);
	void checkProgramLinkStatus();
public:
	Shader(const std::string& vertName, const std::string& fragName);
	virtual ~Shader();

	void use();
};

