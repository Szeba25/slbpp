#include "Input.h"

Input::Input(GLFWwindow* window) : 
	window(window) {

	for (int i = 0; i < 512; i++) {
		keyPressed.push_back(false);
		keyReleased.push_back(false);
		keyCurrentlyPressed.push_back(false);
	}
}

Input::~Input() {

}

void Input::update() {
	for (int i = 0; i < 512; i++) {
		keyPressed[i] = false;
		keyReleased[i] = false;
	}
}

void Input::keyUpdate(int key, int action) {
	if (key < 0 || key >= 512) {
		std::cout << "ERROR: key is invalid, " << key << std::endl;
	} else {
		if (action == GLFW_PRESS) {
			keyPressed[key] = true;
			keyCurrentlyPressed[key] = true;
		} else if (action == GLFW_RELEASE) {
			keyReleased[key] = true;
			keyCurrentlyPressed[key] = false;
		}
	}
}

bool Input::isKeyPressed(Key key) {
	return keyPressed[(int)key];
}

bool Input::isKeyCurrentlyPressed(Key key) {
	return keyCurrentlyPressed[(int)key];
}
