/////////////////////////////////////////////////////////////////////////////
// Name:        createclass.cpp
// Purpose:     
// Author:      Richard W. Allen
// Modified by: 
// Created:     14/07/2018 21:38:08
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
#include "wx/imaglist.h"
////@end includes

#include "createclass.h"
#include "cppfilebuilderapp.h"

////@begin XPM images
////@end XPM images


/*
 * CreateClass type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CreateClass, wxDialog )


/*
 * CreateClass event table definition
 */

BEGIN_EVENT_TABLE( CreateClass, wxDialog )

////@begin CreateClass event table entries
    EVT_BUTTON( XRCID("ID_BUTTON1"), CreateClass::OnDeleteVarClick )
    EVT_CHOICE( XRCID("ID_CHOICE1"), CreateClass::OnConstChoiceSelected )
    EVT_BUTTON( XRCID("ID_BUTTON"), CreateClass::OnAddVarClick )
    EVT_BUTTON( XRCID("ID_BUTTON2"), CreateClass::OnOKClick )
    EVT_BUTTON( XRCID("ID_BUTTON3"), CreateClass::OnCancelClick )
////@end CreateClass event table entries

END_EVENT_TABLE()


/*
 * CreateClass constructors
 */

CreateClass::CreateClass()
{
    Init();
}

CreateClass::CreateClass( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * CreateClass creator
 */

bool CreateClass::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CreateClass creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    SetParent(parent);
    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CreateClass creation
    return true;
}


/*
 * CreateClass destructor
 */

CreateClass::~CreateClass()
{
	std::vector<Model::cVariableModel*>::iterator it;

	for (it = m_varList.begin(); it < m_varList.end(); it++) {
		delete (*it);
		(*it) = nullptr;
	}
	m_varList.clear();
////@begin CreateClass destruction
////@end CreateClass destruction
}


/*
 * Member initialisation
 */

void CreateClass::Init()
{
////@begin CreateClass member initialisation
    m_copy = false;
    m_edit = false;
    mp_classModel = nullptr;
    mp_classNameTxt = NULL;
    mp_singletonChk = NULL;
    mp_nameSpaceTxt = NULL;
    mp_inheritanceLst = NULL;
    mp_varList = NULL;
    mp_staticCh = NULL;
    mp_constCh = NULL;
    mp_signedCh = NULL;
    mp_varTypeCh = NULL;
    mp_pointerCh = NULL;
    mp_nameTxt = NULL;
    mp_valueTxt = NULL;
    mp_getterChBox = NULL;
    mp_setterChBox = NULL;
////@end CreateClass member initialisation
}


/*
 * Control creation for CreateClass
 */

void CreateClass::CreateControls()
{    
////@begin CreateClass content construction
    if (!wxXmlResource::Get()->LoadDialog(this, GetParent(), wxT("ID_CREATECLASS")))
        wxLogError(wxT("Missing wxXmlResource::Get()->Load() in OnInit()?"));
    mp_classNameTxt = XRCCTRL(*this, "ID_TEXTCTRL", wxTextCtrl);
    mp_singletonChk = XRCCTRL(*this, "ID_CHECKBOX2", wxCheckBox);
    mp_nameSpaceTxt = XRCCTRL(*this, "ID_TEXTCTRL2", wxTextCtrl);
    mp_inheritanceLst = XRCCTRL(*this, "ID_CHECKLISTBOX1", wxCheckListBox);
    mp_varList = XRCCTRL(*this, "ID_CHECKLISTBOX", wxCheckListBox);
    mp_staticCh = XRCCTRL(*this, "ID_CHOICE", wxChoice);
    mp_constCh = XRCCTRL(*this, "ID_CHOICE1", wxChoice);
    mp_signedCh = XRCCTRL(*this, "ID_CHOICE2", wxChoice);
    mp_varTypeCh = XRCCTRL(*this, "ID_CHOICE3", wxChoice);
    mp_pointerCh = XRCCTRL(*this, "ID_CHOICE4", wxChoice);
    mp_nameTxt = XRCCTRL(*this, "ID_TEXTCTRL1", wxTextCtrl);
    mp_valueTxt = XRCCTRL(*this, "ID_TEXTCTRL3", wxTextCtrl);
    mp_getterChBox = XRCCTRL(*this, "ID_CHECKBOX", wxCheckBox);
    mp_setterChBox = XRCCTRL(*this, "ID_CHECKBOX1", wxCheckBox);
////@end CreateClass content construction

    // Create custom windows not generated automatically here.
////@begin CreateClass content initialisation
////@end CreateClass content initialisation
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
 */

void CreateClass::OnDeleteVarClick( wxCommandEvent& event )
{
	for (int count = 0; count < mp_varList->GetCount(); count++) {
		if (mp_varList->IsChecked(count) == true) {
			mp_varList->Delete(count);
			Model::cVariableModel* tmp = m_varList.at(count);
			m_varList.erase(m_varList.begin() + count);
			delete tmp;
			tmp = nullptr;
			count--;
		}
	}
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1 in CreateClass.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1 in CreateClass. 
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

void CreateClass::OnAddVarClick( wxCommandEvent& event )
{
	/// if this variable is const and you did not give it a value. point it out and exit.
	if ((mp_constCh->GetSelection() == 1) && (mp_valueTxt->IsEmpty() == true)) {
		wxMessageBox(wxT("If the variable is going to be const. Please fill in the value."), wxT("This is an Error."));
		mp_valueTxt->SetBackgroundColour({ 255, 0, 0 });
		return;
	}

	/// if this variable has not name. point it out and exit.
	if (mp_nameTxt->IsEmpty() == true) {
		wxMessageBox(wxT("Please Give the variable a name."), wxT("This is an Error."));
		mp_nameTxt->SetBackgroundColour({ 255, 0, 0 });
		return;
	}
	
	mp_valueTxt->SetBackgroundColour({ 255, 255, 255 });
	mp_nameTxt->SetBackgroundColour({ 255, 255, 255 });
	Model::cVariableModel* tmp = new Model::cVariableModel();

	if (mp_staticCh->GetSelection() == 1)
		tmp->setStatic(true);

	if (mp_constCh->GetSelection() == 1)
		tmp->setConst(true);

	tmp->setSigned((Model::cVariableModel::eSigned)mp_constCh->GetSelection());
	tmp->setVarType((Model::cVariableModel::eVarType)mp_varTypeCh->GetSelection());
	tmp->setPointer((Model::cVariableModel::ePointer)mp_pointerCh->GetSelection());
	tmp->setName(mp_nameTxt->GetValue().ToStdString());
	tmp->setValue(mp_valueTxt->GetValue().ToStdString());

	tmp->setGetters(mp_getterChBox->GetValue());
	tmp->setSetters(mp_setterChBox->GetValue());

	bool found = false;

	std::vector<Model::cVariableModel*>::iterator it;

	for (it = m_varList.begin(); it < m_varList.end(); it++) {
		if ((*it) == tmp) /// this variable name is already used.
			found = true; 
	}

	if (found == false) {
		m_varList.push_back(tmp);
		mp_varList->AppendString(tmp->StringBuild());
	}
	else {
		/// this name is already used by another variable. Tell user and delete pointer.
		wxMessageBox(wxT("This name is already used by another variable."), wxT("This is an Error."));
		mp_nameTxt->SetBackgroundColour({ 255, 0, 0 });
		delete tmp;
		tmp = nullptr;
	}
	
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in CreateClass.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in CreateClass. 
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON2
 */

void CreateClass::OnOKClick( wxCommandEvent& event )
{
    wxString nameClass = mp_classNameTxt->GetValue();
	wxString nameSpace = mp_nameSpaceTxt->GetValue();

	if (nameClass.empty() == false) {
		
		Model::cClassModel* classModule = nullptr;

		// if this is an edit or copy get the ClassModule
		if ((m_edit == true) || (m_copy == true))
			classModule = wxGetApp().getClassModule(nameClass, nameSpace);

		// if this is a copy we should not have found when we executed the above method.
		if (m_copy == true && classModule != nullptr)
			wxMessageBox(wxT("Please Rename Class Found."), wxT("This is an Error."));
		else {
			// if this is a copy or a new class make it.
			if ((m_edit == false) || (m_copy == true))
				classModule = new Model::cClassModel(nameClass.ToStdString(), nameSpace.ToStdString());
			
			classModule->setSingleton(mp_singletonChk->GetValue());

			GetInheritance(*classModule);

			classModule->DeleteVariables();

			std::vector<Model::cVariableModel*>::iterator it;

			for (it = m_varList.begin(); it < m_varList.end(); it++) {
				classModule->setVariables(*it);
			}
			m_varList.clear();

			if (m_edit == false)
				wxGetApp().setClassesModule(classModule);

			this->Close();
		}		
	}
	else {
		wxMessageBox(wxT("No Class Name Found."), wxT("This is an Error."));
	}
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON2 in CreateClass.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON2 in CreateClass. 
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3
 */

void CreateClass::OnCancelClick( wxCommandEvent& event )
{
    this->Close();
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3 in CreateClass.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3 in CreateClass. 
}


/*
 * Should we show tooltips?
 */

bool CreateClass::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap CreateClass::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CreateClass bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CreateClass bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon CreateClass::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CreateClass icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CreateClass icon retrieval
}

/*
 * Setup Class Creater for Edit Class
 */

void CreateClass::EditClass(const wxString& name)
{
    m_edit = true;
    
    mp_classNameTxt->Enable(false);
    mp_nameSpaceTxt->Enable(false);
    ClassSetup(name);
}

/*
 * Setup Create Class for Copy Class
 */

void CreateClass::CopyClass(const wxString& name)
{
    m_copy = true;
    ClassSetup(name);
}

/*
 * Setup the CreateClass for Edit or Copy
 */

void CreateClass::ClassSetup(const wxString& name)
{
    Model::cClassModel* tmp = wxGetApp().getClassModule(name);
    if (tmp == nullptr) {
        wxMessageBox(wxT("Error Class Not Found."), wxT("This is an Error."));
    }
    else {
        mp_classNameTxt->SetValue(tmp->getName());
        mp_nameSpaceTxt->SetValue(tmp->getNameSpace());
        mp_singletonChk->SetValue(tmp->getSingleton());

		PopulateInheritance(*tmp);
		PopulateVariables(*tmp);
    }
}

/*
 * Populate the Inheritance List
 */

void CreateClass::PopulateInheritanceList(const wxString& ignore /*= ""*/)
{
    mp_inheritanceLst->Clear();
    std::vector<Model::cClassModel*>& classesModule = wxGetApp().getClassesModule();
    std::vector<Model::cClassModel*>::iterator it;

    std::string nametmp;

    for (it = classesModule.begin(); it < classesModule.end(); it++) {
        if ((*it)->getName() != "") {
            nametmp = (*it)->getNameSpace();
            if (nametmp.empty() == false)
                nametmp += "::";
            nametmp += (*it)->getName();
            if (ignore != nametmp)
                mp_inheritanceLst->AppendString(nametmp);
        }
    }
}

/*
 * Get Class this Class inherits from
 */

void CreateClass::GetInheritance(Model::cClassModel& classModule)
{
    wxArrayInt intArray;
    mp_inheritanceLst->GetCheckedItems(intArray);

    wxString string;

    Model::cClassModel* tmp = nullptr;

    classModule.CleanInheritance();

    for (int count = 0; count < intArray.GetCount(); count++) {
        string = mp_inheritanceLst->GetString(intArray.Index(count));

        tmp = wxGetApp().getClassModule(string);
        if (tmp == nullptr)
            wxMessageBox(wxT("Error Class Not Found."), wxT("This is an Error."));
        else
            classModule.setInheritance(tmp);
    }    
}

/*
 * Populates the inherits list from
 */

void CreateClass::PopulateInheritance(Model::cClassModel& classModule)
{
    std::vector<Model::cClassModel*>& inheritance = classModule.getInheritance();
    
    std::vector<Model::cClassModel*>::iterator it;

    wxString nametmp;
    wxString selecttmp;

    for (it = inheritance.begin(); it < inheritance.end(); it++) {
        if ((*it) != nullptr) {
            if ((*it)->getName() != "") {
                nametmp = (*it)->getNameSpace();
                if (nametmp.empty() == false)
                    nametmp += "::";
                nametmp += (*it)->getName();

                for (int count = 0; count < mp_inheritanceLst->GetCount(); count++) {
                    selecttmp = mp_inheritanceLst->GetString(count);
                    if (selecttmp == nametmp)
                        mp_inheritanceLst->Check(count, true);
                }
            }
        }
    }
}


/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE1
 */

void CreateClass::OnConstChoiceSelected( wxCommandEvent& event )
{
	if (mp_constCh->GetCurrentSelection() == 1) {
		mp_setterChBox->Enable(false);
		mp_setterChBox->SetValue(false);
	}
	else {
		mp_setterChBox->Enable(true);
	}
////@begin wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE1 in CreateClass.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE1 in CreateClass. 
}


/*
 * Populates the variables list from
 */

void CreateClass::PopulateVariables(Model::cClassModel& classModel)
{
	std::vector<Model::cVariableModel*> tmpList = classModel.getVariables();
	std::vector<Model::cVariableModel*>::iterator it;

	Model::cVariableModel* var = nullptr;

	for (it = tmpList.begin(); it < tmpList.end(); it++) {
		var = (*it);
		m_varList.push_back(var);
		mp_varList->AppendString(var->StringBuild());
	}
}
