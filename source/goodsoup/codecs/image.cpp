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

#define GS_FILE_NAME "image"

#include "forward.h"
#include "file.h"
#include "debug.h"

namespace gs
{

	void writeIff(const char* path, uint16 w, uint16 h, byte* palette, byte* data)
	{
		const uint32 imageSize = ((uint32) w) * ((uint32) h);
		const uint32 fileSize =
				4	// ILBM
				+ 8 + 20 // BMHD
				+ 8 + (3 * 256) // CMAP
				+ 8 + 4 // DPI
				+ 8 + imageSize // BODY
				;

		WriteFile file;
		file.open(path);

		if (file.isOpen() == false) {
			debug(GS_THIS, "Could not open IFF file for writing at %s", path);
			return;
		}

		debug(GS_THIS, "Path %s", path);
		debug(GS_THIS, "Width %ld Height %ld FileSize = %ld, ImageSize = %ld, HeaderSize = %ld", w, h, fileSize, imageSize, 20);


		file.writeTag("FORM");
		file.writeUInt32BE(fileSize);
		file.writeTag("ILBM");

		file.writeTag("BMHD");
		file.writeUInt32BE(20);
		file.writeUInt16BE(w); // width
		file.writeUInt16BE(h); // height
		file.writeInt16BE(0);	// x
		file.writeInt16BE(0);	// y
		file.writeByte(8);	// planes
		file.writeByte(0);	// masking
		file.writeByte(0);	// compression
		file.writeByte(0x80);	// pad
		file.writeUInt16BE(0); // transparent colour
		file.writeByte(1);	// x aspect
		file.writeByte(1);	// y aspect
		file.writeInt16BE(w); // page width
		file.writeInt16BE(h); // page height

		file.writeTag("CMAP");
		file.writeUInt32BE(3 * 256);
		file.writeBytes(palette, 3 * 256);

		file.writeTag("DPI ");
		file.writeUInt32BE(4);
		file.writeUInt16BE(256);
		file.writeUInt16BE(256);

		file.writeTag("BODY");
		file.writeUInt32BE(imageSize);

		uint32 y = h;
		byte* line = data;

		while(y--) {

			for(uint8 plane=0;plane < 8;plane++) {
				for(uint32 x=0;x < w;x+=8) {
					byte byte = 0;

					for(uint8 p=0;p < 8;p++) {
						byte <<= 1;

						uint8 val = line[x+p];
						val >>= plane;
						val &= 1;
						byte |= val;
					}

					file.writeByte(byte);
				}
			}

			line += w;
		}

		file.close();

	}

	void writeRaw(const char* path, uint16 w, uint16 h, byte* palette, byte* data)
	{
		const uint32 imageSize = ((uint32) w) * ((uint32) h);
		WriteFile file;
		file.open(path);

		if (file.isOpen() == false) {
			debug(GS_THIS, "Could not open RAW file for writing at %s", path);
			return;
		}

		file.writeBytes(palette, 3 * 256);
		file.writeBytes(data, imageSize);

		file.close();
	}
}

