// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_SRC_JASS_APPLICATION_H_
#define JASS_SRC_JASS_APPLICATION_H_
#pragma once

#include <boost/shared_ptr.hpp>

#include "jass/jass.h"

class StateIntro;
class StatePlay;

class Application : boost::noncopyable  {
public:
  enum { kWidth = 800, kHeight = 600, kBpp = 16, kFull = 0 };

  Application();
  ~Application();

  void Initialise();
  void Run();
  void Shutdown();

private:
  void InitialiseSDL();
  // void InitialiseFMOD();
  void InitialiseStates();

  boost::shared_ptr<StateIntro> state_intro_;
  boost::shared_ptr<StatePlay> state_play_;
  // FMUSIC_MODULE* intro_music_;
};

#endif  // JASS_SRC_JASS_APPLICATION_H_
