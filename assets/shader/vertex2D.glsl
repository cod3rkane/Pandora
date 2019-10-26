#version 410

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in mat4 modelMatrix;

uniform vec2 scale;
// uniform mat4 model;

out vec3 color;

void main() {
  gl_Position = modelMatrix * vec4(vertexPosition * scale, 0.0, 1.0);
  color = vertexColor;
}
