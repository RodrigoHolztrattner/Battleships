////////////////////////////////////////////////////////////////////////////////
// Filename: FSmoke.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FSmoke_H_
#define _FSmoke_H_

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
// Class name: FSmoke
////////////////////////////////////////////////////////////////////////////////
class FSmoke : public FActor
{
private:

public:

	FSmoke();
	FSmoke(const FSmoke&);
	~FSmoke();

protected:

	// Update this ship
	void Update(float _time);

	// Set the ship flipbook
	void SetFlipbook(FFlipbook* _flipbook);

	// Return if we should keep track of this (if false, no pick or collision functions will have effect on this object)
	bool ShouldKeepTrack(){ return false; };

private:


	// Called when a renderable animation expired
	void RenderableAnimationExpired(IRenderable* _who);

};

#endif
