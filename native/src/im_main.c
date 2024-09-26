#include "im_main.h"
#include <windef.h>

/**
 * Retrieves the keyboard layout associated with the given foreground window.
 *
 * @param hFgWindow The handle to the foreground window.
 * @return The keyboard layout handle associated with the window.
 *
 * @throws None
 */
inline HKL getHKL(HWND hFgWindow) {
  return GetKeyboardLayout(GetWindowThreadProcessId(hFgWindow, NULL));
}

/**
 * Retrieves the input method (IM) associated with the given window using the
 * ImmGetDefaultIMEWnd and ImmGetConversionStatus functions.
 * Caution: ImmGetContext can only get IME context inside **WINDOW OPENED WITHIN** the process, or it always return 0.
 *
 * @param hFgWindow The handle to the foreground window.
 * @return The input method associated with the window, or 0 if no IM is found.
 *
 * @throws None
 */
int getIMConvStatus(HWND hFgWindow, HKL hKbdLayout) {
  if (hFgWindow) {
    unsigned long imConversion = 0, imSentence = 0;
    unsigned long *lpfdwConversion = &imConversion;
    unsigned long *lpfdwSentence = &imSentence;
    HWND hIME= ImmGetDefaultIMEWnd(hFgWindow);
    HIMC hImc = ImmGetContext(hIME);
    if (hImc && hKbdLayout) {
      imSentence = ImmGetProperty(hKbdLayout, IGP_SENTENCE);
    }
    ImmGetConversionStatus(hImc, lpfdwConversion, lpfdwSentence);
    ImmReleaseContext(hIME, hImc);
    return (int)(imConversion);
  } else {
    return 0;
  }
}

void setIMbyLocale(int Loc) {
  HWND hwnd = GetForegroundWindow();
  LPARAM currentLayout = ((LPARAM)Loc);
  PostMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 0, currentLayout);
}

int switchImConvStatus(HWND hFgWindow, HKL hKbdLayout, DWORD convStatus) {
  if (hFgWindow) {
    unsigned long imConversion = 0, imSentence = 0;
    unsigned long *lpfdwConversion = &imConversion;
    unsigned long *lpfdwSentence = &imSentence;
    char flagSuccess = 0;
    HIMC hImc = ImmGetContext(hFgWindow);
    if (hImc && hKbdLayout) {
      imSentence = ImmGetProperty(hKbdLayout, IGP_SENTENCE);
      imConversion = ImmGetProperty(hKbdLayout, IGP_CONVERSION);
      if (LOWORD(imConversion) != convStatus) {
        flagSuccess = ImmSetConversionStatus(hImc, imConversion, imSentence);
      }
    }
    ImmReleaseContext(hFgWindow, hImc);
    return flagSuccess ? (int)(imConversion) : 0;
  } else {
    return 0;
  }
}