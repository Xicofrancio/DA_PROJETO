<<<<<<< HEAD
# Install script for directory: C:/Users/USER/Desktop/Universidade/2ano/da/DA_PROJETO
=======
# Install script for directory: C:/Users/pinta/OneDrive/Ambiente de Trabalho/trabalho-da2/DA_PROJETO
>>>>>>> 7ca299e6ec80d39f08036f9fbcfc73cb5bc6f4bc

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/DA_PROJETO")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
<<<<<<< HEAD
  set(CMAKE_OBJDUMP "C:/Program Files (x86)/JetBrains/CLion 2022.3.2/bin/mingw/bin/objdump.exe")
=======
  set(CMAKE_OBJDUMP "C:/Program Files/JetBrains/CLion 2022.2.3/bin/mingw/bin/objdump.exe")
>>>>>>> 7ca299e6ec80d39f08036f9fbcfc73cb5bc6f4bc
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD
file(WRITE "C:/Users/USER/Desktop/Universidade/2ano/da/DA_PROJETO/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "C:/Users/pinta/OneDrive/Ambiente de Trabalho/trabalho-da2/DA_PROJETO/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> 7ca299e6ec80d39f08036f9fbcfc73cb5bc6f4bc
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
