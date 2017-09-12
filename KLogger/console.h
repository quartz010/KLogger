#pragma once

#include "stdafx.h"

extern HANDLE hOutput;

void console_init(void);
void DebugPrint(TCHAR *fmt, ...);