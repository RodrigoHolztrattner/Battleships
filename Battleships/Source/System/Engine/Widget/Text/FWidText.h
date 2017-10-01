////////////////////////////////////////////////////////////////////////////////
// Filename: FWidText.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FWidText_H_
#define _FWidText_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\..\..\Core\Widget\IWidget.h"
#include "..\..\..\..\Core\Font\FFontLoader.h"

/////////////
// DEFINES //
/////////////
#include <stdio.h>

/*
template <int n>
void FormatString(const char(&str)[n], va_arg arg)                                                
{       
	char buffer[n * 2];
	sprintf(buffer, arg);
}
*/

// We know the texture class
class FTexture;

// We know the FWidView class
class FWidView;

// We know the FWidTextShader class
class FWidTextShader;

////////////////////////////////////////////////////////////////////////////////
// Class name: FWidText
////////////////////////////////////////////////////////////////////////////////
class FWidText : public IWidget
{
	// Font shader is a friend class
	friend FWidTextShader;

public:

	// The text format type
	enum class TextFormat
	{
		Left,
		Right,
		Center,
		Justify
	};

private:

	// The glyph info type
	struct GlyphInfo
	{
		GlyphInfo(){}
		GlyphInfo(WVector3 _worldLocation, WVector3 _worldSize, WVector4 _textureCoordinates, char _glyphChar, int _lineNumber)
		{
			worldLocation = _worldLocation;
			worldSize = _worldSize;
			textureCoordinates = _textureCoordinates;
			glyphChar = _glyphChar;
			lineNumber = _lineNumber;
		}

		WVector3 worldLocation;
		WVector3 worldSize;
		WVector4 textureCoordinates;
		WVector2 pad;
		char glyphChar;
		int lineNumber;
	};

public:

	/////////////////
	// FONT / TEXT //
	/////////////////

	// Set the font type (and the resolution)
	bool SetFont(FHashedString _fontName, unsigned int _fontResolution);

	// Set the text (const) and the text size
	void SetText(const char* _text, unsigned int _textSize = 32);

	// Set the text (non const (slow)) and the text size
	void SetText(char* _text, unsigned int _textSize = 32){}

	// Return the text
	std::string GetText()
	{
		return m_Text;
	}

	// Return the font face data
	FFontLoader::FontFace* GetFontFace()
	{
		return m_FontFace;
	}

	// Return the text lenght
	int TextLenght()
	{
		return m_Text.length();
	}

	///////////
	// GLYPH //
	///////////

	// Return a glyph info
	GlyphInfo GetGlyphInfo(unsigned int _glyphIndex);

	////////////
	// FORMAT //
	////////////

	// Set the text format
	void SetTextFormat(TextFormat _format);

protected:

	// The update and render virtual functions
	virtual void Update(float _time, WVector2 _mousePosition);

	// The input method
	virtual bool Input(WidgetMessageType _input);

private:

	// Widget is a friend class (so we can access the constructor and destructor)
	friend IWidget;

	// The constructor and destructor are protected because we can only create or delete objects using the Create() or Release() functions
	FWidText();
	~FWidText();

	// Copy constructor is private because we cant share directly data (only ptrs)
	FWidText(const FWidText&);

public:

	// Update the glyph info
	void UpdateGlyphInfo();

	// Update the glyph format
	void UpdateGlyphFormat();

private:

	// The font face for this font widget
	FFontLoader::FontFace* m_FontFace;

	// The text
	std::string m_Text;

	// The glyph info array
	TArray<GlyphInfo> m_GlyphInfo;

	// The text size
	unsigned int m_TextSize;

	// The text format
	TextFormat m_TextFormat;
};

#endif
