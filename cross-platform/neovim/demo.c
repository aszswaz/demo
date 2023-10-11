#include <stdio.h>

#include <luajit-2.1/lua.h>
#include <luajit-2.1/lauxlib.h>

/**
 * 从 neovim 调用 C 动态库。
 * neovim 不是直接使用 lua，而是使用 luajit，因此，在连接动态库时，不能连接 lua.so，只能连接 luajit.so，它们的函数地址完全不一致。
 * 除了头文件和动态库的路径以外，LuaJIT 和 lua 的 API 保持一致，因此 lua 标准 API 的使用可以参考 programming/lua 的代码。
 * GCC 编译指令：gcc -g3 -Werror -Wextra -fPIC -shared -lluajit demo.c -o demo.so
 * 也可以不连接动态库
 * GCC 编译指令：gcc -g3 -Werror -Wextra -fPIC -shared demo.c -o demo.so
 */

int hello(lua_State *l) {
    // 调用 lua 的 print 函数
    lua_getglobal(l, "print");
    lua_pushstring(l, "Hello World");
    // 设置 lua 函数的参数数量为 1，返回值数量为 0
    lua_call(l, 1, 0);
    return 1;
}

/**
 * lua 模块初始化
 */
int luaopen_demo(lua_State *l) {
    luaL_Reg module[] = {
        {"hello", hello},
        {NULL, NULL}
    };
    luaL_newlib(l, module);
    return 1;
}
