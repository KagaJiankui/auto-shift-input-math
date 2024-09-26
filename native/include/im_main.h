#pragma once
#ifndef __IM_MAIN_H
#define __IM_MAIN_H

#define DllExp __declspec(dllexport)
#define DllImp __declspec(dllimport)
#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

DllExp inline HKL getHKL(HWND hFgWindow);
DllExp int getIMConvStatus(HWND hFgWindow, HKL hKbdLayout);
DllExp void setIMbyLocale(int Loc);
DllExp int switchImConvStatus(HWND hFgWindow, HKL hKbdLayout, DWORD convStatus);

#ifdef __cplusplus
}
#endif

#endif // __IM_MAIN_H
