#include "CharacterMario.h"
#include "Character.h"

//class CharacterMario : public Character

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition) : Character(renderer, imagePath, startPosition)
{
}

CharacterMario::~CharacterMario()
{
}
/*imagePath, map,*/
/*LevelMap map,*/
/*map,*/

//CharacterMario::CharacterMario(SDL_Renderer renderer, string iamgePath, Vector2D startPosition) : Character(renderer,  startPosition)
//{
//	
//}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	cout << "Eat my ass";
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
			cout << "MovingLeftFALSE\n";
			break;
		}
	}
}
