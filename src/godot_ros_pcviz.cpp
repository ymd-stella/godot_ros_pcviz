#include <StaticBody.hpp>
#include <String.hpp>
#include <SpatialMaterial.hpp>
#include <Color.hpp>
#include <Texture.hpp> // Mesh.hpp depends this
#include <Mesh.hpp>

#include <sstream>

#include <sensor_msgs/point_cloud_conversion.h>

#include "godot_ros_pcviz.hpp"

using namespace godot;

void GodotRosPcviz::_register_methods()
{
    register_method("_ready", &GodotRosPcviz::_ready);
    register_method("_process", &GodotRosPcviz::_process);
    Ref<PackedScene> default_scene = PackedScene::_new();
    register_property<GodotRosPcviz, Ref<PackedScene>>("immediate_geometry", &GodotRosPcviz::immediate_geometry_scene, *default_scene);
}

GodotRosPcviz::GodotRosPcviz()
    :immediate_geometry(nullptr)
{}

GodotRosPcviz::~GodotRosPcviz()
{}

void GodotRosPcviz::_init()
{
    cloud_sub = nh.subscribe<sensor_msgs::PointCloud2>("/kitti/velo/pointcloud", 1000, &GodotRosPcviz::cloud_cb, this);
    rng = RandomNumberGenerator::_new();
    rng->randomize();
    std::vector<uchar> vec(256);
    for (int i = 0; i < vec.size(); i++)
    {
        vec[i] = i;
    }
    cv::applyColorMap(vec, cm, cv::COLORMAP_PARULA);
    // cv::applyColorMap(vec, cm, cv::COLORMAP_JET);
}

void GodotRosPcviz::_ready()
{
    Godot::print("ready");
    if (immediate_geometry_scene.is_valid() && immediate_geometry_scene->can_instance())
    {
        immediate_geometry = (ImmediateGeometry*)(immediate_geometry_scene->instance());
        add_child(immediate_geometry);
    }
}

void GodotRosPcviz::_process(float delta)
{
    ros::spinOnce();
    if (immediate_geometry != nullptr)
    {
        int intensity_index = -1;
        for (int i = 0; i < latest_cloud.channels.size(); i++)
        {
            if (latest_cloud.channels[i].name == "i")
            {
                intensity_index = i;
            }
        }
        immediate_geometry->clear();
        int i = 0;
        while (i < latest_cloud.points.size())
        {
            immediate_geometry->begin(Mesh::PRIMITIVE_POINTS, nullptr);
            for (int j = 0; i < latest_cloud.points.size() && j < 50000; i++, j++)
            {
                // ROS coordinate to Godot coordinate
                auto x = latest_cloud.points[i].x;
                auto z = latest_cloud.points[i].y;
                auto y = latest_cloud.points[i].z;
                if (intensity_index != -1)
                {
                    auto intensity = latest_cloud.channels[intensity_index].values[i];
                    auto idx = static_cast<uchar>(intensity * 255);
                    auto c = cm.at<cv::Vec3b>(0, idx);
                    immediate_geometry->set_color(Color(c[2] / 255., c[1] / 255., c[0] / 255., 1.0));
                }
                immediate_geometry->add_vertex(Vector3(x, y, z));
            }
            immediate_geometry->end();
        }
    }
}

void GodotRosPcviz::cloud_cb(const sensor_msgs::PointCloud2ConstPtr& msg)
{
    sensor_msgs::convertPointCloud2ToPointCloud(*msg, latest_cloud);
}
