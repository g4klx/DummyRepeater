/*
 *   Copyright (C) 2010,2014 by Jonathan Naylor G4KLX
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

#ifndef	Bleeper_H
#define	Bleeper_H

#include <wx/wx.h>

const unsigned int  DSTAR_BLEEP_FREQ   = 2000U;
const unsigned int  DSTAR_BLEEP_LENGTH = 100U;
const float         DSTAR_BLEEP_AMPL   = 0.5F;

//https://en.wikipedia.org/wiki/Quindar_tones
const unsigned int  QUINDAR_BLEEP_FREQ   = 2475U;
const unsigned int  QUINDAR_BLEEP_LENGTH = 250U;
const float         QUINDAR_BLEEP_AMPL   = 0.25F;

class CBleeper {
public:
	CBleeper(unsigned int sampleRate, unsigned int bleepType, float amplitude);
	~CBleeper();

	unsigned int getAudio(wxFloat32* audio, unsigned int length);

	void reset();

private:
	unsigned int m_bleepType;
	wxFloat32*   m_audio;
	unsigned int m_length;
	unsigned int m_total;
	unsigned int m_position;
};

#endif
