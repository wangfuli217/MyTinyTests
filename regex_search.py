#!/usr/bin/python2
# -*- coding: utf-8 -*-

"""
Description:
    regex search tools, read line from each file of indicated folder then search string via regex
Author:     wangyoucao577@gmail.com
Created Date:   2016-07-14
Version:        2016-07-22
"""

import re
import fileinput


# import my own common file tools
from files_operation import *


#pattern_rule = r'\[curr_.{1,5}kbps_in:[0-9]{1,10}\]'
#dirpath = "F:\\serial_log\\"

def regex_search(to_check_files_path_list, pattern_rule, print_option):
    #print "start match, regex pattern--->" + pattern_rule + ", result:"
    pattern = re.compile(pattern_rule, re.I)
    matched_count = 0
    
    for file_path in to_check_files_path_list:
        line_number = 0
        for line in fileinput.input(file_path, mode="rb"):
            line_number += 1
            match_result = re.search(pattern, line)
            #print line
            if match_result:
                matched_count += 1
                if print_option == "nothing":
                    pass
                elif print_option == "group_0":
                    print file_path + "(" + str(line_number) + "): " + match_result.group(0)
                else:
                    print file_path + "(" + str(line_number) + "): " + line.strip('\n')
                #print file_path + "(" + str(line_number) + "): " + "value--->" +  match_result.group(1)
                
    return matched_count
    
def main():
    if (len(sys.argv) < 4):
        print "Usage: "
        print "      python regex_search.py <dir_path> <suffix[,suffix,...]> <partten>" 
        print "Sample: "
        print "      python regex_search.py ./ .log,.txt \"\[curr_.{1,5}kbps_in:([0-9]{1,10})\]\""
        return
        
    dirpath = sys.argv[1]
    to_check_files_suffix = sys.argv[2].split(',')
    pattern_rule = sys.argv[3]

    #get indicated files
    to_check_files_path_list = []
    for suffix in to_check_files_suffix:
        (file_name_list, file_path_list) = scan_folder_to_get_indicated_files(dirpath, suffix)
        to_check_files_path_list += file_path_list
    #print "to check files path: "
    #print to_check_files_path_list
    #print "\n\n"
    
    #start match
    regex_search(to_check_files_path_list, pattern_rule, "line")

if __name__ == '__main__':
    main()
else:
    print "Python2 Module Loaded: regex_search."
    