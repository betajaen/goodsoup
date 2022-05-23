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

#include "../goodsoup.h"

namespace common
{
	
	bool checkFile(const char* path)
	{
		SDL_RWops* fp = SDL_RWFromFile(path, "rb");

		if (fp)
		{
			SDL_RWclose(fp);
			return true;
		}

		return false;
	}

	CFile openFileRead(const char* path)
	{
		return SDL_RWFromFile(path, "rb");
	}

	CFile openFileWrite(const char* path)
	{
		return SDL_RWFromFile(path, "wb");
	}

	void writeFile(CFile file, const void* data, uint32 length)
	{
		SDL_RWwrite(file, data, length, 1);
	}

	void readFile(CFile file, void* data, uint32 length)
	{
		SDL_RWread(file, data, length, 1);
	}

	void closeFile(CFile file)
	{
		if (file)
		{
			SDL_RWclose(file);
		}
	}

	bool isFileOpen(CFile file)
	{
		return file != NULL;
	}

	int32 seekFile(CFile file, int32 seek, int32 seekOffset)
	{
		return SDL_RWseek(file, seek, seekOffset) != -1;
	}

	int32 tellFile(CFile file)
	{
		return (int32)SDL_RWtell(file);
	}

}