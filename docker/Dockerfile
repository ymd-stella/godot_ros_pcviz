ARG ROS_DISTRO
FROM ros:${ROS_DISTRO}

RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654 && \
    sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list' && \
    apt-get update && apt-get install -y \
    tmux \
    build-essential \
    ccache \
    cmake \
    git \
    pkg-config \
    wget \
    unzip \
    mlocate \
    sudo \
    gdb \
    ros-${ROS_DISTRO}-sensor-msgs \
    ros-${ROS_DISTRO}-tf \
    ros-${ROS_DISTRO}-tf2 \
    ros-${ROS_DISTRO}-tf2-sensor-msgs \
    ros-${ROS_DISTRO}-pcl-ros \
    ros-${ROS_DISTRO}-tf2-geometry-msgs \
    ros-${ROS_DISTRO}-cv-bridge \
    libasound2 \
    libpulse0 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

ARG group_id
ARG group_name
ARG user_id
ARG user_name
RUN groupadd -g ${group_id} ${group_name}
RUN useradd --gid ${group_id} --uid ${user_id} -M -d /home/${user_name} ${user_name} -s /bin/bash
RUN echo "${user_name}:${user_name}" | chpasswd
RUN sed -i-e 's/\(%sudo.*)\)/\1 NOPASSWD:/' /etc/sudoers
RUN visudo -c

COPY entrypoint.sh /work/entrypoint.sh
RUN chmod +x /work/entrypoint.sh

ENTRYPOINT ["/work/entrypoint.sh"]
CMD ["bash"]