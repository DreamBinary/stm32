---
# 一、现有条件
根据稚晖君的教程会得到以下目录：

![在这里插入图片描述](https://img-blog.csdnimg.cn/8ad9910b66a24d2990e44038e9181663.png)

点开 CMakeLists.txt，可以看到下面几行：

![在这里插入图片描述](https://img-blog.csdnimg.cn/4dd4084a9862436b90034ef96797f9b5.png)

只有这几行配置好，CMake 才能正确打包，Clion 才能提供代码提示等等。
可以点开 Core 文件夹看看里面的东西：

![在这里插入图片描述](https://img-blog.csdnimg.cn/69b29a5b193641c3859f2ce5977c933c.png)

这样有放置 .h 文件的 Inc 文件夹和放置 .c 文件的 Src 文件夹，这就明白 include_directories 的作用了。

---
# 二、Clion 和 Keil 结合
## 1. Keil 目录
正常的 Keil 目录是这样的：

![在这里插入图片描述](https://img-blog.csdnimg.cn/c296205445e6459d992c20b5f8334036.png)

## 2. 加入 Clion 生成文件
直接 Copy 以下文件(不用 Core 和 Drivers 目录)到上面 Keil 目录：

![在这里插入图片描述](https://img-blog.csdnimg.cn/50f5472346d34261b5417630e130ef56.png)

得到这样一个目录：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2859fb2955484bb2aa82fa73589b1bbc.png)
## 3. 复制文件
仿照 Core 目录写一个 Clion 目录：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20f3dec658344cca9d8e179019fa260b.png)
这个目录用于 Clion 写代码的时候使用，接下来将原来 Keil 目录中所有的 .h 和 .c文件复制到 Inc 和 Src 两个文件夹。
这里我用 python 写了一个小脚本编成了 copy2clion.exe，.py 和 .exe 都在 [Github](https://github.com/DreamBinary/stm32/tree/master/_Template_Clion_Keil_Init)了，有需要可以直接修改 .py 文件，然后用 auto-py-to-exe(超好用超好用)编译成 exe。
修改 CMakeLists.txt 文件如下：

![在这里插入图片描述](https://img-blog.csdnimg.cn/e76a3c8342ca46ada872161cf7cc9f77.png)

添加 User/main.c 文件方便直接编写 main.c 文件。

## 4. 构建项目
点击 Clion 上方的小锤子构建一下整个项目，点开 main.c 可以看到已经可以有代码提示和点击看源码的功能了:
![在这里插入图片描述](https://img-blog.csdnimg.cn/4d0739627d994d7788e83855689de8a4.png)

点击小锤子如果出现以下错误：

![在这里插入图片描述](https://img-blog.csdnimg.cn/b3ea88333ca24ecc91e4ada672207e3a.png)

需要在 stm32f10x.h 添加一行代码，原因报错也说了：

![在这里插入图片描述](https://img-blog.csdnimg.cn/bfa0942354df49bf98e13e2fc1501fec.png)
## 5. 编译烧录
程序的编译和烧录就要用 Keil 来执行了，所有操作都和之前一样，不过在 Clion 中有新建项目的时候，在 Keil 也要添加一下不然会报错。
