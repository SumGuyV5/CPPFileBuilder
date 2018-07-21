/////////////////////////////////////////////////////////////////////////////
// Name:        cHeaderBuilder.cpp
// Purpose:     
// Author:      Richard W. Allen
// Modified by: 
// Created:     14/07/2018 21:38:08
// RCS-ID:      
// Copyright:   (C) 2017 Richard W. Allen
// Licence:     GPL 2
/////////////////////////////////////////////////////////////////////////////
#include "cHeaderBuilder.hpp"

using Builders::cBaseBuilder;
using Builders::cHeaderBuilder;

using std::endl;

cHeaderBuilder::cHeaderBuilder(const std::string& class_name, const std::string& name_space, const bool singleton /*= false*/)
	: cBaseBuilder(class_name, name_space, singleton), m_inheritanceStr("")
{
	m_file_name += ".hpp";

	m_file.open(m_file_name);
}

cHeaderBuilder::~cHeaderBuilder()
{
	m_file.close();
}

void cHeaderBuilder::Build(const std::string& inheritance /*= ""*/)
{
	if (inheritance.empty() == false)
		ClassInheritance(inheritance);
	PreprocessorBuild();
}

void cHeaderBuilder::ClassInheritance(const std::string& classname, const std::string& nameSpace /*= ""*/)
{
	if (m_inheritanceStr.empty() == true)
		m_inheritanceStr += " :";
	if (m_inheritanceStr.length() > 2) // if the string is greater then 2 char wee need to ad a comma for each addition class we inherited
		m_inheritanceStr += ",";

	m_inheritanceStr += " public ";

	if ((nameSpace.empty() == false) && (nameSpace != m_name_space))
		m_inheritanceStr += nameSpace + "::";

	IncludeFiles(classname);

	m_inheritanceStr += classname;	
}

void cHeaderBuilder::IncludeFiles(const std::string& classname)
{
	m_includeStr += "#include \"" + classname + ".hpp\"\n";
}

/// Private
void cHeaderBuilder::PreprocessorBuild()
{
	std::string preHeader = "_" + m_class_name + "_HPP_";
	m_file << "#ifndef " << preHeader << endl;
	m_file << "#define " << preHeader << endl;

	m_file << endl;

	if (m_includeStr.empty() == false)
		m_file << m_includeStr << endl;
	
	if (m_noNameSpace == true)
		ClassBuild();
	else
		NameSpaceBuild();

	m_file << "#endif/// END IFNDEF " << preHeader << endl;
}

void cHeaderBuilder::NameSpaceBuild()
{
	m_file << "namespace " << m_name_space << " {" << endl;

	m_tabString = "\t";
	ClassBuild();

	m_file << "}/// END NAMESPACE DEFINITION " << m_name_space << endl;
}

void cHeaderBuilder::ClassBuild()
{
	std::string constructer_access = "public:";

	if (m_singleton == true) {
		constructer_access = "private:";
		m_file << m_tabString << "/* Singleton */" << endl;
	}

	m_file << m_tabString << "class " << m_class_name << m_inheritanceStr << endl;
	m_file << m_tabString << "{" << endl;
	m_file << m_tabString << constructer_access << endl;
	m_file << m_tabString << "\t" << m_class_name << "(); /// default constructor" << endl;
	m_file << m_tabString << "\t~" << m_class_name << "();" << endl;

	FunctionsBuild();

	VariablesBuild();	

	m_file << m_tabString << "};/// END CLASS DEFINITION " << m_class_name << endl;
}

void cHeaderBuilder::PublicFunctions()
{
	m_file << m_tabString << "public:" << endl;
	m_file << m_tabString << "\t" << "/// Functions" << endl;
}

void cHeaderBuilder::PrivateVariables()
{
	m_file << m_tabString << "private:" << endl;
	m_file << m_tabString << "\t" << "/// Variables" << endl;
}

void cHeaderBuilder::FunctionsBuild()
{
	m_file << endl;
	PublicFunctions();
	
	SingletonBuild();

	GettersBuild();

	SettersBuild();
	
}

void cHeaderBuilder::FunctionBuild()
{

}

void cHeaderBuilder::SingletonBuild()
{
	if (m_singleton == true) {
		m_file << m_tabString << "\t" << "static " << m_class_name << "& Inst();" << endl;
		m_file << m_tabString << "\t" << "static void Delete();" << endl;
	}
}

void cHeaderBuilder::GettersBuild()
{
	if (m_variables.size() > 0) {
		m_file << m_tabString << "\t" << "/// Getters" << endl;
		std::vector<Model::cVariableModel*>::iterator it;

		for (it = m_variables.begin(); it < m_variables.end(); it++) {
			if ((*it)->getGetters() == true)
				m_file << StringBuild((*it), eStringType::GETTER) << endl;
		}
		m_file << endl;
	}	
}

void cHeaderBuilder::SettersBuild()
{
	if (m_variables.size() > 0) {
		m_file << m_tabString << "\t" << "/// Setters" << endl;
		std::vector<Model::cVariableModel*>::iterator it;

		for (it = m_variables.begin(); it < m_variables.end(); it++) {
			if ((*it)->getSetters() == true)
				m_file << StringBuild((*it), eStringType::SETTER) << endl;
		}
		m_file << endl;
	}
}

void cHeaderBuilder::VariablesBuild()
{
	m_file << endl;
	PrivateVariables();
	if (m_singleton == true) {
		m_file << m_tabString << "\t" << "static " << m_class_name << "* sp_inst; /// = nullptr" << endl;
	}

	if (m_variables.size() > 0) {
		std::vector<Model::cVariableModel*>::iterator it;

		for (it = m_variables.begin(); it < m_variables.end(); it++) {
			VariableBuild(*it);
		}
	}
}

void cHeaderBuilder::VariableBuild(const Model::cVariableModel* var)
{              
	m_file << StringBuild(var, eStringType::VARIABLE) << endl;
}

const std::string cHeaderBuilder::StringBuild(const Model::cVariableModel* var, eStringType type) const
{
	std::string rtn = "";
	std::string staticVar;
	std::string constVar;
	std::string pointerVar;
	std::string varType;
	std::string comment;

	if (var->getStatic() == true)
		staticVar = "static ";

	if (var->getConst() == true)
		constVar = "const ";

	switch (var->getVarType())
	{
	case (Model::cVariableModel::eVarType::BOOL):
		varType = "bool";
		break;
	case (Model::cVariableModel::eVarType::CHAR):
		varType = "char";
		break;
	case (Model::cVariableModel::eVarType::DOUBLE):
		varType = "double";
		break;
	case (Model::cVariableModel::eVarType::FLOAT):
		varType = "float";
		break;
	case (Model::cVariableModel::eVarType::INT):
		varType = "int";
		break;
	case (Model::cVariableModel::eVarType::LONG):
		varType = "long";
		break;
	case (Model::cVariableModel::eVarType::LONG_DOUBLE):
		varType = "long double";
		break;
	case (Model::cVariableModel::eVarType::LONG_LONG):
		varType = "long long";
		break;
	case (Model::cVariableModel::eVarType::SHORT):
		varType = "short";
		break;
	case (Model::cVariableModel::eVarType::vVOID):
		varType = "void";
		break;
	case (Model::cVariableModel::eVarType::AUTO):
		varType = "auto";
		break;
	}

	switch (var->getPointer())
	{
	case (Model::cVariableModel::ePointer::pNONE):
		pointerVar = " ";
		break;
	case (Model::cVariableModel::ePointer::POINTER):
		pointerVar = "* ";
		break;
	case (Model::cVariableModel::ePointer::REFERENCE):
		pointerVar = "& ";
		break;
	}

	comment = var->getValue();
	if (var->getVarType() == Model::cVariableModel::eVarType::CHAR)
		comment = "'" + comment + "'";

	if (comment.size() > 0)
		comment = " /// = " + comment;

	switch (type)
	{
	case (eStringType::GETTER):
		rtn = m_tabString + "\t" + staticVar + constVar + varType + pointerVar + "get" + var->getName() + "() const;";
		break;
	case (eStringType::SETTER):
		rtn = m_tabString + "\t" + staticVar + "void set" + var->getName() + "( " + varType + pointerVar + "value );";
		break;
	case (eStringType::VARIABLE):
		rtn = m_tabString + "\t" + staticVar + constVar + varType + pointerVar + var->getName() + ";" + comment;
		break;
	}

	return rtn;
}