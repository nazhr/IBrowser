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

#ifndef R_IBROWSER_IBROWSERRENDERER_H
#define R_IBROWSER_IBROWSERRENDERER_H

// ibrowser
#include "ibrowser/ibrowserapp.h"

// cef
#include <include/cef_base.h>

namespace ibrowserrenderer 
{
	// Message sent when the focused node changes.
	extern const char kFocusedNodeChangedMessage[];

	// Create the render delegate.
	void CreateRenderDelegates(IBrowserApp::RenderDelegateSet& delegates);

}  // namespace client_renderer

#endif  // R_IBROWSER_IBROWSERRENDERER_H
