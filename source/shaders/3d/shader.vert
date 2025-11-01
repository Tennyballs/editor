#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 TexCoords; // Pass UV coords to fragment shader

void main() {
    gl_Position = vec4(aPos, 1.0);
    TexCoords = aUV;
}