#include "SDL_main.h"
#include "SDL.h"

#include <memory>

#include "Application.h"

int main(int argc, char* argv[]) {

	std::unique_ptr<Application> application = std::make_unique<Application>();

	if (application->initialize()) {
		application->run();
	}	

	return 0;
}