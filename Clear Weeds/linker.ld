/* https://stackoverflow.com/questions/38120764/specifying-section-name-for-code-in-gcc */

OUTPUT_FORMAT("elf32-powerpc")
OUTPUT_ARCH(powerpc:common)

ENTRY(init)
SECTIONS {
	. = 0x80002000;
	mAGrw_ClearGrass = 0x80514B98;
}