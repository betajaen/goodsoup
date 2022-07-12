#include <stdio.h>
#include <stdint.h>

int main(int argc, char** argv) {
	FILE* fp = fopen("DPL.GST", "wb");

	uint8_t line[256];

	for(uint16_t col=0;col < 256;col++) {
		for(uint16_t mul=0;mul < 256;mul++) {
			uint32_t res = ( (col * mul) / 255 ) & 0xFF;
			line[mul] = (uint8_t) res;
		}
		fwrite(&line[0], 256, 1, fp);
	}

	fclose(fp);
}