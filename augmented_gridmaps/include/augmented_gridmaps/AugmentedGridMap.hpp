#pragma once
// ROS
#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/PointStamped.h"
#include "nav_msgs/OccupancyGrid.h"
#include "std_srvs/Empty.h"
#include "visualization_msgs/Marker.h"

#include <iostream>
namespace ros_augmented_gridmaps {

class AugmentedGridMap
{
  public:
  AugmentedGridMap(ros::NodeHandle& nodeHandle);
  ~AugmentedGridMap();
  
  private:
  // ROS stuff
  ros::NodeHandle& nodeHandle_;
  ros::Subscriber mapSubscriber;
  ros::Subscriber pointSubscriber;
  ros::Publisher augmented_map_pub;
  ros::Publisher augmented_metadata_pub;
  ros::Publisher obstacle_marker_pub;
  ros::Subscriber obstacleSubscriber;
  ros::ServiceServer clearServer;
  
  void saveMap(const nav_msgs::OccupancyGrid &map);   
  void addPointCallback(const geometry_msgs::PointStamped &punto);   
  bool clearMapCallback(std_srvs::Empty::Request& request,
        std_srvs::Empty::Response& response);
  void addObstacleToMap(geometry_msgs::PointStamped added_point);
  void makeObstaclesMarkers();

  std::vector<geometry_msgs::Point> obstacles;  
  float obstacle_radius;
  bool debug;
  nav_msgs::OccupancyGrid original_map;
  nav_msgs::MapMetaData map_metadata;
  nav_msgs::OccupancyGrid enhanced_map;
};
}
