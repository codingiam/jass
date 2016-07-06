#version 410 core

layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec2 vUV;

out vec2 fTexCoord;

uniform mat4 mp;

void main() {
  gl_Position = mp * vec4(vPosition, 0.0f, 1.0f);
  fTexCoord = vUV;
}
