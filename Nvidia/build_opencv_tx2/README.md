
1) install dependencies with install_deps.sh 

2) uncompress:
   tar xvzf opencv-3.4.6.tar.gz
   tar xvzf opencv_contrib-3.4.6.tar.gz

3) cd opencv-3.4.6 & mkdir build & cd build
   cp ../../build_opencv.sh ./

4) ./build_opencv.sh

5) time make -j3

6) sudo make install
