/////////////////////////////////////////////////////////////////////////////
// Name:        cVariableModel.cpp
// Purpose:     
// Author:      Richard W. Allen
// Modified by: 
// Created:     14/07/2018 21:38:08
// RCS-ID:      
// Copyright:   (C) 2017 Richard W. Allen
// Licence:     GPL 2
/////////////////////////////////////////////////////////////////////////////
#include "cVariableModel.hpp"

using Model::cVariableModel;

cVariableModel::cVariableModel()
	: m_static(false), m_const(false), m_signed(eSigned::sNONE), m_varType(eVarType::CHAR), m_pointer(ePointer::pNONE),
	m_name(""), m_value(""), m_getters(false), m_setters(false)
{}

cVariableModel::cVariableModel(cVariableModel& copy)
{
	Copy(copy);
}

cVariableModel::~cVariableModel()
{}

cVariableModel& cVariableModel::Copy(cVariableModel& copy, const bool deep /*= true*/)
{
	if (this != &copy)
	{
		m_const = copy.getConst();
		m_static = copy.getStatic();

		m_signed = copy.getSigned();
		m_varType = copy.getVarType();
		m_pointer = copy.getPointer();

		m_name = copy.getName();
		m_value = copy.getValue();

		m_getters = copy.getGetters();
		m_setters = copy.getSetters();
	}
	return *this;
}

const std::string cVariableModel::StringBuild() const
{
	std::string rtn = "";
	if (m_static == true)
		rtn += "static ";
	if (m_const == true)
		rtn += "const ";

	switch (m_varType)
	{
	case (cVariableModel::eVarType::BOOL):
		rtn += "bool";
		break;
	case (cVariableModel::eVarType::CHAR):
		rtn += "char";
		break;
	case (cVariableModel::eVarType::DOUBLE):
		rtn += "double";
		break;
	case (cVariableModel::eVarType::FLOAT):
		rtn += "float";
		break;
	case (cVariableModel::eVarType::INT):
		rtn += "int";
		break;
	case (cVariableModel::eVarType::LONG):
		rtn += "long";
		break;
	case (cVariableModel::eVarType::LONG_DOUBLE):
		rtn += "long double";
		break;
	case (cVariableModel::eVarType::LONG_LONG):
		rtn += "long long";
		break;
	case (cVariableModel::eVarType::SHORT):
		rtn += "short";
		break;
	case (cVariableModel::eVarType::vVOID):
		rtn += "void";
		break;
	case (cVariableModel::eVarType::AUTO):
		rtn += "auto";
		break;
	}

	switch (m_pointer)
	{
	case (cVariableModel::ePointer::pNONE):
		rtn += " ";
		break;
	case (cVariableModel::ePointer::POINTER):
		rtn += "* ";
		break;
	case (cVariableModel::ePointer::REFERENCE):
		rtn += "& ";
		break;
	}

	rtn += m_name;
	rtn += " = ";
	rtn += m_value;

	return rtn;
}

/// Getters
const bool cVariableModel::getConst() const
{
	return m_const;
}

const bool cVariableModel::getStatic() const
{
	return m_static;
}

const cVariableModel::eSigned cVariableModel::getSigned() const
{
	return m_signed;
}

const cVariableModel::eVarType cVariableModel::getVarType() const
{
	return m_varType;
}

const cVariableModel::ePointer cVariableModel::getPointer() const
{
	return m_pointer;
}

const std::string& cVariableModel::getName() const
{
	return m_name;
}

const std::string& cVariableModel::getValue() const
{
	return m_value;
}

const bool cVariableModel::getGetters() const
{
	return m_getters;
}

const bool cVariableModel::getSetters() const
{
	return m_setters;
}

/// Setters
void cVariableModel::setConst(const bool constVar)
{
	m_const = constVar;
}

void cVariableModel::setStatic(const bool staticVar)
{
	m_static = staticVar;
}

void cVariableModel::setSigned(const eSigned signedVar)
{
	m_signed = signedVar;
}

void cVariableModel::setVarType(const eVarType varType)
{
	m_varType = varType;
}

void cVariableModel::setPointer(const ePointer pointerVar)
{
	m_pointer = pointerVar;
}

void cVariableModel::setName(const std::string& name)
{
	m_name = name;
}

void cVariableModel::setValue(const std::string& value)
{
	m_value = value;
}

void cVariableModel::setGetters(const bool getters)
{
	m_getters = getters;
}

void cVariableModel::setSetters(const bool setters)
{
	m_setters = setters;
}

/// operators
bool cVariableModel::operator == (const cVariableModel& rhs) const
{
	return (m_name == rhs.getName());
}

cVariableModel& cVariableModel::operator=(cVariableModel& copy)
{
	return Copy(copy);
}