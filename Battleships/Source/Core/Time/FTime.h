////////////////////////////////////////////////////////////////////////////////
// Filename: FTime.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FTime_H_
#define _FTime_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FTime
////////////////////////////////////////////////////////////////////////////////
class FTime
{
private:

public:
	FTime();
	FTime(const FTime&);
	~FTime();

	// Return the time elapsed since the last call
	static float GetTimeElapsed(bool _reset = false);

private:



};

#endif