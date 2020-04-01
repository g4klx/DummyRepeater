/*
 *	Copyright (C) 2012,2015 by Jonathan Naylor, G4KLX
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; version 2 of the License.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 */

#ifdef GPIO
#ifndef	GPIOController_H
#define	GPIOController_H

#include "GPIOControllerBase.h"

#include <wx/wx.h>

class CGPIOController : public CGPIOControllerBase {
public:
	CGPIOController(unsigned int config);
	virtual ~CGPIOController();

	bool open();

	void getDigitalInputs(bool& inp1, bool& inp2, bool& inp3, bool& inp4, bool& inp5);

	void setDigitalOutputs(bool outp1, bool outp2, bool outp3, bool outp4, bool outp5, bool outp6, bool outp7, bool outp8);

	void close();

private:
	bool         m_outp1;
	bool         m_outp2;
	bool         m_outp3;
	bool         m_outp4;
	bool         m_outp5;
	bool         m_outp6;
	bool         m_outp7;
	bool         m_outp8;
};

#endif
#endif