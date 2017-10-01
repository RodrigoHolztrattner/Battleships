////////////////////////////////////////////////////////////////////////////////
// Filename: FSystem.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FSystem_H_
#define _FSystem_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Core\Video\FGraphic.h"
#include "Engine\Player\FPlayer.h"

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FSystem
////////////////////////////////////////////////////////////////////////////////
class FSystem
{
private:

public:
	FSystem();
	FSystem(const FSystem&);
	~FSystem();

	// Initialize the system
	bool Initialize();

	// Start the system engine
	void StartEngine();

	// Shutdown the system
	void Shutdown();

	FSystem& operator + (FSystem other)
	{

	}

private:

	// The update main method
	void Update(float _timeElapsed);

	// The render main method
	void Render(float _timeElapsed);

private:

	// The graphic context (opengl context)
	FGraphic* m_GraphicContext;

	// The main player
	FPlayer* m_Player;
};

#endif
