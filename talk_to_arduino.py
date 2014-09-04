## import the serial library
import serial
import curses
from curses import wrapper
# set up keyboard input

def main(stdscr):
  ##  stdscr = curses.initscr()
    stdscr.clear
    curses.cbreak()
    stdscr.keypad(1)

    ## Boolean variable that will represent 
    ## whether or not the arduino is connected
    connected = False


    ## open the serial port that your ardiono 
    ## is connected to.
    ser = serial.Serial("/dev/tty.usbmodemfd131", 9600)

    ## loop until the arduino tells us it is ready
    while not connected:
        serin = ser.read()
        connected = True

    key = ''
    while key != ord('q'):
        inkey = ser.read()
        stdscr.addch(0,0,inkey)
        stdscr.refresh()
        
#        key = stdscr.getkey()
#        bkey = key.encode()
         #   stdscr.addch(0,0,key)
#        ser.write(bkey)

    ## close the window
    curses.endwin()
    ## close the port and end the program
    ser.close()

wrapper(main)
