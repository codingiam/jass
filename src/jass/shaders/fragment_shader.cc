// Copyright (c) 2015, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/shaders/fragment_shader.h"

#include <string>

namespace {
  std::string source =
    "#version 430 core"
    "\n"
    "in vec2 UV;"
    ""
    "in vec3 Normal;"
    "in vec3 FragPos;"
    ""
    "uniform sampler2D tex;"
    ""
    "uniform vec3 lightPos;"
    "uniform vec3 viewPos;"
    "uniform vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);"
    "uniform vec4 objectColor;"
    ""
    "out vec4 color;"
    ""
    "void main()"
    "{"
    "  float ambientStrength = 1.0f;"
    "  vec3 ambient = ambientStrength * lightColor;"
    ""
    "  vec3 norm = normalize(Normal);"
    "  vec3 lightDir = normalize(lightPos - FragPos);"
    "  float diff = max(dot(norm, lightDir), 0.0);"
    "  vec3 diffuse = diff * lightColor;"
    ""
    "  float specularStrength = 0.5f;"
    "  vec3 viewDir = normalize(viewPos - FragPos);"
    "  vec3 reflectDir = reflect(-lightDir, norm);"
    "  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);"
    "  vec3 specular = specularStrength * spec * lightColor;"
    ""
    "  color = texture(tex, UV) * vec4(ambient + diffuse + specular, 1.0f) * objectColor;"
    "}";
}  // namespace

namespace Shaders {

FragmentShader::FragmentShader() {
}

FragmentShader::~FragmentShader() {
}

void FragmentShader::Create() {
  Shader::Create(GL_FRAGMENT_SHADER, source);
}

}  // namespace Shaders
