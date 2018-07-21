#define BUTTON_Z 0x2000

enum ItemFlag {
	None = 0,
	Present = 1,
	Quest = 2
};

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

u8 _chkTrigger(u16 button);
u8 _mPr_SetFreePossessionItem(void* player, u16 itemId, u8 itemFlags);

static const u32* currentPlayerPointer = (u32 *)0x8128C53C;
static const u32 firstLetterOffset = 0x52A;

u8 string2Nibble(s8 input) {
	if (input > 0x2F && input < 0x3A) {
		return input - 0x30;
	}
	else if (input > 0x40 && input < 0x47) {
		return input - 0x37;
	}
	else if (input > 0x60 && input < 0x67) {
		return input - 0x57;
	}
	return 0;
}

void string2Byte(s8* input, u8* outputBuffer, u32 count) {
	for (u32 i = 0; i < count; i++, input += 2, outputBuffer++) {
		*outputBuffer = (u8)((string2Nibble(*input) << 4) | string2Nibble(*(input + 1)));
	}
}

void init() {
	if (_chkTrigger(BUTTON_Z) != 0) {
		u8* player = (u8 *)*currentPlayerPointer;
		if (player != 0) {
			u16 itemId = 0;
			string2Byte((s8 *)(player + firstLetterOffset), (u8 *)&itemId, sizeof(itemId));
			_mPr_SetFreePossessionItem((u32 *)*currentPlayerPointer, itemId, None);
		}
	}
}