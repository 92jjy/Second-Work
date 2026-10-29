#include <iostream>
#include "manager.hpp"
#include "ament_index_cpp/get_package_share_directory.hpp"

using namespace std;

int main(int argc, char ** argv) {
    std::string package_share_dir = ament_index_cpp::get_package_share_directory("plus_work");
    
    // config.yaml 的绝对路径
    std::string config_path = package_share_dir + "/config/config.yaml";
    
    // 构造
    manager lkk(config_path);
    
    return 0;
}