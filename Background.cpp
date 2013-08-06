#include "Background.h"
#include "pch.h"
#include "AssetManager.h"
#include "Quiz.h"
#include "ConfigManager.h"
Background::Background()
{
	
}

Background::~Background()
{
	for(std::vector<BackgroundEntity*>::iterator it = mEntities.begin(); it != mEntities.end();++it)
	{
		delete (*it);
	}
}

void Background::Load()
{
	switch(ConfigManager::Instance().GetBackgroundType())
	{
	case BackgroundClouds:
		LoadCounds();
		break;
	case BackgroundDesert:
		LoadDesert();
		break;
	case BackgroundNone:
		break;
	}

}

void Background::Update()
{
	for(std::vector<BackgroundEntity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
	{
		(*it)->x += (*it)->speed;
		if((*it)->x<(*it)->endx)
		{
			(*it)->x = (*it)->startx;
		}
	}
}

void Background::Render() const
{
	for(std::vector<BackgroundEntity*>::const_iterator it = mEntities.begin(); it != mEntities.end(); ++it)
	{
		SDL_Rect pos = {(*it)->x,(*it)->y,0,0};
		SDL_BlitSurface ((*it)->pSurface, NULL, Quiz::Instance().GetScreen(), &pos);
	}
}

void Background::LoadCounds()
{
	AssetManager::Instance().AddSurface("cloud1.png");		
	AssetManager::Instance().AddSurface("cloud2.png");
	AssetManager::Instance().AddSurface("cloud3.png");
	AssetManager::Instance().AddSurface("cloud4.png");
	AssetManager::Instance().AddSurface("cloud5.png");

	mEntities.reserve(6);
	mEntities.push_back(new BackgroundEntity(AssetManager::Instance().GetSurface("cloud1.png"),300,160,800,-200,-20));
	mEntities.push_back(new BackgroundEntity(AssetManager::Instance().GetSurface("cloud1.png"),600,450,800,-200,-20));
	mEntities.push_back(new BackgroundEntity(AssetManager::Instance().GetSurface("cloud2.png"),200,200,800,-100,-40));
	mEntities.push_back(new BackgroundEntity(AssetManager::Instance().GetSurface("cloud3.png"),400,120,800,-1024,-40));
	mEntities.push_back(new BackgroundEntity(AssetManager::Instance().GetSurface("cloud4.png"),300,300,800,-200,-60));
	mEntities.push_back(new BackgroundEntity(AssetManager::Instance().GetSurface("cloud1.png"),500,500,800,-1024,-60));
}

void Background::LoadDesert()
{
	AssetManager::Instance().AddSurface("desert.png");	
	mEntities.push_back(new BackgroundEntity(AssetManager::Instance().GetSurface("desert.png"),0,0,780,-800,-20));
	mEntities.push_back(new BackgroundEntity(AssetManager::Instance().GetSurface("desert.png"),800,0,780,-800,-20));
}


BackgroundEntity::BackgroundEntity( SDL_Surface* pSurface, int x,int y,int startx, int endx,int speed )
{
	this->pSurface = pSurface;
	this->x = x;
	this->y = y;
	this->startx=startx;
	this->endx=endx;
	this->speed = speed;
}
