﻿set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HOME $ENV{USERPROFILE})
set(CMAKE_TOOLCHAIN_FILE ${HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "")

add_executable(vk 
    "src/main.cpp"
    "src/Application.cpp"
    "src/Application.h"
    "src/include.h"
    "src/Utils.cpp"
    "src/Utils.h"
 "src/Vulkan/VulkanContext.cpp"
"src/Vulkan/VulkanContext.h" "src/Vulkan/Window.cpp" "src/Vulkan/Window.h" "src/Vulkan/Device.cpp" "src/Vulkan/Device.h" "src/Vulkan/Swapchain.h" "src/Vulkan/Swapchain.cpp" "src/Vulkan/Shader.h" "src/Vulkan/Shader.cpp")

target_include_directories(vk PUBLIC
    src/
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

target_link_libraries(vk PRIVATE 
    glfw 
    glm::glm-header-only 
    Vulkan::Vulkan
)

set(ASSET_DIR "${CMAKE_SOURCE_DIR}/assets")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
add_custom_command(
    TARGET vk POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${ASSET_DIR}"
    "${EXECUTABLE_OUTPUT_PATH}/assets"
)
