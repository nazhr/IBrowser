/****************************************************************************
 *   Copyright (C) 2014 by Jerry			                           		*
 *                                                                        	*
 *   This file is part of IBrowser.                                        	*
 *                                                                         	*
 *   IBrowser is private software.                                         	*
 *   program.  If not, see <https://github.com/jerrykk/IBrowser>.          	*
 *                                                                         	*
 *   IBrowser website: https://github.com/jerrykk/IBrowser                 	*
 ****************************************************************************/

#include "ibrowser/ibrowserrenderer.h"

#include <sstream>
#include <string>

#include <include/cef_dom.h>
#include <include/utils/util.h>

namespace ibrowserrenderer
{
	const char kFocusedNodeChangedMessage[] = "ClientRenderer.FocusedNodeChanged";

	namespace
	{

		class IBrowserRenderDelegate : public IBrowserApp::RenderDelegate 
		{
		public:
			IBrowserRenderDelegate()
				:	m_last_node_is_editable_(false) {}

			virtual void OnFocusedNodeChanged(	CefRefPtr<IBrowserApp>	app,
				CefRefPtr<CefBrowser>	browser,
				CefRefPtr<CefFrame>		frame,
				CefRefPtr<CefDOMNode>	node) 
				OVERRIDE 
			{
				bool is_editable = (node.get() && node->IsEditable());
				if (is_editable != m_last_node_is_editable_) 
				{
					// Notify the browser of the change in focused element type.
					m_last_node_is_editable_ = is_editable;
					CefRefPtr<CefProcessMessage> message =
						CefProcessMessage::Create(kFocusedNodeChangedMessage);
					message->GetArgumentList()->SetBool(0, is_editable);
					browser->SendProcessMessage(PID_BROWSER, message);
				}
			}

		private:
			bool m_last_node_is_editable_;

			IMPLEMENT_REFCOUNTING(IBrowserRenderDelegate);
		};

	}  // namespace

	void CreateRenderDelegates(IBrowserApp::RenderDelegateSet& delegates) 
	{
	  delegates.insert(new IBrowserRenderDelegate);
	}

}  // namespace client_renderer
