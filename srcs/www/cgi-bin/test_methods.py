#!/usr/bin/env python3
import os
import sys

method = os.environ.get("REQUEST_METHOD", "UNKNOWN")
query = os.environ.get("QUERY_STRING", "")
body = ""

if method == "POST":
    try:
        cl = int(os.environ.get("CONTENT_LENGTH", "0"))
        body = sys.stdin.read(cl)
    except ValueError:
        body = "Erreur de taille"

print("Content-Type: text/html\r\n\r\n", end="")
print("<html><body>")
print("<h1>CGI Python Multi-Methodes</h1>")
print("<p>Methode : " + method + "</p>")
print("<p>Query String : " + query + "</p>")
print("<p>Body POST : " + body + "</p>")
print("</body></html>")
