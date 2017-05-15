#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;

out vec3 fColor;

uniform mat4 mvp;

void main() {
  gl_Position = mvp * vec4(vPosition, 1.0f);
  fColor = vColor;
}
