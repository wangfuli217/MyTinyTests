﻿#!/usr/bin/python2
# -*- coding: utf-8 -*-

"""
Description: 合并各个渠道(AMap/BaiduMap PlaceSearch迭代, wiki城市公交列表等)输出的文件, 生成定义的search_param_in.js文件, 供后续搜索使用
Author:     wangyoucao577@gmail.com
Created Date:   2016-12-30
Version:        2016-12-30
"""

import sys
import datetime
import fileinput
import re
import codecs
sys.path.append(sys.path[0] + r'\..')   #上级目录中加入搜寻列表, 以便于导入上级目录中的py模块
from files_operation import *

def print_list(list):
    for i in list:
        #print i.encode('utf-8')
        print i.decode('utf-8')

def format_list_to_specified_str(list, list_name):
    out_str = ""

    out_str += "search_param_in." + list_name + " = ["
    for l in list:
        out_str += ("\'" + l + "\'")
        if l != list[len(list) - 1]:
            out_str += (", ")
    out_str += ("]")
    return out_str

def read_lines_stations_locations_from_file(file_path):
    comments = ""
    expect_city = ""
    city_lines = []
    city_stations = []
    city_stations_location = []

    expect_city_pattern = re.compile("expect_city *=+ *\'(.+)\'", re.I)
    city_lines_pattern = re.compile("city_lines *=+ *\[(.*)\]", re.I)
    city_stations_pattern = re.compile("city_stations *=+ *\[(.*)\]", re.I)
    city_stations_location_pattern = re.compile("city_stations_location *=+ *\[(.*)\]", re.I)

    for line in fileinput.input(file_path, mode="rb"):
        #print line.decode('utf-8')
        line = line.decode('utf-8')
        if "//" in line:
            comments += (line)
            continue
        
        # 匹配expect_city
        match_result = re.search(expect_city_pattern, line)
        if match_result:
            expect_city = match_result.group(1)
            #print expect_city
            continue

        # 匹配 city_lines
        match_result = re.search(city_lines_pattern, line)
        if match_result:
            city_lines = match_result.group(1).replace(' ', '').replace('\'', '').split(',')
            #print_list(city_lines)
            continue
        
        # 匹配 city_stations
        match_result = re.search(city_stations_pattern, line)
        if match_result:
            city_stations = match_result.group(1).replace(' ', '').replace('\'', '').split(',')
            #print_list(city_stations)
            continue

        # 匹配 city_stations_location
        match_result = re.search(city_stations_location_pattern, line)
        if match_result:
            city_stations_location = match_result.group(1).replace(', ', '|').replace('\'', '').split('|')
            #print_list(city_stations_location)
            continue

    return (comments, expect_city, city_lines, city_stations, city_stations_location)

def main():
    if (len(sys.argv) < 3):
        print "Usage: "
        print "      python generate_search_param_in.py <out_file_name> <in_file_path[,in_file_path,...]>|<in_file_folder>" 
        print "Sample: "
        print "      python generate_search_param_in.py out_search_param_in.js D:\Lines_Stations_Locations_temp_AMap_20161230_163140.txt"
        print "      python generate_search_param_in.py out_search_param_in.js D:\city_lines_stations_location_src"
        return

    in_files_list = []
    if os.path.isdir(sys.argv[2]):
        (file_name_list, file_path_list) = scan_folder_to_get_indicated_files(sys.argv[2], ".txt")
        in_files_list += file_path_list
    else:
        in_files_list = sys.argv[2].split(',')

    out_file_path = sys.path[0] + "\\" + sys.argv[1]
    #print in_files_list
    #print out_file_path

    # 组织out_file的所有内容, 一次性写入文件
    out_file_all_str = "/** Generated on " + str(datetime.datetime.now()) + " **/ \n\n"
    out_file_all_str += "/**********************************************\n\n"
    out_file_all_str += "Generated from: \n\n"

    # 内容
    out_expect_city = None
    out_city_lines = []
    out_city_stations = []
    out_city_stations_location = []

    for f in in_files_list:
        print "analyze file: " + f 
        (comments, expect_city, city_lines, city_stations, city_stations_location) = read_lines_stations_locations_from_file(f)
        out_file_all_str += (comments + "\n\n")

        # expect_city check
        if out_expect_city == None:
            out_expect_city = expect_city
        elif out_expect_city != expect_city:
            print "Error: new expect_city: " + expect_city + ", from " + f + ", can not match with last expect_city: " + out_expect_city
            return

        # city_lines check
        for l in city_lines:
            if l not in out_city_lines:
                out_city_lines.append(l)
        #print "len(out_city_lines): " + str(len(out_city_lines)) + " after file: " + f

        # city_stations check
        for s in city_stations:
            if s not in out_city_stations:
                out_city_stations.append(s)
        #print "len(out_city_stations): " + str(len(out_city_stations)) + " after file: " + f

        # city_stations_location check
        for sl in city_stations_location:
            if sl not in out_city_stations_location:
                out_city_stations_location.append(sl)
        #print "len(out_city_stations_location): " + str(len(out_city_stations_location)) + " after file: " + f

    #拼接输出
    out_file_all_str += "**********************************************/\n\n"

    out_file_all_str += ("// city_lines_count = " + str(len(out_city_lines)) + "\n\n")
    out_file_all_str += ("// city_stations_count = " + str(len(out_city_stations)) + "\n\n")
    out_file_all_str += ("// city_stations_location_count = " + str(len(out_city_stations_location)) + "\n\n")

    out_file_all_str += "var search_param_in = {};\n\n"
    out_file_all_str += ("search_param_in.expect_city = \'" + out_expect_city + "\';\n\n")
    
    out_file_all_str += (format_list_to_specified_str(out_city_lines, "city_lines") + ";\n\n")
    out_file_all_str += (format_list_to_specified_str(out_city_stations, "city_stations") + ";\n\n")
    out_file_all_str += (format_list_to_specified_str(out_city_stations_location, "city_stations_location") + ";\n\n")

    #print out_file_all_str
            
    #写入文件
    f = codecs.open(out_file_path,'w+','utf-8')
    f.write(out_file_all_str)
    f.close()

    #Done!
    print "len(city_lines): " + str(len(out_city_lines)) + ", len(city_stations): " + str(len(out_city_stations)) + ", len(city_stations_location): " + str(len(out_city_stations_location))
    print "Generate file \"" + out_file_path + "\" succeed."

if __name__ == '__main__':
    main()
    

            