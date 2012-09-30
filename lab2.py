import serial
import math
import time
import urllib2
import urllib


def post_to_server(url, values):
	if values['opacity'] != None and values['number'] != None:
		data = urllib.urlencode(values)
		req = urllib2.Request(url, data)
		response = urllib2.urlopen(req)


def get_mode():
	mode = raw_input("Which mode do you want? 0 = manual, 1 = automatic: ")
	return mode

ser = serial.Serial('/dev/ttyACM0', 9600) # open serial port

no_dishes = raw_input("How many dishes are loaded?   ")
ser.write(no_dishes)
ser.write('n')


mode = get_mode()
ser.write(mode)
ser.write('z')
#ser.flush()

i = 1
while i <= no_dishes:
	if int(mode) == 0:
		a = raw_input("press enter to read opacity of dish #" + str(i))
		ser.write('y');
	values = {}
	while (len(values) <2):
		input1 = ser.readline()
		#print input1
		if  len(input1) > 1	:			
			# gets the last 3 digits from serial read
			b = [int(s) for s in input1.split() if s.isdigit()]	
			if "number" in input1: # receiving pan angle
				values['number'] = b[0]
			elif "light" in input1:	# receiving light data
				#print "light data is : " + str(b)
				values['opacity'] = float(b[0])/1023 * 100;
	print 'values are :               '
	print values
	if len(values) == 2:	
		post_to_server('http://pdish.herokuapp.com/data', values)	
		i+=1
