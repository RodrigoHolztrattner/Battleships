////////////////////////////////////////////////////////////////////////////////
// Filename: FProp.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FProp_H_
#define _FProp_H_

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
// Class name: FProp
////////////////////////////////////////////////////////////////////////////////
class FProp : public FActor
{
private:

	// Actor is a friend class
	friend FActor;

public:

protected:

	// Constructor and destructor are private and we can only share ptrs (copy-constructor is private too)
	FProp();
	FProp(const FProp&);
	virtual ~FProp();

	// Set the prop flipbook
	void SetFlipbook(FFlipbook* _flipbook);

	// Return if we should keep track of this (if false, no pick or collision functions will have effect on this object)
	bool ShouldKeepTrack(){ return true; };

private:

};

#endif
