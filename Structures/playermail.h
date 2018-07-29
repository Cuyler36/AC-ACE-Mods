typedef struct PlayerMail {
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
} PlayerMail;