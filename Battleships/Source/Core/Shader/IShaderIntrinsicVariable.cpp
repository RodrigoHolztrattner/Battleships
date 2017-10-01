///////////////////////////////////////////////////////////////////////////////
// Filename: IShaderIntrinsicVariable.cpp
///////////////////////////////////////////////////////////////////////////////
#include "IShaderIntrinsicVariable.h"

IShaderIntrinsicVariable::IShaderIntrinsicVariable()
{
	// Set the intrinsic type
	m_IntrinsicType = IShaderIntrinsic::IntrinsicType::Primitive;
}

IShaderIntrinsicVariable::IShaderIntrinsicVariable(const IShaderIntrinsicVariable& other)
{
}

IShaderIntrinsicVariable::~IShaderIntrinsicVariable()
{
}