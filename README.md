# girdmap

1、roslaunch augmented_gridmaps augmented_gridmap.launch 
2、rosrun map_server map_server map.yaml  #加载地图
3、rosrun augmented_gridmaps save_point #在rviz中使用publish point 然后会在txt下面保存为一个.txt文件
4、rosrun augmented_gridmaps read_point #会读取.txt文件并在rviz中显示，并判断需要查找的范围内出现了多少占据值为100的点
