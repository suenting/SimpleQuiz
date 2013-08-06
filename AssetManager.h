
#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#if Win32
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif
#if __EMSCRIPTEN__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#endif

#include <map>
#include <string>

class AssetManager
{
public:
	static AssetManager& Instance()
	{
		static AssetManager instance;
		return instance;
	}
	~AssetManager();
	SDL_Surface* GetButtonFrame()const{return mButtonFrame;}
	SDL_Surface* GetButtonFrameShort()const{return mButtonFrameShort;}
	SDL_Surface* GetButtonFrameHover()const{return mButtonFrameHover;}
	SDL_Surface* GetButtonFrameShortHover()const{return mButtonFrameShortHover;}
	SDL_Surface* GetFinishFrame()const{return mFinishFrame;}
	SDL_Surface* GetX() const { return mX; }
	SDL_Surface* GetO() const { return mO; }
	TTF_Font* GetFont40()const{return mFont40;}
	TTF_Font* GetTextFont()const{return mFontText;}
	TTF_Font* GetTextFontBold()const{return mFontBoldText;}
	void AddSurface(std::string key);
	SDL_Surface* GetSurface(std::string key);
//private:
	AssetManager();
	SDL_Surface* mButtonFrame;
	SDL_Surface* mButtonFrameShort;
	SDL_Surface* mButtonFrameHover;
	SDL_Surface* mButtonFrameShortHover;
	SDL_Surface* mFinishFrame;
	SDL_Surface* mX;
	SDL_Surface* mO;
	TTF_Font *mFontText;
	TTF_Font *mFontBoldText;
	TTF_Font *mFont40;

	std::map<std::string,SDL_Surface*> mSurfaces;
	
};

#endif