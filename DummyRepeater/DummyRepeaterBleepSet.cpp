/*
 *   Copyright (C) 2010 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "DummyRepeaterBleepSet.h"

const unsigned int BORDER_SIZE   = 5U;
const unsigned int CONTROL_WIDTH = 200U;

CDummyRepeaterBleepSet::CDummyRepeaterBleepSet(wxWindow* parent, int id, const wxString& title, unsigned int bleep, unsigned int volume) :
wxPanel(parent, id),
m_title(title),
m_bleep(NULL)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	m_bleep = new wxChoice(this,  wxID_ANY, wxDefaultPosition, wxSize(CONTROL_WIDTH, -1));
	m_bleep->Append("Off");
	m_bleep->Append("IC91 Like");
	m_bleep->Append("Quindar");
	m_bleep->SetSelection(bleep);

	if(volume < 0) volume = 0;
	if(volume > 100) volume = 100;
	m_volume = new wxSlider(this, -1, volume, 0, 100, wxDefaultPosition, wxSize(CONTROL_WIDTH, -1), wxSL_HORIZONTAL | wxSL_LABELS);

	sizer->Add(m_bleep, 0, wxALL | wxALIGN_LEFT, BORDER_SIZE);
	sizer->Add(m_volume, 0, wxALL | wxALIGN_LEFT, BORDER_SIZE);

	SetAutoLayout(true);

	sizer->Fit(this);
	sizer->SetSizeHints(this);

	SetSizer(sizer);
}


CDummyRepeaterBleepSet::~CDummyRepeaterBleepSet()
{
}

unsigned int CDummyRepeaterBleepSet::getBleep() const
{
	return m_bleep->GetSelection();
}

unsigned int CDummyRepeaterBleepSet::getBleepVolume() const
{
	return m_volume->GetValue();
}

