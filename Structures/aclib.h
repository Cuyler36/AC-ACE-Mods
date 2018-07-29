#ifndef ACLIB_H
#define ACLIB_H

#include <stddef.h>
#include <stdint.h>

// standard C function prototypes are pulled from devkitpro header files

// GameCube functions
extern void ICInvalidateRange(void* start, uint32_t size);
extern void DCInvalidateRange(void* start, uint32_t size);
extern void OSReport(char*, ...);
extern int64_t OSGetTime();
extern void JUTReportConsole(char*);

// Animal Crossing functions
extern void Debug_mode_output(void *arg1);

#endif
