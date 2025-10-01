# shu-ces-archive

本仓库用于存放个人上海大学计算机与工程学院智能科学与技术的课程资料，包含但不限于课程PPT、实验、习题答案等。

你可能需要使用`git submodule`命令来克隆本仓库，以确保所有子模块（课程资料）都被正确下载。

```bash
git clone --recurse-submodules
```

若已经克隆了仓库但没有使用`--recurse-submodules`选项，可以使用以下命令来初始化和更新子模块：

```bash
git submodule update --init --recursive
```

由于我上课时随身携带的电脑为mac系统，所以部分实验代码进行了mac的适配，C++代码大部分使用的是cmake来组织

感谢[SHU-CES-Course-Files](https://github.com/Tristan-SHU/SHU-CES-Course-Files)和[SHU-CS-Source-Share](https://github.com/1051727403/SHU-CS-Source-Share)两个仓库的同学们的无私分享，部分课程资料来自于他们的仓库。