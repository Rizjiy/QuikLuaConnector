////=== Заголовочные файлы LUA ===================================================================================//
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
//		std::thread thr(SendToLua, L); //Запускает выполнение функции MyCallback() в отдельном потоке
//		thr.detach(); //Отсоединяет созданный поток от основного, делая его "фоновым"
//	}
//
//	static int SendToLua(lua_State *L)
//	{
//		lua_getglobal(L, "GetParams"); //Находит в стеке Lua функцию по ее названию и помещает ее наверх стека
//		int callbackRef = luaL_ref(L, LUA_REGISTRYINDEX); //Получает индекс функции в специальной внутренней таблице(реестре) Lua	
//
//		for (int i = 0; i < 3; i++)
//		{
//			lua_rawgeti(L, LUA_REGISTRYINDEX, callbackRef); //Достает функцию из реестра Lua по индексу и помещает в стек
//			lua_pushstring(L, "Привет из DLL"); //Добавляет в стек параметр, который будет передан функции
//			lua_call(L, 1, 1); //Вызывает выбранную функцию в скрипте QLua, передавая в нее 1 параметр (L - стек, 1 - количество передаваемых параметров, 1 - количество возвращаемых значений(нужно, чтобы обновлять стек))
//			Sleep(1000); //Пауза в 1 секунду
//		}
//
//		return 0; //Выход из функции
//	}
//
//
//
//private:
//	//lua_State *L;
//
//};
//
