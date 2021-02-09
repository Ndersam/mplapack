FROM ubuntu:20.04

# change following two lines
ARG GIT_EMAIL="maho.nakata@gmail.com"
ARG GIT_NAME="NAKATA Maho"

RUN apt update
RUN apt -y upgrade
RUN apt install -y sudo 
RUN apt install -y tzdata
# set your timezone
ENV TZ Asia/Tokyo
RUN echo "${TZ}" > /etc/timezone \
  && rm /etc/localtime \
  && ln -s /usr/share/zoneinfo/Asia/Tokyo /etc/localtime \
  && dpkg-reconfigure -f noninteractive tzdata

RUN apt install -y build-essential gfortran-9
RUN apt install -y autotools-dev automake libtool
RUN apt install -y git
RUN apt install -y ng-common ng-cjk emacs-nox

ARG DOCKER_UID=1000
ARG DOCKER_USER=docker
ARG DOCKER_PASSWORD=docker
RUN useradd -u $DOCKER_UID -m $DOCKER_USER --shell /bin/bash && echo "$DOCKER_USER:$DOCKER_PASSWORD" | chpasswd && echo "$DOCKER_USER ALL=(ALL) ALL" >> /etc/sudoers
USER ${DOCKER_USER}
RUN cd /home/$DOCKER_USER && git clone https://github.com/nakatamaho/mplapack.git
RUN echo "\n\
[user]\n\
        email = ${GIT_EMAIL}\n\
        name = ${GIT_NAME}\n\
" > /home/$DOCKER_USER/.gitconfig
RUN cd /home/$DOCKER_USER/mplapack && bash -x misc/reconfig.ubuntu20.04.sh
RUN cd /home/$DOCKER_USER/mplapack && make -j4
