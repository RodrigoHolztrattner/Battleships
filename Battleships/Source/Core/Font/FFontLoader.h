////////////////////////////////////////////////////////////////////////////////
// Filename: FFontLoader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FFontLoader_H_
#define _FFontLoader_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Containers\Array\TArray.h"
#include "..\Video\FGraphic.h"
#include "..\String\FHashedString.h"

#include <ft2build.h>
#include FT_FREETYPE_H

/////////////
// DEFINES //
/////////////

// We know the texture class
class FTexture;

////////////////////////////////////////////////////////////////////////////////
// Class name: FFontLoader
////////////////////////////////////////////////////////////////////////////////
class FFontLoader
{
public:

	// The glyph location type
	struct GlypLocation
	{
		// The glyph origin, texture coordinate, real size and the glyph metrics
		WVector2 origin;
		WVector4 textureCoordinate;
		WVector2 realSize;
		FT_Glyph_Metrics glyphMetrics;
	};

	// The font face type
	struct FontFace
	{
		// The face name hash (used for fast compare)
		size_t stringHash;

		// The font face (freetype)
		FT_Face face;

		// The glyph max size
		unsigned int glyphMaxSize;

		// The font texture
		IDHANDLE texture;

		// All glyph locations
		GlypLocation glyphLocation[256];
	};

public:

	FFontLoader();
	~FFontLoader();
	FFontLoader(const FFontLoader&);

public:

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> Initialize the font loader
	static bool InitializeFontSystem();

// private:

	// <GLOBAL> Load (or get from the loaded array) a font face object
	static FontFace* GetFont(FHashedString _stringName, unsigned int _fontHeight);

private:

	// <GLOBAL> Create the font texture
	static bool CreateFontTexture(FontFace* _fontFace);
	
private:

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> The font library object
	static FT_Library m_FontLibrary;

	// <GLOBAL> The array of loaded font faces
	static TArray<FontFace*> m_FontFaces;
};

#endif
