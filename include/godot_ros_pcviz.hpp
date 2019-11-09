#ifndef GODOT_TUTORIAL_H
#define GODOT_TUTORIAL_H

#include <Godot.hpp>
#include <Spatial.hpp>
#include <PackedScene.hpp>
#include <Ref.hpp>
#include <RandomNumberGenerator.hpp>
#include <ImmediateGeometry.hpp>

#include <opencv2/imgproc.hpp>

#include "ros/ros.h"
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/PointCloud.h>

#define USE_IMMEDIATE_GEOMETRY

namespace godot {

class GodotRosPcviz : public Spatial {
    GODOT_CLASS(GodotRosPcviz, Spatial)

private:
    float time_passed;
    ros::NodeHandle nh;
    ros::Publisher chatter_pub;
    ros::Subscriber cloud_sub;
    Ref<PackedScene> immediate_geometry_scene;
    ImmediateGeometry* immediate_geometry;

public:
    RandomNumberGenerator* rng;
    cv::Mat cm;

    static void _register_methods();

    GodotRosPcviz();
    ~GodotRosPcviz();

    void _init();
    void _ready();

    void _process(float delta);

    sensor_msgs::PointCloud latest_cloud;

    void cloud_cb(const sensor_msgs::PointCloud2ConstPtr& msg);
};

}

#endif
