import socket
import time
from PIL import Image

class EtherNeoPixel:

	#UDP_IP = "192.168.2.2"
	#UDP_PORT = 8888
	#sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	MemorySize = 1920
	LEDMemory = [int]*MemorySize

	def __init__(self, squareMatrixSize, numMatrixHoriz, numMatrixVert):
		print 'Initialized Neo Socket'
 
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
		sendArr = []
		sendArr.append('o')
		sendArr.append('n')
		for x in range(0, 900) :

			if self.LEDMemory[x] > 255 :
				self.LEDMemory[x] = 255
			elif self.LEDMemory[x] < 0 :
				self.LEDMemory[x] = 0

			sendArr.append(chr(self.LEDMemory[x]))
		sendStr = "".join(sendArr)
		UDP_IP = "192.168.2.2"
		UDP_PORT = 8888
		mySock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		mySock.sendto(sendStr, (UDP_IP, UDP_PORT)) 
		
		sendArr = []
		sendArr.append('t')
		sendArr.append('w')
		for x in range(900, 1920) :
			if self.LEDMemory[x] > 255 :
				self.LEDMemory[x] = 255
			elif self.LEDMemory[x] < 0:
				self.LEDMemory[x] = 0
			sendArr.append(chr(self.LEDMemory[x]))
		
		sendStr = "".join(sendArr)
		mySock.sendto(sendStr, (UDP_IP, UDP_PORT))
