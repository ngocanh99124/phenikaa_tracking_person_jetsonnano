# How to run
## Install
```
sudo apt-get install build-essential git libopencv-dev
git clone https://github.com/AlexeyAB/darknet.git
cd darknet
```
Replace Makefile in darknet folder with our Makefile in this repository
```
make
sudo cp libdarknet.so /usr/lib/
sudo cp include/darknet.h /usr/local/include/
sudo ldconfig 
```
Download, extracting:  
https://www.ccoderun.ca/download/darkhelp-1.0.0-2992-Source.tar.gz
```
sudo apt-get install cmake libtclap-dev libmagic-dev libopencv-dev
cd darkhelp-1.0.0-2992-Source
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
** edit in file darkhelp-1.0.0-2992-Source/src-tool/main.cpp : replace CV_FOURCC by cv::VideoWriter::fourcc
make
make package
sudo dpkg -i darkhelp-*.deb
cd ..
```
Download weights from this link   
https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v3_optimal/yolov4.weights  
Move this weights file into phenika_person_tracking_cpp/models  

## How to compile in linux
Under the ./phenika_person_tracking_cpp directory, do the following lines:
```
mkdir build
cd build
cmake ../
make
```
## How to use
Go to the bin diretory and launch the program with the following commands:  
```
./deep_sort /path/to/the/config/file
e.g.:
./deep_sort ../config/deepsort_config.txt
```
