# 简介

debian 软件包的打包方式

# 目录和文件介绍

```txt
DEBIAN：存放构建软件包的辅助文件
DEBIAN/control：保存软件包的信息，比如软件包名和版本
```

# 构建和安装软件包

```bash
# dpkg --build \<source directory\> \<package name\>
$ dpkg --build . demo.deb
$ dpkg -i demo.deb
```
