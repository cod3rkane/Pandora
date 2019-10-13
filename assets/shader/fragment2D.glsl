#version 410

out vec4 FragColor;

in vec2 color;

void main() {
  FragColor = vec4(color, 0.0, 1.0);
}
