# 简介

[LCD 液晶显示屏](https://item.taobao.com/item.htm?_u=p2pfas9b6010&id=607500389198&spm=a1z09.2.0.0.7d562e8dHmSdlj&skuId=5222086214082) 使用演示

屏幕尺寸：2 英寸

# 安装依赖

```bash
$ sudo apt install python3-spidev python3-numpy python3-gpiozero
```

# 设备接线

```
VCC -> 17
GND -> 20
DIN -> 19
CLK -> 23
CS  -> 24
D/C -> 22
RST -> 13
BL  -> 18
```

# 运行程序

```bash
# 显示颜色
$ python show_color/main.py
# 显示图片
$ python show_image/main.py
```
