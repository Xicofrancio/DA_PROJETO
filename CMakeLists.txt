cmake_minimum_required(VERSION 3.23.2)
project(DA_PROJETO)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA_PROJETO main.cpp src/Menu.cpp include/Menu.h src/StationManager.cpp include/StationManager.h data_structures/Graph.h data_structures/Graph.cpp data_structures/Heap.cpp data_structures/Heap.h data_structures/MutablePriorityQueue.h data_structures/UFDS.cpp data_structures/UFDS.h data_structures/VertexEdge.cpp data_structures/VertexEdge.h include/Database.h src/Database.cpp src/Station.cpp include/Station.h src/NetWork.cpp include/NetWork.h)
