/////////////////////////////////////////////////////////////////////////////
// Name:        createclass.h
// Purpose:     
// Author:      Richard W. Allen
// Modified by: 
// Created:     14/07/2018 21:39:24
// RCS-ID:      
// Copyright:   (C) 2017 Richard W. Allen
// Licence:     GPL 2
/////////////////////////////////////////////////////////////////////////////

#ifndef _CREATECLASS_H_
#define _CREATECLASS_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/xrc/xmlres.h"
#include "wx/statline.h"
#include "wx/notebook.h"
////@end includes

#include "../Model/cClassModel.hpp"
#include "../Model/cVariableModel.hpp"
#include <vector>

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_CREATECLASS 10000
#define SYMBOL_CREATECLASS_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CREATECLASS_TITLE _("Create Class")
#define SYMBOL_CREATECLASS_IDNAME ID_CREATECLASS
#define SYMBOL_CREATECLASS_SIZE wxSize(400, 300)
#define SYMBOL_CREATECLASS_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CreateClass class declaration
 */

class CreateClass: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( CreateClass )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CreateClass();
    CreateClass( wxWindow* parent, wxWindowID id = SYMBOL_CREATECLASS_IDNAME, const wxString& caption = SYMBOL_CREATECLASS_TITLE, const wxPoint& pos = SYMBOL_CREATECLASS_POSITION, const wxSize& size = SYMBOL_CREATECLASS_SIZE, long style = SYMBOL_CREATECLASS_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CREATECLASS_IDNAME, const wxString& caption = SYMBOL_CREATECLASS_TITLE, const wxPoint& pos = SYMBOL_CREATECLASS_POSITION, const wxSize& size = SYMBOL_CREATECLASS_SIZE, long style = SYMBOL_CREATECLASS_STYLE );

    /// Destructor
    ~CreateClass();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

    /// Setup Class Creater for Edit Class
    void EditClass(const wxString& name);

    /// Setup Create Class for Copy Class
    void CopyClass(const wxString& name);

    /// Setup the CreateClass for Edit or Copy
    void ClassSetup(const wxString& name);

    /// Populate the Inheritance List
    void PopulateInheritanceList(const wxString& ignore = "");

    /// Get Class this Class inherits from
    void GetInheritance(Model::cClassModel& classModule);

    /// Populates the inherits list from
    void PopulateInheritance(Model::cClassModel& classModule);

    /// Populates the variables list from
    void PopulateVariables(Model::cClassModel& classModel);

////@begin CreateClass event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
    void OnDeleteVarClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE1
    void OnConstChoiceSelected( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
    void OnAddVarClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON2
    void OnOKClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3
    void OnCancelClick( wxCommandEvent& event );

////@end CreateClass event handler declarations

////@begin CreateClass member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CreateClass member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CreateClass member variables
    wxTextCtrl* mp_classNameTxt;
    wxCheckBox* mp_singletonChk;
    wxTextCtrl* mp_nameSpaceTxt;
    wxCheckListBox* mp_inheritanceLst;
    wxCheckListBox* mp_varList;
    wxChoice* mp_staticCh;
    wxChoice* mp_constCh;
    wxChoice* mp_signedCh;
    wxChoice* mp_varTypeCh;
    wxChoice* mp_pointerCh;
    wxTextCtrl* mp_nameTxt;
    wxTextCtrl* mp_valueTxt;
    wxCheckBox* mp_getterChBox;
    wxCheckBox* mp_setterChBox;
private:
    bool m_copy; // is this and class that is being copped?
    bool m_edit; // is this and class that is being edited?
    Model::cClassModel* mp_classModel; // Class model for edit and copy
////@end CreateClass member variables
};

#endif
    // _CREATECLASS_H_
