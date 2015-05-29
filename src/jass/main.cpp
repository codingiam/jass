#include "main.h"
#include "application.h"

int main( int argc, char* argv[] ) {
    char cCurrentPath[FILENAME_MAX];
    
    GetCurrentDir( cCurrentPath, sizeof(cCurrentPath) );
    
    std::cout << "Directorul curent este: " << cCurrentPath << std::endl;
    
	Application* app = Application::getApp();

	try {
		app->init();
		app->run();
	} catch( const std::runtime_error exceptie ) {
		std::cout << "exceptie runtime:\n" << exceptie.what() << std::endl;
	} catch( const std::logic_error exceptie ) {
		std::cout << "exceptie logica:\n" << exceptie.what() << std::endl;
	} /* catch( const std::exception exceptie ) {
	} catch( ... ) {
		std::cout << "O exceptie netrata a fost gasita. Programul va fi oprit." << std::endl;
	} //*/

	return 0;
}