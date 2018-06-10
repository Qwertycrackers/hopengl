#version 330 core

in vec4 vertexColor;

out vec4 color;
uniform float green;

void main() {
  color = vec4(vertexColor.x, green, vertexColor.z, vertexColor.w);
}

