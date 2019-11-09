#include "godot_ros_pcviz.hpp"

int dummy_argc = 1;
char *dummy_argv[] = {"godot_ros_pcviz"};

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
    ros::init(dummy_argc, dummy_argv, "godot_ros_pcviz");
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    godot::register_class<godot::GodotRosPcviz>();
}
