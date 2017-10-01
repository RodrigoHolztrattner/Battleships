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
