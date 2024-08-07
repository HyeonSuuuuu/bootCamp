#pragma once

#define BUFFER_MAX 1024

typedef enum { MENU_EXIT, MENU_CALCULATION, } MY_MENU;

void EventLoopRun(void);
MY_MENU PrintMenu(void);

void Calculator();