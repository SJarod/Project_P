#include "resources/shader.hpp"

#include <iostream>
#include <fstream>

Resources::Shader::Shader(const std::string& shaderName)
{
    std::ifstream vertStream("resources/shaders/" + shaderName + ".vert");
    std::ifstream fragStream("resources/shaders/" + shaderName + ".frag");

    if (!vertStream.is_open() || !fragStream.is_open())
    {
        std::cout << "could not open shader files : " << shaderName << std::endl;
        return;
    }

    std::string vs((std::istreambuf_iterator<char>(vertStream)), std::istreambuf_iterator<char>());
    std::string fs((std::istreambuf_iterator<char>(fragStream)), std::istreambuf_iterator<char>());

    const char* vertexShaderSource = vs.c_str();
    const char* fragmentShaderSource = fs.c_str();

    //shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int  success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    //success?

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    std::cout << "successfully loaded shader files : " << shaderName << std::endl;
}

Resources::Shader::~Shader()
{
    glDeleteShader(program);
}

void Resources::Shader::use() const
{
    glUseProgram(program);
}

void Resources::Shader::passBool(const bool& b, const char* name)
{
    int location = glGetUniformLocation(program, name);
    use();
    glUniform1i(location, b);
}

void Resources::Shader::passFloat(const float& f, const char* name)
{
    int location = glGetUniformLocation(program, name);
    use();
    glUniform1f(location, f);
}

void Resources::Shader::passVec3(const vec3& v, const char* name)
{
    int location = glGetUniformLocation(program, name);
    use();
    glUniform3fv(location, 1, v.e);
}

void Resources::Shader::passMat4(const mat4& m, const char* name)
{
    int location = glGetUniformLocation(program, name);
    use();
    glUniformMatrix4fv(location, 1, false, m.e);
}