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
		=> Variáveis:

			- Precisa ter uma definição de criação, tipo:

				int variável;
				int variável2 = 5;

			- Precisa ter a definição algebrica:

				int variável;
				variável = 6;
				variável += 2;
				variável = variável * 2;
				variável /= 9;

			- Precisa ter as funções de acesso interno (caso seja um vetor, matriz, etc):

				vec4 pos;
				pos.x = 6;

		=> Funções:

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
