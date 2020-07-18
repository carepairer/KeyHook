// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <stdio.h>



HHOOK g_hhk;
HMODULE g_hModule;
//键盘钩子回调函数
LRESULT CALLBACK KeyboardProc(int code,       // hook code
	WPARAM wParam,  // virtual-key code
	LPARAM lParam   // keystroke-message information、
)
{
	//虚拟键盘 我们的键盘在我们的Windows中用一些宏来表示
	unsigned int nVkCode = wParam;
	//表示按了A-Z
	char  szBuf[256];
	if (nVkCode > 'A' && nVkCode < 'Z')
	{
		sprintf_s(szBuf, "%c pressed", nVkCode);
		OutputDebugStringA(szBuf);
	}


	//调试输出工具，输出调试字符串
	//写日志
	OutputDebugString(TEXT("Keyboard pressed!!"));

	//调用下一个钩子
	return CallNextHookEx(g_hhk, code, wParam, lParam);
}


//dll 导出函数，提供给其他程序使用
BOOL MySetHook() {
	g_hhk = SetWindowsHookEx(WH_KEYBOARD,//钩子类型
		(HOOKPROC)KeyboardProc, //回调函数
		g_hModule, //表示第三方注入DLL,全局钩子使用, Dll的模块句柄
		0 //线程ID ，填0表示钩所有桌面程序
	);

	if (g_hhk == NULL)
	{
		return FALSE;
	}

	return TRUE;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		//当DLL被加载时调用
		//编写初始化操作
		g_hModule = hModule;
	}
	break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
	{
		//当DLL被释放时调用
		//编写反初始化操作
	}
        break;
    }
    return TRUE;
}

