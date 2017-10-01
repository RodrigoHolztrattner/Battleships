////////////////////////////////////////////////////////////////////////////////
// Filename: FLighthouse.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FLighthouse_H_
#define _FLighthouse_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\Engine\Prop\FProp.h"

/////////////
// DEFINES //
/////////////

// We know the spotlight class
class FSpotLight;
class FPointLight;

////////////////////////////////////////////////////////////////////////////////
// Class name: FLighthouse
////////////////////////////////////////////////////////////////////////////////
class FLighthouse : public FProp
{
private:

	// Entity is a friend class
	friend IEntity;

public:

protected:

	// Constructor and destructor are private and we can only share ptrs (copy-constructor is private too)
	FLighthouse();
	FLighthouse(const FLighthouse&);
	~FLighthouse();

	// Update this prop
	virtual void Update(float _time);

private:

	// The light
	FSpotLight* m_Light;

	// The self light
	FPointLight* m_SelfLight;
};

#endif
