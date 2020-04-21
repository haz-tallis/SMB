#include "CharacterLuigi.h"
#include "Character.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition) : Character(renderer, imagePath, startPosition)
{
}
CharacterLuigi::~CharacterLuigi()
{
}


void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		cout << "Good here\n";
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = true;
			cout << "MovingLeftTRUE\n";
			break;

		case SDLK_RIGHT:
			mMovingRight = true;
			cout << "MovingRightTRUE\n";
			break;

		case SDLK_UP:
			//mCanJump
			if (!mJumping)
			{
				cout << "Good Jump\n";
				Jump();
			}
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = false;
			cout << "MovingLeftFALSE\n";
			break;

		case SDLK_RIGHT:
			mMovingRight = false;
			cout << "MovingRightFALSE\n";
			break;
		}
	}
}
