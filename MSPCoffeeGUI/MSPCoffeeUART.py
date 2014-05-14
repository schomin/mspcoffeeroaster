

# PySerial include
import serial
import csv
from math import trunc


"""
  MSPCoffeeUART

  This class is a UART object and will connect and communicate with the
  mspcoffee device

"""
class MSPCoffeeUART:

  """
    __init__

    Initilization function for the MSPCoffeeUART class
  """
  def __init__(self):

    # Open the serial port for use in the object
    self.__SerialPort = serial.Serial('/dev/ttyACM0', 9600, bytesize = serial.EIGHTBITS, parity = serial.PARITY_NONE, stopbits = serial.STOPBITS_ONE, timeout=1)

  """
    __del__

    Desctructor for the MSPCoffeeUART class
  """
  def __del__(self):

    self.__SerialPort.close() # Close the serial port on object deletion

  """
    upload_curve

    upload a curve to the mspcoffee device given a csv file location
  """
  def upload_curve(self, file_name):

    # Write an 's' char to the uart to tell the device we want to save a curve
    self.__SerialPort.write('s'.encode('utf-8'))
    self.__SerialPort.flush()

    # Get the response and wait for the receiveing of the 'k' char
    response = self.__SerialPort.read()
    while response != b'k':
      print ("Waiting for hand shake\n")
      response = self.__SerialPort.read()
    print ("Uploading the curve\n")

    # Open Curve csv file for transfer
    with open(file_name, newline='') as f:
      # Create a csv reader
      reader = csv.reader(f)
      # For each item in the curve
      for row in reader:
        # Convert the string on the row to a int for transfer
        # Only the first column will be converted all others will be ignored
        temp = int(row[0]);
        print (temp)
        # Convert int into two bytes
        bytes_to_send = temp.to_bytes(2, 'little', signed=True)
        print (bytes_to_send)
        # Send the int to the devices uart
        self.__SerialPort.write(bytes_to_send)
        self.__SerialPort.flush()
      # Send excape int value
      self.__SerialPort.write(b'\xff\xff')
      self.__SerialPort.flush()

  """
    download_curve

    down a curve from the mspcoffee device
  """
  def download_curve(self):
    # Write an 's' char to the uart to tell the device we want to save a curve
    self.__SerialPort.write('g'.encode('utf-8'))
    self.__SerialPort.flush()

    # Get the response and wait for the receiveing of the 'k' char
    response = self.__SerialPort.read()
    while response != b'k':
      print ("Waiting for hand shake\n")
      response = self.__SerialPort.read()

    while 1:
      response = self.__SerialPort.read(2)
      temp = int.from_bytes(response,'little')
      print (temp)
      if temp == 0xFFFF:
          break;
