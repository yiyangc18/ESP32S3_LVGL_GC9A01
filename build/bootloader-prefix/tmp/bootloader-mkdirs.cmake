# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Users/chery/esp/Espressif/frameworks/esp-idf-v4.4.3/components/bootloader/subproject"
  "D:/M_EMBEDDED/LVGL/ESP32/ESP32S3_LVGL_GC9A01/build/bootloader"
  "D:/M_EMBEDDED/LVGL/ESP32/ESP32S3_LVGL_GC9A01/build/bootloader-prefix"
  "D:/M_EMBEDDED/LVGL/ESP32/ESP32S3_LVGL_GC9A01/build/bootloader-prefix/tmp"
  "D:/M_EMBEDDED/LVGL/ESP32/ESP32S3_LVGL_GC9A01/build/bootloader-prefix/src/bootloader-stamp"
  "D:/M_EMBEDDED/LVGL/ESP32/ESP32S3_LVGL_GC9A01/build/bootloader-prefix/src"
  "D:/M_EMBEDDED/LVGL/ESP32/ESP32S3_LVGL_GC9A01/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/M_EMBEDDED/LVGL/ESP32/ESP32S3_LVGL_GC9A01/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
