docker run -it mplapack:centos7            bash -x /home/docker/a.sh 2>&1 | tee log.centos7
docker run -it mplapack:centos8            bash -x /home/docker/a.sh 2>&1 | tee log.centos8
docker run -it mplapack:ubuntu2004         bash -x /home/docker/a.sh 2>&1 | tee log.ubuntu2004
docker run -it mplapack:ubuntu2004intel    bash -x /home/docker/a.sh 2>&1 | tee log.ubuntu2004intel
docker run -it mplapack:ubuntu2004mingw64  bash -x /home/docker/a.sh 2>&1 | tee log.ubuntu2004mingw64
docker run -it mplapack:ubuntu1804         bash -x /home/docker/a.sh 2>&1 | tee log.ubuntu1804
