from NeoPixelMatrix import NeoPixelMatrix
from EtherNeoPixel import EtherNeoPixel
from SimulationMatrix import SimulationMatrix
from PIL import Image
from PIL import ImageDraw

def GetTestImage() :
	image = Image.new("RGB", (320, 32))
	#image = Image.open("digikeyx10.png")
	draw = ImageDraw.Draw(image)
	draw.line( (0,0,31,31), fill=(0,255,0) )
	draw.line( (0, 31, 31, 0), fill=(0,255,0) )
	draw.line( (32,0,63,31), fill=(255,0,0) )
	draw.line( (32, 31, 63, 0), fill=(255,0,0) )
	draw.rectangle((64, 0, 95, 31), fill=(0, 0, 255), outline=(255,0,0))
	draw.rectangle((96, 0, 127, 31), fill=(0, 255, 255), outline=(255,0,0))
	draw.rectangle((128, 0, 159, 31), fill=(255, 255, 0), outline=(255,0,0))
	draw.rectangle((160, 0, 191, 31), fill=(0, 255, 0), outline=(255,0,0))
	draw.rectangle((192, 0, 223, 31), fill=(0, 0, 0), outline=(255,0,0))
	draw.rectangle((224, 0, 255, 31), fill=(0, 0, 0), outline=(255,0,0))
	draw.rectangle((256, 0, 287, 31), fill=(0, 0, 0), outline=(0, 0,255))
	draw.rectangle((288, 0, 319, 31), fill=(0, 0, 0), outline=(255,255,255))
	return image


def GetRGBFromWheel(WheelPos) :
  WheelPos = 255 - WheelPos;
  if WheelPos < 85 :
    return (255-WheelPos*3, 0, WheelPos*3) 
  
  if WheelPos < 170 :
    WheelPos -= 85;
    return (0, WheelPos * 3, 255 - WheelPos * 3)

  WheelPos -= 170;
  return (WheelPos * 3, 255 - WheelPos * 3, 0)

def map(x, fromLow, fromHigh, toLow, toHigh) :
	return (x - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow

#Overall Control Variables
frame = 0
lastDrawTime = 0
matrixType = 0

neoPixelMatrixPort = '/dev/serial0'

# Image Preprocessing
image = Image.new("RGB", (320, 32))

if matrixType == 0 :
	matrix = SimulationMatrix()
elif matrixType == 1 :
	matrix = RGBMatrix(32, 10, 1)
elif matrixType == 2 :
	matrix = NeoPixelMatrix(neoPixelMatrixPort)
else  :
	matrix = EtherNeoPixel()

matrix.Clear()
matrix.SetImage(image, 0, 0)

while 1:
	# Define the frame rate for the whole system.. Only for Neo Pixel
	if matrixType > 1 :
		if time.time() - lastDrawTime > 0.05 :
			matrix.DrawLEDMemory()
			lastDrawTime = time.time()
			
	image = GetTestImage()
	matrix.SetImage(image, 0, 0)

	frame = frame + 1

	

