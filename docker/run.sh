#!/bin/sh
env USER_ID=`id -u` \
    USER_NAME=`id -nu` \
    GROUP_ID=`id -g` \
    GROUP_NAME=`id -ng` \
    XSOCK=/tmp/.X11-unix \
    XAUTH=/tmp/.docker.xauth \
    sh -c '
    touch $XAUTH && \
    xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge - && \
    docker-compose run godot_ros_pcviz'
