/////////////////////////////////////////////////////////////////////////////
// Name:        cppfilebuilderapp.cpp
// Purpose:     
// Author:      Richard W. Allen
// Modified by: 
// Created:     14/07/2018 21:35:22
// RCS-ID:      
// Copyright:   (C) 2017 Richard W. Allen
// Licence:     GPL 2
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
#include "wx/fs_zip.h"
////@end includes

#include "cppfilebuilderapp.h"


extern void InitXmlResource();

////@begin XPM images
////@end XPM images


/*
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( CPPFileBuilderApp )
////@end implement app


/*
 * CPPFileBuilderApp type definition
 */

IMPLEMENT_CLASS( CPPFileBuilderApp, wxApp )


/*
 * CPPFileBuilderApp event table definition
 */

BEGIN_EVENT_TABLE( CPPFileBuilderApp, wxApp )

////@begin CPPFileBuilderApp event table entries
////@end CPPFileBuilderApp event table entries

END_EVENT_TABLE()


/*
 * Constructor for CPPFileBuilderApp
 */

CPPFileBuilderApp::CPPFileBuilderApp()
{
    Init();
}


/*
 * Member initialisation
 */

void CPPFileBuilderApp::Init()
{
////@begin CPPFileBuilderApp member initialisation
////@end CPPFileBuilderApp member initialisation
}

/*
 * Initialisation for CPPFileBuilderApp
 */

bool CPPFileBuilderApp::OnInit()
{    

	// Remove the comment markers above and below this block
	// to make permanent changes to the code.

	wxXmlResource::Get()->InitAllHandlers();
    InitXmlResource();
	//wxFileSystem::AddHandler(new wxZipFSHandler);
	//wxXmlResource::Get()->Load(wxT("resource.xrc"));

#if wxUSE_XPM
	wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif
	CPPFileBuilder* mainWindow = new CPPFileBuilder(NULL);
	mainWindow->SetSize(500, 300);
	/* int returnValue = */ mainWindow->ShowModal();

	mainWindow->Destroy();
	// A modal dialog application should return false to terminate the app.
	//return false;

    return true;
}


/*
 * Cleanup for CPPFileBuilderApp
 */

int CPPFileBuilderApp::OnExit()
{    
	std::vector<Model::cClassModel*>::iterator it;

	for (it = m_classesModel.begin(); it < m_classesModel.end(); it++) {
		delete (*it);
		(*it) = nullptr;
	}
	m_classesModel.clear();
////@begin CPPFileBuilderApp cleanup
	return wxApp::OnExit();
////@end CPPFileBuilderApp cleanup
}


/*
 * Get the ClassesModule Vector
 */

std::vector<Model::cClassModel*>& CPPFileBuilderApp::getClassesModel()
{
    return m_classesModel;
}

/*
 * Get ClassModule pointer by single string
 */

Model::cClassModel* CPPFileBuilderApp::getClassModel(const wxString& name)
{
    Model::cClassModel* rtn = nullptr;

    wxString nameClass = name;
    name.Mid(name.Find(':') + 2, name.length());
    wxString nameSpace = "";
    if (name.First(':') != wxNOT_FOUND) {
        nameClass = name.Mid(name.Find(':') + 2, name.length());
        nameSpace = name.Mid(0, name.Find(':'));
    }

    rtn = getClassModel(nameClass, nameSpace);

    return rtn;
}

/*
 * Get ClassModule pointer by class name and namespace
 */

Model::cClassModel* CPPFileBuilderApp::getClassModel(const wxString& nameClass, const wxString& nameSpace)
{
	Model::cClassModel* rtn = nullptr;
	std::vector<Model::cClassModel*>& classesModule = wxGetApp().getClassesModel();
	std::vector<Model::cClassModel*>::iterator it;

	for (it = classesModule.begin(); it < classesModule.end(); it++) {
		if ((*it)->getName() == nameClass) {
			if ((*it)->getNameSpace() == nameSpace) {
				rtn = (*it);
				break;
			}
		}
	}
	return rtn;
}

/*
 * Set ClassModule
 */

void CPPFileBuilderApp::setClassesModel(Model::cClassModel* value)
{
    m_classesModel.push_back(value);
}

/*
 * Removes that ClassModule that is passed to it from the vector
 */

void CPPFileBuilderApp::RemoveModel(const Model::cClassModel& module)
{
std::vector<Model::cClassModel*>::iterator it;

    for (it = m_classesModel.begin(); it < m_classesModel.end(); it++) {
        if (module == *(*it)) {
            delete (*it);
            (*it) = nullptr;
            m_classesModel.erase(it);
            break;
        }
    }
}

/*
 * Generate Source Files and Header files
 */

void CPPFileBuilderApp::GenerateSourceFiles()
{
    std::vector<Model::cClassModel*>::iterator it;

    for (it = m_classesModel.begin(); it < m_classesModel.end(); it++)
        (*it)->BuildCPPFile();
}
