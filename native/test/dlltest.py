from ctypes import cdll, windll, CDLL

myDll=CDLL("../build/windows-clang-x64/Debug/im-backend.dll")
user32Dll=windll.LoadLibrary("user32.dll")
imm32Dll=windll.LoadLibrary("imm32.dll")

hFgWnd=user32Dll.GetForegroundWindow()
hIMWnd=imm32Dll.ImmGetDefaultIMEWnd(hFgWnd)

convStatus=myDll.getIMConvStatus(hFgWnd, hIMWnd)

print(hIMWnd)
print(convStatus)