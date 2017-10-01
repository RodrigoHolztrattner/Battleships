////////////////////////////////////////////////////////////////////////////////
// Filename: IShaderIntrinsic.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _IShaderIntrinsic_H_
#define _IShaderIntrinsic_H_

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
// Class name: IShaderIntrinsic
////////////////////////////////////////////////////////////////////////////////
class IShaderIntrinsic
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

	// The type of intrinsic
	enum class IntrinsicType
	{
		Primitive,		// Like int, float, vec3, mat4, etc...
		Function		// Functions like abs(var), lerp(var1, var2, var3), etc...
	};

public:
	IShaderIntrinsic();
	IShaderIntrinsic(const IShaderIntrinsic&);
	~IShaderIntrinsic();

protected:

	// The intrinsic type
	IntrinsicType m_IntrinsicType;

};

#endif
