#version 410

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec2 vertexColor;

uniform vec2 scale;
uniform mat4 model;

out vec2 color;

void main() {
  gl_Position = model * vec4(vertexPosition * scale, 0.0, 1.0);
  color = vertexColor;
}
