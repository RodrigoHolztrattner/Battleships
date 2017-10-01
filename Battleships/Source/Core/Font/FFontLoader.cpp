///////////////////////////////////////////////////////////////////////////////
// Filename: FFontLoader.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FFontLoader.h"

FFontLoader::FFontLoader()
{
}

FFontLoader::FFontLoader(const FFontLoader& other)
{
}

FFontLoader::~FFontLoader()
{
}

////////////
// GLOBAL //
////////////

// <GLOBAL> Declare the font library object
FT_Library FFontLoader::m_FontLibrary;

// <GLOBAL> Declare the array of loaded font faces
TArray<FFontLoader::FontFace*> FFontLoader::m_FontFaces;

bool FFontLoader::InitializeFontSystem()
{
	int error;

	// Initialize the freetype library
	error = FT_Init_FreeType(&m_FontLibrary);
	if (error)
	{
		return false;
	}

	return true;
}

FFontLoader::FontFace* FFontLoader::GetFont(FHashedString _stringName, unsigned int _fontHeight)
{
	FontFace* newFontFace;

	// Check if this font was already loaded
	for (int i = 0; i < m_FontFaces.Size(); i++)
	{
		// Compare the hash
		if (m_FontFaces[i]->stringHash == _stringName.Hash())
		{
			// Font loaded!
			return m_FontFaces[i];
		}
	}

	// If we are here, we need to load the font //

	// Create the new font face object
	newFontFace = new FontFace;

	// Create the new font face
	int error = FT_New_Face(m_FontLibrary, _stringName.String(), 0, &newFontFace->face);
	if (error == FT_Err_Unknown_File_Format)
	{
		// Unknow file format
		return nullptr;
	}
	else if (error)
	{
		// Invalid path, font does not exist or another error
		return nullptr;
	}

	// Set the font height
	FT_Set_Pixel_Sizes(newFontFace->face, 0, _fontHeight);

	// Create the font texture
	if (!CreateFontTexture(newFontFace))
	{
		return nullptr;
	}

	// Set the font face hash
	newFontFace->stringHash = _stringName.Hash();

	// Insert the new font into the font array
	m_FontFaces.Add(newFontFace);
	
	// Return the new font face
	return m_FontFaces[m_FontFaces.Size() - 1];
}

bool FFontLoader::CreateFontTexture(FontFace* _fontFace)
{
	int highestSize = 0;

	// Check each glyph and find the highest size
	for (int i = 0; i < 256; i++)
	{
		// Get the glyph data
		FT_UInt glyphindex = FT_Get_Char_Index(_fontFace->face, i);
		FT_Load_Glyph(_fontFace->face, glyphindex, FT_LOAD_RENDER);
		FT_GlyphSlot slot = _fontFace->face->glyph;
		FT_Bitmap bitmap = slot->bitmap;

		// Get the glyph width and height
		int w = bitmap.width;
		int h = bitmap.rows;

		// Check if any of them is higher
		if (w > highestSize) highestSize = w;
		if (h > highestSize) highestSize = h;
	}

	// Set the glyph max size
	_fontFace->glyphMaxSize = highestSize;

	// Set the new texture dimension
	int textureWidth = highestSize * 16;	// Ex: 256
	int textureHeight = highestSize * 16;	// Ex: 256

	// Prepare the data for the new texture
	unsigned char* textureData = new unsigned char[textureWidth * textureHeight * 4];

	// Zero the texture data
	memset(textureData, 0, sizeof(unsigned char) * textureWidth * textureHeight * 4);

	// For each glyph
	for (int i = 0; i < 256; i++)
	{
		// Get the glyph data
		FT_UInt glyphindex = FT_Get_Char_Index(_fontFace->face, i);
		FT_Load_Glyph(_fontFace->face, glyphindex, FT_LOAD_RENDER);
		FT_GlyphSlot slot = _fontFace->face->glyph;
		FT_Bitmap bitmap = slot->bitmap;

		// Get the glyph width and height
		int w = bitmap.width;
		int h = bitmap.rows;

		// Get the texture writing location
		int textureWriteWidth = (i % 16) * highestSize;
		int textureWriteHeight = (i / 16) * highestSize;

		// Set the glyph location, texture coordinate and real size
		_fontFace->glyphLocation[i].origin = WVector2(textureWriteWidth, textureWriteHeight);
		_fontFace->glyphLocation[i].textureCoordinate = WVector4((float)textureWriteWidth / textureWidth, (float)textureWriteHeight / textureHeight,
			((float)textureWriteWidth + highestSize) / textureWidth, ((float)textureWriteHeight + highestSize) / textureHeight);
		_fontFace->glyphLocation[i].realSize = WVector2(bitmap.width, bitmap.rows);
		_fontFace->glyphLocation[i].glyphMetrics = _fontFace->face->glyph->metrics;
	
		// For each botmap row
		for (int y = 0; y < bitmap.rows; y++)
		{
			// For each bitmap width
			for (int x = 0; x < bitmap.width; x++)
			{
				// Set the glyph coordinate
				WVector2 glyphCoordinate = WVector2(x, bitmap.rows - y - 1);

				// Set the texture write index
				int textureWriteIndex = ((textureWriteHeight + glyphCoordinate.y) * textureHeight) * 4 + (textureWriteWidth + glyphCoordinate.x) * 4;

				// Set the texture data
				textureData[textureWriteIndex + 0] = bitmap.buffer[x + bitmap.width * y];
				textureData[textureWriteIndex + 1] = bitmap.buffer[x + bitmap.width * y];
				textureData[textureWriteIndex + 2] = bitmap.buffer[x + bitmap.width * y];
				textureData[textureWriteIndex + 3] = 255;
			}
		}
	}

	// Generate an ID for the texture.
	glGenTextures(1, &_fontFace->texture);

	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, _fontFace->texture);

	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, textureData);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, textureData);

	// Set the texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Generate mipmaps for the texture.
	glGenerateMipmap(GL_TEXTURE_2D);

	// Delete the temporary texture data
	delete[] textureData;

	return true;
}