/////////////////////////////////////////////////////////////////////////////
// Name:        ClassModel.hpp
// Purpose:     
// Author:      Richard W. Allen
// Modified by: 
// Created:     14/07/2018 21:38:08
// RCS-ID:      
// Copyright:   (C) 2017 Richard W. Allen
// Licence:     GPL 2
/////////////////////////////////////////////////////////////////////////////
#ifndef _CCLASSMODEL_HPP_
#define _CCLASSMODEL_HPP_

#include "cVariableModel.hpp"
#include "../Builders/cSourceBuilder.hpp"

#include <string>
#include <vector>

#include <wx/string.h>

namespace Model {
	class cClassModel
	{
	public:
		cClassModel(const std::string& name, const std::string& nameSpace);
		cClassModel(cClassModel& copy);
		~cClassModel();

		cClassModel& Copy(cClassModel& copy, bool deep = true);

		void BuildCPPFile();
		void CleanInheritance();
		void DeleteVariables();

		/// Getters
		const std::string& getName() const;
		const std::string& getNameSpace() const;

		const bool getSingleton() const;

		std::vector<cVariableModel*>& getVariables();
		std::vector<cClassModel*>& getInheritance();

		/// Setters
		void setName(const std::string& name);
		void setNameSpace(const std::string& nameSpace);

		void setSingleton(const bool singleton);

		void setVariables(cVariableModel* var);
		void setInheritance(cClassModel* classModule);

		// operators
		bool operator == (const cClassModel& rhs) const;

	private:
		void BuildHeaderFile();
		void BuildSourceFile();

	private:
		std::string m_name;
		std::string m_nameSpace;

		bool m_singleton;

		std::vector<cVariableModel*> m_variables;
		std::vector<cClassModel*> m_inheritance;
	};/// END CLASS DEFINITION cClassModel
}/// END NAMESPACE DEFINITION Model
#endif/// END IFNDEF _CCLASSMODEL_HPP_

