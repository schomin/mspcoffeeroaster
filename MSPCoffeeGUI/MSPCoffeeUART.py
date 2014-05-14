

# PySerial include
import serial

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

    self.__SerialPort = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    # Open the serial port for use in the object

  """
    __del__

    Desctructor for the MSPCoffeeUART class
  """
  def __del__(self):

    self.__SerialPort.close() # Close the serial port on object deletion

  def send_something(self):

    self.__SerialPort.write('s'.encode('utf-8'))
    self.__SerialPort.flush();
    while 1:
      stuff = self.__SerialPort.read(2)
      print (stuff)
      x = int.from_bytes(stuff, byteorder='little')
      print (x)
      if x == 0xFFFF:
        break
    print ("Broke the loop")
