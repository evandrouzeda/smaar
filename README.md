# Trabalho com ROS

Abrir um terminal e executar o comando 
```
roscore
```

Abrir outro terminal e executar
```
rosrun image_converter mypublisher inimigo.png
```

Abrir outro terminal e executar
```
rosrun image_converter mysubscriber
```

caso de erro de nao encontrar os pacotes tente:
```
source devel/setup.bash
```
ou
```
source /opt/ros/noetic/setup.bash
```
lembre de compilar
```
catkin_make
```
