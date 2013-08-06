#ifndef BUTTON_H
#define BUTTON_H
#include "Widget.h"
#include <string>
#if Win32
#include <SDL2\SDL_ttf.h>
#endif
#if __EMSCRIPTEN__
#include <SDL/SDL_ttf.h> 
#endif 
class WidgetButton : Widget
{
public:
	WidgetButton();
	~WidgetButton();
	void Render()const;
	void Render(float percent)const;
	void Input(SDL_Event &event);
	void SetPos(int x, int y);
	void SetText(std::string text);
	void SetButtonFrame(SDL_Surface* frame);
	void SetButtonFrameHover(SDL_Surface* frame);
	void SetOnClick( void(*OnClick)(std::string));
	void SetFont(TTF_Font* font);
	void SetVerticalOffSet(int offSet);
	void SetParam(std::string param);

	int GetX()const{return x;}
	int GetY()const{return y;}
	int GetHeight()const{return h;}
	int GetWidth()const{return w;}

private:
	TTF_Font* mFont;
	SDL_Surface* mFrame;
	SDL_Surface* mFrameHover;
	std::string mText;
	int x;
	int y;
	int w;
	int h;
	int mVerticalOffSet;
	std::string mParam; // used for callback
	bool mbHover;
	void (*pOnClick)(std::string);
};

#endif