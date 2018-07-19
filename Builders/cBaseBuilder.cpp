#include "cBaseBuilder.hpp"

using Builders::cBaseBuilder;

cBaseBuilder::cBaseBuilder(const std::string& class_name, const std::string& name_space, const bool singleton /*= false*/)
	: m_file_name(class_name), m_class_name(class_name), m_name_space(name_space), m_noNameSpace(false), m_singleton(singleton)
{
	if (m_name_space.length() == 0)
		m_noNameSpace = true;
}

cBaseBuilder::~cBaseBuilder()
{
}

void cBaseBuilder::setVariableModel(const std::vector<Model::cVariableModel*>& value)
{
	m_variables = value;
}
