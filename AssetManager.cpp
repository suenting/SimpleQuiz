#include "AssetManager.h"

AssetManager::AssetManager()
{
	mButtonFrame = IMG_Load("./Assets/button.png");
	mButtonFrameShort = IMG_Load("./Assets/button_short.png");
	mButtonFrameHover = IMG_Load("./Assets/button_hover.png");
	mButtonFrameShortHover = IMG_Load("./Assets/button_short_hover.png");
	mFinishFrame = IMG_Load("./Assets/finish_frame.png");
	mX = IMG_Load("./Assets/x.png");
	mO = IMG_Load("./Assets/o.png");
	TTF_Init();
#ifdef Win32
	mFontText = TTF_OpenFont("verdana.ttf", 12);
	mFont40 = TTF_OpenFont("verdana.ttf", 40);
	mFontBoldText = TTF_OpenFont("verdana.ttf", 12);
	TTF_SetFontStyle(mFontBoldText,TTF_STYLE_BOLD);
#endif

#if EMSCRIPTEN
	mFontText = TTF_OpenFont("sans-serif", 12);
	mFontBoldText = TTF_OpenFont("sans-serif", 14);
	mFont40 = TTF_OpenFont("sans-serif", 40);
#endif
	
}

AssetManager::~AssetManager()
{
	
	SDL_FreeSurface(mButtonFrame);
	SDL_FreeSurface(mButtonFrameShort);
	SDL_FreeSurface(mButtonFrameHover);
	SDL_FreeSurface(mButtonFrameShortHover);
	SDL_FreeSurface(mX);
	SDL_FreeSurface(mO);

	for(std::map<std::string,SDL_Surface*>::iterator it = mSurfaces.begin(); it != mSurfaces.end();++it)
	{
		SDL_FreeSurface(it->second);
	}
}

void AssetManager::AddSurface( std::string key )
{
	SDL_Surface* surface = IMG_Load(("./Assets/"+key).c_str());
	mSurfaces.insert(std::pair<std::string,SDL_Surface*>(key,surface));
}

SDL_Surface* AssetManager::GetSurface( std::string key )
{
	return mSurfaces[key];
}
