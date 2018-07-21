/////////////////////////////////////////////////////////////////////////////
// Name:        cHeaderBuilder.hpp
// Purpose:     
// Author:      Richard W. Allen
// Modified by: 
// Created:     14/07/2018 21:38:08
// RCS-ID:      
// Copyright:   (C) 2017 Richard W. Allen
// Licence:     GPL 2
/////////////////////////////////////////////////////////////////////////////
#ifndef _CHEADERBUILDER_HPP_
#define _CHEADERBUILDER_HPP_

#include "cBaseBuilder.hpp"

#include <string>

namespace Builders {
	class cHeaderBuilder: public cBaseBuilder
	{
	public:
		cHeaderBuilder(const std::string& class_name, const std::string& name_space, const bool singleton = false);	// default constructor
		~cHeaderBuilder();

		void Build(const std::string& inheritance = "");
		void ClassInheritance(const std::string& classname, const std::string& nameSpace = "");
		void IncludeFiles(const std::string& classname);

	private:
		void PreprocessorBuild();
		void NameSpaceBuild();
		void ClassBuild();

		void PublicFunctions();
		void PrivateVariables();

		void FunctionsBuild();
		void FunctionBuild();

		void SingletonBuild();

		void GettersBuild();
		void SettersBuild();

		void VariablesBuild();
		void VariableBuild(const Model::cVariableModel* var);

		const std::string StringBuild(const Model::cVariableModel* var, eStringType type) const;

	private:
		std::string m_tabString;
		std::string m_includeStr;
		std::string m_inheritanceStr;
	};/// END CLASS DEFINITION cHeaderBuilder
}/// END NAMESPACE DEFINITION Builder
#endif/// END IFNDEF _CHEADERBUILDER_HPP_
