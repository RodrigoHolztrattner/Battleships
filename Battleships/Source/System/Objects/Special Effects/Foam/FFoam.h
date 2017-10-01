////////////////////////////////////////////////////////////////////////////////
// Filename: FFoam.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FFoam_H_
#define _FFoam_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\..\Core\Entity\Actor\FActor.h"

// Say that the Flipbook class exist
class FFlipbook;

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FFoam
////////////////////////////////////////////////////////////////////////////////
class FFoam : public FActor
{
private:

	// The maximum and minimum expiration time
	const float MaximumExpirationTime = 3.6f;
	const float MinimumExpirationTime = 2.9;

	// The size minimum, maximum and the grow values
	const float MaximumSize = 40.0f;
	const float MinimumSize = 40.0f;
	const float GrowSize = 30.0f;

public:

	FFoam();
	FFoam(const FFoam&);
	~FFoam();

protected:

	// Update this ship
	void Update(float _time);

	// Set the ship flipbook
	void SetFlipbook(FFlipbook* _flipbook);

	// Return if we should keep track of this (if false, no pick or collision functions will have effect on this object)
	bool ShouldKeepTrack(){ return false; };

private:

private:

	// The maximum expiration time
	float m_MaximumExpirationTime;

	// The current expiration time
	float m_CurrentExpirationTime;

	// The initial size
	WVector2 m_InitialSize;

	// The dust flipbook
	FFlipbook* m_DustFlipbook;
};

#endif
