#ifndef R_IBROWSER_MAIN_H
#define R_IBROWSER_MAIN_H

#include <wx/wx.h>
namespace ibrowser
{
	class MyApp: public wxApp
	{
	public : 
		MyApp();
		virtual ~MyApp();
	private :
		virtual bool OnInit();

		/**
		 * @brief : full screen size and pos
		 */
		void GetFullWinInfo(wxPoint &pos, wxSize &size);
	};

}

#endif // R_IBROWSER_MAIN_H