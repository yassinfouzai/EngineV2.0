#include "Engine/Core/Logger.h"
#include "Shader.h"

#include <fstream>
#include <sstream>

using namespace std;

Shader::Shader(const char* vPath, const char* fPath) {


            string vCode, fCode;
            ifstream vShaderFile, fShaderFile;

            vShaderFile.exceptions ( ifstream::failbit | ifstream::badbit);
            fShaderFile.exceptions ( ifstream::failbit | ifstream::badbit);

            try
            {
                vShaderFile.open(vPath);
                fShaderFile.open(fPath);
                stringstream vShaderStream, fShaderStream;

                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();

                vShaderFile.close();
                fShaderFile.close();

                vCode = vShaderStream.str();
                fCode = fShaderStream.str();
            }
            catch(ifstream::failure &e)
            {
                cerr << "ERR: SHADER : file didn't get raed succesfully!!" << endl;
            }
            const char* vShaderCode = vCode.c_str();
            const char* fShaderCode = fCode.c_str();

            unsigned int vertex, fragment;
            int success;
            char infoLog[512];

            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex,1,&vShaderCode,NULL);
            glCompileShader(vertex);

            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(vertex,512,NULL,infoLog);
                cerr << "ERR: vertex shader couldn't compile !!\n" << infoLog << endl;
            };

            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment,1,&fShaderCode,NULL);
            glCompileShader(fragment);

            glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(fragment,512,NULL,infoLog);
                cerr << "ERR: fragment shader couldn't compile !!\n" << infoLog << endl;
            };

            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            glLinkProgram(ID);

            glGetProgramiv(ID, GL_LINK_STATUS , &success);

            if(!success)
            {
                glGetShaderInfoLog(ID,512,NULL,infoLog);
                cerr << "ERR: Program couldn't link !!\n" << infoLog << endl;
            };

            glDeleteShader(vertex);
            glDeleteShader(fragment);

}

void Shader::use() const {
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const {
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompileErrors(GLuint shader, const std::string& type) const {
    GLint success;
    GLchar infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            LOG_ERROR("SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog);
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            LOG_ERROR("PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog);
        }
    }
}

