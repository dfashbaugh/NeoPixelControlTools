import numpy as np
import cv2
import serial # if you have not already done so
from time import sleep
from PIL import Image
from PIL import ImageDraw

def PrintXYMatrix(XYMatrix) :
	print 'Start Print'
	print str(len(XYMatrix))
	print str(len(XYMatrix[0]))
	printStr = ''
	for y in range(0, len(XYMatrix[0])) :
		print printStr
		printStr = ''
		for x in range(0, len(XYMatrix)) :
			if len(XYMatrix[x][y]) > 0 :
				printStr = printStr + str(XYMatrix[x][y][0]) + '	'
			else :
				printStr = printStr + ' 	'

def PrintXYMatrixSmall(XYMatrix) :
	printStr = ''
	for y in range(0, len(XYMatrix[0])) :
		print printStr
		printStr = ''
		for x in range(0, len(XYMatrix)) :
			if len(XYMatrix[x][y]) > 0 :
				printStr = printStr + 'x '
			else :
				printStr = printStr + '  '

def PrintXYMatrixImage(XYMatrix) :
	matrixDraw = Image.new("RGB", (len(XYMatrix), len(XYMatrix[0])))
	draw = ImageDraw.Draw(matrixDraw)
	px = matrixDraw.load()
	for x in range(0, len(XYMatrix)) :
		for y in range(0, len(XYMatrix[0])) :
			if len(XYMatrix[x][y]) > 0 :
				px[x,y] = (255,0,0)
			else :
				px[x,y] = (0,0,0)

	matrixDraw.save('out.bmp')
			

def GetLEDsInBox(xLow, xHigh, yLow, yHigh, posList) :
	LEDAddrs = []

	for x in range(0, len(posList)) :
		curX = posList[x][1]
		curY = posList[x][2]
		led = posList[x][0]

		if curX < xHigh and curX > xLow and curY < yHigh and curY > yLow :
			print led
			LEDAddrs.append(led)

	return LEDAddrs

def BinLEDsByPercentage(posList, percentBin, maxX, maxY) :
	newX = maxX * percentBin
	newY = maxY * percentBin
	newX = int(round(newX))
	newY = int(round(newY))
	return BinLEDsToNewXY(posList, newX, newY, maxX, maxY)

def BinLEDsToNewXY(posList, newX, newY, maxX, maxY) :
	xFraction = maxX / newX
	yFraction = maxY / newY
	eachX = []
	XYMatrix = []

	for y in range(0, newY) :
		for x in range(0, newX) :
			eachX.append(GetLEDsInBox(x*xFraction, (x+1)*xFraction, y*yFraction, (y+1)*yFraction, posList))
		XYMatrix.append(eachX)
		eachX = []

	#PrintXYMatrix(XYMatrix)
	#PrintXYMatrixSmall(XYMatrix)
	PrintXYMatrixImage(XYMatrix)

	return XYMatrix

def GetLongestLEDList(XYMatrix) :
	longestLEDList = 0

	for y in range(0, len(XYMatrix[0])) :
		for x in range(0, len(XYMatrix)) :
			if len(XYMatrix[x][y]) > longestLEDList :
				longestLEDList = len(XYMatrix[x][y])

	return longestLEDList

def PrintArduinoCode(XYMatrix) :
	LEDLength = GetLongestLEDList(XYMatrix)
	XLength = len(XYMatrix)
	YLength = len(XYMatrix[0])

	writeFile = open('MatrixMapping.h', 'w')
	writeFile.write('int xSize = ' + str(XLength) + ';\n')
	writeFile.write('int ySize = ' + str(YLength) + ';\n')
	writeFile.write('int maxLEDList = ' + str(LEDLength) + ';\n')
	writeFile.write('int LEDMap[' +str(XLength) + '][' + str(YLength) + '][' + str(LEDLength) + '];\n')

	for y in range(0, YLength) :
		for x in range(0, XLength) :
			for l in range(0, LEDLength) :
				if len(XYMatrix[x][y]) <= l :
					writeFile.write('LEDMap[' + str(x) + '][' + str(y) + '][' + str(l) + '] = ' + '-1' + ';\n')
				else :
					writeFile.write('LEDMap[' + str(x) + '][' + str(y) + '][' + str(l) + '] = ' + str(XYMatrix[x][y][l]) + ';\n')

	writeFile.close()

captureVideo = 1
fileName = 'LEDpositions.csv'

binByPercentage = 0 #Keep aspect ratio
percentBin = 0.1
newX = 16  # X and Y size of the array that the pixels will be held in
newY = 16  
NumLEDS = 255

if captureVideo :

	ser = serial.Serial('/dev/tty.usbmodem1668021', 9600)
	# while 1 :
		# for x in range(0, 85) :
		# 	ser.write(str(x).encode())
		# 	sleep(1)
		# 	ser.flush()

	cap = cv2.VideoCapture(1)
	cap.set(21, 0)

	ret, frame = cap.read()
	# Our operations on the frame come here
	grayFirst = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

	minContourSize = 1
	maxContourSize = 300

	posList = []

	for i in range(0, NumLEDS) :

	    ser.write(str(i).encode() + str('\n'))
	    sleep(0.1)

	    tempList = []
	    for j in range(0, 5) :

		    ret, frame = cap.read()

		    # Our operations on the frame come here
		    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
		    b,g,r = cv2.split(frame)

		    #g = cv2.subtract(g,r)
		    #g = cv2.subtract(g, b)
		    
		    #ret,thresh1 = cv2.threshold(g,200,255,cv2.THRESH_BINARY)
		    ret,thresh1 = cv2.threshold(r,230,255,cv2.THRESH_BINARY)



		    #gray = gray - grayFirst

		    im2, contours, hierarchy = cv2.findContours(thresh1,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
		    #print contours

		    count = 0
		    finalContours = []
		    for x in range(0, len(contours)) :
		    	cnt = contours[x]
		    	if cv2.contourArea(cnt) > minContourSize and cv2.contourArea(cnt) < maxContourSize :
		    		finalContours.append(cnt)
		    		count = count + 1

		    x = 0
		    y = 0
		    w = 0
		    h = 0
		    if len(finalContours) > 0 :
		    	tX = 0
		    	tY = 0
		    	tX,tY,w,h = cv2.boundingRect(cnt)
		    	if abs(w-h) < 200 :
			    	(x,y),radius = cv2.minEnclosingCircle(finalContours[0])
			    	center = (int(x),int(y))
			    	radius = int(radius)
			    	cv2.circle(frame,center,radius,(0,0,255),8)
			    	#print 'Contours: ' + str(count) + ' X: ' + str(x) + ' Y: ' + str(y) + ' W: ' + str(w) + ' H: ' + str(h) + ' Area: ' + str(cv2.contourArea(finalContours[0]))
			    	tempList.append( (i, x, y) )

			cv2.drawContours(frame, finalContours, -1, (255,0,0), 20)

		    #cv2.drawContours(thresh1, contours, -1, 255, 3)

			#detector = cv2.SimpleBlobDetector()
			 
			# Detect blobs.
			#keypoints = detector.detect(thresh1)
			 
			# Draw detected blobs as red circles.
			# cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS ensures the size of the circle corresponds to the size of blob
			#im_with_keypoints = cv2.drawKeypoints(im, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

		    # Display the resulting frame
		    #cv2.namedWindow('frame', cv2.WINDOW_NORMAL)
		    
		    small = cv2.resize(frame, (0,0), fx=0.5, fy=0.5) 
		    cv2.imshow('frame',small)
		    if cv2.waitKey(1) & 0xFF == ord('q'):
		        break

		# Process Temp List
	    try :
		    rangeX = 0
		    rangeY = 0
		    minX = 99999999999
		    minY = 99999999999
		    maxX = 0
		    maxY = 0
		    sumX = 0
		    sumY = 0
		    for j in range(0, len(tempList)) :
		    	if tempList[j][1] > maxX :
		    		maxX = tempList[j][1]
		    	if tempList[j][1] < minX :
		    		minX = tempList[j][1]
		    	if tempList[j][2] > maxY :
		    		maxY = tempList[j][2]
		    	if tempList[j][2] < minY :
		    		minY = tempList[j][2]
		    	sumX = sumX + tempList[j][1]
		    	sumY = sumY	+ tempList[j][2]

		    averageX = sumX / len(tempList)
		    averageY = sumY / len(tempList)
		    rangeX = maxX - minX
		    rangeY = maxY - minY

		    print 'Average X: ' + str(averageX) + ', AverageY: ' + str(averageY) + ', Range X: ' + str(rangeX) + ', Range Y: ' + str(rangeY)

		    posList.append( (i, averageX, averageY) )
	    except :
			print 'Failed to find LED'


	# When everything done, release the capture
	cap.release()
	cv2.destroyAllWindows()

	writeFile = open(fileName, 'w')

	for x in range(0, len(posList) ) :
	     writeFile.write(str(posList[x][0]))
	     writeFile.write('	')
	     writeFile.write(str(posList[x][1]))
	     writeFile.write('	')
	     writeFile.write(str(posList[x][2]))
	     writeFile.write('\n')

	writeFile.close()

else :
	posList = []
	myFile = open(fileName, 'r')
	while 1 :
		curStr = myFile.readline()
		if len(curStr) > 0 :
			curStr = curStr.split('	')
			posList.append( (int(curStr[0]), float(curStr[1]), float(curStr[2])) )
		else :
			myFile.close()
			break

# TIME FOR POST PROCESSING
minX = 999999999
minY = 999999999
maxX = 0
maxY = 0

lastPos = 0;
lastX = 0;
lastY = 0;

newPostList = []

for i in range(0, len(posList)) :
	curX = posList[i][1]
	curY = posList[i][2]

	print posList[i][0]
	if posList[i][0] - lastPos > 1 :
		print 'In Here ' + str(posList[i][1]) + ',' + str(posList[i][2]) + '     ' + str(lastX) + ',' + str(lastY)
		# Interpolate
		if lastX == 0 or lastY == 0 :
			pass
		else :
			numLEDToInterp = posList[i][0] - lastPos
			xDiff = curX - lastX
			yDiff = curY - lastY

			for x in range(0, numLEDToInterp)  :
				print str(lastPos+x) + ',' + str(lastX + x*(xDiff/numLEDToInterp)) + ',' + str(lastY + x*(yDiff/numLEDToInterp))
				newPostList.append( (lastPos+x, lastX + x*(xDiff/numLEDToInterp), lastY + x*(yDiff/numLEDToInterp)) )
			print 'Out here'

	lastX = curX
	lastY = curY
	lastPos = posList[i][0]

	if curX > maxX :
		maxX = curX
	if curX < minX :
		minX = curX
	if curY > maxY :
		maxY = curY
	if curY < minY :
		minY = curY

for i in range(0, len(newPostList)) :
	posList.append(newPostList[i])

for x in range(0, len(posList)) :
	print posList[x]

print 'MinX: ' + str(minX) + ' MaxX: ' + str(maxX) + ' MinY: ' + str(minY) + ' MaxY: ' + str(maxY)
maxX = maxX - minX
maxY = maxY - minY
print 'Adjusted to MinX: ' + str(minX) + ' MaxX: ' + str(maxX) + ' MinY: ' + str(minY) + ' MaxY: ' + str(maxY)

adjustedPosList = []
for x in range(0, len(posList)) :
	curX = posList[x][1] - minX
	curY = posList[x][2] - minY
	adjustedPosList.append( (posList[x][0], curX, curY) )

if binByPercentage :
	XYMatrix = BinLEDsByPercentage(adjustedPosList, percentBin, maxX, maxY)
else :
	XYMatrix = BinLEDsToNewXY(adjustedPosList, newX, newY, maxX, maxY)

PrintArduinoCode(XYMatrix)



