/*
 *	Copyright (C) 2014 by Jonathan Naylor, G4KLX
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

#include "DongleThread.h"
#include "DStarDefines.h"
#include "Bleeper.h"

// A 3 kHz low pass filter at a sample rate of 48000 samples/sec. Calculated by the fir1 command in
// MATLAB.
// const wxFloat32 FIR_TAPS[] = {
// 	 0.001215122399171F,  0.001363519692447F,  0.001447384226195F,  0.001287712318712F,  0.000614680825630F,
// 	-0.000833383976996F, -0.003176495118124F, -0.006261958697776F, -0.009578203328048F, -0.012249770207721F,
// 	-0.013132705407240F, -0.011005254575316F, -0.004822958879920F,  0.006013373011413F,  0.021438048217733F,
// 	 0.040605942188804F,  0.061921094815680F,  0.083217403172960F,  0.102067175368858F,  0.116163746412471F,
// 	 0.123705527541065F,  0.123705527541065F,  0.116163746412471F,  0.102067175368858F,  0.083217403172960F,
// 	 0.061921094815680F,  0.040605942188804F,  0.021438048217733F,  0.006013373011413F, -0.004822958879920F,
// 	-0.011005254575316F, -0.013132705407240F, -0.012249770207721F, -0.009578203328048F, -0.006261958697776F,
// 	-0.003176495118124F, -0.000833383976996F,  0.000614680825630F,  0.001287712318712F,  0.001447384226195F,
// 	 0.001363519692447F,  0.001215122399171F};

/* Generated using GNU Octave

pkg load signal;
fsamp = 48000;
fcuts = [200 400 3000 3400];
mags = [0 1 0];
devs = [0.2 1 0.2];
[n,Wn,beta,ftype] = kaiserord(fcuts,mags,devs,fsamp);
n = n + rem(n,2);
hh = fir1(n,Wn,ftype,kaiser(n+1,beta),'noscale');
freqz(hh);
[H,f] = freqz(hh,1,1024,fsamp);
plot(f,abs(H))
disp(hh);
grid

*/
const wxFloat32 FIR_TAPS[] = {
  -0.00023487,  0.00013857, -0.00058714, -0.00236369 ,
  -0.00495938, -0.00799094, -0.01098265, -0.01344367 ,
  -0.01495143, -0.01522721, -0.01419068, -0.01198328 ,
  -0.00895517, -0.00561592, -0.00255587, -0.00034956 ,
   0.00054320, -0.00013774, -0.00239685, -0.00596681 ,
  -0.01033715, -0.01482543, -0.01868166, -0.02121067 ,
  -0.02189335, -0.02048686, -0.01708616, -0.01213422 ,
  -0.00637595, -0.00075947,  0.00370336,  0.00609781 ,
   0.00576505,  0.00243404, -0.00369535, -0.01193400 ,
  -0.02115698, -0.02992550, -0.03666402, -0.03987016 ,
  -0.03832949, -0.03130516, -0.01867470, -0.00099254 ,
   0.02053350,  0.04415199,  0.06775232,  0.08910178 ,
   0.10610527,  0.11705439,  0.12083333,  0.11705439 ,
   0.10610527,  0.08910178,  0.06775232,  0.04415199 ,
   0.02053350, -0.00099254, -0.01867470, -0.03130516 ,
  -0.03832949, -0.03987016, -0.03666402, -0.02992550 ,
  -0.02115698, -0.01193400, -0.00369535,  0.00243404 ,
   0.00576505,  0.00609781,  0.00370336, -0.00075947 ,
  -0.00637595, -0.01213422, -0.01708616, -0.02048686 ,
  -0.02189335, -0.02121067, -0.01868166, -0.01482543 ,
  -0.01033715, -0.00596681, -0.00239685, -0.00013774 ,
   0.00054320, -0.00034956, -0.00255587, -0.00561592 ,
  -0.00895517, -0.01198328, -0.01419068, -0.01522721 ,
  -0.01495143, -0.01344367, -0.01098265, -0.00799094 ,
  -0.00495938, -0.00236369, -0.00058714,  0.00013857 ,
  -0.00023487 
};

const unsigned int FIR_LEN = 101;//42U;

const wxFloat32 UPSAMPLE_AMP   = 6.0F;
const wxFloat32 DOWNSAMPLE_AMP = 0.9F;

CDongleThread::CDongleThread() :
wxThread(wxTHREAD_JOINABLE),
m_encodeCallback(NULL),
m_decodeCallback(NULL),
m_encodeAudio(DSTAR_RADIO_BLOCK_SIZE * 30U),
m_decodeData(VOICE_FRAME_LENGTH_BYTES * 30U),
m_bleep(true),
m_killed(false),
m_filter(FIR_TAPS, FIR_LEN)
{
}

CDongleThread::~CDongleThread()
{
}

void CDongleThread::setEncodeCallback(IEncodeCallback* callback)
{
	wxASSERT(callback != NULL);

	m_encodeCallback = callback;
}

void CDongleThread::setDecodeCallback(IDecodeCallback* callback)
{
	wxASSERT(callback != NULL);

	m_decodeCallback = callback;
}

unsigned int CDongleThread::getEncodeSpace() const
{
	return m_encodeAudio.freeSpace();
}

unsigned int CDongleThread::getDecodeSpace() const
{
	return m_decodeData.freeSpace();
}

unsigned int CDongleThread::writeEncode(const wxFloat32* audio, unsigned int length)
{
	wxASSERT(audio != NULL);

	return m_encodeAudio.addData(audio, length);
}

unsigned int CDongleThread::writeDecode(const unsigned char* ambe, unsigned int length)
{
	wxASSERT(ambe != NULL);

	return m_decodeData.addData(ambe, length);
}

void CDongleThread::setBleep(int bleep)
{
	m_bleep = bleep;
}

void CDongleThread::kill()
{
	m_killed = true;

	Wait();
}

void CDongleThread::reset()
{
	m_filter.reset();
}

void CDongleThread::sendBleep()
{
	wxFloat32 audio[DSTAR_RADIO_BLOCK_SIZE];
	unsigned int n;

	//CBleeper bleep(DSTAR_RADIO_SAMPLE_RATE, DSTAR_BLEEP_FREQ, DSTAR_BLEEP_LENGTH, DSTAR_BLEEP_AMPL);
	CBleeper bleep = CBleeper(DSTAR_RADIO_SAMPLE_RATE, m_bleep, DSTAR_BLEEP_AMPL);

	while ((n = bleep.getAudio(audio, DSTAR_RADIO_BLOCK_SIZE)) > 0U)
		m_decodeCallback->decodeCallback(audio, n);
}

// Convert from 8000 samples/sec to 48000 samples/sec
void CDongleThread::upSample(const wxFloat32* audioIn, wxFloat32* audioOut)
{
	unsigned int out = 0U;
	for (unsigned int in = 0U; in < DSTAR_AUDIO_BLOCK_SIZE; in++) {
		audioOut[out++] = m_filter.process(audioIn[in]) * UPSAMPLE_AMP;

		audioOut[out++] = m_filter.process(0.0F) * UPSAMPLE_AMP;
		audioOut[out++] = m_filter.process(0.0F) * UPSAMPLE_AMP;
		audioOut[out++] = m_filter.process(0.0F) * UPSAMPLE_AMP;
		audioOut[out++] = m_filter.process(0.0F) * UPSAMPLE_AMP;
		audioOut[out++] = m_filter.process(0.0F) * UPSAMPLE_AMP;
	}
}

// Convert from 48000 samples/sec to 8000 samples/sec
void CDongleThread::downSample(const wxFloat32* audioIn, wxFloat32* audioOut)
{
	unsigned int in = 0U;
	for (unsigned int out = 0U; out < DSTAR_AUDIO_BLOCK_SIZE; out++) {
		audioOut[out] = m_filter.process(audioIn[in++]) * DOWNSAMPLE_AMP;

		m_filter.process(audioIn[in++]);
		m_filter.process(audioIn[in++]);
		m_filter.process(audioIn[in++]);
		m_filter.process(audioIn[in++]);
		m_filter.process(audioIn[in++]);
	}
}
