// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JASS_APPLICATION_H_
#define JASS_APPLICATION_H_

#include <memory>

namespace Subsystems {
class Window;
class GL;
class DevIL;
}

namespace States {
class StatesManager;
}

class Application  {
 public:
  Application(const Application &) = delete;
  Application & operator=(const Application &) = delete;

  Application(void);
  ~Application(void);

  void Initialize(void);

  void Run(void);

 private:
  void ShutDown(void);

  void InitializeWindow(void);
  void InitializeGL(void);
  void InitializeDevIL(void);
  void InitializeStates(void);

  std::shared_ptr<Subsystems::Window> window_;
  std::shared_ptr<Subsystems::GL> gl_;
  std::shared_ptr<Subsystems::DevIL> devil_;
  std::shared_ptr<States::StatesManager> states_manager_;
};

#endif  // JASS_APPLICATION_H_
