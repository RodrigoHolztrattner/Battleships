////////////////////////////////////////////////////////////////////////////////
// Filename: FPointLight.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FPointLight_H_
#define _FPointLight_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\..\Core\Entity\Actor\FActor.h"

// Say that the FLight class exist
class FLight;

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FPointLight
////////////////////////////////////////////////////////////////////////////////
class FPointLight : public FActor
{
private:

	// Actor is a friend class
	friend FActor;
	friend IEntity;

public:

protected:

	// Constructor and destructor are private and we can only share ptrs (copy-constructor is private too)
	FPointLight();
	FPointLight(const FPointLight&);
	~FPointLight();

	// Update this ship
	virtual void Update(float _time);

	// Set the light
	void SetLight(FLight* _light);

protected:

	// Return if we should keep track of this (if false, no pick or collision functions will have effect on this object)
	bool ShouldKeepTrack(){ return false; };

};

#endif
