#include "pch.h"
#include "Quiz.h"
#include "SingleChoiceQuestion.h"
#include "WidgetButton.h"
#include "AssetManager.h"
#include "ConfigManager.h"
#include "Background.h"


namespace
{
	static const float fadeTicks = 20;
	static const float postAnswerTicks = 30;


	static SDL_Color color = {255,255,255,255};
	static SDL_Rect rect;

	WidgetButton startButton;
	void start(std::string)
	{
		Quiz::Instance().SetState(QS_QUESTION);
	}
	void nullclick(std::string)
	{

	}
	WidgetButton finishText;

	// trim for emscripten
	std::string trim(const std::string &str)
	{
		size_t s = str.find_first_not_of(" \n\r\t");
		size_t e = str.find_last_not_of (" \n\r\t");

		if(( std::string::npos == s) || ( std::string::npos == e))
			return "";
		else
			return str.substr(s, e-s+1);
	}

	std::string GetText(std::string path)
	{
		std::string ret;
		std::string line;

		std::ifstream file("Assets/quiz/"+trim(path));
		SingleChoiceQuestion *scq;
		size_t ansIndex = 0;
		if (file.is_open())
		{
			while ( file.good() )
			{
				getline(file,line);
				ret.append(line);
				ret.append("\n");
			}
			file.close();
		}
		return ret;
	}
}

void Quiz::Initialize()
{
	SDL_Init(SDL_INIT_VIDEO);

	ConfigManager::Instance().Load();
	mpBackground = new Background();
	mpBackground->Load();
#if Win32
	window = SDL_CreateWindow("A Simple Quiz", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	screen = SDL_GetWindowSurface(window);
#endif
#if EMSCRIPTEN
	screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
#endif
	
	startButton.SetPos(300,250);
	startButton.SetText("start");

	startButton.SetOnClick(start);
	startButton.SetButtonFrame(AssetManager::Instance().GetButtonFrameShort());
	startButton.SetButtonFrameHover(AssetManager::Instance().GetButtonFrameShortHover());
	startButton.SetFont(AssetManager::Instance().GetFont40());
	// load questions
	state = QS_START;
	LoadQuiz();
	mQuestionIterator = mQuestionList.begin();
	
	// initialize logic
	mScore = 0;

}

void Quiz::Input()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
#if Win32
		if (event.type == SDL_QUIT)
		{
			SDL_Quit();
			exit(0);
		}
#endif
		 SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent*)&event;
		switch(state)
		{
		case QS_START:
			startButton.Input(event);
			break;
		case QS_QUESTION:
			(*mQuestionIterator)->Input(event);
			break;
		case QS_QUESTION_ENTER:
		case QS_POSTANSWER:
		case QS_QUESTION_FADE:
		case QS_FINISH:
			break;
		}
	}
}

void Quiz::Update()
{

	switch(state)
	{
	case QS_QUESTION_ENTER:
		UpdateQuestionEnter();
		if(NULL != mpBackground)
		{
			mpBackground->Update();
		}
		break;
	case QS_QUESTION_FADE:
		UpdateFade();
		if(NULL != mpBackground)
		{
			mpBackground->Update();
		}
		break;
	case QS_POSTANSWER:
		UpdatePostAnswers();
		break;
	case QS_START:
	case QS_QUESTION:
	case QS_FINISH:
		break;
	}
}

void Quiz::Render()const
{
	
	// clear screen
	SDL_Rect screenRect;
	screenRect.x = screenRect.y = 0;
	screenRect.w = screen->w;
	screenRect.h = screen->h;
	SDL_FillRect(screen, &screenRect, SDL_MapRGBA(screen->format, ConfigManager::Instance().GetR(), ConfigManager::Instance().GetG(), ConfigManager::Instance().GetB(), ConfigManager::Instance().GetA()));
	if(NULL != mpBackground)
	{
		mpBackground->Render();
	}
	switch(state)
	{
	case QS_START:
		startButton.Render();
		break;
	case QS_QUESTION_ENTER:
		(*mQuestionIterator)->Render(static_cast<float>(mFade)/fadeTicks);
		break;
	case QS_QUESTION:
		(*mQuestionIterator)->Render();
		break;
	case QS_POSTANSWER:
		(*mQuestionIterator)->RenderAnswer();
		break;
	case QS_QUESTION_FADE:
		(*mQuestionIterator)->Render(static_cast<float>(mFade)/fadeTicks);
		break;
	case QS_FINISH:
		finishText.Render();
		break;
	}
	
#if Win32
	SDL_UpdateWindowSurface(window);
#endif
#if EMSCRIPTEN
	SDL_Flip(screen); 
#endif

}

Quiz::~Quiz()
{
	for(std::vector<Question*>::iterator it = mQuestionList.begin(), et = mQuestionList.end(); it !=et;++it)
	{
		delete (*it);
	}
	if(NULL != mpBackground)
	{
		delete mpBackground;
	}
}

void Quiz::LoadQuiz()
{
	std::string line;
	std::ifstream file("Assets/quiz/quiz.txt");
	SingleChoiceQuestion *scq;
	size_t ansIndex = 0;
	if (file.is_open())
	{
		while ( file.good() )
		{
			getline(file,line);
			char key = line[0];
			std::string text;
			char codestr[5];
			switch(key)
			{
			case 's':
				scq = new SingleChoiceQuestion();
				if('e'==line[1])
				{
					text = line.substr(3);
					scq->SetText(GetText(text));
				}
				else
				{
					text = line.substr(2);
					scq->SetText(text);
				}
				mQuestionList.push_back(scq);
				ansIndex=0;
				break;
			case 'r':
				sscanf(line.c_str(),"%c",&key);
				scanf(codestr,"%d",ansIndex);
				++ansIndex;
				text = line.substr(2);
				scq->AddAnswer(text,std::string(codestr),true);
				break;
			case 'w':
				sscanf(line.c_str(),"%c",&key);
				scanf(codestr,"%d",ansIndex);
				++ansIndex;
				text = line.substr(2);
				scq->AddAnswer(text,std::string(codestr),false);
				break;
			}
		}
		file.close();
	}
	if(ConfigManager::Instance().GetRandomize())
	{
		srand(unsigned(time(NULL)));
		std::random_shuffle(mQuestionList.begin(),mQuestionList.end());
	}
	ConfigManager::Instance().SetQuizMaxLength(std::min(mQuestionList.size(),ConfigManager::Instance().GetQuizMaxLength()));
}


void Quiz::SelectAnswer( std::string code, int points )
{
	mSelectedCodes += code;
	mScore +=points;
	if(ConfigManager::Instance().GetPostAnswers())
	{
		mFade = postAnswerTicks;
		SetState(QS_POSTANSWER);
	}
	else
	{
		mFade = fadeTicks;
		SetState(QS_QUESTION_FADE);
	}
}

void Quiz::UpdateFade()
{
	--mFade;
	if(mFade<1)
	{
		++mQuestionIterator;
		if((mQuestionIterator == mQuestionList.end()) || (mQuestionIterator == (mQuestionList.begin()+ConfigManager::Instance().GetQuizMaxLength())))
		{
			SetState(QS_FINISH);
			finishText.SetPos(170,50);
			startButton.SetOnClick(nullclick);
			finishText.SetFont(AssetManager::Instance().GetFont40());
			char finalText[256];
			size_t total = std::min(mQuestionList.size(),ConfigManager::Instance().GetQuizMaxLength());
			sprintf(finalText,"       FINISHED!! \n   you scored %d/%d",mScore,total);
			finishText.SetText(std::string(finalText));
			finishText.SetButtonFrame(AssetManager::Instance().GetFinishFrame());
		}
		else
		{
			mFade = -1.f*fadeTicks;
			SetState(QS_QUESTION_ENTER);
		}
	}
}

void Quiz::UpdateQuestionEnter()
{
	++mFade;
	if(mFade>-1)
	{
		SetState(QS_QUESTION);
	}
}

void Quiz::UpdatePostAnswers()
{
	--mFade;
	if(mFade<1)
	{
		mFade=fadeTicks;
		SetState(QS_QUESTION_FADE);
	}
}
