#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture2D{
public:
    unsigned int ID;
    // texture dimensions
    unsigned int Width, Height; 
    // texture Format
    unsigned int Internal_Format;   // texture object
    unsigned int Image_Format;      // format of loaded img
    // texture configuration
    unsigned int WRAP_S;
    unsigned int WRAP_T;
    unsigned int Filter_Min;
    unsigned int Filter_Max;

    Texture2D();
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind() const;
};

#endif