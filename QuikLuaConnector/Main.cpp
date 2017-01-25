/*
В библиотеке реализовано 3 функции взаимодействия с Lua
1) CheckGotPARAMS() - Проверяет получил-ли C# последнюю строку параметров по инструменту (или еще не было отправлено ни одной строки), возвращает true, либо false
2) SendPARAMS() - Получает от QLua(Lua) строку инструмента из Текущей Таблицы Параметров и отправляет ее в C#
3) GetMilliseconds() - Возвращает текущее время работы ОС в миллисекундах

(c)QuikLuaCSharp.ru
*/
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "TcpSender.h"
#include "TcpListener.h"
//#include "LuaCallback.cpp"

//for TcpListener
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <strsafe.h>
using namespace std;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27014"
//

//=== Необходимые для Lua константы ============================================================================//
#define LUA_LIB
#define LUA_BUILD_AS_DLL

//=== Заголовочные файлы LUA ===================================================================================//
extern "C" {
#include "Lua\lauxlib.h"
#include "Lua\lua.h"
}

TcpListener tcpListener(27014);
TcpSender tcpSender(27015);

//=== Стандартная точка входа для DLL ==========================================================================//
BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

//=== Реализация функций, вызываемых из LUA ====================================================================//

// Получает строку инструмента из Текущей Таблицы Параметров и отправляет ее в C#
static int SendParams(lua_State *L)
{	
	
	// Считывает из Lua-стека строку инструмента
	const char *Params = lua_tostring(L, 1);

	//Посылаем во внешнее приложение
	tcpSender.Connect();
	tcpSender.Send(Params);
	tcpSender.Disconnect();

	return(0);
}

static int GetParams(lua_State *L)
{
	TcpListener tcpListener(27014);
	tcpListener.StartServer();
	const char* res = tcpListener.Listen();
	//tcpListener.StopServer();

	lua_pushstring(L, res);

	return(1);
}

static int StartServer(lua_State *L)
{
	tcpListener.StartServer();

	return 0;
}

static int StopServer(lua_State *L)
{
	tcpListener.StopServer();

	return 0;
}


//=== Регистрация реализованных в dll функций, чтобы они стали "видимы" для Lua ================================//
static struct luaL_reg ls_lib[] = {
	{ "SendParams", SendParams },
	{ "GetParams", GetParams },
	{ "StartServer", StartServer },
	{ "StopServer", StopServer },
	{ NULL, NULL }
};

//=== Регистрация названия библиотеки, видимого в скрипте Lua ==================================================//
extern "C" LUALIB_API int luaopen_QuikLuaConnector(lua_State *L) {
	luaL_openlib(L, "QuikLuaConnector", ls_lib, 0);
	return 0;
}
