/////////////////////////////////////////////////////////////////////////////
// Name:        cBaseBuilder.hpp
// Purpose:     
// Author:      Richard W. Allen
// Modified by: 
// Created:     14/07/2018 21:38:08
// RCS-ID:      
// Copyright:   (C) 2017 Richard W. Allen
// Licence:     GPL 2
/////////////////////////////////////////////////////////////////////////////
#ifndef _CBASEBUILDER_HPP_
#define _CBASEBUILDER_HPP_

#include <fstream>
#include <string>
#include <vector>

#include "../Model/cVariableModel.hpp"

namespace Builders {
	class cBaseBuilder
	{
	public:
		cBaseBuilder(const std::string& class_name, const std::string& name_space, const bool singleton = false);	// default constructor
		~cBaseBuilder();

		void setVariableModel(const std::vector<Model::cVariableModel*>& value);

	protected:
		enum eStringType : unsigned int
		{
			GETTER = 0,
			SETTER,
			VARIABLE
		};

	protected:
		std::ofstream m_file;

		bool m_noNameSpace;
		bool m_singleton;

		std::string m_file_name;
		std::string m_class_name;
		std::string m_name_space;

		std::vector<Model::cVariableModel*> m_variables;
	};/// END CLASS DEFINITION cBaseBuilder
}/// END NAMESPACE DEFINITION Builder
#endif/// END IFNDEF _CBASEBUILDER_HPP_
