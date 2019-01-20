/* https://stackoverflow.com/questions/38120764/specifying-section-name-for-code-in-gcc */

OUTPUT_FORMAT("elf32-powerpc")
OUTPUT_ARCH(powerpc:common)

ENTRY(init)
SECTIONS {
	. = 0x80002084;
	gfxprint_init = 0x8005b7e4;
	gfxprint_open = 0x8005b878;
	gfxprint_close = 0x8005b8c4;
	gfxprint_color = 0x8005b1a0;
	gfxprint_locate8x8 = 0x8005b210;
	gfxprint_printf = 0x8005b91c;
	_gfxopen = 0x804054b0;
	_gfxclose = 0x804054b8;
	_chkTrigger = 0x80395ff8;
	_chkButton = 0x80395f58;
	__qrand_idum = 0x80217DE8;
}