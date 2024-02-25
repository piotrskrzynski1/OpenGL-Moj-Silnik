#include "shaderClass.h"

std::string get_file_contents(const char* filename) {
	
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile){

	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);;
	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(VertexShader, 1, &vertexSource, NULL);
	glCompileShader(VertexShader);
	glShaderSource(FragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(FragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, VertexShader);
	glAttachShader(ID, FragmentShader);
	glLinkProgram(ID);

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}