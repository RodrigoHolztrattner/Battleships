////////////////////////////////////////////////////////////////////////////////
// Filename: FSprite.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FSprite_H_
#define _FSprite_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Containers\Array\TArray.h"
#include "..\Support\Math\WMath.h"
#include "FTexture.h"

/////////////
// DEFINES //
/////////////

// The sprite name size
#define SpriteNameSize	25

//////////////
// COMMENTS //
//////////////

/*
	=> Currently we will not use any sprite manager (so, the textures problably will be loaded into memory more then just one per type) (this may change
	in the future).

	=> We will not use (now) any resource loader, so, the sprite object itself and the texture shoul know how to load the data from any external file (again
	this may change in the future).

	=> Use threads to load the sprite (and set the "is loaded" variable using mutexes (in the future).

	=> TODO: We need a way to create sprite files... Think about a sprite maker (or just create programatically a function to build one using textures).
*/

/*
	=> GUI RENDERING:

		- There is a problem... We need to separate the world rendering from the UI rendering (talking about sprites), so, we will use another sprite
		type for the UI called FWidget, it will have the same goal but will work only for the GUI.

		- Sprites are going to be used ONLY by the world itself.
*/

////////////////////////////////////////////////////////////////////////////////
// Class name: FSprite
////////////////////////////////////////////////////////////////////////////////
class FSprite
{
private:

	// The structure that represents our sprite type (data)
	struct SpriteType
	{
		// The sprite name
		char spriteName[SpriteNameSize];

		// If this sprite is animated (if yes, he must habe at last 2 textures and the animation time must be different from zero)
		bool animated;

		// The animation time (not used if this sprite is not animated)
		float animationTime;

		// The number of textures for this sprite
		unsigned int numberOfTextures;
	};

public:
	FSprite();
	FSprite(const FSprite&);
	~FSprite();

	// Load this sprite
	bool Load();

	// Set this sprite to be rendered
	void Render();

	// Release this sprite
	void Release();

	// Return the current texture
	FTexture* GetCurrentTexture();

	// Set the world location for this sprite
	void SetWorldLocation(WVector2 _location)
	{
		m_WorldLocation = _location;
	}

	// Return the world location
	WVector2 GetWorldLocation()
	{
		return m_WorldLocation;
	}

	// Set the sprite size
	void SetSize(WVector2 _size)
	{
		m_Size = _size;
	}

	// Return the size
	WVector2 GetSize()
	{
		return m_Size;
	}

	// Set the sprite rotation
	void SetRotation(float _rotation)
	{
		m_Rotation = _rotation;
	}

	// Return the rotation
	float GetRotation()
	{
		return m_Rotation;
	}

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> Register the sprite inside the global sprite array
	static void RegisterSprite(FSprite* _sprite);

	// <GLOBAL> Update all sprites inside the global sprite array (this will delete any sprite marked to be deleted)
	static void UpdateSprites(float _time);

	// <GLOBAL> Try to render all sprites inside the global sprite array
	static void RenderSprites();

private:

	// Update this sprite
	void Update(float _time);

private:

	// If this sprite is loaded
	bool m_bIsLoaded;

	// The sprite data
	SpriteType m_SpriteData;

	// The texture array (only one if this sprite is not animated)
	FTexture* m_TextureArray;

	// The current animation time (this will be used to calculate the current texture too)
	float m_CurrentAnimationTime;

	// The world location, size and rotation
	WVector2 m_WorldLocation;
	WVector2 m_Size;
	float m_Rotation;
};

#endif
