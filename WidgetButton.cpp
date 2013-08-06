#include "WidgetButton.h"
#include "pch.h"
#include "Quiz.h"


namespace
{
static SDL_Color color = {0,0,0,255};

}

WidgetButton::WidgetButton()
{
	x = 0;
	y = 0;
	w = 200;
	h = 50;
	mText = "";
	mVerticalOffSet=0;
	mbHover = false;
	mParam = "";
	mFrame=NULL;
	mFrameHover=NULL;
}




WidgetButton::~WidgetButton()
{

}

void WidgetButton::Render()const
{
	Render(1.0f);
}

void WidgetButton::Render( float percent ) const
{

	int shiftPos;
	if(percent>0)
	{
		shiftPos = (-1.f*(percent-1))*850;
	}
	if(percent<0)
	{
		shiftPos = (percent)*800;
	}

	SDL_Rect pos = {x,y,0,0};
	pos.x -= shiftPos;
	if(mbHover && (NULL != mFrameHover))
	{
		SDL_Rect posTemp = pos; // sdl2 work around
		SDL_BlitSurface (mFrameHover, NULL, Quiz::Instance().GetScreen(), &posTemp);
	}
	else if(NULL != mFrame)
	{
		SDL_Rect posTemp = pos; // sdl2 work around
		SDL_BlitSurface (mFrame, NULL, Quiz::Instance().GetScreen(), &posTemp);
	}

	pos.x+=30;
	pos.y+=mVerticalOffSet;


	// for each line in string
	std::string tempText = mText;
	int sub = 0;
	while(sub != -1)
	{
		sub = tempText.find('\n',0);
		std::string strSub = tempText.substr( 0,sub );
		SDL_Surface *text = TTF_RenderText_Solid(mFont, strSub.c_str(), color);
		SDL_BlitSurface (text, NULL, Quiz::Instance().GetScreen(), &pos);
		SDL_FreeSurface(text);
		tempText = tempText.substr( sub+1, -1 );
		int wf;
		int hf;
		TTF_SizeText( mFont, strSub.c_str(), &wf,&hf );
		pos.y+= hf+1;
	}
	
}
	



void WidgetButton::Input( SDL_Event &event )
{
	switch(event.type)
	{
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
			{
			SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent*)&event;
			int mx = m->x;
			int my = m->y;
			if( (mx>x) && (mx<(x+w)) && (my>y) && (my<(y+h)) )
			{
				mbHover = true;
			}
			else
			{
				mbHover = false;
			}
			}
			break;
		break;
		case SDL_MOUSEBUTTONUP: 
			{
			SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent*)&event;
			int mx = m->x;
			int my = m->y;
			if( (mx>x) && (mx<(x+w)) && (my>y) && (my<(y+h)) )
			{
				pOnClick(mParam);
			}
			}
			break;
	}
}

void WidgetButton::SetPos( int x, int y )
{
	this->x = x;
	this->y = y;
}

void WidgetButton::SetText( std::string text )
{
	mText = text;
}

void WidgetButton::SetOnClick( void(*OnClick)(std::string) )
{
	pOnClick = OnClick;
}

void WidgetButton::SetButtonFrame( SDL_Surface* frame )
{
	mFrame = frame;
	w = mFrame->w;
	h = mFrame->h;
}

void WidgetButton::SetFont( TTF_Font* font )
{
	mFont = font;
}

void WidgetButton::SetVerticalOffSet( int offSet )
{
	mVerticalOffSet = offSet;
}

void WidgetButton::SetParam( std::string param )
{
	mParam = param;
}

void WidgetButton::SetButtonFrameHover( SDL_Surface* frame )
{
		mFrameHover = frame;
}

