/*
 *	Copyright (C) 2007-2009 Gabest
 *	http://www.gabest.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include "stdafx.h"
#include "GSVector.h"

GSVector4i GSVector4i::m_xff[17];
GSVector4i GSVector4i::m_x0f[17];

void GSVector4i::InitVectors()
{
	GSVector4i xff[17] =
	{
		GSVector4i(0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector4i(0x000000ff, 0x00000000, 0x00000000, 0x00000000),
		GSVector4i(0x0000ffff, 0x00000000, 0x00000000, 0x00000000),
		GSVector4i(0x00ffffff, 0x00000000, 0x00000000, 0x00000000),
		GSVector4i(0xffffffff, 0x00000000, 0x00000000, 0x00000000),
		GSVector4i(0xffffffff, 0x000000ff, 0x00000000, 0x00000000),
		GSVector4i(0xffffffff, 0x0000ffff, 0x00000000, 0x00000000),
		GSVector4i(0xffffffff, 0x00ffffff, 0x00000000, 0x00000000),
		GSVector4i(0xffffffff, 0xffffffff, 0x00000000, 0x00000000),
		GSVector4i(0xffffffff, 0xffffffff, 0x000000ff, 0x00000000),
		GSVector4i(0xffffffff, 0xffffffff, 0x0000ffff, 0x00000000),
		GSVector4i(0xffffffff, 0xffffffff, 0x00ffffff, 0x00000000),
		GSVector4i(0xffffffff, 0xffffffff, 0xffffffff, 0x00000000),
		GSVector4i(0xffffffff, 0xffffffff, 0xffffffff, 0x000000ff),
		GSVector4i(0xffffffff, 0xffffffff, 0xffffffff, 0x0000ffff),
		GSVector4i(0xffffffff, 0xffffffff, 0xffffffff, 0x00ffffff),
		GSVector4i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff),
	};

	GSVector4i x0f[17] =
	{
		GSVector4i(0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector4i(0x0000000f, 0x00000000, 0x00000000, 0x00000000),
		GSVector4i(0x00000f0f, 0x00000000, 0x00000000, 0x00000000),
		GSVector4i(0x000f0f0f, 0x00000000, 0x00000000, 0x00000000),
		GSVector4i(0x0f0f0f0f, 0x00000000, 0x00000000, 0x00000000),
		GSVector4i(0x0f0f0f0f, 0x0000000f, 0x00000000, 0x00000000),
		GSVector4i(0x0f0f0f0f, 0x00000f0f, 0x00000000, 0x00000000),
		GSVector4i(0x0f0f0f0f, 0x000f0f0f, 0x00000000, 0x00000000),
		GSVector4i(0x0f0f0f0f, 0x0f0f0f0f, 0x00000000, 0x00000000),
		GSVector4i(0x0f0f0f0f, 0x0f0f0f0f, 0x0000000f, 0x00000000),
		GSVector4i(0x0f0f0f0f, 0x0f0f0f0f, 0x00000f0f, 0x00000000),
		GSVector4i(0x0f0f0f0f, 0x0f0f0f0f, 0x000f0f0f, 0x00000000),
		GSVector4i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x00000000),
		GSVector4i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0000000f),
		GSVector4i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x00000f0f),
		GSVector4i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x000f0f0f),
		GSVector4i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f),
	};

	for (size_t n = 0; n < countof(xff); ++n)
		m_xff[n] = xff[n];

	for (size_t n = 0; n < countof(x0f); ++n)
		m_x0f[n] = x0f[n];
}

GSVector4 GSVector4::m_ps0123;
GSVector4 GSVector4::m_ps4567;
GSVector4 GSVector4::m_half;
GSVector4 GSVector4::m_one;
GSVector4 GSVector4::m_two;
GSVector4 GSVector4::m_four;
GSVector4 GSVector4::m_x4b000000;
GSVector4 GSVector4::m_x4f800000;
GSVector4 GSVector4::m_max;
GSVector4 GSVector4::m_min;

void GSVector4::InitVectors()
{
	m_ps0123 = GSVector4(0.0f, 1.0f, 2.0f, 3.0f);
	m_ps4567 = GSVector4(4.0f, 5.0f, 6.0f, 7.0f);
	m_half = GSVector4(0.5f);
	m_one = GSVector4(1.0f);
	m_two = GSVector4(2.0f);
	m_four = GSVector4(4.0f);
	m_x4b000000 = GSVector4(_mm_castsi128_ps(_mm_set1_epi32(0x4b000000)));
	m_x4f800000 = GSVector4(_mm_castsi128_ps(_mm_set1_epi32(0x4f800000)));
	m_max = GSVector4(FLT_MAX);
	m_min = GSVector4(FLT_MIN);
}

#if _M_SSE >= 0x500

GSVector8 GSVector8::m_half;
GSVector8 GSVector8::m_one;
GSVector8 GSVector8::m_x7fffffff;
GSVector8 GSVector8::m_x80000000;
GSVector8 GSVector8::m_x4b000000;
GSVector8 GSVector8::m_x4f800000;
GSVector8 GSVector8::m_max;
GSVector8 GSVector8::m_min;

void GSVector8::InitVectors()
{
	m_half = GSVector8(0.5f);
	m_one = GSVector8(1.0f);
	m_x7fffffff = GSVector8(_mm256_castsi256_ps(_mm256_set1_epi32(0x7fffffff)));
	m_x80000000 = GSVector8(_mm256_castsi256_ps(_mm256_set1_epi32(0x80000000)));
	m_x4b000000 = GSVector8(_mm256_castsi256_ps(_mm256_set1_epi32(0x4b000000)));
	m_x4f800000 = GSVector8(_mm256_castsi256_ps(_mm256_set1_epi32(0x4f800000)));
	m_max = GSVector8(FLT_MAX);
	m_min = GSVector8(FLT_MIN);
}

#endif

#if _M_SSE >= 0x501
GSVector8i GSVector8i::m_xff[33];
GSVector8i GSVector8i::m_x0f[33];

void GSVector8i::InitVectors()
{
	GSVector8i xff[33] =
	{
		GSVector8i(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x000000ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0000ffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x00ffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0x000000ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0x0000ffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0x00ffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0x000000ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0x0000ffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0x00ffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0x000000ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0x0000ffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0x00ffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x000000ff, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x0000ffff, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00ffffff, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x000000ff, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x0000ffff, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00ffffff, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x000000ff, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x0000ffff, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00ffffff, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x000000ff),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x0000ffff),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00ffffff),
		GSVector8i(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff),
	};

	GSVector8i x0f[33] =
	{
		GSVector8i(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0000000f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x00000f0f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x000f0f0f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0000000f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x00000f0f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x000f0f0f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0000000f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x00000f0f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x000f0f0f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0000000f, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x00000f0f, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x000f0f0f, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x00000000, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0000000f, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x00000f0f, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x000f0f0f, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x00000000, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0000000f, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x00000f0f, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x000f0f0f, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x00000000, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0000000f, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x00000f0f, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x000f0f0f, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x00000000),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0000000f),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x00000f0f),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x000f0f0f),
		GSVector8i(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f),
	};

	for (size_t n = 0; n < countof(xff); ++n)
		m_xff[n] = xff[n];

	for (size_t n = 0; n < countof(x0f); ++n)
		m_x0f[n] = x0f[n];
}
#endif
