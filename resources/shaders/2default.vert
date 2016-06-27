#version 430 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 vUV;

out vec2 TexCoord;

uniform mat4 mp;

void main() {
  gl_Position = mp * vec4(position, 0.0f, 1.0f);
  TexCoord = vUV;
}
