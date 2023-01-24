#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>

/**
 * lua 的 C 动态库调用演示
 */

int lhello01(lua_State *l) {
    printf("Hello World\n");
    return 1;
}

int lhello02(lua_State *l) {
    lua_getglobal(l, "print");
    lua_pushstring(l, "Hello World");
    lua_call(l, 1, 0);
    return 1;
}

/*
 * lua 加载动态库时，会执行 luaopen_${MODULE_NAME} 函数来初始化模块，该函数的返回值必须是 int，0
 * 表示仅执行该函数，动态库不会被作为模块使用，非零数表示动态库作为 lua 模块使用。
 */
int luaopen_demo(lua_State *l) {
    // 将模块中的函数注册到 lua
    luaL_Reg lst[] = {
        {"hello01", lhello01},
        {"hello02", lhello02},
        {NULL, NULL}
    };
    luaL_newlib(l, lst);
    return 1;
}
