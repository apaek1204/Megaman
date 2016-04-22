#!/usr/bin/env python2.7

# Import libraries
import socket
import os
import sys
import logging
import getopt
import time
import re

# Define initial variables
URL=""
ADDRESS  = ''
PORT     = 80
PROGRAM  = os.path.basename(sys.argv[0])
LOGLEVEL = logging.INFO
PATH="/"
REQUESTS=1
PROCESSES=1


# Usage Function
def usage(exit_code=0):
	print >>sys.stderr, '''Usage: {program} [-r REQUESTS -p PROCESSES -v] URL

	Options:

    	-h       Show this help message
    	-v       Set logging to DEBUG level
    	
	-r REQUESTS  Number of requests per process (default is 1)
	-p PROCESSES Number of processes (default is 1)'''.format(port=PORT, program=PROGRAM)
	sys.exit(exit_code)
	
# Parse Command-Line Options Function
def parse_arguments():
	# make Constants global
	global LOGLEVEL
	global REQUESTS
	global PROCESSES
	global URL
	
	# parse command-line options
	try:
		options, arguments = getopt.getopt(sys.argv[1:], "hvr:p:")
	except getopt.GetoptError as e:
		usage(1)

	for option, value in options:
		if option == '-v':
			LOGLEVEL = logging.DEBUG
		elif option == '-r':
			REQUESTS=int(value)
		elif option == '-p':
			PROCESSES=int(value)
		else:
			usage(1)
	
	
	# Get URL
	if len(arguments) == 1:
		URL=arguments[0]
	else:
		usage(1)
		
	# Parse the URL
	URL_parser(URL)
	
# URL parsing function
def URL_parser(url):
	# globalize constants
	global ADDRESS
	global PORT
	global PATH
	global URL

	# initial ADDRESS set
	ADDRESS=url
	
	# Parse multiple patterns
	p="http://*"
	pattern=re.compile(p)
	if pattern.match(url):
		ADDRESS= url.split('://')[1]
		URL=ADDRESS
		
		
	p="www.*.com"
	pattern=re.compile(p)
	if pattern.match(url):
		ADDRESS=url
		
	p="www.*.com/"
	pattern=re.compile(p)
	if pattern.match(url):
		ADDRESS=url.split('/')[0]
		PATH='/'+url.split('/')[1]
		
	p="www.*.com:[0-9]*/"
	pattern=re.compile(p)
	if pattern.match(url):
		ADDRESS=url.split(':')[0]
		temp=url.split(':')[1]
		PORT=int(temp.split('/')[0])
		PATH='/'+temp.split('/')[1]
		
	p="www.*.com:[0-9]*/index.html"
	pattern=re.compile(p)
	if pattern.match(url):
		ADDRESS=url.split(':')[0]
		temp=url.split(':')[1]
		PORT=int(temp.split('/')[0])
		PATH='/'+temp.split('/')[1]
		
	p="www.*.com/index.html"
	pattern=re.compile(p)
	if pattern.match(url):
		ADDRESS=url.split('/')[0]
		PATH='/'+url.split('/')[1]
		
	p="www.*.com/index.html?name=value"
	pattern=re.compile(p)
	if pattern.match(url):
		ADDRESS=url.split('/')[0]
		PATH='/'+url.split('/')[1]
		
			
		
# Set logging level	
def set_logger(loglev):
	logging.basicConfig(
		level   = loglev,
		format  = '[%(asctime)s] %(message)s',
		datefmt = '%Y-%m-%d %H:%M:%S',
		)
		
# Send initial logging info, if requested
def send_constants_info():
	logging.debug("URL: {}".format(URL))
	logging.debug("HOST: {}".format(ADDRESS))
	logging.debug("PORT: {}".format(PORT))
	logging.debug("PATH: {}".format(PATH))
	
# TCP Client class
class TCPClient(object):
	def __init__(self, address, port):
		'''Initialization of object'''
		# Grab logging instance
		self.logger  = logging.getLogger()           
		
		# get IP address
		try:
			self.address = socket.gethostbyname(address) 
		except socket.gaierror as e:
			logging.error('Unable to lookup {}: {}'.format(ADDRESS, e))
			sys.exit(1)
		# define port	
		self.port = port
		# make socket object
		self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		
	def handle(self):
		'''Handle, not implemented'''
		self.logger.debug('Handle')
		raise NotImplementedError
	
	def run(self):
		'''Main run function'''
		# connect and make stream object
		try:
			self.socket.connect((self.address, self.port))
			self.stream = self.socket.makefile('w+')

		except socket.error as e:
			self.logger.error('Could not connect to {}:{}: {}'.format(self.address, self.port, e))
			sys.exit(1)
			
		self.logger.debug('Connected to {}:{}...'.format(self.address, self.port))
		
		# call handle and finish
		try:
			self.handle()
		except Exception as e:
			self.logger.exception('Exception: {}', e)
		finally:
			self.finish()
		
	def finish(self):
		'''Finish function, close socket'''
		self.logger.debug('Finish')
		try:
			self.socket.shutdown(socket.SHUT_RDWR)
		except socket.error:
			pass    # Ignore socket errors
		finally:
			self.socket.close()
		
# HTTP Client
class HTTPClient(TCPClient):
	def __init__(self, address, port, path):
		'''Initialize HTTP object'''
		TCPClient.__init__(self, address, port)	
		self.path = path
		self.host= address
		
	def handle(self):
		'''Handle connection by getting data from web server'''
		self.logger.debug('Handle')
		try:
			# Send request
			self.logger.debug("Sending request...")
			self.stream.write('GET {} HTTP/1.0\r\n'.format(self.path))
			self.stream.write('Host: {}\r\n'.format(self.host))
			self.stream.write('\r\n')
			self.stream.flush()
		
			# Recieve response
			self.logger.debug("Recieving response...")
			data = self.stream.readline()
			while data:
				sys.stdout.write(data)	
				data=self.stream.readline()
		except socket.error:
			pass    # Ignore socket errors
			
# Main Execution	
if __name__ == "__main__":
	# Average time of requests
	average=0
	
	# elapsed time
	elapsed_time=0
	
	# parse command line options
	parse_arguments()
	
	# Fork processes
	for process in range(PROCESSES):	
		try:
			PID=os.fork()
		
		except OSError as e:
			print "Unable to fork"
			sys.exit(1)	
			
		
	for request in range(REQUESTS):
		if PID==0:	
			# set logger
			set_logger(LOGLEVEL)
			# Send initial logging info, if requested
			send_constants_info()	
			
			# Make client
			client=HTTPClient(ADDRESS, PORT, PATH)
			try:
				# Run Client and get Time Stamp information
				start_time=time.time()
				client.run()
				end_time=time.time()
					
				print time.strftime("[%Y-%m-%d %H:%M:%S]"), "{} | Elapsed time: {:0.2f} seconds".format(os.getpid(), end_time-start_time)
				elapsed_time=end_time-start_time
			except KeyboardInterrupt:
				sys.exit(0)
		else:	
			try:
				# Make parent wait
				PID, status= os.wait()
				set_logger(LOGLEVEL)
				logging.debug("Process {} terminated with exit status {}".format(PID, status))		
			except:
				pass
		
		# iterage time average
		if elapsed_time!=0:
			average=average+elapsed_time				
				
	# Print average time
	if PID == 0:
		print time.strftime("[%Y-%m-%d %H:%M:%S]"), "{} | Average elapsed time: {:0.2f} seconds".format(os.getpid(), float(average)/float(REQUESTS))
				
