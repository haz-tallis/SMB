#include "Texture2D.h"
#include "constants.h"
#include <SDL_image.h>
#include <iostream>
using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	
	mWidth;
	mHeight;
}

Texture2D::~Texture2D()
{
	//Free up the memory.
	Free();

	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(string path)
{
	//Remove the memory used for a previous texture.
	Free();

	
	//Load the image.
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		//Colour key the image - The colour to be transparent.
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
		
		//Create the texture from the pixels on the surface.
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		else
		{
			//Set the dimensions.
			mWidth = pSurface->w;
			mHeight = pSurface->h;
		}

		//Remove the loaded surface now tha twe have the texture.
		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError() << endl;
	}
	//Return the texture. Return whether the process was successful.
	return mTexture != NULL;
}

void Texture2D::Free()
{
	//Check if the texture exists before removing it.
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	
	//Set where to render the texture.
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };

	//Render to screen.
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);

}