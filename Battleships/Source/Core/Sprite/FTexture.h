////////////////////////////////////////////////////////////////////////////////
// Filename: FTexture.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FTexture_H_
#define _FTexture_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Video\FGraphic.h"

/////////////
// DEFINES //
/////////////

//////////////
// COMMENTS //
//////////////

/*
	=> We use the .bmp format for any image.
*/

/* TO BE IMPLEMENTED */ /* TO BE IMPLEMENTED */ /* TO BE IMPLEMENTED */ /* TO BE IMPLEMENTED */ /* TO BE IMPLEMENTED */

////////////////////////////////////////////////////////////////////////////////
// Class name: FTexture
////////////////////////////////////////////////////////////////////////////////
class FTexture
{
private:

public:
	FTexture();
	FTexture(const FTexture&);
	~FTexture();

	bool Initialize();

	// Return the texture handle that we will use to render it
	IDHANDLE GetTextureHandle()
	{
		return m_TextureHandle;
	}

private:

	// The texture handle that we use to store the opengl information
	IDHANDLE m_TextureHandle;

};

#endif
