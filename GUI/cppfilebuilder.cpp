/////////////////////////////////////////////////////////////////////////////
// Name:        cppfilebuilder.cpp
// Purpose:     
// Author:      Richard W. Allen
// Modified by: 
// Created:     14/07/2018 21:36:31
// RCS-ID:      
// Copyright:   (C) 2017 Richard W. Allen
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "cppfilebuilder.h"

#include "cppfilebuilderapp.h"
#include "createclass.h"
#include "../Model/cClassModel.hpp"
#include <vector>
#include <string>

////@begin XPM images
////@end XPM images


/*
 * CPPFileBuilder type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CPPFileBuilder, wxDialog )


/*
 * CPPFileBuilder event table definition
 */

BEGIN_EVENT_TABLE( CPPFileBuilder, wxDialog )

////@begin CPPFileBuilder event table entries
    EVT_BUTTON( XRCID("ID_BUTTON"), CPPFileBuilder::OnCreateClassClick )
    EVT_BUTTON( XRCID("ID_BUTTON1"), CPPFileBuilder::OnEditClassClick )
    EVT_BUTTON( XRCID("ID_BUTTON2"), CPPFileBuilder::OnDeleteClassClick )
    EVT_BUTTON( XRCID("ID_BUTTON3"), CPPFileBuilder::OnCopyClassClick )
    EVT_BUTTON( XRCID("ID_BUTTON4"), CPPFileBuilder::OnGenerateFilesClick )
////@end CPPFileBuilder event table entries

END_EVENT_TABLE()


/*
 * CPPFileBuilder constructors
 */

CPPFileBuilder::CPPFileBuilder()
{
    Init();
}

CPPFileBuilder::CPPFileBuilder( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * CPPFileBuilder creator
 */

bool CPPFileBuilder::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CPPFileBuilder creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    SetParent(parent);
    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CPPFileBuilder creation
    return true;
}


/*
 * CPPFileBuilder destructor
 */

CPPFileBuilder::~CPPFileBuilder()
{
////@begin CPPFileBuilder destruction
////@end CPPFileBuilder destruction
}


/*
 * Member initialisation
 */

void CPPFileBuilder::Init()
{
////@begin CPPFileBuilder member initialisation
    mp_classChoice = NULL;
////@end CPPFileBuilder member initialisation
}


/*
 * Control creation for CPPFileBuilder
 */

void CPPFileBuilder::CreateControls()
{    
////@begin CPPFileBuilder content construction
    if (!wxXmlResource::Get()->LoadDialog(this, GetParent(), wxT("ID_CPPFILEBUILDER")))
        wxLogError(wxT("Missing wxXmlResource::Get()->Load() in OnInit()?"));
    mp_classChoice = XRCCTRL(*this, "ID_CHOICE", wxChoice);
////@end CPPFileBuilder content construction

    // Create custom windows not generated automatically here.
////@begin CPPFileBuilder content initialisation
////@end CPPFileBuilder content initialisation
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

void CPPFileBuilder::OnCreateClassClick( wxCommandEvent& event )
{
    CreateClass* classWindow = new CreateClass(this);
	classWindow->PopulateInheritanceList();
    classWindow->SetSize(wxDefaultCoord, 600);
	classWindow->ShowModal();

	classWindow->Destroy();
	PopulateChoiceList();
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in CPPFileBuilder.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in CPPFileBuilder. 
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
 */

void CPPFileBuilder::OnEditClassClick( wxCommandEvent& event )
{
	if (mp_classChoice->GetSelection() != wxNOT_FOUND) {
		CreateClass* classWindow = new CreateClass(this);
		classWindow->PopulateInheritanceList(mp_classChoice->GetStringSelection());
		classWindow->EditClass(mp_classChoice->GetStringSelection());
		classWindow->SetSize(wxDefaultCoord, 600);
		classWindow->ShowModal();

		classWindow->Destroy();
		PopulateChoiceList();
	}
	else {
		wxMessageBox(wxT("No Class Selected."), wxT("This is an Error."));
	}
    
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1 in CPPFileBuilder.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1 in CPPFileBuilder. 
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON2
 */

void CPPFileBuilder::OnDeleteClassClick( wxCommandEvent& event )
{
	if (mp_classChoice->GetSelection() != wxNOT_FOUND) {
		wxString name = mp_classChoice->GetStringSelection();

		wxString nameClass = name; name.Mid(name.Find(':') + 2, name.length());
		wxString nameSpace = "";
		if (name.First(':') != wxNOT_FOUND) {
			nameClass = name.Mid(name.Find(':') + 2, name.length());
			nameSpace = name.Mid(0, name.Find(':'));
		}

		Model::cClassModel* classModule = wxGetApp().getClassModule(nameClass, nameSpace);

		wxGetApp().RemoveModule(*classModule);

		PopulateChoiceList();
	}
	else {
		wxMessageBox(wxT("No Class Selected."), wxT("This is an Error."));
	}
    
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON2 in CPPFileBuilder.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON2 in CPPFileBuilder. 
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3
 */

void CPPFileBuilder::OnCopyClassClick( wxCommandEvent& event )
{
	if (mp_classChoice->GetSelection() != wxNOT_FOUND) {
		CreateClass* classWindow = new CreateClass(this);
		classWindow->PopulateInheritanceList();
		classWindow->CopyClass(mp_classChoice->GetStringSelection());
		classWindow->SetSize(wxDefaultCoord, 600);
		classWindow->ShowModal();

		classWindow->Destroy();
		PopulateChoiceList();
	}
	else {
		wxMessageBox(wxT("No Class Selected."), wxT("This is an Error."));
	}
    
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3 in CPPFileBuilder.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3 in CPPFileBuilder. 
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON4
 */

void CPPFileBuilder::OnGenerateFilesClick( wxCommandEvent& event )
{
    wxGetApp().GenerateSourceFiles();
	wxMessageBox(wxT("c++ file generated."), wxT("All done."));
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON4 in CPPFileBuilder.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON4 in CPPFileBuilder. 
}


/*
 * Should we show tooltips?
 */

bool CPPFileBuilder::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap CPPFileBuilder::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CPPFileBuilder bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CPPFileBuilder bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon CPPFileBuilder::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CPPFileBuilder icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CPPFileBuilder icon retrieval
}

/*
 * Populate the Choice List with all avalible Classes
 */

void  CPPFileBuilder::PopulateChoiceList()
{
	mp_classChoice->Clear();
    std::vector<Model::cClassModel*>& classesModule = wxGetApp().getClassesModule();
    if (mp_classChoice != nullptr) {
        std::vector<Model::cClassModel*>::iterator it;

        for (it = classesModule.begin(); it < classesModule.end(); it++) {
            if ((*it)->getName() != "") {
                std::string nametmp = (*it)->getNameSpace();
                if (nametmp.empty() == false)
                    nametmp += "::";
                nametmp += (*it)->getName();
                mp_classChoice->AppendString(nametmp);
            }                
        }
    }
}
