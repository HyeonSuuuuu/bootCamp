#pragma once


typedef enum { MENU_EXIT, MENU_CALCULATION, } MY_MENU;

void EventLoopRun(void);
MY_MENU PrintMenu(void);

void Calculator();