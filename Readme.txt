步骤：
1.解压文件
2.在ert_rtw文件下新建文件夹bin build include lib src
3.将.c文件放在src下，.h文件放在include下（可以用已有的include），.so文件放在lib下，注意是所有文件。
4.按照CMAKELISTS链接好源文件、头文件和库文件
5.在build下
打开终端
——cmake ..
——make
6.遭遇报错：
-acados_sim_solver_bicycle_model.c:48:10:
No such file or directory
 #include "bicycle_model_model/bicycle_model_model.h"
          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-解决：将src中几个acados_开头文件中的bicycle_model_model/bicycle_model_model.h，改为bicycle_model_model.h（删除目录）

-implicit declaration of function ‘cos’等
-解决：在src中几个bicycle_model开头文件中添加math.h路径（和原先的math不同）：
#include </usr/include/math.h>

-simulink_model_closedloop_convert.h:171:5: error: unknown type name ‘RTWSfcnInfo’
-解决：在include中的simulink_model_closedloop_convert.h文件30行中添加#include "sfcn_bridge.h"

-simulink_model_closedloop_convert.c:270:9: warning: implicit declaration of function ‘ssSetStatesInfo2’; did you mean ‘_ssSetStatesInfo2’?
-解决：按提示找到文件，将里面的ssS前面加上_(4处，270 273 755 758)

-报找不到mxArray数据类型
-解决：在报错最外层文件中加入#include "rt_matrx.h"

7.生成/查找动态链接库
-首先编译acados：acados/build目录下打开终端，输入命令cmake ..成功后输入make 完成编译，重新编译是为了生成对应架构/操作系统的库文件
-在编译完成后，四个动态链接库位置如下：
(1)acados/build/external/hpipm/libhpipm.so
(2)acados/build/external/hpipm/libblasfeo.so
(3)acados/build/acados/acados/libacados.so

