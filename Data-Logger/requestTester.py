# -*- coding: utf-8 -*-
"""
Created on Wed Aug  7 22:45:24 2019

@author: Jacob
"""

import requests

resp = requests.post('http://192.168.1.140:8080', json={'temp': 21})