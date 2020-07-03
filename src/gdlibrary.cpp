#include "godot_ros_pcviz.hpp"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
    std::vector<std::string> arguments = {"godot_ros_pcviz"};
    std::vector<char*> argv;
    for (const auto& arg : arguments) {
      argv.push_back((char*)arg.data());
    }
    argv.push_back(nullptr);
    int argc = arguments.size();
    ros::init(argc, argv.data(), "godot_ros_pcviz");
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    godot::register_class<godot::GodotRosPcviz>();
}
