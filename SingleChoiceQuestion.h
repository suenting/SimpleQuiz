#ifndef SINGLECHOICEQUESTION_H
#define SINGLECHOICEQUESTION_H

#include "Question.h"
#include <vector>
#include <string>
#include "WidgetButton.h"

struct SingleChoiceAnswer
{
public:
	SingleChoiceAnswer( std::string text, std::string code, bool correct, size_t index);
	std::string answerText;
	std::string code;
	bool bIsCorrect;
	WidgetButton button;
	bool bIsSelected;
};

class SingleChoiceQuestion : public Question
{
public:
	SingleChoiceQuestion();
	~SingleChoiceQuestion();
	virtual void Render()const;
	virtual void Render(float percent)const;
	virtual void RenderAnswer()const;
	virtual void Update();
	virtual void Input(SDL_Event &event);
	void AddAnswer(std::string text, std::string code, bool isCorrect);
	void SelectAnswer(int index);

private:
	std::vector<SingleChoiceAnswer> mAnswerList;
	std::string mSelectedCode;
};



#endif