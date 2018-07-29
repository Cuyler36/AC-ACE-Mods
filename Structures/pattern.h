typedef struct Pattern {
	char Name[16];
	uint8_t Palette;
	uint8_t Unused[15];
	uint8_t ImageData[0x200]; // 32x32, each nibble corresponds to a palette color.
} Pattern;