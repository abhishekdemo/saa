#!/usr/bin/env python3

from http.server import BaseHTTPRequestHandler, HTTPServer
import logging

class S(BaseHTTPRequestHandler):
    def _set_response(self):
        self.send_response(200,'on')
        self.send_header('content-type','text/html')
        self.send_headers()

    def _do_GET(self):
        logging.info("GET request, \nPAth: %s\nHeaders:\n%s|n",str(self.path),str(self.headers))
        self._set_response()
        message="Hello ,World! Here is the GET response"
        self.wfile.write(bytes(message,"utf8"))

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        print("Value Received:", post_data.decode('utf-8'))
        self._set_response()
        self.wfile.write("POST request for {}".format(self.path).encode('utf-8'))

def run(server_class=HTTPServer, handler_class =S,port=8080):
    logging.basicConfig(level=logging.INFO)
    server_address =('',port)
    httpd=server_class(server_address,handler_class)
    logging.info('Starting HTTP Server....\n')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
    logging.info('Stopping HTTP Server....\n')

if __name__ == '__main__':
    from sys import argv

    if len(argv) ==2:
        run(port=int(argv[1]))
    else:
        run()