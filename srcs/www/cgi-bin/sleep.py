#!/usr/bin/env python3
import time
import sys

# 1. On envoie les headers requis par le protocole HTTP
print("Content-Type: text/html\r\n\r\n", end="")
sys.stdout.flush() # On force l'écriture dans le tuyau

time.sleep(5)

print("<html><body><h1>CGI terminé après 5 secondes d'attente !</h1></body></html>")
