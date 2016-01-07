#!/usr/bin/python
# -*- coding: utf-8 -*-

#!/usr/bin/python

import serial
import serial.tools.list_ports
import sys
import traceback

power_on_cmd = [0x55, 0x01, 0x12, 0x00, 0x00, 0x00, 0x01, 0x69]
power_off_cmd = [0x55, 0x01, 0x11, 0x00, 0x00, 0x00, 0x01, 0x68]

def scan_comports_out():
	comport_list = list(serial.tools.list_ports.comports())
	comport_name_list = []
	#sys.stdout.write("Available Serial Ports: ")
	for com in comport_list:
		comport_name_list.append(list(com)[0])
		#sys.stdout.write(list(com)[0] + ' ')
	#sys.stdout.write("\n")
	return comport_name_list

	
def power_operate_com(comport, cmd):
	try:
		serialPort = serial.Serial(comport)
		#print(cmd)
		serialPort.write(cmd)
		serialPort.close()
	except:
		print("Error: Can not open serial port ", comport)
		#traceback.print_exc()
		
#Working start
available_comports = scan_comports_out()
available_commands = ["ON", "OFF"]
operation_commands = {}
operation_commands[available_commands[0]] = power_on_cmd
operation_commands[available_commands[1]] = power_off_cmd
#添加字典元素的方法二
#operation_commands.update({available_commands[0]:power_on_cmd})
#operation_commands.update({available_commands[1]:power_off_cmd})

#print(sys.argv)
if (len(sys.argv) < 3 or (sys.argv[1].upper() not in available_comports) or (sys.argv[2].upper() not in available_commands)) :
	print("Usage: ")
	print("      python serial_power_on_off.py [COM1|COM2|...] [ON|OFF]")
	print("Available Serial Ports: ", available_comports)
else:
	power_operate_com(sys.argv[1].upper(), operation_commands[sys.argv[2].upper()])
	
	