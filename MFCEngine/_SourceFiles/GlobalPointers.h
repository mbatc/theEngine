#pragma once
#include "Console.h"
#include "KeyboardInput.h"

#ifndef CONSOLE
extern console* Console;
#define CONSOLE
#endif

#ifndef KEYBOARD
extern KeyboardClient* kbd;
#define KEYBOARD
#endif