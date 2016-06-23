#version 430 core

layout(location = 0) in vec3 vpModelspace;
layout(location = 1) in vec2 vUV;

out vec2 UV;

uniform mat4 mvp;

void main() {
  gl_Position = mvp * vec4(vpModelspace, 1.0f);
  UV = vUV;
};
