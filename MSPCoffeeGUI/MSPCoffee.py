

from MSPCoffeeUART import MSPCoffeeUART
import tkinter
from tkinter import filedialog
from tkinter import ttk

mspcu = MSPCoffeeUART()

# define options for opening or saving a file
file_opt = options = {}
options['defaultextension'] = '.csv'
options['filetypes'] = [('all files', '.*'), ('csv files', '.csv')]
options['initialdir'] = 'C:\\'
options['initialfile'] = 'myfile.csv'
options['title'] = 'Select a valid curve file'

# get filename
filename = filedialog.askopenfilename(**file_opt)
# open file on your own
if filename:
  mspcu.upload_curve(filename)

print ("Now downloading saved data\n")

mspcu.download_curve()
