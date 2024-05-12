import os
import numpy as np 


print("Current folder:",os.getcwd())

print("file in folder: ",os.listdir())

try:
    
    data = np.genfromtxt("shortwalk.csv", delimiter=",", skip_header=1)
    print("Data Loaded Successfully")
except FileNotFoundError:
    print("File not found. Please check the file path and name.")
except Exception as e:
    print("An error occurred:", e)