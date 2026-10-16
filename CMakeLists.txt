cmake_minimum_required(VERSION 3.15)
project(MiniRedis VERSION 0.1.0 LANGUAGES CXX)

# Modern C++20 standardını zorunlu kılalım
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include/ klasörünü başlık dosyaları için tanıtıyoruz
include_directories(include)

# 1. Asıl mantığı tutan bir kütüphane oluşturalım
add_library(kvstore_lib
    src/kvstore.cpp
)

# 2. Çalıştırılabilir ana programımızı oluşturalım
add_executable(mini_redis
    src/main.cpp
)

# 3. Ana programımıza kütüphanemizi bağlayalım
target_link_libraries(mini_redis PRIVATE kvstore_lib)