#include "playermail.h"
#include "pattern.h"

typedef struct Birthday {
	uint8_t Month;
	uint8_t Day;
} Birthday;

typedef struct Player {
	char Name[8];
	char TownName[8];
	uint16_t Id;
	uint16_t TownId;
	uint8_t Gender;
	uint8_t Face;
	uint8_t ResetCount;
	uint8_t UnknownB;
	uint32_t Unknown1[20];
	uint16_t Pockets[15];
	uint16_t InventoryPadding;
	uint32_t InventoryFlags;
	uint32_t Wallet;
	uint32_t Debt;
	uint32_t QuestData[260]; // This needs to be researched.
	uint16_t HeldItem;
	uint16_t HeldItemPadding;
	char LastLetterHeaderFooter[0x38];
	PlayerMail Mail[10];
	uint16_t PocketBackground;
	uint8_t Unknown2[3];
	uint8_t ShirtLowerByte; // Used for patterns. Must be set.
	uint16_t Shirt;
	uint32_t Unknown3[6];
	uint16_t Unknown4;
	Birthday Birthday;
	uint32_t Unknown5[19];
	uint32_t ResetCode;
	uint32_t Bitmaps[77]; // Bitmaps for catalog, fish, insects, etc
	uint32_t Savings; // Aka Post Office Bank
	uint32_t Unknown6[4];
	Pattern Patterns[8];
	uint32_t Unknown7[34];
	uint8_t Tan;
	uint8_t Unknown8[3];
	uint32_t Unknown9[29];
} Player;