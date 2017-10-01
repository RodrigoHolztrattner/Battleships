////////////////////////////////////////////////////////////////////////////////
// Filename: FLight.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FLight_H_
#define _FLight_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\Containers\Array\TArray.h"
#include "..\IRenderable.h"
#include "..\..\Resource\Texture\FTexture.h"

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FLight
////////////////////////////////////////////////////////////////////////////////
class FLight : public IRenderable
{
private:

	// Actor is a friend class
	friend FActor;

public:
	FLight(FActor* _owner, FShaderBase* _shader);
	FLight(const FLight&);
	~FLight();

	// Release this light
	void Release();

	// Set the light texture
	void SetTexture(FTexture* _texture);

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

	// Return the current texture for this light
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

protected:

	// Update the light
	void Update(float _time);

private:

	// The alpha value
	float m_Alpha;

	// The color
	WVector3 m_Color;

	// The light texture
	FTexture* m_Texture;
};

#endif
