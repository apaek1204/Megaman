#!/usr/bin/env python2.7

# import libraries
import os
import socket
import sys
import getopt
import logging
import mimetypes
import signal

# Define constants
ADDRESS= '0.0.0.0'
PORT     = 9999
BACKLOG  = 0
LOGLEVEL = logging.INFO
PROGRAM  = os.path.basename(sys.argv[0])
DOCROOT='.'
FORK=False

# Usage Function

def usage(exit_code=0):
    print >>sys.stderr, '''Usage: {program} [-d DOCROOT -p PORT -v -f]

	Options:

    	-h       Show this help message
    	-f	 Enable forking mode
    	-v       Set logging to DEBUG level
    
    	-p PORT  TCP Port to listen to (default is {port})
    	-d DOCROOT Set root directory (default is current directory)'''.format(port=PORT, program=PROGRAM)
    sys.exit(exit_code)
    
# Parse Command-Line Options Function
def parse_arguments():
	# make Constants global
	global LOGLEVEL
	global PORT
	global FORK
	global DOCROOT
	
	# parse command-line options
	try:
		options, arguments = getopt.getopt(sys.argv[1:], "hvp:d:f")
	except getopt.GetoptError as e:
		usage(1)
		

	for option, value in options:
		if option == '-v':
			LOGLEVEL = logging.DEBUG
		elif option == '-p':
			PORT=int(value)
		elif option == '-d':
			DOCROOT=value
		elif option == '-f':
			FORK=True
		else:
			usage(1)
			
# Set the logging information			
def set_logger(log_level):
	logging.basicConfig(
        	level   = log_level,
        	format  = '[%(asctime)s] %(message)s',
        	datefmt = '%Y-%m-%d %H:%M:%S',
    	)

# class TCP Server
class TCPServer(object):
	def __init__(self, handler, address=ADDRESS, port=PORT, forking=FORK):
		'''Initialization of TCP Server object'''
		# make logger
		self.logger=logging.getLogger()
		# get IP address
		try:
			self.address = address
		except socket.gaierror as e:
			logging.error('Unable to lookup {}: {}'.format(self.address, e))
			sys.exit(1)
		
		# make port
		self.port = PORT
		
		# make socket
		self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		# get handler
		self.handler=handler
		
		# set forking
		self.forking=FORK
		
	def run(self):
		# Bind to the specified web server
		try:
			self.socket.bind((self.address, self.port))
			self.socket.listen(BACKLOG)
		except socket.error as e:
			self.logger.error('Could not listen on {}:{}: {}'.format(self.address, self.port, e))
            		sys.exit(1)
            		
            	# set signal to ignore children
		signal.signal(signal.SIGCHLD, signal.SIG_IGN)
		
		# run the connection
		while True:
			# Accept incoming connection
			client, address=self.socket.accept()
			self.logger.debug('Accepted connection from {}:{}'.format(*address))
			
			# Instantiate handler, handle connection, finish connection
           		try:
                		handler = self.handler(client, address)
             
                		# handle connection if no children wanted
                		if self.forking==False:
                			handler.handle()
                		else:
                			# otherwise fork it
                			PID=os.fork()
         
          				if PID==0:
          					handler.handle()
          					sys.exit(0)
          				else:
          					self.socket.close()
            		except Exception as e:
                		handler.exception('Exception: {}', e)
            		finally:
                		handler.finish()
		
# Class Base Handler
class BaseHandler(object):
	def __init__(self, fd, address):
		self.logger=logging.getLogger()
		self.socket=fd
		self.address='{}:{}'.format(*address)
		self.stream=self.socket.makefile('w+')
		
		self.debug('Connect')
		
	def debug(self, message, *args):
       		''' Convenience debugging function '''
        	message = message.format(*args)
        	self.logger.debug('{} | {}'.format(self.address, message))

 	def info(self, message, *args):
        	''' Convenience information function '''
        	message = message.format(*args)
        	self.logger.info('{} | {}'.format(self.address, message))

    	def warn(self, message, *args):
        	''' Convenience warning function '''
        	message = message.format(*args)
        	self.logger.warn('{} | {}'.format(self.address, message))

    	def error(self, message, *args):
        	''' Convenience error function '''
        	message = message.format(*args)
        	self.logger.error('{} | {}'.format(self.address, message))

    	def exception(self, message, *args):
        	''' Convenience exception function '''
        	message = message.format(*args)
        	self.logger.exception('{} | {}'.format(self.address, message))
		
	def handle(self):
		''' Handle connection '''
        	self.debug('Handle')
        	raise NotImplementedError

	def finish(self):
		''' Finish connection by flushing stream, shutting down socket, and then closing it '''
        	self.debug('Finish')
        	
        	# flush and shut the socket
        	try:
            		self.stream.flush()
            		self.socket.shutdown(socket.SHUT_RDWR)
        	except socket.error as e:
            		pass    # Ignore socket errors
            	# close the socket
        	finally:
            		self.socket.close()
		
# class HTTP Handler
class HTTPHandler(BaseHandler):
	def __init__(self, fd, address=ADDRESS, docroot=DOCROOT):
		BaseHandler.__init__(self, fd, address)
		self.docroot=docroot
		
	def handle(self):
		''' Handle connection by reading data and then writing it back until EOF '''
		# parse the HTTP request
		self._parse_request()
		
		# Build uripath by normalizing REQUEST_URI
    		self.uripath = os.path.normpath(self.docroot + os.environ['REQUEST_URI'])
		
	
   		# Check path existence and types and then dispatch
    		if os.path.abspath(self.uripath).startswith(os.path.abspath(self.docroot))==False or not os.path.exists(self.uripath):
        		self._handle_error(404) # 404 error
        	elif os.path.isfile(self.uripath) and os.access(self.uripath, os.X_OK): # executable
        		self._handle_script()
        	elif os.path.isfile(self.uripath) and os.access(self.uripath, os.R_OK): # static file
        		self._handle_file()
        	elif os.path.isdir(self.uripath) and os.access(self.uripath, os.R_OK): # directory listing
        		self._handle_directory()
        	else:
        		self._handle_error(403)
        	
		
	def _parse_request(self):
		''' SET ENVIRONMENTAL VARIABLES FROM WEB SERVER'''
		# set DATA_DICT
		DATA_DICT={}
		
		try:
			# Get first line of data
			data= self.stream.readline().rstrip()
			self.debug('Parsing {}', data.split(' '))
			
			# Set Request Uri, request method, and query string
			try:
				REQUEST_URI=data.split(' ')[1]
			except:
				REQUEST_URI='/'
			
			try:
				temp=REQUST_URI.split('?')
				REQUEST_URI=temp[0]
				QUERY_STRING=temp[1]
			except:
				pass
				
			REQUEST_METHOD=data.split(' ')[0]
			
			os.environ["REQUEST_METHOD"] = REQUEST_METHOD
			os.environ["REQUEST_URI"]=REQUEST_URI
			
			
			try:
				os.environ["QUERY_STRING"]=QUERY_STRING
			except:
				pass
			# get other data and set it
			while data:
				# get key
				data= self.stream.readline().rstrip()
				d=data.split(":")
				
				try:
					case = d[0].split("-")
				except:
					case = d[0]
				
				key="HTTP"
				for i in case:
					key=key+"_" + i.upper() 
				
				# get value and add to dictionary
				try:
					value=d[1]
					DATA_DICT[key]=value
				except:
					pass
			# add dictionary to environment		
			for i in DATA_DICT:
				os.environ[i]=DATA_DICT[i]
					
					
		except socket.error:
			pass	
		
		# add other remote variables to environment
		
		REMOTE_ADDR = self.address.split(':', 1)[0]
		os.environ["REMOTE_ADDR"]=REMOTE_ADDR
		
		REMOTE_HOST=self.address.split(':', 1)[0]
		os.environ["REMOTE_HOST"]=REMOTE_HOST
		
		REMOTE_PORT=str(PORT)
		os.environ["REMOTE_PORT"]=REMOTE_PORT
			
		
	def _handle_error(self, error):
		'''Handle errors'''
		# write error message
		self.stream.write("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n")
		self.stream.write("<h1> ERROR {}</h1>".format(error))
		
		# fun picture
		self.stream.write('''<img src="http://missmillmag.com/wp-content/uploads/2015/05/oh-no-241x300.jpg" alt="oh no">''')
	
	def _handle_file(self):
		'''display file to user'''
		# get mimetype
		mimetype, _ = mimetypes.guess_type(self.uripath)
		if mimetype is None:
    			mimetype = 'text/html'
    		
    		# Request to send content to server	
		self.stream.write("HTTP/1.0 200 OK\r\nContent-Type: {}\r\n\r\n".format(mimetype))
		
		# Get file and send it to server
		
		# get fd
		istream=os.open(self.uripath, os.O_RDONLY)
		# read file
		r_info=os.read(istream, 512)
		# continue reading and writing while possible
		while r_info:
			self.stream.write('{}'.format(r_info))
			r_info=os.read(istream, 512)
			
	
		
	def _handle_directory(self):
		# Set mimetype
    		mimetype = 'text/html'	
	
		# Get directory list
		l=os.listdir(self.uripath)
		
		# Make into sorted list
		sorted_l=sorted(l, key=os.path.getsize, reverse=True)
		
		# write file contents to webpage
		self.stream.write("HTTP/1.0 200 OK\r\nContent-Type: {}\r\n\r\n".format(mimetype))
		# headers
		self.stream.write('''<html> 
			<head> <title> {} </title> </head>\r\n
			<body>
			<h1 style="color:blue">
			Directory Listing: {}\r\n
			</h1>'''.format(self.uripath, self.uripath))
		# Item types in table
		self.stream.write('''
			<table border="1" style="width:100%">
			<tr>
			<th> Type </th>
			<th> Name </th>
			<th > Size </th>
			</tr>
			''')
		# Print all items in table
		for i in sorted_l:
			# Find i's type
			if os.path.isfile(i):
				t='file'
			elif os.path.isdir(i):
				t='dir'
		
			self.stream.write('''
				<tr>
				<td> {}</td>
				<td> <p> <a href="{}"> {} </a> </p> </td>
				<td> {} </td> 
				</tr>
				'''.format(t, i, i, os.path.getsize(i)))
		# Finishing stuff
		self.stream.write('''
			</table>
			</body>
			</html>''')
			
	def _handle_script(self):
		'''Handle Executables'''
		
    		mimetype = 'text/html'
    		
    		# change signal to default	
    		signal.signal(signal.SIGCHLD, signal.SIG_DFL)
		
		self.stream.write("HTTP/1.0 200 OK\r\nContent-Type: {}\r\n\r\n".format(mimetype))
		
		#exe=os.popen(self.uripath)
		#if sys.stdin.isatty():
		#	self.stream.write('''
		#		<form>
		#		<br><input type="text" var="var"><br>
		#		</form>
		#	''')
			
		
		# write output to stream	
		for line in os.popen(self.uripath):
			self.stream.write("{}".format(line))
			
		signal.signal(signal.SIGCHLD, signal.SIG_IGN)
		
# Main Execution
if __name__ == "__main__":
	# parse command line arguments
	parse_arguments()
	
	# set logging info
	set_logger(LOGLEVEL)
	
	# make a server object
	server = TCPServer(handler=HTTPHandler)
	
	# run server object
	try:
		server.run() 
	except KeyboardInterrupt:
		sys.exit(0)
