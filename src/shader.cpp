#include <shader.h>

#include <iostream>

Shader &Shader::Use(){
    glUseProgram(this->ID);
    return *this;
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource){
    unsigned int sVertex, sFragment, gShader;
    
    // vertex shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");

    // fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");

    // geometry shader
    if (geometrySource != nullptr){
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }

    // shader program
    this->ID = glCreateProgram();
    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(this->ID, gShader);
    
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");
    // delete Shaders
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);
}

void Shader::SetFloat(const char *name, float value, bool useShader){
    if (useShader)
        this->Use();
        glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetInteger(const char *name, int value, bool useShader){
    if (useShader)
        this->Use();
        glUniform1i(glGetUniformLocation(this->ID, int value, booluseShader));

}