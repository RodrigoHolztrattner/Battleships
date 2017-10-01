////////////////////////////////////////////////////////////////////////////////
// Filename: FFlipbook.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FFlipbook_H_
#define _FFlipbook_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\Containers\Array\TArray.h"
#include "..\IRenderable.h"
#include "..\..\Resource\Texture\FTexture.h"
#include "..\..\Support\Callback\WCallback.h"

/////////////
// DEFINES //
/////////////

/*
	=> Flipbook

		- Store an animation or just a static sprite using textures
		- NOT USED BY UI RENDERING
*/

////////////////////////////////////////////////////////////////////////////////
// Class name: FFlipbook
////////////////////////////////////////////////////////////////////////////////
class FFlipbook : public IRenderable
{
private:

	// Actor is a friend class
	friend FActor;

public:
	FFlipbook(FActor* _owner, FShaderBase* _shader);
	FFlipbook(const FFlipbook&);
	~FFlipbook();

	// Release this flipbook
	void Release();

	// Add a texture to this flipbook
	void AddTexture(FTexture* _texture);

	// Change the flipbook animation time
	void SetAnimationTime(float _totalTime);

	// Set the alpha
	void SetAlpha(float _value)
	{
		m_Alpha = _value;
	}

	// Set the color
	void SetColor(WVector3 _color, float _alpha = -1)
	{
		m_Color = _color;
		if (_alpha >= 0)
		{
			m_Alpha = _alpha;
		}
	}

	// Return the current texture for this flipbook
	FTexture* Texture();

	// Return the alpha value
	float Alpha()
	{
		return m_Alpha;
	}

	// Return the color
	WVector3 Color()
	{
		return m_Color;
	}

	// Check if the given position is inside the colision region for this flipbook (if there is a collision, call the m_CollisionFunction function)
	bool VerifyPreciseCollision(WVector2 _location, bool _takeParentPosition = true);

protected:

	// Update the flipbook animation
	void Update(float _time);

private:

	// The alpha value
	float m_Alpha;

	// The color
	WVector3 m_Color;

	// The total animation time
	float m_TotalAnimationTime;
	
	// The current animation time
	float m_CurrentAnimationTime;

	// The array of textures/sprites
	TArray<FTexture*> m_Textures;
};

#endif
