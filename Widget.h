#ifndef WIDGET_H
#define WIDGET_H
#if Win32
#include <SDL2\SDL_events.h>
#endif
#if __EMSCRIPTEN__
#include <SDL\SDL_events.h>
#endif
class Widget
{
public:
	Widget();
	virtual ~Widget();
	virtual void Render()const=0;
	virtual void Render(float percent)const=0;
	virtual void Input(SDL_Event &event)=0;

private:
};

#endif