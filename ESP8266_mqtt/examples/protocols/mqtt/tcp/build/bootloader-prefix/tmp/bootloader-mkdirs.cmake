# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/jake/projects/Rauch_Logger/smoke_monitor/ESP8266_mqtt/components/bootloader/subproject"
  "/home/jake/projects/Rauch_Logger/smoke_monitor/ESP8266_mqtt/examples/protocols/mqtt/tcp/build/bootloader"
  "/home/jake/projects/Rauch_Logger/smoke_monitor/ESP8266_mqtt/examples/protocols/mqtt/tcp/build/bootloader-prefix"
  "/home/jake/projects/Rauch_Logger/smoke_monitor/ESP8266_mqtt/examples/protocols/mqtt/tcp/build/bootloader-prefix/tmp"
  "/home/jake/projects/Rauch_Logger/smoke_monitor/ESP8266_mqtt/examples/protocols/mqtt/tcp/build/bootloader-prefix/src/bootloader-stamp"
  "/home/jake/projects/Rauch_Logger/smoke_monitor/ESP8266_mqtt/examples/protocols/mqtt/tcp/build/bootloader-prefix/src"
  "/home/jake/projects/Rauch_Logger/smoke_monitor/ESP8266_mqtt/examples/protocols/mqtt/tcp/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/jake/projects/Rauch_Logger/smoke_monitor/ESP8266_mqtt/examples/protocols/mqtt/tcp/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/jake/projects/Rauch_Logger/smoke_monitor/ESP8266_mqtt/examples/protocols/mqtt/tcp/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
