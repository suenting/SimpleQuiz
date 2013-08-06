#include "pch.h"
#include "ConfigManager.h"

ConfigManager::ConfigManager()
{

}

ConfigManager::~ConfigManager()
{

}

void ConfigManager::Load()
{
	// set defaults
	mbRandomize = true;
	mQuizMaxLength = 10;
	mBackgroundType = BackgroundClouds;
	mbPostAnswers = true;

	mBgR=0xbb;
	mBgG=0xcc;
	mBgB=0xff;
	mBgA=0xff;
}

