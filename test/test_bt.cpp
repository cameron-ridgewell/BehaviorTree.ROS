#include <behaviortree_ros/bt_service_node.h>
#include <behaviortree_ros/bt_action_node.h>
#include <ros/ros.h>

#include <fstream>
#include <streambuf>
#include <ros/package.h>

#include <geometry_msgs/Twist.h>

using namespace BT;

//-------------------------------------------------------------
// Simple Action to move on a Twist message
//-------------------------------------------------------------

class moveTwist : public BT::SyncActionNode
{
public:
  moveTwist(const std::string& name, const BT::NodeConfiguration& config)
  : BT::SyncActionNode(name, config) {}

  BT::NodeStatus tick() override {
    double value = 0.0;
    
    if( getInput("linear_x", value ) ){
      geometry_msgs::Twist msg;
      getInput("linear_x", msg.linear.x);
      getInput("linear_y", msg.linear.y);
      getInput("linear_z", msg.linear.z);
      getInput("angular_x", msg.angular.x);
      getInput("angular_y", msg.angular.y);
      getInput("angular_z", msg.angular.z);

      ros::NodeHandle nh;
      ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
      // std::cout << msg << std::endl;
      
      ros::Duration(0.1).sleep();

      for (int i = 0; i < 5; i++)
      {
        pub.publish(msg);
        ros::Duration(0.1).sleep();
      }

      pub.publish(msg);
      ros::Duration(0.5).sleep();

      return NodeStatus::SUCCESS;   
    }
    else{
      std::cout << "moveTwist FAILED "<< std::endl;
      return NodeStatus::FAILURE;
    }
  }

  static BT::PortsList providedPorts() {
    return  {
      InputPort<double>("linear_x"),
      InputPort<double>("linear_y"),
      InputPort<double>("linear_z"),
      InputPort<double>("angular_x"),
      InputPort<double>("angular_y"),
      InputPort<double>("angular_z")};
  }
};

// Retrieve the xml file from tree_filename inside the trees/ directory 
std::string tree_filename = "squaredance.xml";
std::ifstream treefile(ros::package::getPath("behaviortree_ros") + "/trees/" + tree_filename);
std::string xml_text((std::istreambuf_iterator<char>(treefile)), std::istreambuf_iterator<char>());

int main(int argc, char **argv)
{
  ros::init(argc, argv, "test_behavior_tree");
  ros::NodeHandle nh;

  BehaviorTreeFactory factory;

  factory.registerNodeType<moveTwist>("moveTwist");

  if(treefile.fail())
  {
    ROS_ERROR("File \"%s\" does not exist at %s", tree_filename.c_str(), 
      (ros::package::getPath("behaviortree_ros")+ "/trees/").c_str());
  }

  auto tree = factory.createTreeFromText(xml_text);

  NodeStatus status = NodeStatus::IDLE;

  while( ros::ok() && (status == NodeStatus::IDLE || status == NodeStatus::RUNNING))
  {
    ros::spinOnce();
    status = tree.tickRoot();
    std::cout << status << std::endl;
    ros::Duration sleep_time(0.01);
    sleep_time.sleep();
  }

  return 0;
}
