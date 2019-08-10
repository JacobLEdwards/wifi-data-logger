# -*- coding: utf-8 -*-
"""
Created on Wed Aug  7 22:22:39 2019

@author: Jacob
"""

from http import server
from socketserver import TCPServer
from socket import gethostname, gethostbyname
import datetime
import json

# Host Port
PORT_NUM = 8080

# Log File
LOG_FILE = '/home/pi/ESPDataLogger/weatherData.log'

def log(message):
    # Log Data.
        with open(LOG_FILE, 'a') as f:
            print(message)
            f.write(message + '\n')

# Server Handler for POST requests.
class ServerHandler(server.SimpleHTTPRequestHandler):
 
    def do_GET(self):
        logged_data = []
        
        with open(LOG_FILE, 'r') as f:
            for line in f:
                logged_data.append(line.strip())
        
        logged_data = ',\n'.join(logged_data)
            
        self.send_response(200)
        self.end_headers()
        self.wfile.write(logged_data.encode())
 
    def do_POST(self):
        # Log Receipt
        timestamp = datetime.datetime.now().strftime('%Y_%m_%d %H:%M:%S')
        log('\nData recieved %s.' % timestamp)
        
        # Get data
        content_length = int(self.headers['Content-Length'])
        post_data = json.loads(self.rfile.read(content_length))
        log('data: %s' % post_data)

        # Add timestamp.
        post_data['timestamp'] = timestamp

        log(json.dumps(post_data))

        # Send response.
        self.send_response(200)
        self.end_headers()
        self.wfile.write(json.dumps(post_data).encode())
        
        

Handler = ServerHandler

with TCPServer(("0.0.0.0", PORT_NUM), Handler) as s:
    log('Server started at %s:%d' % (gethostbyname(gethostname()), PORT_NUM))
    s.serve_forever()
