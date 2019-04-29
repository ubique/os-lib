//
// Created by gankedbymom on 30.04.19.
//

#include "dynamic_second.hpp"
#include <iostream>
extern "C"
void hello(){
    std::cout<<"Hi,I am second dynamic lib,you called me during the run-time"<<"\n";
}
