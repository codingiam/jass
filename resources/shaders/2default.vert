#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vUV;

out vec2 TexCoord;

uniform mat4 mvp;

void main() {
  gl_Position = mvp * vec4(position, 1.0f);
  TexCoord = vUV;
}
