#include<iostream>
#include<string>
#include<fstream> 
#include<yaml-cpp/yaml.h>
using namespace std;

class manager{
public:
    int a_ = 0;
    int b_ = 0;

    manager(const string & filepath){
        YAML::Node config; 
        if(!getfile(filepath)) {
            return; 
        }
        if (!formal(filepath, config)) {
            return; 
        }
        if (!less(filepath, config)) {
            return; 
        }
        if (!erro(filepath, config)) {
            return; 
        }                
        
        int result = function(a_, b_);
        cout << "此次运行结果为 " << result << endl;
    }

    bool getfile(const std::string& filepath){
        ifstream f(filepath);
        if(!f.good()){
            cout<<"无法找到配置文件"<<endl;
            return false;
        }
        return true;
    }

    bool formal(const std::string& filepath, YAML::Node& config){
        try {
            config = YAML::LoadFile(filepath); 
        } catch (const YAML::Exception&) { 
            cout << "yaml格式错误" << endl;
            return false;
        }
        return true;
    }

    bool less(const std::string& filepath, YAML::Node config){
        if(!config["a"] || !config["b"]){
            cout<<"参数缺失"<<endl;
            return false;
        }
        return true;
    }

    bool erro(const std::string& filepath, YAML::Node config){
        try {
            a_ = config["a"].as<int>();
            b_ = config["b"].as<int>();
        } catch (const YAML::TypedBadConversion<int>&) { 
            cout << "参数类型错误" << endl;
            return false;
        }
        return true;
    }

    int function(int a, int b){
        return a+b;
    }
};