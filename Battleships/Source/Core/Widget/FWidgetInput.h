////////////////////////////////////////////////////////////////////////////////
// Filename: FWidgetInput.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FWidgetInput_H_
#define _FWidgetInput_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "IWidget.h"

/////////////
// DEFINES //
/////////////

// We know the input message type and the input types
struct InputMessage;
enum class InputTypes;

// The message type
struct WidgetMessageType
{
	WidgetMessageType(){};
	WidgetMessageType(InputMessage _input);
	WidgetMessageType(const WidgetMessageType&);
	~WidgetMessageType();

	// The type of input (mouse, keyboard, etc)
	InputTypes inputType;

	// The button (what button for both the mouse and the keyboard)
	unsigned int button;

	// The action ID (press, release or hold)
	unsigned int actionID;

	// The mouse position (only used for mouse inputs)
	unsigned int mouseX, mouseY;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: FWidgetInput
////////////////////////////////////////////////////////////////////////////////
class FWidgetInput
{
public:

public:
	FWidgetInput();
	FWidgetInput(const FWidgetInput&);
	~FWidgetInput();

	// Initialize the widget input system
	bool Initialize();

	// Process the input for all widgets
	void ProcessInput(IWidget* _root);

private:

	// The process input helper
	bool ProcessInputHelper(IWidget* _widget, WidgetMessageType _input);

};

#endif
