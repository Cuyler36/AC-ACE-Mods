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
typedef long s64;
typedef unsigned long u64;

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

struct randInfo{
	u32 seed;
	u8 set;
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

extern const u64* __qrand_idnum;

static const u32* buttonTriggers = (u32 *)0x8148FE00;
static const u32* gfxbuff_ptr = (u32 *)0x8148fde0;
static struct randInfo* info = (struct randInfo *)0x80001FE0;

void setSeed() {
	if (info->set == 0) {
		info->seed = *(u32 *) __qrand_idnum;
		info->set = 1;
	}
}

void init() {
	u32* internalGfxInfo = (u32 *)*gfxbuff_ptr;
	struct gfxinfo hexGfxInfo;
	gfxprint_init(&hexGfxInfo);

	u32* currentGfxObj = (u32 *)*(u32 *)((u8 *)internalGfxInfo + 0x2D0);
	u32* newGfxObj = _gfxopen(currentGfxObj);
	u32* currentGfxInfo = (u32 *)*(u32 *)((u8 *)internalGfxInfo + 0x2C0);
	*(u32 *)((u8 *)internalGfxInfo + 0x2C0) += 8;
	*((s32 *)currentGfxInfo) = -0x22000000;
	*(u32 *)((u8 *)currentGfxInfo + 4) = (u32)newGfxObj;

	// Print the seed info
	gfxprint_open(&hexGfxInfo, newGfxObj);
	gfxprint_color(&hexGfxInfo, 212, 175, 56, 255);
	gfxprint_locate8x8(&hexGfxInfo, xCellStart, 4);
	gfxprint_printf(&hexGfxInfo, "Seed: %d\nSet: %d", info->seed, info->set);

	struct gfxinfo* gfxInfoReturned = gfxprint_close(&hexGfxInfo); // returns the passed gfxinfo struct
	*((s32 *)gfxInfoReturned) = -0x21000000;
	u32* nextGfxObj = (u32 *)((u8 *)gfxInfoReturned + 8);
	*((s32 *)((u8 *)gfxInfoReturned + 4)) = 0;
	_gfxclose(nextGfxObj, gfxInfoReturned);
	*(u32 *)((u8 *)internalGfxInfo + 0x2D0) = (u32)nextGfxObj;
}