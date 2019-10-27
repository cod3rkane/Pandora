#version 410

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec4 vertexColor;
layout (location = 2) in mat4 modelMatrix;

uniform vec2 viewport;
uniform mat4 projection;
uniform mat4 view;

out vec4 color;

void main() {
  gl_Position = modelMatrix * vec4(vertexPosition.xy / viewport.xy, 0.0, 1.0);
  color = vertexColor;
}
