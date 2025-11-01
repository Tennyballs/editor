#ifndef HELPER_H
#define HELPER_H

#include "Image.h"
#include "Object.h"

#include <emscripten/html5_webgl.h>
#include <GL/glfw.h>
#include <GLES2/gl2.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

GLuint helper_gen_texture(Image *img)
{
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}

char *helper_read_file(const char *path)
{
    FILE *f = fopen(path, "rb");
    char *data;
    long file_size;

    if (f == NULL)
    {
        printf("Error reading file! %s\n", path);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    file_size = ftell(f);

    if (file_size == -1) {
        printf("Error getting file size for %s\n", path);
        fclose(f);
        return NULL;
    }

    data = (char *)malloc(sizeof(char) * (file_size + 1)); 

    if (data == NULL) {
        printf("Memory allocation failed for %s\n", path);
        fclose(f);
        return NULL;
    }

    fseek(f, 0, SEEK_SET);

    size_t bytes_read = fread(data, 1, file_size, f);

    if (bytes_read != file_size) {
        printf("Error reading file content fully for %s\n", path);
        free(data);
        fclose(f);
        return NULL;
    }

    data[file_size] = '\0';

    fclose(f);

    return data;
}


GLuint helper_new_shader(GLenum shaderType, const char *source)
{
    GLuint shader = glCreateShader(shaderType);
    char *data = helper_read_file(source);

    const GLchar* sources[] = { data };

    glShaderSource(shader, 1, sources, NULL);
    glCompileShader(shader);

    free(data);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE)
    {
        printf("Error with compiling shader %s!!!\n", source);

        // Optional: Retrieve and print the shader log for debugging
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            char *log = (char *)malloc(logLength);
            glGetShaderInfoLog(shader, logLength, NULL, log);
            printf("Shader compilation log:\n%s\n", log);
            free(log);
        }

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint helper_basic_shader_program_setup()
{
    GLuint vertexShader, fragmentShader;
    vertexShader = helper_new_shader(GL_VERTEX_SHADER, "/shader/base.vert");
    fragmentShader = helper_new_shader(GL_FRAGMENT_SHADER, "/shader/base.frag");
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        char* infoLog = (char*)malloc(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);

        printf("Error linking shader program:\n%s\n", infoLog);

        // Delete the program if linking failed
        glDeleteProgram(program);
        free(infoLog);

        return 0;
    }
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    return program;
};

#endif//HELPER_H