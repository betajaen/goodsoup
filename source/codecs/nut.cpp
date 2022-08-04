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

#define GS_FILE_NAME "nut"

#include "../types.h"
#include "../debug.h"
#include "../endian.h"
#include "../file.h"
#include "../string.h"
#include "../disk.h"

#include "rle.h"
#include "buffer.h"
#include "array.h"

namespace gs
{

	int print = 0;

#if GS_RELEASE == 0
	static void debug_printNutBitmap(byte* bitmap, uint16 width, uint16 height) {

		for(uint16 y=0;y < height;y++) {

			for(uint16 x=0;x < width;x++) {
				byte b = *bitmap++;
				debug_write_hex(b);
			}
			debug_write_char('\n');
		}
		debug_write_char('\n');
	}

#endif


	uint32 decodeNutFrame44ToRLE2(byte* nutSrc, byte* rleDst, byte* tempGlyphBuffer, uint16 width, uint16 height, uint16 offsets[2]) {

		int16 len, t, s;
		byte *nextSrc, *x;
		byte *originalRleDst = rleDst;
		byte *originalTempGlyphBuffer = tempGlyphBuffer;
		int8 *writeRle = (int8 *) rleDst;

		// byte histogram[256] = { 0 };

		for (uint16 y = 0; y < height; y++) {

			t = READ_LE_UINT16(nutSrc);
			nutSrc += 2;
			nextSrc = nutSrc + t;

			if (t == 0)
				continue;

			len = width;
			x = tempGlyphBuffer;

			do {

				// Offset
				t = READ_LE_INT16(nutSrc);
				nutSrc += 2;
				len -= t;

				if (len <= 0)
					break;

				x += t;

				// Matte
				t = READ_LE_INT16(nutSrc) + 1;
				nutSrc += 2;
				len -= t;

				if (len < 0) {
					t += len;
				}


				while (t--) {
					s = *nutSrc;
					s = 1 + ((s - 0xE0) & 1);    // Colours seen are 0, 1, 224, 225
					// So if you do:
					//				x - 224
					//				then & 1
					//				it will be limited to 0..1
					//
					// histogram[s & 0xFF] = 1;
					*x = s;
					x++;
					nutSrc++;
				}

			} while (len > 0);


			tempGlyphBuffer += width;
			nutSrc = nextSrc;
		}

		for (uint8 i = 0; i < 2; i++) {
			offsets[i] = ((byte *) writeRle) - rleDst;

			uint8 colourIdx = i + 1;
			byte *img = originalTempGlyphBuffer;

			for (uint16 y = 0; y < height; y++) {

				uint8 count = 0;
				uint8 type = 0;

				for (uint16 x = 0; x < width; x++) {
					uint8 thisType = (*img == colourIdx ? 1 : 0);
					img++;

					if (x == 0) {
						count = 1;
						type = thisType;
						continue;
					}

					if (thisType == type) {
						count++;
						continue;
					}


					if (type == 0) {
						*writeRle = -((int8) count);
						writeRle++;
					} else {
						*writeRle = (int8) count;
						writeRle++;
					}

					count = 1;
					type = thisType;
				}


				if (count > 0) {
					if (type == 0 && count != width) {
						*writeRle = -((int8) count);
						writeRle++;
					} else if (type == 1) {
						*writeRle = (int8) count;
						writeRle++;
					}
				}

				*writeRle = 0;
				writeRle++;
			}

			*writeRle = -128;
			writeRle++;
		}

#if 0
		if (print == 1) {
			// for(uint16 i=0;i < 256;i++) {
			// 	byte count = histogram[i];
			// 	if (count != 0) {
			// 		debug(GS_THIS, "[%i]", i);
			// 	}
			// }

			debug_write_char('\n');
			debug_write_int(width);
			debug_write_char('x');
			debug_write_int(height);

			debug_write_char('\n');


			byte *dd = originalTempGlyphBuffer;
			for (uint16 y = 0; y < height; y++) {
				for (uint16 x = 0; x < width; x++) {
					byte t = (*dd);
					if (t == 0) {
						debug_write_char('.');
					} else {
						debug_write_char('0' + t);
					}

					dd++;
				}
				debug_write_char('\n');
			}
			debug_write_char('\n');

			debug_write_char('\n');
			int8 *tv = (int8 *) originalRleDst;

			while (tv < writeRle) {
				debug_write_int(*tv);
				debug_write_char(' ');
				tv++;
			}

			debug_write_char('\n');
		}
#endif

		return ((byte*) writeRle) - originalRleDst;
	}


	uint32 decodeNutFrame44ToRLE64(byte* nutSrc, byte* rleDst, byte* tempGlyphBuffer, uint16 width, uint16 height, int8 colourShift) {

		int16 len, t, s;
		byte *nextSrc, *x;
		byte *originalRleDst = rleDst;
		byte *originalTempGlyphBuffer = tempGlyphBuffer;
		byte *writeRle = rleDst;

		for (uint16 y = 0; y < height; y++) {

			t = READ_LE_UINT16(nutSrc);
			nutSrc += 2;
			nextSrc = nutSrc + t;

			if (t == 0)
				continue;

			len = width;
			x = tempGlyphBuffer;

			do {

				// Offset
				t = READ_LE_INT16(nutSrc);
				nutSrc += 2;
				len -= t;

				if (len <= 0)
					break;

				x += t;

				// Matte
				t = READ_LE_INT16(nutSrc) + 1;
				nutSrc += 2;
				len -= t;

				if (len < 0) {
					t += len;
				}


				while (t--) {
					s = *nutSrc;
					s = 1 + ((s - 0xE0) & 1);    // Colours seen are 0, 1, 224, 225
					// So if you do:
					//				x - 224
					//				then & 1
					//				it will be limited to 0..1
					//
					// histogram[s & 0xFF] = 1;
					*x = s;
					x++;
					nutSrc++;
				}

			} while (len > 0);


			tempGlyphBuffer += width;
			nutSrc = nextSrc;
		}

		for (uint8 i = 0; i < 2; i++) {
			uint8 colourIdx = i + 1;
			byte *img = originalTempGlyphBuffer;

			byte* before = writeRle;

			*writeRle = 0x40 | (i + colourShift);	// Set Colour and X=0, Y=0.
			writeRle++;
			uint8 wrotePixels = 0;

			for (uint16 y = 0; y < height; y++) {

				uint8 count = 0;
				uint8 type = 0;

				for (uint16 x = 0; x < width; x++) {
					uint8 thisType = (*img == colourIdx ? 1 : 0);
					img++;

					if (x == 0) {
						count = 1;
						type = thisType;
						continue;
					}

					if (thisType == type) {
						count++;
						continue;
					}


					if (type == 0) {
						*writeRle = 0x80 | count;
						writeRle++;
					} else {
						*writeRle = count;
						writeRle++;
						wrotePixels = 1;
					}

					count = 1;
					type = thisType;
				}


				if (count > 0) {
					if (type == 0 && count != width) {
						*writeRle = 0x80 | count;	// 0x80 | count
						writeRle++;
					} else if (type == 1) {
						*writeRle = count;			// 0x00 | count
						writeRle++;
						wrotePixels = 1;
					}
				}

				*writeRle = 0xC0 | 0x01;	// Skip one line.
				writeRle++;

			}

			if (wrotePixels == 0) {
				writeRle = before;
			}

		}

		*writeRle = 0xFF;	// End
		writeRle++;

#if 0
		if (print == 1) {
			// for(uint16 i=0;i < 256;i++) {
			// 	byte count = histogram[i];
			// 	if (count != 0) {
			// 		debug(GS_THIS, "[%i]", i);
			// 	}
			// }

			debug_write_char('\n');
			debug_write_int(width);
			debug_write_char('x');
			debug_write_int(height);

			debug_write_char('\n');


			byte *dd = originalTempGlyphBuffer;
			for (uint16 y = 0; y < height; y++) {
				for (uint16 x = 0; x < width; x++) {
					byte t = (*dd);
					if (t == 0) {
						debug_write_char('.');
					} else {
						debug_write_char('0' + t);
					}

					dd++;
				}
				debug_write_char('\n');
			}
			debug_write_char('\n');

			debug_write_char('\n');
			byte *tv = (byte *) originalRleDst;

			while (tv < writeRle) {
				debug_write_hex(*tv);
				debug_write_char(' ');
				tv++;
			}

			debug_write_char('\n');
		}
#endif

		return (writeRle - originalRleDst);
	}

	bool convertNutFontToRleFont(uint8 id) {

		print = (id == 1) ? 1 : 0;

		ReadFile nutFile;
		String nutPath = String::format(GS_GAME_PATH "RESOURCE/FONT%ld.NUT", id);
		nutFile.open(nutPath.string());

		if (nutFile.isOpen() == false) {
			error(GS_THIS, "Could not open %s file for reading!", nutPath.string());
			abort_quit_stop();
			return false;
		}

		WriteFile rleFile;
		String rlePath = String::format(GS_GAME_PATH "FONT%ld.GSF", id);
		rleFile.open(rlePath.string());

		if (rleFile.isOpen() == false) {
			error(GS_THIS, "Could not open %s file for writing!", rlePath.string());
			abort_quit_stop();
			return false;
		}

		DiskReader nutReader = DiskReader(nutFile, 0);
		Buffer<byte, uint16> characterImageData;
		characterImageData.setSize(64*64);	// Probably good size, based on tests/usage.
		Buffer<byte, uint16> characterNutData;
		characterNutData.setSize(2048);		// Probably good size, based on tests/usage.
		Buffer<byte, uint16> rleFontImageData;
		uint16 rleFontImageDataSize = 0;
		rleFontImageData.setSize(65535);	// Maximum size, and usually good guess.

		// Tag is ANIM
		TagPair animTag = nutReader.readSanTagPair();
		CHECK_IF_RETURN(animTag.isTag(GS_MAKE_ID('A','N','I','M')) == false, false, "This is not a NUT file! Missing ANIM tag.");

		// Tag is ADHR
		TagPair ahdrTag = nutReader.readSanTagPair();
		CHECK_IF_RETURN(ahdrTag.isTag(GS_MAKE_ID('A','H','D','R')) == false, false, "This is not a NUT file! Missing ADHR tag.");

		nutReader.skip(2); // Skip Unknown Field
		uint16 numCharacters = nutReader.readUInt16LE();	// Read number of characters.

		// numCharacters < 256
		CHECK_IF_RETURN_1(numCharacters > 256, false, "NUT file has too many %ld characters supported.", numCharacters);

		rleFile.writeUInt16BE(numCharacters); // Write number of characters.

		nutReader.seekEndOf(ahdrTag);

		// Read FRME tags
		for(uint16 i=0;i < numCharacters;i++) {

			TagPair frme = nutReader.readSanTagPair();	// Read FRME tag
			CHECK_IF_RETURN(frme.isTag(GS_MAKE_ID('F','R','M','E')) == false, false, "This is not a NUT file! Missing FRME tag.");

			TagPair fobj = nutReader.readSanTagPair();
			CHECK_IF_RETURN(fobj.isTag(GS_MAKE_ID('F','O','B','J')) == false, false, "This is not a NUT file! Missing FOBJ tag.");


			uint16 codec = nutReader.readUInt16LE();	// 2 0-1 :Read Codec
			// codec != 44
			CHECK_IF_RETURN_1(codec != 44, false, "This is not a supported NUT file! Codec %ld is unsupported", codec);

			nutReader.skip(4);							// 4 2,3,4,5 Skip unknown
			uint16 width = nutReader.readUInt16LE();	// 2 6, 7	 Read Width
			uint16 height = nutReader.readUInt16LE();	// 2 8, 9 Read Height
			nutReader.skip(4);							// 4  10,11,12,13,14	Skip unknown

			// Read NUT Image into temporary buffer, then decode to the end of rleFontImageData
			nutReader.readBytes(characterNutData.ptr(0), fobj.length - 14);
			int8 colourShift = 0;

			// In COMI - FONT0.NUT is only 1bpp which by default is shadow (1). Shift it to the primary.
			if (id == 0) {
				colourShift = -1;
			}

			uint16 size = decodeNutFrame44ToRLE64(characterNutData.ptr(0), rleFontImageData.ptr(rleFontImageDataSize), characterImageData.ptr(0),  width, height, colourShift);

			// For RLEImage2:-
			rleFile.writeByte(width & 0xFF);			// Write Width (as byte)
			rleFile.writeByte(height & 0xFF);			// Write Height (as byte)

#if defined(GS_BIG)
			rleFile.writeUInt16BE(rleFontImageDataSize);
#else
			rleFile.writeUInt16LE(rleFontImageDataSize);
#endif
			// Advance data a size.
			rleFontImageDataSize += size;

			// Clear image after use.
			uint32* imgData = (uint32*) characterImageData.ptr(0);
			uint32  imgDataSize = characterImageData.getSize() >> 2;
			while(imgDataSize--) {
				*imgData++ = 0;
			}

		}

#if defined(GS_BIG)
		rleFile.writeUInt16BE(rleFontImageDataSize);
#else
		rleFile.writeUInt16LE(rleFontImageDataSize);
#endif
		rleFile.writeBytes(rleFontImageData.ptr(0), rleFontImageDataSize);

		rleFile.close();
		nutFile.close();
		return true;
	}

}
