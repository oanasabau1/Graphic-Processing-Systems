#version 400
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColour;
out vec3 colour;
uniform vec3 position;
void main() {
 colour = vertexColour;
 gl_Position = vec4(vertexPosition + position, 1.0);
}