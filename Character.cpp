#include "Character.h"
#include "Texture2D.h"
#include "constants.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
}

Character::~Character()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
}

void Character::Render()
{
	mTexture->Render(GetPosition(), SDL_FLIP_NONE);

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);
		//cout << "FacingRight";
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
		//cout << "FacingLeft";
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	//Deal with Jumping first.
	if (mJumping)
	{
		//Adjust the position.
		mPosition.y -= mJumpForce + deltaTime;

		//Reduce the jump force.
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		//Has the jump force reduced to zero?
		if (mJumpForce <= 0.0f)
			mJumping = false;
	}

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
		cout << "MoveLeftExecuted\n";
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
		cout << "MoveRightExecuted\n";
	}

	/*switch (e.type)
	{

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = true;
			cout << "MovingLeftTrue\n";
			break;
		case SDLK_RIGHT:
			mMovingRight = true;
			cout << "MovingRightTrue\n";
			break;

		case SDLK_UP:
			if (!mJumping)
			{
				cout << "Jumped";
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
			cout << "MovingLeftFalse\n";
			break;
		case SDLK_RIGHT:
			mMovingRight = false;
			cout << "MovingRightFalse\n";
			break;
		}
	}*/
	AddGravity(deltaTime);
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

void Character::MoveLeft(float deltaTime)
{
	mPosition.x -= MOVEMENTSPEED;
	mFacingDirection = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{
	mPosition.x += MOVEMENTSPEED;
	mFacingDirection = FACING_RIGHT;
}

void Character::AddGravity(float deltaTime)
{
	if (mPosition.y <= 350)
	{
		mPosition.y += GRAVITY * deltaTime;
		mCanJump = false;
	}
}

void Character::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}