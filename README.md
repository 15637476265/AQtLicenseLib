# AQtLicenseLib
一个Qt的license项目
1.通过cpuid和当前验证结果输出license文件，并验证
2.通过msvc2015环境编译
----------------------------------------------------------
使用方法
*如果你的include文件放在项目里
INCLUDEPATH   += "$$PWD\include" \
                 "$$PWD\include\src"
*在绝对路径
INCLUDEPATH   += "H:\Myself\license\include" \
                 "H:\Myself\license\include\src"
****************************************************
LIBS += "$$PWD\lib\license.lib"
----------------------------------------------------------
