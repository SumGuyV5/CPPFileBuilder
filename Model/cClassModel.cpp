#include "cClassModel.hpp"

#include "../Builders/cHeaderBuilder.hpp"
#include "../Builders/cSourceBuilder.hpp"

using Model::cClassModel;
using Model::cVariableModel;

cClassModel::cClassModel(const std::string& name, const std::string& nameSpace)
	: m_name(name), m_nameSpace(nameSpace), m_singleton(false)
{
}

cClassModel::~cClassModel()
{
	DeleteVariables();
}

void cClassModel::BuildCPPFile()
{
	BuildHeaderFile();
	BuildSourceFile();
}

void cClassModel::CleanInheritance()
{
	m_inheritance.clear();
}

void cClassModel::DeleteVariables()
{
	std::vector<Model::cVariableModel*>::iterator it;

	for (it = m_variables.begin(); it < m_variables.end(); it++) {
		delete (*it);
		(*it) = nullptr;
	}
	m_variables.clear();
}

/// Getters
const std::string& cClassModel::getName() const
{
	return m_name;
}

const std::string& cClassModel::getNameSpace() const
{
	return m_nameSpace;
}

const bool cClassModel::getSingleton() const
{
	return m_singleton;
}

std::vector<cVariableModel*>& cClassModel::getVariables()
{
	return m_variables;
}

std::vector<cClassModel*>& cClassModel::getInheritance()
{
	return m_inheritance;
}

/// Setters
void cClassModel::setName(const std::string& name)
{
	m_name = name;
}

void cClassModel::setNameSpace(const std::string& nameSpace)
{
	m_nameSpace = nameSpace;
}

void cClassModel::setSingleton(const bool singleton)
{
	m_singleton = singleton;
}

void cClassModel::setVariables(cVariableModel* var)
{
	m_variables.push_back(var);
}

void cClassModel::setInheritance(cClassModel* classModule)
{
	m_inheritance.push_back(classModule);
}

bool cClassModel::operator == (const cClassModel& rhs) const
{
	return (m_name == rhs.getName()) && (m_nameSpace == rhs.getNameSpace());
}

///Private
void cClassModel::BuildHeaderFile()
{
	Builders::cHeaderBuilder headerBuilder(m_name, m_nameSpace, m_singleton);

	std::vector<cClassModel*>::iterator it;

	for (it = m_inheritance.begin(); it < m_inheritance.end(); it++)
		headerBuilder.ClassInheritance((*it)->getName(), (*it)->getNameSpace());

	headerBuilder.setVariableModel(m_variables);
	headerBuilder.Build();
}

void cClassModel::BuildSourceFile()
{
	Builders::cSourceBuilder sourceBuilder(m_name, m_nameSpace, m_singleton);
	
	sourceBuilder.setVariableModel(m_variables);
	sourceBuilder.Build();
}