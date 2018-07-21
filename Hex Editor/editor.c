/*
PATCHER
.text
patch:
stwu r1, -0x20(r1)
stw r3, 0x1C(r1)
stw r4, 0x18(r1)
stw r0, 0x14(r1)
lis r3, OverwriteAddr@h
ori r3, r3, OverwriteAddr@l
lis r4, JumpOp@h
ori r4, r4, JumpOp@l
stw r4, 0(r3)
li r4, 8
bl ICInvalidateRange - 0x80002028
lis r3, STORAGE_ADDRESS@h
ori r3, r3, STORAGE_ADDRESS@l
li r4, 0x1000
bl ICInvalidateRange - 0x80002038 // invalidate everything to be safe
lis r3, STORAGE_ADDRESS@h
ori r3, r3, STORAGE_ADDRESS@l
lis r4, 0x8000
stw r4, 4(r3) // set initial current pointer as 0x80000000
lis r4, PRINT_STRING_VAL@h
ori r4, r4, PRINT_STRING_VAL@l
stw r4, 8(r3) // set "%02X" for the hex string
lis r4, OFFSET_STRING_VAL@h
ori r4, r4, OFFSET_STRING_VAL@l
stw r4, 0xD(r3) // set "%8X" for the offset string
li r4, 0
stw r4, 0(r3) // store current selected index as 0
lwz r0, 0x14(r1)
mtlr r0
lwz r3, 0x1C(r1)
lwz r4, 0x18(r1)
addi r1, r1, 0x20
blr

.data
this_address = 0x80002000
// AC Pointer Addresses
ICInvalidateRange = 0x80079CAC
gfxprint_init = 0x8005b7e4 - this_address // void* gfxinfo
gfxprint_open = 0x8005b878 - this_address// void* gfxinfo
gfxprint_close = 0x8005b8c4 - this_address// void* gfxinfo
gfxprint_color = 0x8005b1a0 - this_address// void* gfxinfo, R, G, B, A
gfxprint_locate8x8 = 0x8005b210 - this_address// void* gfxinfo, X cell, Y cell
gfxprint_printf = 0x8005b91c - this_address// void* gfxinfo, char* string, T args...
gfxopen = 0x804054b0 - this_address
gfxclose = 0x804054b8 - this_address

gfxbuff_ptr = 0x8148fde0

// Patch stuff
OverwriteAddr = 0x80486f30; // lis r3, 0x8130 // aQMgr_actor_move_main => addi r27, r1, 8
JumpOp = 0x4BB7B3BD; // bl 0x80002000

STORAGE_ADDRESS = 0x80001FE0
CURRENT_POINTER = STORAGE_ADDRESS + 4
PRINT_STRING = STORAGE_ADDRESS + 8 // %02X
OFFSET_STRING = STORAGE_ADDRESS + 0x10 // %8X
MAX_ROWS = 8 // how many rows are on screen at once
X_CELL_START = 3
Y_CELL_START = 6
PRINT_STRING_VAL = 0x25303258 // %02X
OFFSET_STRING_VAL = 0x25303858 // %08X
*/

#define BUTTON_NONE 0x0000
#define BUTTON_C_RIGHT 0x0001
#define BUTTON_C_LEFT 0x0002
#define BUTTON_C_DOWN 0x0004
#define BUTTON_C_UP 0x0008
#define BUTTON_R 0x0010
#define BUTTON_L 0x0020
#define BUTTON_X 0x0040
#define BUTTON_Y 0x0080
#define BUTTON_DPAD_RIGHT 0x0100
#define BUTTON_DPAD_LEFT 0x0200
#define BUTTON_DPAD_DOWN 0x0400
#define BUTTON_DPAD_UP 0x0800
#define BUTTON_START 0x1000
#define BUTTON_Z 0x2000
#define BUTTON_B 0x4000
#define BUTTON_A 0x8000

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

struct gfxinfo {
    u32 Pointer1;
    u32 Pointer2;
    u16 Half1;
    u16 Half2;
    u16 Half3;
    u8 Byte1;
    u8 Flags;
    u32 Pointer3;
};

struct hexEditor {
    u32 selectedIndex;
    u32 currentRAMPointer;
    char printString[5];
    char addressString[5];
    u8 enabled;
};

void gfxprint_init(struct gfxinfo* info);
void gfxprint_open(struct gfxinfo* info, void* nextGfxObject);
struct gfxinfo* gfxprint_close(struct gfxinfo* info);
void gfxprint_color(struct gfxinfo* info,  u8 R, u8 G, u8 B, u8 A);
void gfxprint_locate8x8(struct gfxinfo* info, u16 xCell, u16 yCell);
void gfxprint_printf(struct gfxinfo* info, const char* string, ...);
u32* _gfxopen(void* internalGfxInfo);
u32*  _gfxclose(void* internalGfxInfo, struct gfxinfo* gfxinfo);
int _chkTrigger(u32 button); // checks if the button was pressed on that frame
int _chkButton(u32 button); // checks if the button is down at all

static const u32* buttonTriggers = (u32 *)0x8148FE00;
static const u32* gfxbuff_ptr = (u32 *)0x8148fde0;
static struct hexEditor* editor = (struct hexEditor *)0x80001FE0;
static const u16 xCellStart = 4;
static const u16 yCellStart = 6;
static const u32 editorRows = 16;
static const u32 editorColumns = 16;

void checkZTrigger() {
	if (_chkTrigger(BUTTON_Z)) {
		editor->enabled = !editor->enabled;
	}
}

void checkTriggerButtons() {
	u32 NewPointer = editor->currentRAMPointer;
	u32 ChangeDelta = 0x100;
	if (_chkButton(BUTTON_B)) {
		ChangeDelta = 0x8000;
	}
	else if (_chkButton(BUTTON_A)) {
		ChangeDelta = 0x100000;
	}

	if (_chkTrigger(BUTTON_L)) {
		NewPointer -= ChangeDelta;
		if (NewPointer < 0x80000000) {
			NewPointer = 0x80000000;
		}
	}
	else if (_chkTrigger(BUTTON_R)) {
		NewPointer += ChangeDelta;
		if (NewPointer >= 0x81800000) {
			NewPointer = 0x817FFF00;
		}
	}
	editor->currentRAMPointer = NewPointer;
}

void checkCStick() {
	if (_chkTrigger(BUTTON_C_LEFT)) {
		if (editor->selectedIndex > 0) {
			editor->selectedIndex--;
		}
	}
	else if (_chkTrigger(BUTTON_C_RIGHT)) {
		if (editor->selectedIndex < 0xFF) {
			editor->selectedIndex++;
		}
	}
	else if (_chkTrigger(BUTTON_C_UP)) {
		if (editor->selectedIndex - 0x10 >= 0) {
			editor->selectedIndex -= 0x10;
		}
	}
	else if (_chkTrigger(BUTTON_C_DOWN)) {
		if (editor->selectedIndex + 0x10 <= 0xFF) {
			editor->selectedIndex += 0x10;
		}
	}
}

void checkDPad() {
	if (_chkTrigger(BUTTON_DPAD_DOWN)) {
		(*((u8 *)editor->currentRAMPointer + editor->selectedIndex))--;
	}
	else if (_chkTrigger(BUTTON_DPAD_UP)) {
		(*((u8 *)editor->currentRAMPointer + editor->selectedIndex))++;
	}
}

void init() {
	checkZTrigger(); // check for a Z button press to toggle if the editor is enabled
	if (editor->enabled != 0) {
		checkTriggerButtons();
		checkCStick();
		checkDPad();

	    u32* internalGfxInfo = (u32 *)*gfxbuff_ptr;
	    struct gfxinfo hexGfxInfo;
	    gfxprint_init(&hexGfxInfo);

	    u32* currentGfxObj = (u32 *)*(u32 *)((u8 *)internalGfxInfo + 0x2D0);
	    u32* newGfxObj = _gfxopen(currentGfxObj);
	    u32* currentGfxInfo = (u32 *)*(u32 *)((u8 *)internalGfxInfo + 0x2C0);
	    *(u32 *)((u8 *)internalGfxInfo + 0x2C0) += 8;
	    *((s32 *)currentGfxInfo) = -0x22000000;
	    *(u32 *)((u8 *)currentGfxInfo + 4) = (u32)newGfxObj;

	    gfxprint_open(&hexGfxInfo, newGfxObj);
	    gfxprint_color(&hexGfxInfo, 212, 175, 56, 255);
	    gfxprint_locate8x8(&hexGfxInfo, xCellStart, 4);
	    gfxprint_printf(&hexGfxInfo, editor->addressString, editor->currentRAMPointer + editor->selectedIndex);

	    u32 addressAdjust = 0;
	    for (s32 row = 0; row < editorRows; row++) {
	        for (s32 column = 0; column < editorColumns; column++) {
	        	if (addressAdjust == editor->selectedIndex) {
	        		gfxprint_color(&hexGfxInfo, 255, 150, 167, 255);
	        	}
	        	else {
	        		gfxprint_color(&hexGfxInfo, 255, 255, 255, 255);
	        	}
	            gfxprint_locate8x8(&hexGfxInfo, xCellStart + column * 2, yCellStart + row);
	            gfxprint_printf(&hexGfxInfo, editor->printString, *((u8 *)(editor->currentRAMPointer + addressAdjust)));
	            addressAdjust++;
	        }
	    }

	    struct gfxinfo* gfxInfoReturned = gfxprint_close(&hexGfxInfo); // returns the passed gfxinfo struct
	    *((s32 *)gfxInfoReturned) = -0x21000000;
	    u32* nextGfxObj = (u32 *)((u8 *)gfxInfoReturned + 8);
	    *((s32 *)((u8 *)gfxInfoReturned + 4)) = 0;
	    _gfxclose(nextGfxObj, gfxInfoReturned);
	    *(u32 *)((u8 *)internalGfxInfo + 0x2D0) = (u32)nextGfxObj;
	}
	__asm__("lis 3, 0x8130"); // this is the instruction I overwrote with the hook.
}