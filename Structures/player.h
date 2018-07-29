typedef struct Mail {
	char Receipiant[8];
	char ReceipiantTownName[8];
	uint16_t ReceipiantID;
	uint16_t ReceipiantTownID;
	uint16_t Unknown;
	char Sender[8];
	char SenderTownName[8];
	uint16_t SenderID;
	uint16_t SenderTownID;
	uint16_t Unknown2;
	uint16_t Present;
	uint8_t Read; // Or opened
	uint8_t HeaderReceipiantNameStartOffset; // Tells how many characters to skip before placing the receipiant's name.
	uint8_t Unknonw3;
	uint8_t StationaryType; // Only the lower byte. 0x2000 | StationaryType
	char Header[0x18];
	char Body[0xC0];
	char Footer[0x20];
} Mail;

typedef struct Birthday {
	uint8_t Month;
	uint8_t Day;
} Birthday;

typedef struct Pattern {
	char Name[16];
	uint8_t Palette;
	uint8_t Unused[15];
	uint8_t ImageData[0x200]; // 32x32, each nibble corresponds to a palette color.
} Pattern;

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
	Mail Mail[10];
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