

# PySerial include
import serial
import time

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

    self.__SerialPort = serial.Serial('/dev/ttyACM0', 9600, bytesize = serial.EIGHTBITS, parity = serial.PARITY_NONE, stopbits = serial.STOPBITS_ONE, timeout=1)
    # Open the serial port for use in the object

  """
    __del__

    Desctructor for the MSPCoffeeUART class
  """
  def __del__(self):

    self.__SerialPort.close() # Close the serial port on object deletion

  def send_something(self):

    self.__SerialPort.write('s'.encode('utf-8'))
    self.__SerialPort.flush()
    print ("Sending stuff\n")
    response = self.__SerialPort.read()
    while response != b'k':
      print ("Waiting for hand shake\n")
      response = self.__SerialPort.read()
    print ("Got response\n")
    self.__SerialPort.write(b'\x01\x05')
    self.__SerialPort.flush()
    response = self.__SerialPort.readline()
    print (response)
    self.__SerialPort.write(b'\xFF\xFF')
    self.__SerialPort.flush()
    response = self.__SerialPort.readline()
    print (response)
