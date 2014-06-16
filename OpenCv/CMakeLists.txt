cmake_minimum_required(VERSION 2.8)
project( detectar )
find_package( OpenCV REQUIRED )

add_executable( detectar detectar.cpp )

SET(RASPICAM_CV $ENV{HOME}/git/robidouille/raspicam_cv)
SET(USERLAND $ENV{HOME}/git/raspberrypi/userland)
SET(CVBLOB $ENV{HOME}/cvblob/lib/libcvblob.so)
SET(WIRINGPI /usr/local/lib/libwiringPi.so.2.0)


include_directories(${RASPICAM_CV})
include_directories(/usr/local/include)

SET(MMAL_LIBS
    ${USERLAND}/build/lib/libmmal_core.so
    ${USERLAND}/build/lib/libmmal_util.so
    ${USERLAND}/build/lib/libmmal_vc_client.so
    ${USERLAND}/build/lib/libvcos.so)
SET(BCM_LIBS ${USERLAND}/build/lib/libbcm_host.so)
SET(GLES_LIBS ${USERLAND}/build/lib/libGLESv2.so)
SET(EGL_LIBS ${USERLAND}/build/lib/libEGL.so)
SET(DISPLAY_CAMERA_LIBS
    ${RASPICAM_CV}/libraspicamcv.a
    ${MMAL_LIBS} ${BCM_LIBS} ${OpenCV_LIBS} )


target_link_libraries( detectar	 ${LD_LIBRARY_PATH})
target_link_libraries( detectar	 ${OpenCV_LIBS})
target_link_libraries( detectar  ${DISPLAY_CAMERA_LIBS} ${WIRINGPI})
