#version 300 es
precision mediump float;

in vec2 TexCoords;
uniform sampler2D ourTexture;

out vec4 FragColor;


void main() {
    FragColor = texture(ourTexture, TexCoords);
}