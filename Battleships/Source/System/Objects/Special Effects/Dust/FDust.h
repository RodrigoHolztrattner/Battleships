////////////////////////////////////////////////////////////////////////////////
// Filename: FDust.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FDust_H_
#define _FDust_H_

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
// Class name: FDust
////////////////////////////////////////////////////////////////////////////////
class FDust : public FActor
{
private:

	// The maximum and minimum expiration time
	const float MaximumExpirationTime = 1.4f;
	const float MinimumExpirationTime = 1.0f;

	// The size minimum, maximum and the grow values
	const float MaximumSize = 10.0f;
	const float MinimumSize = 20.0f;
	const float GrowSize = 20.0f;

public:

	FDust();
	FDust(const FDust&);
	~FDust();

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
