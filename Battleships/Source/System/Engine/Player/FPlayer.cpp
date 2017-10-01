///////////////////////////////////////////////////////////////////////////////
// Filename: FPlayer.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FPlayer.h"
#include "..\..\..\Core\Input\FInput.h"

#include <iostream>
#include "string"

#include "..\..\..\Core\Camera\FCamera.h"

#include "..\..\..\Core\Renderable\Flipbook\FFlipbook.h"
#include "..\..\..\Core\Video\FShaderBase.h"
#include "..\..\..\Core\Renderable\Flipbook\FFlipbookShader.h"

#include "..\..\..\Core\Environment\Water\FWaterShader.h"

#include "..\Widget\View\FWidView.h"

#include "..\Light\FPointLight.h"

#include "..\..\Objects\Prop\FLighthouse.h"

#include "..\..\Objects\Prop\FNuncio.h"

#include "..\..\..\Core\Entity\Actor\FActorController.h"

FPlayer::FPlayer()
{
}

FPlayer::FPlayer(const FPlayer& other)
{
}

FPlayer::~FPlayer()
{
}

FWidView* speedMeterPointer;

bool FPlayer::Initialize(FGraphic* _graphicContext)
{
	// Create the camera object
	m_Camera = new FCamera;

	// Set the camera viewport size
	m_Camera->SetViewportSize(_graphicContext->GetWindowResolution());

	// Build the ortho matrix
	m_Camera->CreateOrthoMatrix();

	// Create the water shader
	FShaderBase* waterShader = FShaderBase::GetShader<FWaterShader>();

	// Create a ship just to test
	m_Ship = FNormalShip::Create<FNormalShip>();

	// m_Ship->LoadSprite("dummy");
	m_Ship->SetSize(WVector3(128, 128, 1));
	m_Ship->SetLocation(WVector2(200, 200));

	//
	//
	//

	FLighthouse* lighthouse = FLighthouse::Create<FLighthouse>();
	lighthouse->SetSize(WVector3(128, 128, 1));
	lighthouse->SetLocation(WVector2(100, 100));

	FNuncio* nuncio = FNuncio::Create<FNuncio>();
	nuncio->SetSize(WVector3(768, 768, 1));
	nuncio->SetLocation(WVector2(-300, 500));

	
	
	//
	//
	//

	// Speed meter base
	FWidView* speedMeterBase = IWidget::Create<FWidView>();
	speedMeterBase->SetLayout(IWidget::LayoutLocationHeight::Top, IWidget::LayoutLocationWidth::Left, IWidget::LayoutSize::Absolute);
	speedMeterBase->SetSize(WVector2(128, 128));
	speedMeterBase->Texture(IResource::GetResourceByName<FTexture>(FHashedString("speedmeterbase.tga")));

	// Speed meter pointer
	speedMeterPointer = IWidget::Create<FWidView>(speedMeterBase);
	speedMeterPointer->SetLayout(IWidget::LayoutLocationHeight::Proportional, IWidget::LayoutLocationWidth::Proportional, IWidget::LayoutSize::Proportional);
	speedMeterPointer->SetPosition(WVector2(0, 0));
	speedMeterPointer->SetSize(WVector2(1.0, 0.89));
	speedMeterPointer->Texture(IResource::GetResourceByName<FTexture>(FHashedString("speedmeterpointer.tga")));

	// Speed meter layer
	FWidView* speedMeterLayer = IWidget::Create<FWidView>();
	speedMeterLayer->SetLayout(IWidget::LayoutLocationHeight::Top, IWidget::LayoutLocationWidth::Left, IWidget::LayoutSize::Absolute);
	speedMeterLayer->SetSize(WVector2(128, 128));
	speedMeterLayer->Texture(IResource::GetResourceByName<FTexture>(FHashedString("speedmeterlayer.tga")));

	// Fuel indicator
	FWidView* fuelIndicator = IWidget::Create<FWidView>();
	fuelIndicator->SetLayout(IWidget::LayoutLocationHeight::Top, IWidget::LayoutLocationWidth::Left, IWidget::LayoutSize::Absolute, WVector2(138, 10));
	fuelIndicator->SetSize(WVector2(64, 64));
	fuelIndicator->Texture(IResource::GetResourceByName<FTexture>(FHashedString("fuelindicator.tga")));

	// Fuel flame
	FWidView* fuelFlame = IWidget::Create<FWidView>(fuelIndicator);
	fuelFlame->SetLayout(IWidget::LayoutLocationHeight::Proportional, IWidget::LayoutLocationWidth::Proportional, IWidget::LayoutSize::Absolute);
	fuelFlame->SetPosition(WVector2(0.2, 0.16));
	fuelFlame->SetSize(WVector2(32, 32));
	fuelFlame->Texture(IResource::GetResourceByName<FTexture>(FHashedString("fuelflame.tga")));

	//
	//
	//

	// Deferred view
	FWidView* deferredView = IWidget::Create<FWidView>();
	deferredView->SetLayout(IWidget::LayoutLocationHeight::Top, IWidget::LayoutLocationWidth::Right, IWidget::LayoutSize::Proportional);
	deferredView->SetSize(WVector2(0.125, 0.125));

	// Create the deferred texture
	FTexture* deferredTexture = new FTexture;
	deferredTexture->SetHandleWithoutLoading(_graphicContext->GetDeferredTexture());
	deferredView->Texture(deferredTexture);

	return true;
}

void FPlayer::Update(float _time)
{
	static float speedMeterTarget = 0.0;
	static int shipAccelerationFactor = 0;

	// Set the camera position
	m_Camera->SetLocation(WVector2::PolarCoordinateWithOffset(m_Ship->GetLocation(), m_Ship->GetRotation().z, m_Ship->GetAcceleration() / 2));
//	m_Camera->SetLocation(m_Ship->GetLocation());
	
	// Update the camera
	m_Camera->Update();

	// Get all input messages
	FInput::Iterator iterator;

	// For each input message
	for (iterator.Begin(); iterator.End(); iterator.Next())
	{
		// Get the current input message
		InputMessage currentMessage = iterator();

		/*
		
			=> TEST ONLY
		
		*/

		// Check if the input is a keyboard message and the action == press
		if (currentMessage.type == InputTypes::Keyboard)
		{
			// Switch the button
			switch (currentMessage.button)
			{
				#define MoveTotal 50

				// Top
				case 265:
				{
					if (currentMessage.actionID != 0)
					{
						m_Ship->ChanceAcceleration(MoveTotal, 100);

						if (shipAccelerationFactor < 2)
							shipAccelerationFactor++;
					}

					break;
				}

				// Right
				case 262:
				{
					if (currentMessage.actionID != 0)
					{
						m_Ship->ChangeTurnDirection(60);
					}
					else
					{
						m_Ship->ChangeTurnDirection(0);
					}

					break;
				}

				// Bottom
				case 264:
				{
					if (currentMessage.actionID != 0)
					{
						m_Ship->ChanceAcceleration(-MoveTotal, 100);

						if (shipAccelerationFactor > -2)
							shipAccelerationFactor--;
					}

					break;
				}

				// Left
				case 263:
				{
					if (currentMessage.actionID != 0)
					{
						m_Ship->ChangeTurnDirection(-60);
					}
					else
					{
						m_Ship->ChangeTurnDirection(0);
					}

					break;
				}

				// L
				case 76:
				{
					if (currentMessage.actionID != 0)
					m_Ship->Light();

					break;
				}

				// Esc
				case 256:
				{
					exit(0);

					break;
				}
			}
		}
	}

	// Clear all input messages
	FInput::ClearInputMessages();

	/////////////////////////
	// SPEED METER POINTER //
	/////////////////////////
	
	// Set the speed meter target
	speedMeterTarget = shipAccelerationFactor * 38;

	// Check if we need to change the angle
	if (abs(speedMeterPointer->GetRotation() - speedMeterTarget) > 0.1)
	{
		speedMeterPointer->SetRotation(speedMeterPointer->GetRotation() + (speedMeterTarget - speedMeterPointer->GetRotation()) * _time * 10.0f);
	}
}