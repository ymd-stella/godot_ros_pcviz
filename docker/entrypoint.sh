#!/bin/bash

export HOME=/home/${USER_NAME}
cd ${HOME}

if [ ! -e ${HOME}/.bashrc_profile ]; then
    echo "#!/bin/bash"       >  ${HOME}/.bash_profile
    echo ". ${HOME}/.bashrc" >> ${HOME}/.bash_profile
fi

if [ ! -e ${HOME}/catkin_ws/src/CMakeLists.txt ]; then
    source /opt/ros/${ROS_DISTRO}/setup.bash
    mkdir -p catkin_ws/src
    cd catkin_ws/src
    catkin_init_workspace
    cd ..
    catkin_make
    source devel/setup.bash
    cd src/godot_ros_pcviz
    midir -p $HOME/install
    cd $HOME/install
    wget https://downloads.tuxfamily.org/godotengine/3.1.1/Godot_v3.1.1-stable_x11.64.zip
    unzip Godot_v3.1.1-stable_x11.64.zip
    rm Godot_v3.1.1-stable_x11.64.zip
    cd $HOME
    ln -s install/Godot_v3.1.1-stable_x11.64 godot
    # godot --gdnative-generate-json-api api.json
    # cp api.json catkin_ws/src/godot_ros_pcviz/thirdparty/godot-cpp/godot_headers
fi

tmux new-session "exec $@"
