import numpy as np
import cv2
import time

cap = cv2.VideoCapture(2)
cap.set(21, 0)

ret, frame = cap.read()
# Our operations on the frame come here
grayFirst = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

minContourSize = 200
maxContourSize = 4000

while(True):

    # Capture frame-by-frame
    #time.sleep(1)
    ret, frame = cap.read()

    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    b,g,r = cv2.split(frame)

    #g = cv2.subtract(g,r)
    #g = cv2.subtract(g, b)
    
    #ret,thresh1 = cv2.threshold(g,200,255,cv2.THRESH_BINARY)
    ret,thresh1 = cv2.threshold(g,250,255,cv2.THRESH_BINARY)



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
	    	cv2.circle(frame,center,radius,(0,0,255),2)
	    	print 'Contours: ' + str(count) + ' X: ' + str(x) + ' Y: ' + str(y) + ' W: ' + str(w) + ' H: ' + str(h) + ' Area: ' + str(cv2.contourArea(finalContours[0]))

	cv2.drawContours(frame, finalContours, -1, (0,255,0), 3)









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



# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()