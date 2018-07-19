#include "cSourceBuilder.hpp"

using Builders::cBaseBuilder;
using Builders::cSourceBuilder;

using std::endl;

cSourceBuilder::cSourceBuilder(const std::string& class_name, const std::string& name_space, const bool singleton /*= false*/)
	: cBaseBuilder(class_name, name_space, singleton)
{
	m_file_name += ".cpp";
	m_file.open(m_file_name);
}

cSourceBuilder::~cSourceBuilder()
{
	m_file.close();
}

void cSourceBuilder::Build()
{
	PreprocessorBuild();
	NameSpaceBuild();
	VariableBuild();
	ConstructorBuild();
	FunctionsBuild();
}

/// Private
void cSourceBuilder::PreprocessorBuild()
{
	m_file << "#include \"" << m_class_name << ".hpp\"" << endl;
	m_file << endl;
}

void cSourceBuilder::NameSpaceBuild()
{
	if (m_noNameSpace == false) {
		m_file << "using " << m_name_space << "::" << m_class_name << ";" << endl;
		m_file << endl;
	}
}

void cSourceBuilder::VariableBuild()
{
	if (m_singleton == true)
		m_file << "/*static*/ " << m_class_name << "* " << m_class_name << "::sp_inst = nullptr;" << endl << endl;

	if (m_variables.size() > 0) {
		std::vector<Model::cVariableModel*>::iterator it;

		for (it = m_variables.begin(); it < m_variables.end(); it++) {
			if (((*it)->getStatic() == true) || ((*it)->getConst() == true))
				m_file << StringBuild((*it), eStringType::VARIABLE) << endl;
		}
		m_file << endl;
	}
}

void cSourceBuilder::ConstructorBuild()
{
	m_file << m_class_name << "::" << m_class_name << "()" << endl;
	m_file << "{}" << endl;
	m_file << endl;

	m_file << m_class_name << "::~" << m_class_name << "()" << endl;
	m_file << "{}" << endl;
	m_file << endl;
}

void cSourceBuilder::FunctionsBuild()
{
	m_file << "/// Functions" << endl;
	SingletonBuild();

	GettersBuild();
	SettersBuild();
}

void cSourceBuilder::SingletonBuild()
{
	if (m_singleton == false)
		return;

	std::string static_str = "/*static*/";

	m_file << static_str << " " << m_class_name << "& " << m_class_name << "::Inst()" << endl;
	m_file << "{" << endl;
	m_file << "\t" << "if (sp_inst == nullptr)" << endl;
	m_file << "\t\t" << "sp_inst = new " << m_class_name << "();" << endl;
	m_file << "\t" << "return *sp_inst;" << endl;
	m_file << "}" << endl;

	m_file << endl;

	m_file << static_str << " void " << m_class_name << "::Delete()" << endl;
	m_file << "{" << endl;
	m_file << "\t" << "delete sp_inst;" << endl;
	m_file << "\t" << "sp_inst = nullptr;" << endl;
	m_file << "}" << endl;
}

void cSourceBuilder::GettersBuild()
{
	if (m_variables.size() > 0) {
		m_file << "/// Getters" << endl;
		std::vector<Model::cVariableModel*>::iterator it;

		for (it = m_variables.begin(); it < m_variables.end(); it++) {
			if ((*it)->getGetters() == true) {
				m_file << StringBuild((*it), eStringType::GETTER) << endl;
				m_file << "{" << endl;
				m_file << "\t" << "return " + (*it)->getName() + ";" << endl;
				m_file << "}" << endl;
				m_file << endl;
			}
		}
	}
}

void cSourceBuilder::SettersBuild()
{
	if (m_variables.size() > 0) {
		m_file << "/// Setters" << endl;
		std::vector<Model::cVariableModel*>::iterator it;

		for (it = m_variables.begin(); it < m_variables.end(); it++) {
			if ((*it)->getSetters() == true) {
				m_file << StringBuild((*it), eStringType::SETTER) << endl;
				m_file << "{" << endl;
				m_file << "\t" << (*it)->getName() << " = value;" << endl;
				m_file << "}" << endl;
				m_file << endl;
			}
		}
	}
}

const std::string cSourceBuilder::StringBuild(const Model::cVariableModel* var, eStringType type) const
{
	std::string rtn = "";
	std::string staticVar;
	std::string constVar;
	std::string pointerVar;
	std::string varType;

	if (var->getStatic() == true)
		staticVar = "/*static*/ ";

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
	
	switch (type)
	{
	case (eStringType::GETTER):
		rtn = staticVar + constVar + varType + pointerVar + m_class_name + "::get" + var->getName() + "() const";
		break;
	case (eStringType::SETTER):
		rtn = staticVar + "void " + m_class_name + "::set" + var->getName() + "( " + varType + pointerVar + "value" + " )";
		break;
	case (eStringType::VARIABLE):
		rtn = staticVar + constVar + varType + pointerVar + m_class_name + "::" + var->getName() + " = " + var->getValue() + ";";
		break;
	}

	return rtn;
}