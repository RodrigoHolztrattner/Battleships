///////////////////////////////////////////////////////////////////////////////
// Filename: FSprite.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FSprite.h"
#include "..\Video\FShaderManager.h"
#include "FSpriteShader.h"

FSprite::FSprite()
{
	// Register this sprite
	RegisterSprite(this);

	// Set all ptrs to null
	m_TextureArray = nullptr;

	// Set the initial data
	m_bIsLoaded = false;
	m_CurrentAnimationTime = 0;
	m_Size = WVector2(1, 1);
	m_Rotation = 0;
}

FSprite::FSprite(const FSprite& other)
{
}

FSprite::~FSprite()
{
}

bool FSprite::Load()
{
	bool result;

	// Use mutexes here //

	return true;
}

void FSprite::Update(float _time)
{
	// Increment the current animation time
	m_CurrentAnimationTime += _time;

	// Check if the time overlap the maximum
	if (m_CurrentAnimationTime >= m_SpriteData.animationTime)
	{
		m_CurrentAnimationTime -= m_SpriteData.animationTime;
	}
}

void FSprite::Render()
{
	// Send this sprite to the sprite shader
	(FShaderManager::GetShaderManagerReference()->GetShader<FSpriteShader>())->AddObject(this);
}

void FSprite::Release()
{
	// Use mutexes here //

	// Set the is loaded variable to false to make sure no other object will try to use this data
	m_bIsLoaded = false;

	// Unload the texture data
	// ...
}

FTexture* FSprite::GetCurrentTexture()
{
	// Calculate the current texture
	unsigned int currentTexture = (m_CurrentAnimationTime / m_SpriteData.animationTime) * m_SpriteData.numberOfTextures;

	return &m_TextureArray[currentTexture];
}

////////////
// GLOBAL //
////////////

// <GLOBAL> The global sprite array
static TArray<FSprite*> s_SpriteArray;

void FSprite::RegisterSprite(FSprite* _sprite)
{
	s_SpriteArray.Add(_sprite);
}

void FSprite::UpdateSprites(float _time)
{
	// For each sprite inside the global sprite array
	for (int i = 0; i < s_SpriteArray.Size(); i++)
	{
		// Update this sprite
		s_SpriteArray[i]->Update(_time);
	}
}

void FSprite::RenderSprites()
{
	// For each sprite inside the global sprite array
	for (int i = 0; i < s_SpriteArray.Size(); i++)
	{
		// Check if this sprite should be rendered
		// ...

		// Render this sprite
		s_SpriteArray[i]->Render();
	}
}