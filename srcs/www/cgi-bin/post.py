#!/usr/bin/env python3
import sys

body = sys.stdin.read()
sys.stdout.write("Content-Type: text/html\r\n\r\n")

print("<html>")
print("<head><title>Test POST CGI</title></head>")
print("<body style='font-family: Arial, sans-serif; padding: 20px;'>")
print("<h2>Script Python execute avec succes !</h2>")
print("<p>Voici les donnees brutes que le script a lu depuis le tuyau (stdin) :</p>")
print("<pre style='background: #eee; padding: 15px; border-radius: 5px;'>")

if body:
    print(body)
else:
    print("Aucune donnee - body vide")

print("</pre>")
print("</body>")
print("</html>")
