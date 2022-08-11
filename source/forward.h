/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef GS_FORWARD_H
#define GS_FORWARD_H

#include "types.h"

namespace gs {

	class ReadFile;
	class WriteFile;
	class DiskReader;
	class TagPair;

	struct String;

	template<typename T, typename Index = uint16>
	struct Buffer;

	template<typename T, uint32 N, typename Index = uint16>
	class FixedArray;

	template<typename T, typename Index = uint16>
	class Array;

	template<typename T, typename Index, Index Capacity>
	class InlineArray;

	template<typename T, typename Index, Index PO2_Capacity>
	struct RingArray;

	template<typename T>
	struct RingLog;

	template<typename T, typename Index, Index Capacity>
	class Stack;

	template<typename T>
	class Queue;

	template<typename T>
	class List;

	template<typename T, typename Index = uint16>
	struct ArrayPool;

	template<typename T, typename Index = uint16>
	class AllocatedPool;

	template<typename T>
	class LinkedListPool;

	template<typename T, typename Index>
	struct ReadSpan;

	template<typename T, typename Index>
	struct SequentialReadSpanReader;

	template<typename T, typename Index>
	struct ReadWriteSpan;

}

#endif