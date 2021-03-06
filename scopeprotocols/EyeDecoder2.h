/***********************************************************************************************************************
*                                                                                                                      *
* ANTIKERNEL v0.1                                                                                                      *
*                                                                                                                      *
* Copyright (c) 2012-2020 Andrew D. Zonenberg                                                                          *
* All rights reserved.                                                                                                 *
*                                                                                                                      *
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the     *
* following conditions are met:                                                                                        *
*                                                                                                                      *
*    * Redistributions of source code must retain the above copyright notice, this list of conditions, and the         *
*      following disclaimer.                                                                                           *
*                                                                                                                      *
*    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the       *
*      following disclaimer in the documentation and/or other materials provided with the distribution.                *
*                                                                                                                      *
*    * Neither the name of the author nor the names of any contributors may be used to endorse or promote products     *
*      derived from this software without specific prior written permission.                                           *
*                                                                                                                      *
* THIS SOFTWARE IS PROVIDED BY THE AUTHORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED   *
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL *
* THE AUTHORS BE HELD LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES        *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR       *
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
* POSSIBILITY OF SUCH DAMAGE.                                                                                          *
*                                                                                                                      *
***********************************************************************************************************************/

/**
	@file
	@author Andrew D. Zonenberg
	@brief Declaration of EyeDecoder2
 */

#ifndef EyeDecoder2_h
#define EyeDecoder2_h

#include "../scopehal/ProtocolDecoder.h"

class EyeWaveform : public WaveformBase
{
public:
	EyeWaveform(size_t width, size_t height, float center);
	virtual ~EyeWaveform();

	float* GetData()
	{ return m_outdata; }

	int64_t* GetAccumData()
	{ return m_accumdata; }

	void Normalize();

	size_t GetTotalUIs()
	{ return m_totalUIs; }

	float GetCenterVoltage()
	{ return m_centerVoltage; }

	size_t GetHeight()
	{ return m_height; }

	size_t GetWidth()
	{ return m_width; }

	void IntegrateUIs(size_t uis)
	{ m_totalUIs += uis; }

	float m_uiWidth;

	float m_saturationLevel;

protected:
	size_t m_width;
	size_t m_height;

	float* m_outdata;
	int64_t* m_accumdata;

	size_t m_totalUIs;
	float m_centerVoltage;
};

class EyeDecoder2 : public ProtocolDecoder
{
public:
	EyeDecoder2(std::string color);

	virtual void Refresh();

	virtual bool NeedsConfig();
	virtual bool IsOverlay();

	static std::string GetProtocolName();
	virtual void SetDefaultName();

	virtual bool ValidateChannel(size_t i, OscilloscopeChannel* channel);

	virtual double GetVoltageRange();
	virtual double GetOffset();

	virtual void ClearSweeps();

	//TODO: this should be a property of the capture, not the decode
	int64_t GetUIWidth()
	{ return m_uiWidth; }

	void SetWidth(size_t width)
	{
		m_width = width;
		SetData(NULL);
	}

	void SetHeight(size_t height)
	{
		m_height = height;
		SetData(NULL);
	}

	size_t GetWidth()
	{ return m_width; }

	size_t GetHeight()
	{ return m_height; }

	PROTOCOL_DECODER_INITPROC(EyeDecoder2)

protected:

	size_t m_width;
	size_t m_height;

	size_t m_uiWidth;

	std::string m_saturationName;
	std::string m_centerName;
};

#endif
