// ibrowser
#include "ibrowser/main.h"
#include "ibrowser/myframe.h"

// vc
#if WIN32
#include <Windows.h>
#endif

namespace ibrowser
{
	// Constructors
	MyApp::MyApp(){}
	MyApp::~MyApp(){}

	// private inherit
	bool MyApp::OnInit()
	{
		wxPoint pos;
		wxSize	size(1024, 768);
		// GetFullWinInfo(pos, size);
		MyFrame *frame = new MyFrame(NULL, -1, _("IBrowser"), 
			pos, size);
		frame->Show(true);
		SetTopWindow(frame);
		return true;
	}

	// private
	void MyApp::GetFullWinInfo(wxPoint &pos, wxSize &size)
	{
#if WIN32
		RECT clWorkAreaRect;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &clWorkAreaRect, 0); 
		if(clWorkAreaRect.right && clWorkAreaRect.bottom)
		{
			int		width = clWorkAreaRect.right - clWorkAreaRect.left;
			int		height = clWorkAreaRect.bottom - clWorkAreaRect.top;
			size.SetWidth(width);
			size.SetHeight(height);
		}

		// window position
		if(clWorkAreaRect.top || clWorkAreaRect.left)
		{
			pos.x = clWorkAreaRect.left;
			pos.y = clWorkAreaRect.top;
		}
#endif
	}

}


DECLARE_APP(ibrowser::MyApp)
IMPLEMENT_APP(ibrowser::MyApp)