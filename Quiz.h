#ifndef QUIZ_H
#define QUIZ_H
#if Win32
#include "SDL2\SDL.h"
#endif
#if __EMSCRIPTEN__
#include "SDL\SDL.h"
#endif
#include <vector>
#include "Question.h"
#include "Background.h"

enum QuizState
{
	QS_START,
	QS_QUESTION_ENTER,
	QS_QUESTION,
	QS_POSTANSWER,
	QS_QUESTION_FADE,
	QS_FINISH
};

class Quiz
{
public:
	static Quiz& Instance()
	{
		static Quiz instance;
		return instance;
	}
	~Quiz();

	void Initialize();
	void Input();
	void Update();
	void Render()const;
	SDL_Surface* GetScreen()const{return screen;};

	QuizState GetState() const { return state; }
	void SetState(QuizState val) { state = val; }
	void SelectAnswer(std::string code, int points);
	void UpdateFade();
	void UpdatePostAnswers();
	void UpdateQuestionEnter();
	std::vector<Question*>::iterator GetCurrentQuestion()const{return mQuestionIterator;}
private:
	Quiz(){};
	Quiz(const Quiz& ref){};
	void operator=(Quiz const&); 
	QuizState state;
	void LoadQuiz();

	int mFade;
	std::vector<Question*> mQuestionList;
	std::vector<Question*>::iterator mQuestionIterator;

	size_t mScore;
	std::string mSelectedCodes;
	
	// effects
	Background *mpBackground;

	// SDL (todo re factor out later)
#if Win32
	SDL_Window *window;
	SDL_Renderer* renderer;
#endif
	SDL_Surface *screen;
};

#endif // !QUIZ_H
