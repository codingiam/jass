// Copyright (c) 2011, Doru Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/jass.h"

#include "jass/application.h"

int main(int argc, char *argv[]) {
  int result = EXIT_FAILURE;

  try {
    Application application;

    application.Initialize();

    application.Run();

    result = EXIT_SUCCESS;
  } catch (const std::runtime_error &e) {
    std::cout << "Runtime exception caught: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  } catch (...) {
    std::cout << "Unknown exception caught." << std::endl;
  }

  return result;
}
