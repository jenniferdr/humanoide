cmake_minimum_required(VERSION 2.8)
project( detectar )
find_package( OpenCV REQUIRED )

add_executable( detectar detectar.cpp )

include_directories(/usr/local/include)



target_link_libraries( detectar	 ${LD_LIBRARY_PATH})
target_link_libraries( detectar	 ${OpenCV_LIBS})
