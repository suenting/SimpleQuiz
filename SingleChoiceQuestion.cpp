#include "SingleChoiceQuestion.h"
#include "pch.h"
#include "AssetManager.h"
#include "Quiz.h"

namespace
{
	static SDL_Color color = {0,0,0,255};

	void SelectAnswer(std::string param)
	{
		int index;
		sscanf(param.c_str(),"%d",&index);
		static_cast<SingleChoiceQuestion*>( (*Quiz::Instance().GetCurrentQuestion()))->SelectAnswer(index);

	}
}
SingleChoiceQuestion::SingleChoiceQuestion()
{

}

SingleChoiceQuestion::~SingleChoiceQuestion()
{

}

void SingleChoiceQuestion::Render()const
{
	Render(1.0);
}

void SingleChoiceQuestion::Render( float percent ) const
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
	SDL_Rect pos = {50,20,0,0};
	pos.x -= shiftPos;

	// for each line in string
	std::string tempText = mText;
	int sub = 0;
	while(sub != -1)
	{
		sub = tempText.find('\n',0);
		std::string strSub = tempText.substr( 0,sub );
		SDL_Surface *text = TTF_RenderText_Solid(AssetManager::Instance().GetTextFontBold(), strSub.c_str(), color);
		SDL_Rect posTemp = pos; // sdl2 work around
		SDL_BlitSurface (text, NULL, Quiz::Instance().GetScreen(), &posTemp);
		SDL_FreeSurface(text);
		tempText = tempText.substr( sub+1, -1 );
		int wf;
		int hf;
		TTF_SizeText( AssetManager::Instance().GetTextFontBold(), strSub.c_str(), &wf,&hf );
		pos.y+= hf+1;
	}


	for(std::vector<SingleChoiceAnswer>::const_iterator it = mAnswerList.begin(),et = mAnswerList.end(); it != et; ++it)
	{
		it->button.Render(percent);
	}
}

void SingleChoiceQuestion::Update()
{

}

void SingleChoiceQuestion::Input( SDL_Event &event )
{
	for(std::vector<SingleChoiceAnswer>::iterator it = mAnswerList.begin(), et = mAnswerList.end(); it != et; ++it)
	{
		(*it).button.Input(event);
	}
}

void SingleChoiceQuestion::AddAnswer( std::string text, std::string code, bool isCorrect )
{
	mAnswerList.push_back(SingleChoiceAnswer(text, code,isCorrect,mAnswerList.size()));
}

void SingleChoiceQuestion::SelectAnswer( int index )
{
	mSelectedCode = mAnswerList[index].code;
	mAnswerList[index].bIsSelected=true;
	Quiz::Instance().SelectAnswer(mSelectedCode,static_cast<int>(mAnswerList[index].bIsCorrect));
}

void SingleChoiceQuestion::RenderAnswer() const
{
	Render();
	for(std::vector<SingleChoiceAnswer>::const_iterator it = mAnswerList.begin(),et = mAnswerList.end(); it != et; ++it)
	{
		int x = it->button.GetX()+it->button.GetWidth()-60;
		int y = it->button.GetY();
		SDL_Rect pos = {x,y,0,0};
		if(it->bIsSelected)
		{
			if(it->bIsCorrect)
			{
				SDL_BlitSurface (AssetManager::Instance().GetO(), NULL, Quiz::Instance().GetScreen(), &pos);
			}
			else
			{
				SDL_BlitSurface (AssetManager::Instance().GetX(), NULL, Quiz::Instance().GetScreen(), &pos);
			}
		}
		else
		{
			if(it->bIsCorrect)
			{
				SDL_BlitSurface (AssetManager::Instance().GetO(), NULL, Quiz::Instance().GetScreen(), &pos);
			}
		}
	}
}

SingleChoiceAnswer::SingleChoiceAnswer( std::string text, std::string code, bool correct, size_t index )
{
	bIsSelected=false;
	answerText = text;
	bIsCorrect = correct;
	this->code = code;
	button.SetButtonFrame(AssetManager::Instance().GetButtonFrame());
	button.SetButtonFrameHover(AssetManager::Instance().GetButtonFrameHover());
	button.SetText(text);
	button.SetFont(AssetManager::Instance().GetTextFont());
	button.SetPos( 25, 150+60*index);
	button.SetVerticalOffSet(5);
	char param[64];
	sprintf(param,"%d",index);
	button.SetParam(param);
	button.SetOnClick(SelectAnswer);
}
