#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <string>
#include <vector>
#if Win32
#include <SDL2\SDL_surface.h>
#endif
#if __EMSCRIPTEN__
#include <SDL\SDL_surface.h>
#endif

struct BackgroundEntity
{
	BackgroundEntity(SDL_Surface* pSurface, int x,int y,int startx, int endx,int speed);
	SDL_Surface *pSurface;
	int x;
	int y;
	int endx;
	int startx;
	int speed;
};

class Background
{
public:
	Background();
	~Background();
	void Load();
	void Update();
	void Render()const;
private:
	void LoadCounds();
	void LoadDesert();
	std::vector<BackgroundEntity*> mEntities;

};

#endif