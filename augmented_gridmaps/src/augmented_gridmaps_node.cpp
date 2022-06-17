#include <ros/ros.h>
#include "augmented_gridmaps/AugmentedGridMap.hpp"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "augmented_gridmap_node");
  ros::NodeHandle nodeHandle;

  ros_augmented_gridmaps::AugmentedGridMap rosAgmentedGridmap(nodeHandle);

  ros::spin();
  return 0;
}
