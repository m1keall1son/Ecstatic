//
//  Manager.hpp
//  Arkanoid
//
//  Created by Mike Allison on 7/25/14.
//
//

#pragma once
#include "Common.h"
#include <map>

namespace ec {
    
    template <class T>
    class Manager {
    public:
        
        Manager( const std::string& name = "" );
        
        IdType save( const IdType &_key, const T& _obj );
        T retreive( const IdType &_key );
        bool contains( const IdType &_key );
        bool remove( const IdType &_key );
        
        const std::string& getName() const { return mName; }
        void list();
        
        virtual ~Manager(){}
        
    protected:
        
        std::map<uint32_t, T> mData;
        
        std::string mName;
        
        Manager(Manager const& copy);            // for safety
        Manager& operator=(Manager const& copy); // for safety
        
    };
    
    template <class T>
    Manager<T>::Manager( const std::string& name ): mName(name){}
    
    template <class T>
    IdType Manager<T>::save( const IdType &_key, const T& _obj ){
        mData.insert( std::make_pair( _key, _obj ) );
        return _key;
    }
    
    template <class T>
    T Manager<T>::retreive( const IdType &_key ){
        return mData.find( _key )->second;
    }
    
    template <class T>
    void Manager<T>::list(){
        ci::app::console()<<mName<<" listing manager items: "<<std::endl;
        for(auto item : mData){
            ci::app::console()<<typeid(T).name()<<" ID: "<< std::to_string(item.first) << std::endl;
        }
        
    }

    template<class T>
    bool Manager<T>::contains( const IdType &_key ){
        if( mData.count( _key ) > 0 ){
            return true;
        }else{
            return false;
        }
    }
    
    template<class T>
    bool Manager<T>::remove( const IdType &_key ){
        if( mData.count( _key ) == 0 ){
            return false;
        }else{
            mData.erase( _key );
            return true;
        }
    }
    
}//end namespace ignite