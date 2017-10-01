///////////////////////////////////////////////////////////////////////////////
// Filename: FSystem.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FSystem.h"
#include "..\Core\Sprite\FSprite.h"
#include "..\Core\Video\FShaderBase.h"
#include "..\Core\Time\FTime.h"

#include "..\Core\Entity\IEntity.h"
#include "..\Core\Renderable\IRenderable.h"
#include "..\Core\Resource\IResource.h"
#include "..\Core\Widget\IWidget.h"
#include "..\Core\Entity\Actor\FActorController.h"
#include "..\Core\Font\FFontLoader.h"

#include "Engine\Widget\Text\FWidText.h"

// The fps and frame time texts
FWidText* s_FpsText;
FWidText* s_FrameTime;

FSystem::FSystem()
{
	// Initialize with nullptr the ptr variables
	m_GraphicContext = nullptr;
	m_Player = nullptr;
}

FSystem::FSystem(const FSystem& other)
{
}

FSystem::~FSystem()
{
}

bool FSystem::Initialize()
{
	bool bResult;

	// Create the opengl context
	m_GraphicContext = new FGraphic;
	if (!m_GraphicContext)
	{
		// Error
		return false;
	}

	// Initialize the opengl context and create the main window
	bResult = m_GraphicContext->Initialize(WVector2(1600, 900), false);
	if (!bResult)
	{
		// Error
		return false;
	}

	// Initialize the resource system
	bResult = IResource::InitializeResourceSystem("teste");
	if (!bResult)
	{
		return false;
	}

	// Initialize the font loader system
	bResult = FFontLoader::InitializeFontSystem();
	if (!bResult)
	{
		return false;
	}

	// Initialize the widget system
	bResult = IWidget::InitializeWidgetSystem(m_GraphicContext);
	if (!bResult)
	{
		return false;
	}
	
	// Create the main player
	m_Player = new FPlayer;
	if (!m_Player)
	{
		return false;
	}

	// Initialize the player
	bResult = m_Player->Initialize(m_GraphicContext);
	if (!bResult)
	{
		return false;
	}

	/* From here we are free to call any opengl function without referencing the graphic context */

	// Reset the time
	FTime::GetTimeElapsed(true);

	//
	//
	//

	// Fps text
	s_FpsText = IWidget::Create<FWidText>();
	s_FpsText->SetLayout(IWidget::LayoutLocationHeight::Bottom, IWidget::LayoutLocationWidth::Left, IWidget::LayoutSize::Absolute, WVector2(0, 64));
	s_FpsText->SetSize(WVector2(512, 64));
	s_FpsText->SetFont(FHashedString("arial.ttf"), 32);
	s_FpsText->SetTextFormat(FWidText::TextFormat::Left);

	// Frame time text
	s_FrameTime = IWidget::Create<FWidText>();
	s_FrameTime->SetLayout(IWidget::LayoutLocationHeight::Bottom, IWidget::LayoutLocationWidth::Left, IWidget::LayoutSize::Absolute, WVector2(0, 32));
	s_FrameTime->SetSize(WVector2(512, 64));
	s_FrameTime->SetFont(FHashedString("arial.ttf"), 32);
	s_FrameTime->SetTextFormat(FWidText::TextFormat::Left);

	//
	//
	//
	
	return true;
}

void FSystem::StartEngine()
{
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(m_GraphicContext->GetWindowReference()))
	{
		// Get the time elapsed
		float elapsedTime = FTime::GetTimeElapsed();

		// Run the main update function
		Update(elapsedTime);

		// Run the main render function
		Render(elapsedTime);

		/* Swap front and back buffers */
		glfwSwapBuffers(m_GraphicContext->GetWindowReference());

		/* Poll for and process events */
		glfwPollEvents();
	}
}

void FSystem::Shutdown()
{

}

/*
	=> Function to clear the console
*/
#include <Windows.h>
void ClearConsole() 
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	SetConsoleCursorPosition(console, topLeft);
}

void FSystem::Update(float _timeElapsed)
{
	static float logTime = 0;
	static int frameCount = 0;

	// Update entities, renderables and resources
	IEntity::UpdateEntities(_timeElapsed);
	IRenderable::UpdateRenderables(_timeElapsed);
	IResource::UpdateResourceSystem(_timeElapsed);
	IWidget::UpdateWidgets(_timeElapsed);

	// Update the main player
	m_Player->Update(_timeElapsed);

	/////////
	// LOG //
	/////////

	// Increment the log time
	logTime += _timeElapsed;

	// Increment the log count
	frameCount++;

	// Check if we should print the log data
	if (logTime >= 1)
	{
		// Clear the console (this operation is NOT slow ANYMORE)
		ClearConsole();

		// Print the initial text
		std::cout << "////////////////////////////////////////////////////////////////////////////////";
		std::cout << "//                                                                            //";
		std::cout << "// | Console log |                                                            //";
		std::cout << "//                                                                            //";
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << std::endl;

		// Print the number of objects
		LEntityLog::PrintNumberEntities();
		LRenderableLog::PrintNumberRenderables();
		LResourceLog::PrintNumberResources();

		// Jump a line
		std::cout << std::endl;

		// Print the fps and the frame time
		std::cout << "FPS: " << frameCount << std::endl;
		std::cout << "Frame time: " << 1.0 / frameCount << std::endl;
		s_FpsText->SetText("FPS: 1414", 32);
		s_FrameTime->SetText("Frame time: 0.00068736", 32);

		unsigned int actorCounter;
		FActor** pickedActors = FActorController::PickAllActorsInRange<FNormalShip>(WVector2(0, 0), 300, actorCounter);
		std::cout << "Total picked actors: " << actorCounter << std::endl;

		// Print a separator
		std::cout << std::endl << "////////////////////////////////////////////////////////////////////////////////" << std::endl;

		// Zero the log time and the frame count
		logTime = 0;
		frameCount = 0;
	}
}

void FSystem::Render(float _timeElapsed)
{
	///////////////////////
	// OBJECT RENDER SET //
	///////////////////////

	// Render all objects inside the engine
	IRenderable::RenderRenderables();

	// Render the UI
	IWidget::RenderWidgets();

	////////////////////////
	// DEFERRED RENDERING //
	////////////////////////

	// Bind the deferred framebuffer
	m_GraphicContext->BindDeferredFramebuffer();

	// Set the color to clear the screen and clear it
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render all non deferred objects inside all shaders
	FShaderBase::RenderDeferredShaders(_timeElapsed, m_Player->Camera(), m_GraphicContext);

	//////////////////////
	// NORMAL RENDERING //
	//////////////////////
	
	// Unbind the deferred framebuffer
	m_GraphicContext->UnbindDeferredFramebuffer();

	// Set the color to clear the screen and clear it
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render all non deferred objects inside all shaders
	FShaderBase::RenderShaders(_timeElapsed, m_Player->Camera(), m_GraphicContext);
}