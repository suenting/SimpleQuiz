#ifndef CONFIG_H
#define CONFIG_H
#include <string>

enum BackgroundType
{
	BackgroundClouds,
	BackgroundDesert,
	BackgroundNone
};

class ConfigManager
{
public:
	static ConfigManager& Instance()
	{
		static ConfigManager instance;
		return instance;
	}
	~ConfigManager();
	void Load();
	bool GetRandomize() const { return mbRandomize; }
	size_t GetQuizMaxLength() const { return mQuizMaxLength; }
	void SetQuizMaxLength(size_t maxLength){mQuizMaxLength=maxLength;}
	BackgroundType GetBackgroundType() const { return mBackgroundType; }
	bool GetPostAnswers() const { return mbPostAnswers; }

	Uint8 GetR()const{return mBgR;}
	Uint8 GetG()const{return mBgG;}
	Uint8 GetB()const{return mBgB;}
	Uint8 GetA()const{return mBgA;}
private:
	ConfigManager();
	size_t mQuizMaxLength;
	bool mbRandomize;
	bool mbPostAnswers;


	BackgroundType mBackgroundType;
	Uint8 mBgR;
	Uint8 mBgG;
	Uint8 mBgB;
	Uint8 mBgA;

	


};

#endif