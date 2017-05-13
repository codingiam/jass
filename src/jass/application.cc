// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/application.h"

#include <boost/format.hpp>

#include <iostream>

#include "jass/subsystems/gl_window.h"
#include "jass/subsystems/gl_renderer.h"
#include "jass/subsystems/devil.h"
#include "jass/states/states_manager.h"

Application::Application() {
  std::cout << "Application being constructed ..." << std::endl;
}

Application::~Application() {
  ShutDown();
  std::cout << "Application destroyed." << std::endl;
}

void Application::Initialize() {
  InitializeWindow();
  InitializeGL();
  InitializeDevIL();
  InitializeStates();
}

void Application::ShutDown() {
  states_manager_.reset();
  devil_.reset();
  window_.reset();
//  SDL_Quit();
}

void Application::InitializeWindow() {
  this->window_ = std::make_shared<Subsystems::GLWindow>();
  window_->Initialize();
}

void Application::InitializeGL() {
  this->gl_ = std::make_shared<Subsystems::GLRenderer>();
  gl_->Initialize();
}

void Application::InitializeDevIL() {
  this->devil_ = std::make_shared<Subsystems::DevIL>();
  devil_->Initialize();
}

void Application::InitializeStates() {
  this->states_manager_ = std::make_shared<States::StatesManager>();
  states_manager_->Initialize();
}

void Application::Run() {
  window_->Run();
}
