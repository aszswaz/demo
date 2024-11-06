import pygame

AXIS_LEFT_X = 0
AXIS_LEFT_Y = 1
AXIS_LT = 4
AXIS_RT = 5
AXIS_ZERO = -3.051850947599719e-05

BTN_A = 0
BTN_B = 1
BTN_X = 2
BTN_Y = 3
BTN_LB = 4
BTN_RB = 5
BTN_BACK = 6
BTN_START = 7
BTN_LS = 8
BTN_RS = 9


def main():
    # 初始化 pygame 模块
    pygame.init()
    # 获取已连接到计算机的手柄
    pygame.joystick.init()

    # 打印所有手柄
    count = pygame.joystick.get_count()
    if count == 0:
        print("请连接手柄")
        return

    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    # 打印手柄名称
    print("已连接到手柄：", joystick.get_name())
    print("开始监听手柄事件")

    event_quit = False
    while not event_quit:
        for event in pygame.event.get():
            data = event.dict
            # print("event type:", event.type)

            # 处理轴运动事件
            if event.type == pygame.JOYAXISMOTION:
                axis = data["axis"]
                value = data["value"]
                if axis == AXIS_LT:
                    # 按下 LT 轴，低频颤动
                    joystick.rumble(0.7, 0, 0)
                elif axis == AXIS_RT:
                    # 按下 RT 轴，高频颤动
                    joystick.rumble(0, 0.7, 0)
                elif axis == AXIS_LEFT_X:
                    print(value)
                    if value == -3.051850947599719e-05:
                        print("归位")
                else:
                    print(data)
            elif event.type == pygame.JOYBUTTONDOWN:
                # 按钮按下事件
                btn_id = data["button"]
                print(btn_id)
                if btn_id == BTN_BACK:
                    # 按下返回键/菜单键，终止颤动
                    joystick.stop_rumble()
                elif btn_id == BTN_LB:
                    joystick.rumble(0.7, 0.7, 0)
                pass
            elif event.type == pygame.JOYHATMOTION:
                # 方向键
                value = data["value"]
                # 横向
                horizontal = value[0]
                # 纵向
                vertical = value[1]

                if horizontal == -1 and vertical == 0:
                    print("左")
                elif horizontal == 1 and vertical == 0:
                    print("右")
                elif horizontal == 0 and vertical == -1:
                    print("下")
                elif horizontal == 0 and vertical == 1:
                    print("上")
                elif horizontal == -1 and vertical == -1:
                    print("左下")
                elif horizontal == -1 and vertical == 1:
                    print("左上")
                elif horizontal == 1 and vertical == -1:
                    print("右下")
                elif horizontal == 1 and vertical == 1:
                    print("右上")
                elif horizontal == 0 and vertical == 0:
                    print("停止")
                    pass
            else:
                print(event)
            pass
        pass
    print("监听结束")
    pygame.joystick.quit()


# 获取已连接的手柄，并处理事件
if __name__ == '__main__':
    main()
