#include "im_main.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
  HWND hFgWindow = GetForegroundWindow();
  HKL hKbdLayout = getHKL(hFgWindow);
  // int convStatus = getIMConvStatus(hFgWindow, hKbdLayout);
  int convStatus = ImmGetProperty(hKbdLayout, IGP_CONVERSION);
  printf("hFG: %08x hKbdLayout: %08x\nconvStatus: %08x\n", hFgWindow, hKbdLayout,
         convStatus);
  return 0;
}
