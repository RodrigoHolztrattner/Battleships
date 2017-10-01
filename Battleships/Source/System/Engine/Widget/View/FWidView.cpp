///////////////////////////////////////////////////////////////////////////////
// Filename: FWidView.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FWidView.h"
#include "..\..\..\..\Core\Widget\FWidgetInput.h"
#include "..\..\..\..\Core\Video\FShaderBase.h"
#include "FWidViewShader.h"

FWidView::FWidView()
{
	// Set the shader
	SetShader(FShaderBase::GetShader<FWidViewShader>());
}

FWidView::FWidView(const FWidView& other)
{
}

FWidView::~FWidView()
{
}

void FWidView::Update(float _time, WVector2 _mousePosition)
{

}

bool FWidView::Input(WidgetMessageType _input)
{
	// Do nothing
	return false;
}