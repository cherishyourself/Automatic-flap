# Automatic-flap
基于空速管MS4525DO的自动襟翼系统。开发板stm32f103c8t6,HAL库

# 前言
具体资料请查看
 [https://github.com/cherishyourself/Automatic-flap/tree/master](https://github.com/cherishyourself/Automatic-flap/tree/master)
开发板：stm32f103c8t6
空速计：MS4525DO
# 实物图与原理图
![在这里插入图片描述](https://img-blog.csdnimg.cn/dd3a5a5e44fb4cf5ace0f18f578e2237.jpeg)
![请添加图片描述](https://img-blog.csdnimg.cn/130ddf53edaa4d4eafb8cd63aeee1ea6.png)
# ==涉及的说明书和程序查看我上传的资源==
![在这里插入图片描述](https://img-blog.csdnimg.cn/c10ee2aba73045cdb34d1791313727c5.png)

# 一：硬件
## 1.1 在文件说明书的(poYBAGECmyqAD.......)和Hardware中查看主板理图
![在这里插入图片描述](https://img-blog.csdnimg.cn/7beb02c497ed431b8ab36f05e8ff9076.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/f2acb23e45c6490c8d664dbe0997c571.png)

 1. ==SUPPLY与GND之间连接一个100nf电容(电容距离传感器2cm之内)==
 2. ==SCL上拉电阻为4.7K或者10K（我用的4.7K可以，网上有说10K也可以的）==


# 二：软件 
**查看我上传程序中pree.h和pree.c文件**
## 2.1 pree.h文件

**【1】主要是在宏定义中修改对应的引脚**
![在这里插入图片描述](https://img-blog.csdnimg.cn/16363be51dbd44d48276465840994491.png)
## 2.2 pree.c文件
**【1】主要是修改你购买的MS4525DO的型号的参数**
![在这里插入图片描述](https://img-blog.csdnimg.cn/018213c8038a4039b31d0be026c2baf8.png)
**【2】型号参数参考说明书**

> 我的是A 001： 所以
>==p1 p2为16383*90%和16383*10%==
>  ==Pmax=1  Pmin=-1==

![在这里插入图片描述](https://img-blog.csdnimg.cn/1adf9c8db410421cae24de85e278dd10.png)

