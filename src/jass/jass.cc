// Copyright (c) 2011, Doru Catalin Budai. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "jass/jass.h"

#include "jass/application.h"

#define STATUS_OK 0
#define STATUS_ERROR 1

int main(int argc, char *argv[]) {
//#if defined(_DEBUG) && defined(_WINDOWS)
//  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
//#endif

  int result = STATUS_ERROR;

  try {
    Application application;  
    
    application.Initialize();
    
    application.Run();

    result = STATUS_OK;
  } catch (const std::runtime_error &e) {
    std::cout << "Runtime exception caught: " << e.what() << std::endl << "Exiting." << std::endl;
  } catch (const std::exception &e) {
    std::cout << "Exception caught: " << e.what() << std::endl << "Exiting." << std::endl;
  } catch (...) {
    std::cout << "Unknown exception caught." << std::endl << "Exiting." << std::endl;
  }

//#if defined(_DEBUG) && defined(_WINDOWS)
//  _CrtDumpMemoryLeaks();
//#endif

  return result;
}
