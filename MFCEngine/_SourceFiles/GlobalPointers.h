#pragma once
#include "Console.h"
#include "KeyboardInput.h"
#include "MouseInput.h"

#ifndef CONSOLE
extern console* Console;
#define CONSOLE
#endif

#ifndef KEYBOARD
extern KeyboardClient* kbd;
#define KEYBOARD
#endif

#ifndef MOUSE
extern MouseClient* mouse;
#define MOUSE
#endif