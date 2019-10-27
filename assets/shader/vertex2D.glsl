#version 410

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec4 vertexColor;
layout (location = 2) in mat4 modelMatrix;

uniform mat4 projection;

out vec4 color;

void main() {
  gl_Position = projection * modelMatrix * vec4(vertexPosition, 0.0, 1.0);
  color = vertexColor;
}
