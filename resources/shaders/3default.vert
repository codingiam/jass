#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vUV;
layout(location = 2) in vec3 vNormal;

out vec2 fTexCoord;
out vec3 fNormal;
out vec3 fFragPos;

uniform mat4 mvp;
uniform mat4 model;

void main() {
  gl_Position = mvp * vec4(vPosition, 1.0f);
  fFragPos = vec3(model * vec4(vPosition, 1.0f));
  fNormal = mat3(transpose(inverse(model))) * vNormal;
  fTexCoord = vec2(vUV.x, 1.0f - vUV.y);
}
