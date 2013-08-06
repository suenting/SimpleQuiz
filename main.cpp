#include "pch.h"
#include "Quiz.h"

namespace
{
	const int SIM_FRAMES_PER_SECOND = 15;
	const int RENDER_FRAMES_PER_SECOND = 30;
	int frame = 0;
	size_t simStart=0;
	size_t renderStart=0;
	size_t currentTimer;
	void MainLoop()
	{
		
		Quiz::Instance().Input();
		currentTimer = SDL_GetTicks();
		if( (0==renderStart) || (currentTimer-renderStart)>(1000/RENDER_FRAMES_PER_SECOND))
		{		
			renderStart=SDL_GetTicks();
			Quiz::Instance().Update();
			Quiz::Instance().Render();
		}

	}
}



int main(int argc, char** argv)
{
	
#if EMSCRIPTEN
	// include GL stuff, to check that we can compile hybrid 2d/GL apps
	extern void glBegin(int mode);
	extern void glBindBuffer(int target, int buffer);
	if (argc == 9876) {
		glBegin(0);
		glBindBuffer(0, 0);
	}
#endif
	

	
	Quiz::Instance().Initialize();
	
#if Win32
	while(true)
	{
		MainLoop();
	}
#endif
	
#if EMSCRIPTEN

	emscripten_set_main_loop(MainLoop, 30, 1);
	
#endif
	
	SDL_Quit();
	return 0;
	
}