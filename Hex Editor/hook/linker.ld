/* https://stackoverflow.com/questions/38120764/specifying-section-name-for-code-in-gcc */

OUTPUT_FORMAT("elf32-powerpc")
OUTPUT_ARCH(powerpc:common)

SECTIONS {
	. = 0x80486F30;
	editor_main = 0x80002084;
}