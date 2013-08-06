#ifndef QUESTION_H
#define QUESTION_H
#if Win32
#include <SDL2\SDL_events.h>
#endif
#if __EMSCRIPTEN__
#include <SDL\SDL_events.h>
#endif

#include <string>

class Question
{
public:
	Question();
	virtual ~Question();
	virtual void Render()const=0;
	virtual void Render(float percent)const=0;
	virtual void RenderAnswer()const=0;
	virtual void Update()=0;
	virtual void Input(SDL_Event &event)=0;
	void SetText(std::string text);


protected:
	std::string mText;
};

#endif