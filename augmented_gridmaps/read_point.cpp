#include "ros/ros.h"
#include "std_msgs/String.h"

#include <geometry_msgs/PointStamped.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "src/AugmentedGridmaps.cpp"
#include "augmented_gridmaps/AugmentedGridMap.hpp"


#include "geometry_msgs/Point.h"
#include "nav_msgs/OccupancyGrid.h"
#include "std_srvs/Empty.h"
#include "visualization_msgs/Marker.h"


using namespace std;

 
void LoadImages(const string &trajectory, vector<string> &position_x)
{
    ifstream fTimes; //ifstream : 读文件
    // 数据流读取文件
    fTimes.open(trajectory.c_str()); // //c_str是string类的一个函数,可以把string类型变量转换成char*变量 
    position_x.reserve(5000); //.reserve重新分配空间

    //循环读入timestamp文件到一个名为position_x的vector
    while(!fTimes.eof())
    {
        string s;
        //从流中读取一行内容到字符串
        getline(fTimes,s);

        //如果字符串不是空的，就写进流，读成double类型放入vector
        if(!s.empty())
        {
            //可注释
            stringstream ss;
            ss << s;
            ROS_INFO("%s",s.c_str());

	        position_x.push_back(s); 
        }
    }
}
 
 
int main(int argc, char **argv){

    vector<string> vposition;
 
    // LoadImages(string(argv[1]),vposition);
    LoadImages("/home/wm/project_ws/src/txt/point.txt",vposition);
 
    ros::init(argc,argv,"publish"); //ros::init()——你可以利用这个函数命名你的节点，这一步是初始化你的节点
    ros::NodeHandle n;   //为此进程的节点创建句柄 n
    ros::Publisher chatter_pub = n.advertise<geometry_msgs::PointStamped>("clicked_point",10000); 
    //在clicked_point话题中发布geometry_msgs::PointStamped的消息
    //主机告诉任何监听 clicked_point节点的节点，clicked_point节点将发布该主题的数据。
    //第二个参数是发布队列的大小，在这种情况下，如果发布得太快，缓冲最多1000条消息，之后将开始丢弃旧消息
    //NodeHandle :: advertise（）返回一个ros :: Publisher对象，它有两个目的：
    //1）它包含一个publish（）方法，允许你将消息发布到它创建的主题上；
    //2）当它超出范围时，它会自动退出。
    ros::Rate loop_rate(1); 
    //使用ros::Rate对象指定要循环的频率。跟踪自上次调用Rate :: sleep（）以来的持续时间。在这种情况下，告诉系统以10Hz运行。

    //vector<string>::iterator i = vposition.begin();
    //auto i = vposition.begin();

    geometry_msgs::PointStamped msg;
    msg.header.frame_id = "map";

    //可注释
    int num = vposition.size();
    printf("num = %d \n",num);

    int i = 0;  //默认情况下roscpp将安装一个SIGINT处理程序，该处理程序提供Ctrl-C处理，将导致ros :: ok（）返回false。
    while (ros::ok()){
        // if (i == (vposition.end() - 5)){
        if (i > (vposition.size() -1)){
            break;
        }


        string x, y, z;
    
        for (int j = 0; j < vposition.size(); j++)
        {
        x = vposition[i].substr(0, 5); //substr就是截取字符，20指的是在第几个字符上，13从第20个数据向后截取的长度。
        
        msg.point.x = atof(x.c_str());
        //X.push_back(atof(x.c_str())); //string类型转化为double型分为两步，先将string转为字符数组，然后数组转为double。
                                    //c_str将string转为数组，atof将数组转为double。
        y = vposition[i].substr(6, 11);
        msg.point.y = atof(y.c_str());
        
        msg.point.z = 0;
	
	//AugmentedGridMap::addObstacleToMap(msg);
        chatter_pub.publish(msg); //现在将消息广播给任何已连接的节点
        
 	 i ++; 
        ROS_INFO("i = %d \n",i);
          
        //ros::spin();
        loop_rate.sleep();
        }
	}
    return 0;
}


