#version 330 core

in vec2 fTexCoord;

uniform sampler2D tex;
uniform vec4 objectColor;

out vec4 color;

void main()
{
  color = texture(tex, fTexCoord) * objectColor;
}
