#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>

/**
 * lua 的 C 动态库调用演示
 */

int lhello01(lua_State *l) {
    printf("Hello World\n");
    // 函数的返回值数量
    return 0;
}

/**
 * lua 调用 C 函数，然后再由 C 调用 lua 函数
 */
int lhello02(lua_State *l) {
    // 获取要调用的函数
    lua_getglobal(l, "print");
    // 设置函数的参数
    lua_pushstring(l, "Hello World");
    // 调用函数，设置参数的参数数量和返回值数量
    lua_call(l, 1, 0);
    return 0;
}

/*
 * lua 加载动态库时，会执行 luaopen_${MODULE_NAME} 函数来初始化模块。
 * 函数的返回值是 require 函数返回值的数量，如果为 0，require 的返回值就是 boolean。
 */
int luaopen_capi01(lua_State *l) {
    // 将模块中的函数注册到 lua
    luaL_Reg module[] = {
        {"hello01", lhello01},
        {"hello02", lhello02},
        {NULL, NULL}
    };
    luaL_newlib(l, module);
    return 1;
}
