#include "aclib.h"
#include "player.h"

Player* Player1 = (Player*)0x81266420;

void __entry() {
	OSReport("Player struct size: %X", sizeof(Player));
	OSReport("Player1's name is %s", Player1->Name); // Also prints town name since it's not null terminated.
	OSReport("Player1's wallet has %d bells in it!", Player1->Wallet);
	OSReport("Player1 is %d bells in debt!", Player1->Debt);
	OSReport("Player1's first item id is %04X", Player1->Pockets[0]);
	OSReport("Player1's birthday is %d-%d", Player1->Birthday.Month, Player1->Birthday.Day);
	OSReport("Player1 has %d bells in savings!", Player1->Savings);
	OSReport("Done reporting on Player1! Goodbye.");
}