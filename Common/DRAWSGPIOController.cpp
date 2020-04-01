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
#ifndef DRAWSGPIOController_H

#include "DRAWSGPIOController.h"

#include <wiringPi.h>

CDRAWSGPIOController::CDRAWSGPIOController(unsigned int config) : CGPIOControllerBase(config),
m_outp1(false)
{

}

CDRAWSGPIOController::~CDRAWSGPIOController()
{

}

bool CDRAWSGPIOController::open()
{
    if(!CGPIOControllerBase::open()) {
        return false;
    }

    ::pinMode(DRAWS_SQUELCH_RIGHT, INPUT); //DRAWS Right
	::pinMode(DRAWS_SQUELCH_LEFT, INPUT); //DRAWS Left

    ::pullUpDnControl(DRAWS_SQUELCH_RIGHT, PUD_UP); //DRAWS Right
	::pullUpDnControl(DRAWS_SQUELCH_LEFT, PUD_UP); //DRAWS Left

	::pinMode(DRAWS_PTT_RIGHT, OUTPUT);//DRAWS Right
	::pinMode(DRAWS_PTT_LEFT, OUTPUT);//DRAWS Left

    return true;
}

void CDRAWSGPIOController::getDigitalInputs(bool& inp1, bool& inp2, bool& inp3, bool& inp4, bool& inp5)
{
    if(m_config == DRAWS_LEFT) {
        inp1 = ::digitalRead(DRAWS_SQUELCH_LEFT) == LOW;
    } else {
        inp1 = ::digitalRead(DRAWS_SQUELCH_RIGHT) == LOW;
    }
}

void CDRAWSGPIOController::setDigitalOutputs(bool outp1, bool outp2, bool outp3, bool outp4, bool outp5, bool outp6, bool outp7, bool outp8)
{
    if(m_outp1 != outp1){
        if(m_config == DRAWS_LEFT) {
            ::digitalWrite(DRAWS_PTT_LEFT, outp1 ? HIGH : LOW);
        } else {
            ::digitalWrite(DRAWS_PTT_RIGHT, outp1 ? HIGH : LOW);
        }
        m_outp1 = outp1;
    }
}

void CDRAWSGPIOController::close()
{
    CGPIOControllerBase::close();
}
#endif // !DRAWSGPIOController_H
#endif //GPIO