#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 Color;

uniform mat4 mvp;

void main() {
  gl_Position = mvp * vec4(position, 1.0f);
  Color = color;
}
