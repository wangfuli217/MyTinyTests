
#include <assert.h>
#include <string.h>
#include <arpa/inet.h>

#include <iostream>
#include <typeinfo>

#include "FlvTag.h"

#define FLV_VNAME(name) (#name)

FlvTag::FlvTag(char* buff, int len){
    assert(NULL != buff && len >= kMinTagLength);

    filter_ = buff[0] & 0x20;
    tag_type_ = buff[0] & 0x1F;
    data_size_ = ((buff[1] & 0xFF) << 16) | ((buff[2] & 0xFF) << 8) | (buff[3] & 0xFF);
    
    memcpy(&timestamp_, buff + 4, sizeof(timestamp_));
    timestamp_ = ntohl(timestamp_);

    stream_id_ = ((buff[8] & 0xFF) << 16) | ((buff[9] & 0xFF) << 8) | (buff[10] & 0xFF);   //always 0
}

void FlvTag::Dump()
{
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(filter_) << ": " << static_cast<int>(filter_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(tag_type_) << ": " << static_cast<int>(tag_type_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(data_size_) << ": " << data_size_ << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(timestamp_) << ": " << timestamp_ << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(stream_id_) << ": " << stream_id_ << std::endl;
}

uint32_t FlvTag::FetchPreviousTagSize(char * buff, int len){
    assert(NULL != buff && len >= kPreviousTagSizeTypeLength);

    uint32_t size;
    memcpy(&size, buff, sizeof(size));
    size = ntohl(size);
    return size;
}