//
//  Common.cpp
//  System_test
//
//  Created by Mike Allison on 4/29/15.
//
//

#include "Common.h"
#include <boost/functional/hash.hpp>

namespace ec {
    
static TimeStepType sPrevTime = 0;

uint64_t getHash( const std::string &to_hash )
{
    static boost::hash<std::string> hasher;
    return hasher( to_hash );
}
    
TimeStepType getFrameTimeStep(){
    TimeStepType ret;
    auto s = ci::app::getElapsedSeconds();
    ret = s - sPrevTime;
    sPrevTime = s;
    if(ret > MAX_DELTA_TIME)ret=0.;
    return ret;
}

}