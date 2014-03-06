#ifndef R_IBROWSER_MYFRAME_H
#define R_IBROWSER_MYFRAME_H

#include <wx/wx.h>
#include <wx/event.h>

namespace ibrowser
{
	
	class MyFrame: public wxFrame
	{
	public :

		MyFrame(
			wxWindow *parent,
			wxWindowID id,
			const wxString& title, 
			const wxPoint& pos, 
			const wxSize& size,
			long style = wxSYSTEM_MENU |
			wxCLOSE_BOX |
			wxMAXIMIZE |
			wxMINIMIZE_BOX |
			wxMAXIMIZE_BOX |
			wxCAPTION |
			wxCLIP_CHILDREN | 
			wxSUNKEN_BORDER);

	private :

	private :
		DECLARE_EVENT_TABLE();
	};

}

#endif // R_IBROWSER_MYFRAME_H