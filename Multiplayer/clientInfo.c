typedef struct clientItemInfo = {
	unsigned char enabled;
	unsigned short itemId;
	unsigned short worldPosition;
} CLIENT_ITEM_INFO;

typedef struct clientPlayerInfo = {
	float positionX;
	float positionY;
	float positionZ;
	
} CLIENT_PLAYER_INFO;

const static CLIENT_ITEM_INFO* itemInfo = (CLIENT_ITEM_INFO *)0x80001FD0;

void sendClientInfo(unsigned short itemId, unsigned short position) {
	itemInfo->enabled = 1;
	itemInfo->itemId = itemId;
	itemInfo->worldPosition = position;
}