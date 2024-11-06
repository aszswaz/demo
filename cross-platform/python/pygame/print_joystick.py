import pygame

# 获取已连接的手柄，并打印手柄名称
if __name__ == '__main__':
    # 初始化 pygame 模块
    pygame.init()
    # 获取已连接到计算机的手柄
    pygame.joystick.init()

    # 打印所有手柄
    count = pygame.joystick.get_count()
    for i in range(count):
        joystick = pygame.joystick.Joystick(i)
        joystick.init()
        # 打印手柄名称
        print(joystick.get_name())
