////=== ������������ ����� LUA ===================================================================================//
//#include "Lua\lauxlib.h"
//#include "Lua\lua.h"
//
//#include <thread>
//
//
//#pragma once
//class LuaCallback
//{
//public:
//	LuaCallback(lua_State *l)
//	{
//		//L = l;
//	}
//
//	static void StartServer(lua_State *L)
//	{
//		std::thread thr(SendToLua, L); //��������� ���������� ������� MyCallback() � ��������� ������
//		thr.detach(); //����������� ��������� ����� �� ���������, ����� ��� "�������"
//	}
//
//	static int SendToLua(lua_State *L)
//	{
//		lua_getglobal(L, "GetParams"); //������� � ����� Lua ������� �� �� �������� � �������� �� ������ �����
//		int callbackRef = luaL_ref(L, LUA_REGISTRYINDEX); //�������� ������ ������� � ����������� ���������� �������(�������) Lua	
//
//		for (int i = 0; i < 3; i++)
//		{
//			lua_rawgeti(L, LUA_REGISTRYINDEX, callbackRef); //������� ������� �� ������� Lua �� ������� � �������� � ����
//			lua_pushstring(L, "������ �� DLL"); //��������� � ���� ��������, ������� ����� ������� �������
//			lua_call(L, 1, 1); //�������� ��������� ������� � ������� QLua, ��������� � ��� 1 �������� (L - ����, 1 - ���������� ������������ ����������, 1 - ���������� ������������ ��������(�����, ����� ��������� ����))
//			Sleep(1000); //����� � 1 �������
//		}
//
//		return 0; //����� �� �������
//	}
//
//
//
//private:
//	//lua_State *L;
//
//};
//
