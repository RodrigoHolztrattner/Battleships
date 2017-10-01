////////////////////////////////////////////////////////////////////////////////
// Filename: FWidView.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FWidView_H_
#define _FWidView_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\..\..\Core\Widget\IWidget.h"

/////////////
// DEFINES //
/////////////

// We know the texture class
class FTexture;

////////////////////////////////////////////////////////////////////////////////
// Class name: FWidView
////////////////////////////////////////////////////////////////////////////////
class FWidView : public IWidget
{
private:

public:

	// The update and render virtual functions
	virtual void Update(float _time, WVector2 _mousePosition);

	// The input method
	virtual bool Input(WidgetMessageType _input);

	// Set the view texture
	virtual void Texture(FTexture* _texture)
	{
		m_Texture = _texture;
	}

	// Return the texture
	virtual FTexture* Texture()
	{
		return m_Texture;
	}

protected:

	// Widget is a friend class (so we can access the constructor and destructor)
	friend IWidget;

	// The constructor and destructor are protected because we can only create or delete objects using the Create() or Release() functions
	FWidView();
	~FWidView();

	// Copy constructor is private because we cant share directly data (only ptrs)
	FWidView(const FWidView&);

private:

	// The texture
	FTexture* m_Texture;

};

#endif
