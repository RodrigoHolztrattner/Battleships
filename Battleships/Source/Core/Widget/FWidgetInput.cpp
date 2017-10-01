///////////////////////////////////////////////////////////////////////////////
// Filename: FWidgetInput.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FWidgetInput.h"
#include "..\Input\FInput.h"

FWidgetInput::FWidgetInput()
{
}

FWidgetInput::FWidgetInput(const FWidgetInput& other)
{
}

FWidgetInput::~FWidgetInput()
{
}

WidgetMessageType::WidgetMessageType(InputMessage _input)
{
	// Copy the data
	inputType = _input.type;
	button = _input.button;
	actionID = _input.actionID;
	mouseX = _input.longParam;
	mouseY = _input.shortParam;
}

WidgetMessageType::WidgetMessageType(const WidgetMessageType& other)
{
	// Copy the data
	inputType = other.inputType;
	button = other.button;
	actionID = other.actionID;
	mouseX = other.mouseX;
	mouseY = other.mouseY;
}

WidgetMessageType::~WidgetMessageType()
{
}

bool FWidgetInput::Initialize()
{
	bool result;

	return true;
}

void FWidgetInput::ProcessInput(IWidget* _root)
{
	bool result;

	// Get the input iterator
	FInput::Iterator iterator;

	// For each input message
	for (iterator.Begin(); iterator.End(); iterator.Next())
	{
		// Process this input for all widgets
		result = ProcessInputHelper(_root, iterator());

		// Check if any widget used this input
		if (result)
		{
			// Remove this input
			iterator.RemoveCurrent();
		}
	}
}

bool FWidgetInput::ProcessInputHelper(IWidget* _widget, WidgetMessageType _input)
{
	bool result;

	// Check if this widget is visible
	if (!_widget->CheckFlag(IWidget::StatusFlag::Visible))
	{
		// Ignore
		return false;
	}

	// Check if this widget accept events
	if (!_widget->CheckFlag(IWidget::StatusFlag::AcceptEvents))
	{
		// Ignore
		return false;
	}

	// We need to make sure that none of the widget child use this input before consider calling the process input for it
	for (int i = 0; i < (*_widget->GetChildArray()).Size(); i++)
	{
		// Call this function for this child
		result = ProcessInputHelper((*_widget->GetChildArray())[i], _input);

		// Check if the child used the input
		if (result)
		{
			// Ok, end the iteration
			return true;
		}
	}

	// If we are here, none of the widget childs used the input, so, try to process the input for this widget
	result = _widget->Input(_input);

	// Check if the widget used the input
	if (!result)
	{
		return false;
	}

	// Ok, we need to update the triggering widget and the focus widget //
}