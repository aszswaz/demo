#include <lua.h>
#include <stdio.h>
#include <lauxlib.h>

static void stack_dump(lua_State *l) {
    int i;
    // Get the depth of the stack.
    int top = lua_gettop(l);

    for (int i = 1; i <= top; i++) {
        int t = lua_type(l, i);
        switch (t) {
            case LUA_TSTRING:
                printf("%d: %s\n", i, lua_tostring(l, i));
                break;
            case LUA_TBOOLEAN:
                printf("%d: %d\n", i, lua_toboolean(l, 1));
                break;
            case LUA_TNUMBER:
                printf("%d: %g\n", i, lua_tonumber(l, i));
                break;
            default:
                printf("%d: type name: %s\n", i, lua_typename(l, t));
                break;
        }
    }
    printf("=========================================================\n");
}

/**
 * lua 的堆栈操作，如果栈索引为正数，索引的基准是栈底，如果栈索引为负数，索引的基准是栈顶。
 */
int main() {
    lua_State *l = luaL_newstate();

    lua_pushstring(l, "stack 01");
    lua_pushstring(l, "stack 02");
    lua_pushstring(l, "stack 03");
    lua_pushstring(l, "stack 04");

    stack_dump(l);

    // 在栈中添加一个指定栈元素的副本
    printf("lua_pushvalue:\n");
    lua_pushvalue(l, -4);
    stack_dump(l);

    // 把栈中的最后一个元素放到栈的指定位置，栈的大小减 1
    printf("lua_replace:\n");
    lua_replace(l, 3);
    stack_dump(l);

    // 将栈顶设置为指定的值，即修改栈中元素的数量，lua_settop(l, 0) 用于清空栈。当索引为负数时，用于从栈中弹出 n 个元素
    printf("lua_settop:\n");
    lua_settop(l, 6);
    stack_dump(l);

    /*
     * void lua_rotate(lua_State *L, int index, int n)
     * n 为正数，指定元素向栈顶方向转动。
     * n 为负数，指定元素向栈底方向转动。
     * “转动”的意思是指定元素和之后的元素都向下移动，空出来的位置填充 nil，超出栈大小的部分会被删除。
     */
    printf("lua_rotate:\n");
    lua_rotate(l, 3, 1);
    stack_dump(l);

    // 删除栈中元素
    printf("lua_remove:\n");
    lua_remove(l, -3);
    stack_dump(l);

    // 弹出栈中元素
    printf("lua_settop:\n");
    lua_settop(l, -5);
    stack_dump(l);
}
