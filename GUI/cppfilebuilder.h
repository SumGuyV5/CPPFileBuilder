/////////////////////////////////////////////////////////////////////////////
// Name:        cppfilebuilder.h
// Purpose:     
// Author:      Richard W. Allen
// Modified by: 
// Created:     14/07/2018 21:37:43
// RCS-ID:      
// Copyright:   (C) 2017 Richard W. Allen
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _CPPFILEBUILDER_H_
#define _CPPFILEBUILDER_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/xrc/xmlres.h"
#include "wx/statline.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_CPPFILEBUILDER 10000
#define SYMBOL_CPPFILEBUILDER_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CPPFILEBUILDER_TITLE _("C++ File Builder")
#define SYMBOL_CPPFILEBUILDER_IDNAME ID_CPPFILEBUILDER
#define SYMBOL_CPPFILEBUILDER_SIZE wxSize(400, 300)
#define SYMBOL_CPPFILEBUILDER_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CPPFileBuilder class declaration
 */

class CPPFileBuilder: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( CPPFileBuilder )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CPPFileBuilder();
    CPPFileBuilder( wxWindow* parent, wxWindowID id = SYMBOL_CPPFILEBUILDER_IDNAME, const wxString& caption = SYMBOL_CPPFILEBUILDER_TITLE, const wxPoint& pos = SYMBOL_CPPFILEBUILDER_POSITION, const wxSize& size = SYMBOL_CPPFILEBUILDER_SIZE, long style = SYMBOL_CPPFILEBUILDER_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CPPFILEBUILDER_IDNAME, const wxString& caption = SYMBOL_CPPFILEBUILDER_TITLE, const wxPoint& pos = SYMBOL_CPPFILEBUILDER_POSITION, const wxSize& size = SYMBOL_CPPFILEBUILDER_SIZE, long style = SYMBOL_CPPFILEBUILDER_STYLE );

    /// Destructor
    ~CPPFileBuilder();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

    /// Populate the Choice List with all avalible Classes
    void  PopulateChoiceList();

////@begin CPPFileBuilder event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
    void OnCreateClassClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
    void OnEditClassClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON2
    void OnDeleteClassClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3
    void OnCopyClassClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON4
    void OnGenerateFilesClick( wxCommandEvent& event );

////@end CPPFileBuilder event handler declarations

////@begin CPPFileBuilder member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CPPFileBuilder member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CPPFileBuilder member variables
    wxChoice* mp_classChoice;
////@end CPPFileBuilder member variables
};

#endif
    // _CPPFILEBUILDER_H_
