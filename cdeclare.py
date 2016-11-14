#!/usr/bin/python
# -*- coding: utf-8 -*-

"""
Description:
Author:     wangyoucao577@gmail.com
Created Date:   2016-11-11
Version:        2016-11-10
"""

import sys

c_basic_types = ["void", "char", "short", "int", "unsigned", "long"]
c_basic_marks = ['*', '(', ')', '[', ']', "const", "volatile"]

def search_first_identifier(declare_array):
    left_stack = []
    right_stack = []
    first_identifier_found = False
    for c in declare_array:
        if first_identifier_found :
            right_stack.append(c)   # 左边是栈顶, 从最左边开始取
        elif (c not in c_basic_types and c not in c_basic_marks) :
            # find first indentifier
            first_identifier = c
            first_identifier_found = True
        else :
            left_stack.insert(0, c) # 左边是栈顶, 从最左边开始取
    #print left_stack
    #print right_stack
    #print first_identifier
    return (first_identifier, left_stack, right_stack)

def find_next_right_bracket_index(right_stack) :
    #print right_stack
    #print len(right_stack)
    match_right_bracket_index = 0
    for i in range(1, len(right_stack)):    # right_stack[0] mush be '('
        if (right_stack[i] == '('):
            match_right_bracket_index += 1
        elif (right_stack[i] == ')'):
            if match_right_bracket_index == 0:
                #print i
                return i
            else:
                match_right_bracket_index -= 1
        else:
            pass
    print "format error : no \')\' found"
    exit()

def analyse_expression(left_stack, right_stack):
    description_str = ""

    if len(right_stack) > 0:
        if (right_stack[0] == '[') : 
            if right_stack[1] == ']':
                description_str += ("an array, each element is ")
                right_stack.pop(0)
                right_stack.pop(0)
            elif right_stack[2] == ']':
                description_str += ("an array, with " + right_stack[1] + " elements, each element is ")
                right_stack.pop(0)
                right_stack.pop(0)
                right_stack.pop(0)
            else:
                print "format error: " + str(right_stack)
                exit()

        if (right_stack[0] == '(') :
            right_bracket_index = find_next_right_bracket_index(right_stack)
            description_str += ("an function ")
            if right_bracket_index == 1 :
                description_str += ", the function don't have any parameter, "
                right_stack.pop(0)
                right_stack.pop(0)
            else:
                description_str += ", the function have parameters \' "
                for i in range(1, right_bracket_index): #ignore '(' and ')'
                    description_str += (right_stack[i] + " ")
                description_str += " \' , "
                for i in range(0, right_bracket_index + 1):
                    right_stack.pop(0)
            #print description_str

    first_enter_return = False
    while ((len(left_stack) > 0)):
        if (left_stack[0] == '(' ):  
            if (right_stack[0] == ')'):
                #expression end
                left_stack.pop(0)
                right_stack.pop(0)
                return (description_str, left_stack, right_stack)
            else:
                print  "format error: " + str(right_stack)
                exit() 
        else:
            if (not first_enter_return) and len(right_stack) == 0:
                description_str += " return "
                first_enter_return = True

            if (left_stack[0] == "const"):
                description_str += " readonly "
                left_stack.pop(0)
                continue
            elif (left_stack[0] == "volatile"):
                description_str += " volatile"
                left_stack.pop(0)
                continue
            elif (left_stack[0] == '*'):
                description_str += " an pointer, point to "
                left_stack.pop(0)
                continue
            else :
                description_str += ( ' ' + left_stack[0] + ' ')
                left_stack.pop(0)


    #print left_stack
    #print right_stack
    #print description_str
    return (description_str, left_stack, right_stack)
    
def main():
    if (len(sys.argv) < 2):
        print "Usage: "
        print "      python cdeclare.py <'c declare string'>" 
        print "NOTE: split tokens with SPACE"
        print "Sample: "
        print "      python cdeclare.py 'char * const * ( * next ) ( )'"
        return
        
    declare_str = sys.argv[1]
    print "Going to analyse--->" + declare_str

    # step1: TODO: split tokens into an array
    # NOTE: simple to split via SPACE now
    declare_array = declare_str.split(' ');
    for c in declare_array:
        pass
        #print c

    # step2: TODO: search the array as the flowchart, find first identifider
    (first_identifier, left_stack, right_stack) = search_first_identifier(declare_array)
    description_str = "\'" + first_identifier + "\' is "

    # step3: analyse as the flowchart
    while (len(left_stack) > 0 or len(right_stack) > 0):
        (temp_str, left_stack, right_stack) = analyse_expression(left_stack, right_stack)
        #print temp_str
        #print left_stack
        #print right_stack

        description_str += temp_str

    if (len(right_stack) > 0):
        for c in right_stack:
            print "right_stack remain: " + c 

    print "\n\nResult:"
    print description_str

if __name__ == '__main__':
    main()
    