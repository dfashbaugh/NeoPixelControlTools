import serial
import time
from PIL import Image

class NeoPixelMatrix:

	MemorySize = 1920
	ser = serial.Serial()
	LEDMemory = [int]*MemorySize

	def __init__(self, SerialPort):
		self.ser.baudrate = 500000
		self.ser.port = SerialPort
		self.ser.open()
		print 'Initialized NeoPixel Serial Port'
 
	def Clear(self) :
		for x in range(0, self.MemorySize) :
			self.LEDMemory[x] = 0
		return

	def SetAllRed(self, value) :

		for x in range(0, self.MemorySize) :
			if x%3 == 1 :
				self.LEDMemory[x] = value
			else :
				self.LEDMemory[x] = 0x00
	
	def BinImage(self, image) :
		px = image.load()
		#Bin 16 -> 1
		neoImage = Image.new("RGB", (80,8))
		neoPix = neoImage.load()
		for x in range(0, 80) :
			for y in range(0, 8) :
				channel1 = 0
				channel2 = 0
				channel3 = 0
				for subX in range(0,4) :
					for subY in range(0, 4) :
						theColor = px[4*x+subX, 4*y+subY]
						channel1 = channel1 + theColor[0]
						channel2 = channel2 + theColor[1]
						channel3 = channel3 + theColor[2]
				channel1 = channel1/16
				channel2 = channel2/16
				channel3 = channel3/16
				neoPix[x,y] = (channel1, channel2, channel3)
		return neoPix

	def SetImage(self, image, x, y):
		neoPix = self.BinImage(image)

		for memoryPos in range(0, self.MemorySize/3) :
			pixelX = memoryPos%8 + 8*(memoryPos/64)
			pixelY = (memoryPos/8)%8
			self.LEDMemory[memoryPos*3] = neoPix[pixelX, pixelY][1]
			self.LEDMemory[memoryPos*3+1] = neoPix[pixelX, pixelY][0]
			self.LEDMemory[memoryPos*3+2] = neoPix[pixelX, pixelY][2]

	def DrawLEDMemory(self) :
		self.ser.write('start'.encode())
		for x in range(0, len(self.LEDMemory)) :

			if self.LEDMemory[x] > 255 :
				self.LEDMemory[x] = 255
			elif self.LEDMemory[x] < 0 :
				self.LEDMemory[x] = 0

			self.ser.write(chr(self.LEDMemory[x]))
		return