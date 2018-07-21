/* https://stackoverflow.com/questions/38120764/specifying-section-name-for-code-in-gcc */

OUTPUT_FORMAT("elf32-powerpc")
OUTPUT_ARCH(powerpc:common)

ENTRY(init)
SECTIONS {
	. = 0x80002084;
	_chkTrigger = 0x80395ff8;
	_mPr_SetFreePossessionItem = 0x803e0ff0;
}