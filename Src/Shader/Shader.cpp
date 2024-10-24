#include "Shader.hpp"

unsigned int Shader::usingShader = -1;

Shader::Shader() {

}

Shader::Shader(const char* vertexPath, const char *fragmentPath) {
    int vertex_shader, fragment_shader;

    vertex_shader = createShader(vertexPath, GL_VERTEX_SHADER);
    fragment_shader = createShader(fragmentPath, GL_FRAGMENT_SHADER);
    ID = createProgram(vertex_shader, fragment_shader);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

void Shader::use() {
    if (usingShader != ID) {
        usingShader = ID;
        glUseProgram(ID);
    }
}

void Shader::setBool(const std::string &name, bool value) {
    if (uniformLocations.find(name) == uniformLocations.end())
        uniformLocations[name] = glGetUniformLocation(ID, name.c_str());

    use();
    glUniform1i(uniformLocations[name], (int)value);
}

void Shader::setInt(const std::string &name , int value) {
    if (uniformLocations.find(name) == uniformLocations.end())
        uniformLocations[name] = glGetUniformLocation(ID, name.c_str());

    use();
    glUniform1i(uniformLocations[name], value);
}

void Shader::setFloat(const std::string &name, float value) {
    if (uniformLocations.find(name) == uniformLocations.end())
        uniformLocations[name] = glGetUniformLocation(ID, name.c_str());

    use();
    glUniform1f(uniformLocations[name], value);
}

void Shader::setMat4(const std::string &name, glm::mat4 &value) {
    if (uniformLocations.find(name) == uniformLocations.end())
        uniformLocations[name] = glGetUniformLocation(ID, name.c_str());

    use();
    glUniformMatrix4fv(uniformLocations[name], 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, glm::vec3 &value) {
    if (uniformLocations.find(name) == uniformLocations.end())
        uniformLocations[name] = glGetUniformLocation(ID, name.c_str());

    use();
    glUniform3fv(uniformLocations[name], 1, glm::value_ptr(value));
}

std::string Shader::loadShader(const char *filename) {
    std::ifstream shader_file;
    std::string line;
    std::string shader_path;
    std::string shader_code;

    shader_path = shaderPath + std::string(filename) + ".glsl";
    shader_code = "";

    shader_file.open(shader_path.c_str());

    if (!shader_file.is_open()) return NULL;

    while (std::getline(shader_file, line)) shader_code += line + "\n";
    if (*(shader_code.end() - 1) == '\n') shader_code.erase(shader_code.end() - 1); // Erase last newline character

    shader_file.close();
    return shader_code;
}

int Shader::createShader(const char *filename, int type) {
    unsigned int    shader;
    std::string     shader_code_str;
    const char      *shader_code;
    int             issuccess;
    char            infoLog[512];

    shader_code_str = loadShader(filename);

    shader_code = shader_code_str.c_str();
    shader = glCreateShader(type);

    glShaderSource(shader, 1, &shader_code, NULL);

    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &issuccess);
    if(!issuccess)
    {
        memset(infoLog, 0, sizeof(infoLog));
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER " << char('0' + type) << " " << infoLog << std::endl;
    }

    return shader;
}

int Shader::createProgram(int vertexShader, int fragmentShader)
{
    unsigned int    program;
    int             issuccess;
    char            infoLog[512];

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &issuccess);
    if(!issuccess)
    {
        memset(infoLog, 0, sizeof(infoLog));
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void Shader::createGeometryShader(const char *geometryPath) {
    int geometry_shader;
    int issuccess;
    char infoLog[512];

    geometry_shader = createShader(geometryPath, GL_GEOMETRY_SHADER);
    glAttachShader(ID, geometry_shader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &issuccess);
    if(!issuccess)
    {
        memset(infoLog, 0, sizeof(infoLog));
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED: " << infoLog << std::endl;
    }
    glDeleteShader(geometry_shader);
}

