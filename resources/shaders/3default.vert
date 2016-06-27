#version 430 core

layout(location = 0) in vec3 vpModelspace;
layout(location = 1) in vec2 vUV;
layout(location = 2) in vec3 vnModelspace;

out vec2 UV;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 mvp;
uniform mat4 model;

void main() {
  gl_Position = mvp * vec4(vpModelspace, 1.0f);
  FragPos = vec3(model * vec4(vpModelspace, 1.0f));
  Normal = Normal = mat3(transpose(inverse(model))) * vnModelspace;
  UV = vUV;
};
