/////////////////////////////////////////////////////////////////////////////
// Name:        cppfilebuilderapp.h
// Purpose:     
// Author:      Richard W. Allen
// Modified by: 
// Created:     14/07/2018 21:35:22
// RCS-ID:      
// Copyright:   (C) 2017 Richard W. Allen
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _CPPFILEBUILDERAPP_H_
#define _CPPFILEBUILDERAPP_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/xrc/xmlres.h"
#include "wx/image.h"
#include "cppfilebuilder.h"
////@end includes

#include <vector>
#include "../Model/cClassModel.hpp"

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
////@end control identifiers

/*!
 * CPPFileBuilderApp class declaration
 */

class CPPFileBuilderApp: public wxApp
{    
    DECLARE_CLASS( CPPFileBuilderApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    CPPFileBuilderApp();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

    /// Get the ClassesModule Vector
    std::vector<Model::cClassModel*>& getClassesModule();

    /// Get ClassModule pointer by single string
    Model::cClassModel* getClassModule(const wxString& name);

    /// Get ClassModule pointer by class name and namespace
    Model::cClassModel* getClassModule(const wxString& nameClass, const wxString& nameSpace);

    /// Set ClassModule
    void setClassesModule(Model::cClassModel* value);

    /// Removes that ClassModule that is passed to it from the vector
    void RemoveModule(const Model::cClassModel& module);

    /// Generate Source Files and Header files
    void GenerateSourceFiles();

////@begin CPPFileBuilderApp event handler declarations

////@end CPPFileBuilderApp event handler declarations

////@begin CPPFileBuilderApp member function declarations

////@end CPPFileBuilderApp member function declarations

////@begin CPPFileBuilderApp member variables
private:
	std::vector<Model::cClassModel*> m_classesModule;
////@end CPPFileBuilderApp member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(CPPFileBuilderApp)
////@end declare app

#endif
    // _CPPFILEBUILDERAPP_H_
