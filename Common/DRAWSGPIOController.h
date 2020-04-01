/*
 *   Copyright (C) 2010-2015,2018, 2019, 2020 by Jonathan Naylor G4KLX
 *   Copyright (C) 2020 by Geoffrey Merck F4FXL - KC3FRA
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

#ifdef GPIO


#include "GPIOControllerBase.h"

 //Important ! Document https://nw-digital-radio.groups.io/g/udrc/files/DRAWSTech.pdf refers to BCM pin numbers !
// PTT pins map as follow
// BCM 23 => wPi 4 (left)
// BCM 12 => wPi 26 (right)
#define DRAWS_PTT_RIGHT 4
#define DRAWS_PTT_LEFT 26

//Important ! Document https://nw-digital-radio.groups.io/g/udrc/files/DRAWSTech.pdf refers to BCM pin numbers !
// Input pins map as follow
// BCM 25 => wPi 6 (left)
// BCM 27 => wPi 2 (right)
#define DRAWS_SQUELCH_LEFT 6
#define DRAWS_SQUELCH_RIGHT 2

#define DRAWS_LEFT 1
#define DRAWS_RIGHT 2

class CDRAWSGPIOController : public CGPIOControllerBase
{
public:
    CDRAWSGPIOController(unsigned int config);
    ~CDRAWSGPIOController();

    bool open();
    void getDigitalInputs(bool& inp1, bool& inp2, bool& inp3, bool& inp4, bool& inp5);
	void setDigitalOutputs(bool outp1, bool outp2, bool outp3, bool outp4, bool outp5, bool outp6, bool outp7, bool outp8);
    void close();

private:
    bool m_outp1;
};
 
#endif // GPIO