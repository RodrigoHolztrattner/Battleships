////////////////////////////////////////////////////////////////////////////////
// Filename: FPlayer.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FPlayer_H_
#define _FPlayer_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\Objects\Ship\FNormalShip.h"

// We know the camera class
class FCamera;

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FPlayer
////////////////////////////////////////////////////////////////////////////////
class FPlayer
{
private:

public:
	FPlayer();
	FPlayer(const FPlayer&);
	~FPlayer();

	// Initialize this player
	bool Initialize(FGraphic* _graphicContext);

	// Update the player data and objects (process the input messages, etc etc)
	void Update(float _time);

	// Return the player camera
	FCamera* Camera()
	{
		return m_Camera;
	}

private:

	// The player ship
	FShip* m_Ship;

	// the player camera
	FCamera* m_Camera;
};

#endif
