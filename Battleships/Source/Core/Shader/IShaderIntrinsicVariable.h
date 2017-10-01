////////////////////////////////////////////////////////////////////////////////
// Filename: IShaderIntrinsicVariable.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _IShaderIntrinsicVariable_H_
#define _IShaderIntrinsicVariable_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "IShaderIntrinsic.h"

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: IShaderIntrinsicVariable
////////////////////////////////////////////////////////////////////////////////
class IShaderIntrinsicVariable : public IShaderIntrinsic
{
protected:

	/*
		=> Vari�veis:

			- Precisa ter uma defini��o de cria��o, tipo:

				int vari�vel;
				int vari�vel2 = 5;

			- Precisa ter a defini��o algebrica:

				int vari�vel;
				vari�vel = 6;
				vari�vel += 2;
				vari�vel = vari�vel * 2;
				vari�vel /= 9;

			- Precisa ter as fun��es de acesso interno (caso seja um vetor, matriz, etc):

				vec4 pos;
				pos.x = 6;

		=> Fun��es:

	*/


public:
	IShaderIntrinsicVariable();
	IShaderIntrinsicVariable(const IShaderIntrinsicVariable&);
	~IShaderIntrinsicVariable();

protected:

	// String on creation
	virtual void CreationString() = 0;

protected:

	// The variable name
	char m_VariableName[25];
};

#endif
