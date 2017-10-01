////////////////////////////////////////////////////////////////////////////////
// Filename: FIFloat.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FIFloat_H_
#define _FIFloat_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\IShaderIntrinsicVariable.h"

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FIFloat
////////////////////////////////////////////////////////////////////////////////
class FIFloat : public IShaderIntrinsicVariable
{
protected:

public:
	FIFloat();
	FIFloat(const FIFloat&);
	~FIFloat();

	////////////////
	// ASSIGNMENT //
	////////////////

	// String on assignment
	FIFloat& operator=(float arg);
	FIFloat& operator=(FIFloat arg);

	// String on add
	FIFloat operator+(const float& arg);
	FIFloat operator+(const FIFloat& arg);

	// String on add + assignment
	FIFloat operator+=(const float& arg);
	FIFloat operator+=(const FIFloat& arg);

	// String on subtraction
	FIFloat operator-(const float& arg);
	FIFloat operator-(const FIFloat& arg);

	// String on subtraction + assignment
	FIFloat operator-=(const float& arg);
	FIFloat operator-=(const FIFloat& arg);

	// String on multiplication
	FIFloat operator*(const float& arg);
	FIFloat operator*(const FIFloat& arg);

	// String on multiplication + assignment
	FIFloat operator*=(const float& arg);
	FIFloat operator*=(const FIFloat& arg);

	// String on division
	FIFloat operator/(const float& arg);
	FIFloat operator/(const FIFloat& arg);

	// String on division + assignment
	FIFloat operator/=(const float& arg);
	FIFloat operator/=(const FIFloat& arg);

	//////////////////
	// COMPARISSION //
	//////////////////

	bool operator< (const float& arg);
	bool operator> (const float& arg);
	bool operator<=(const float& arg);
	bool operator>=(const float& arg);

	bool operator< (const FIFloat& arg);
	bool operator> (const FIFloat& arg);
	bool operator<=(const FIFloat& arg);
	bool operator>=(const FIFloat& arg);

protected:

	// String on creation
	void CreationString();
};

#endif
