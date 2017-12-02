如何添加一个图形?
修改Basic.h的enum Shape，在末尾增加你的图形的名字
建立图形的类，继承Graph，重写需要的函数
在Manager.h里修改string graphName[]
在Manager.cpp里修改void createGraph()
在Menu.h里修改菜单