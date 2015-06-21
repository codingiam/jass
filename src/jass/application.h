// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_APPLICATION_H_
#define JASS_APPLICATION_H_
#pragma once

#include <boost/shared_ptr.hpp>

#include "jass/jass.h"

class Window;
class StatesManager;

class Application : boost::noncopyable  {
 public:
  Application(void);
  ~Application(void);

  void Initialize(void);
  void ShutDown(void);

  void Run(void);

 private:
  void InitializeWindow(void);
  void InitializeVideo(void);
  void InitialiseStates(void);

  void Tick(const Uint32 dt);

  bool sdl_initialized_;

  boost::shared_ptr<Window> window_;
  boost::shared_ptr<StatesManager> states_manager_;
};

#endif  // JASS_APPLICATION_H_
