#include "ibrowser/myframe.h"

#include <wx/event.h>

namespace ibrowser
{
	BEGIN_EVENT_TABLE(MyFrame, wxFrame)
		// EVT_MENU(ID_Quit,  ibrowser::MyFrame::OnQuit)
		// EVT_MENU(ID_About, ibrowser::MyFrame::OnAbout)

	END_EVENT_TABLE()

	

	MyFrame::MyFrame(
		wxWindow *parent,
		wxWindowID id,
		const wxString& title, 
		const wxPoint& pos, 
		const wxSize& size,
		long style)
	: wxFrame(parent, id, title, pos, size, style)
	{
		CreateStatusBar();
		SetStatusText( _("Welcome to wxWidgets!") );
	}

}