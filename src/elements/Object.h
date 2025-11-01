#ifndef OBJECT_H
#define OBJECT_H


#include <stdlib.h>
#include <GLES3/gl3.h>

typedef struct __attribute__((packed)) Object {
    GLuint VAO;
    GLuint positionVBO;
    GLuint uvVBO;
    GLuint EBO;         // for indexed drawing
    GLuint textureID;
    GLsizei vertexCount;
    GLsizei indexCount; // 0 for arrays
} Object;

void object_draw(Object *obj)
{
    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, obj->textureID); 
    
    glBindVertexArray(obj->VAO);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, obj->vertexCount);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


Object object_create_from_points(float *positions, float *uvs, GLsizei num_vertices) {
    Object obj;
    obj.vertexCount = num_vertices;
    obj.textureID = 0;

    size_t pos_size = num_vertices * 3 * sizeof(float);
    size_t uv_size = num_vertices * 2 * sizeof(float);

    glGenVertexArrays(1, &obj.VAO);
    glBindVertexArray(obj.VAO);

    glGenBuffers(1, &obj.positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, obj.positionVBO);
    glBufferData(GL_ARRAY_BUFFER, pos_size, positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &obj.uvVBO);
    glBindBuffer(GL_ARRAY_BUFFER, obj.uvVBO);
    glBufferData(GL_ARRAY_BUFFER, uv_size, uvs, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return obj;
}


#endif//OBJECT_H