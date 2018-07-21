/////////////////////////////////////////////////////////////////////////////
// Name:        cSourceBuilder.hpp
// Purpose:     
// Author:      Richard W. Allen
// Modified by: 
// Created:     14/07/2018 21:38:08
// RCS-ID:      
// Copyright:   (C) 2017 Richard W. Allen
// Licence:     GPL 2
/////////////////////////////////////////////////////////////////////////////
#ifndef _CSOURCEBUILDER_HPP_
#define _CSOURCEBUILDER_HPP_

#include "cBaseBuilder.hpp"

#include <string>

namespace Builders {
	class cSourceBuilder : public cBaseBuilder
	{
	public:
		cSourceBuilder(const std::string& class_name, const std::string& name_space, const bool singleton = false);	// default constructor
		~cSourceBuilder();

		void Build();

	private:
		void PreprocessorBuild();
		void NameSpaceBuild();
		void VariableBuild();
		void ConstructorBuild();
		void FunctionsBuild();
		
		void SingletonBuild();

		void GettersBuild();
		void SettersBuild();

		const std::string StringBuild(const Model::cVariableModel* var, eStringType type) const;
	};/// END CLASS DEFINITION cSourceBuilder
}/// END NAMESPACE DEFINITION Build
#endif/// END IFNDEF _CSOURCEBUILDER_HPP_
