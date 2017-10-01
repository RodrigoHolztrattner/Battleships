///////////////////////////////////////////////////////////////////////////////
// Filename: FFlipbook.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FFlipbook.h"
#include "..\..\Entity\Actor\FActor.h"

FFlipbook::FFlipbook(FActor* _owner, FShaderBase* _shader) : IRenderable(_owner, _shader)
{
	// Set the initial data
	m_Alpha = 1.0f;
	m_Color = WVector3(1, 1, 1);
	m_TotalAnimationTime = 0;
	m_CurrentAnimationTime = 0;
	m_IgnoreCollision = true;
}

FFlipbook::FFlipbook(const FFlipbook& other) : IRenderable(other)
{
}

FFlipbook::~FFlipbook()
{
}

void FFlipbook::Release()
{
	// Call the base release
	IRenderable::Release();

	// Release all textures
	for (int i = 0; i < m_Textures.Size(); i++)
	{
		// Release all textures
		m_Textures[i]->Release();
	}
}

void FFlipbook::AddTexture(FTexture* _texture)
{
	// Add the new texture
	m_Textures.Add(_texture);
}

void FFlipbook::SetAnimationTime(float _totalTime)
{
	// Set the new animation time
	m_TotalAnimationTime = _totalTime;

	// Reset the current animation time
	m_CurrentAnimationTime = 0;
}

void FFlipbook::Update(float _time)
{
	// Increment the current animation time
	m_CurrentAnimationTime += _time;

	if (m_CurrentAnimationTime > m_TotalAnimationTime)
	{
		// Call the actor animation expired callback
		GetOwner()->OnRenderableAnimationExpired(this);
	}

	// Check if we dont overlap
	while(m_CurrentAnimationTime > m_TotalAnimationTime)
	{
		// Set the new current time
		m_CurrentAnimationTime -= m_TotalAnimationTime;
	}
}

FTexture* FFlipbook::Texture()
{
	// Check if we have at last one texture and the total animation time is not zero
	if (!m_Textures.Size() || !m_TotalAnimationTime)
	{
		return nullptr;
	}

	return m_Textures[(m_CurrentAnimationTime / m_TotalAnimationTime) * m_Textures.Size()];
}

bool FFlipbook::VerifyPreciseCollision(WVector2 _location, bool _takeParentPosition)
{
	// Check if we ignore collision
	if (m_IgnoreCollision)
	{
		return false;
	}

	// Check if we should consider the parent position
	if (_takeParentPosition)
	{
		// Subtract the parent position
		_location.x -= GetOwner()->GetLocation().x;
		_location.y -= GetOwner()->GetLocation().y;
	}

	// Check if the location is inside the parent area
	if (_location.x >= GetOwner()->GetSize().x || _location.y >= GetOwner()->GetSize().y)
	{
		// Does not collide
		return false;
	}

	// Get the pixel info inside the region
	WVector4 pixelInfo = Texture()->PixelInfo(WVector2(_location.x / GetOwner()->GetSize().x, _location.y / GetOwner()->GetSize().y));

	// Check if the pixel data indicate a collision
	if (pixelInfo.w > 0.05)
	{
		// There is a collision!
		return true;
	}

	// No collision
	return false;
}