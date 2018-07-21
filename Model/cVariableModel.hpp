/////////////////////////////////////////////////////////////////////////////
// Name:        cVariableModel.hpp
// Purpose:     
// Author:      Richard W. Allen
// Modified by: 
// Created:     14/07/2018 21:38:08
// RCS-ID:      
// Copyright:   (C) 2017 Richard W. Allen
// Licence:     GPL 2
/////////////////////////////////////////////////////////////////////////////
#ifndef _CVARIABLEMODEL_HPP_
#define _CVARIABLEMODEL_HPP_

#include <string>

namespace Model {
	class cVariableModel
	{
	public:
		enum eSigned : unsigned int
		{
			sNONE = 0,
			UNSIGNED,
			SIGNED
		};

		enum eVarType : unsigned int
		{
			CHAR = 0,
			SHORT,
			INT,
			LONG,
			LONG_LONG,
			BOOL,
			FLOAT,
			DOUBLE,
			LONG_DOUBLE,
			vVOID,
			AUTO
		};

		enum ePointer : unsigned int
		{
			pNONE = 0,
			POINTER,
			REFERENCE
		};

		cVariableModel();	// default constructor
		cVariableModel(cVariableModel& copy);		
		~cVariableModel();

		cVariableModel& Copy(cVariableModel& copy, const bool deep = true);

		const std::string StringBuild() const;

		/// Getters
		const bool getConst() const;
		const bool getStatic() const;

		const eSigned getSigned() const;
		const eVarType getVarType() const;
		const ePointer getPointer() const;

		const std::string& getName() const;
		const std::string& getValue() const;

		const bool getGetters() const;
		const bool getSetters() const;

		/// Setters
		void setConst(const bool constVar);
		void setStatic(const bool staticVar);
		
		void setSigned(const eSigned signedVar);
		void setVarType(const eVarType varType);
		void setPointer(const ePointer pointerVar);

		void setName(const std::string& name);
		void setValue(const std::string& value);

		void setGetters(const bool getters);
		void setSetters(const bool setters);

		/// operators
		bool operator == (const cVariableModel& rhs) const;

		cVariableModel& operator=(cVariableModel& copy);

	private:
		bool m_const;
		bool m_static;

		eSigned m_signed;
		eVarType m_varType;
		ePointer m_pointer;

		std::string m_name;
		std::string m_value;

		bool m_getters;
		bool m_setters;
	};/// END CLASS DEFINITION cVariableModel
}/// END NAMESPACE DEFINITION Model
#endif/// END IFNDEF _CVARIABLEMODEL_HPP_
