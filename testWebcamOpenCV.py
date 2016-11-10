import numpy as np
import cv2
import time

cap = cv2.VideoCapture(0)
ret, frame = cap.read()
# Our operations on the frame come here
grayFirst = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

minContourSize = 500
maxContourSize = 2000

while(True):

    # Capture frame-by-frame
    #time.sleep(1)
    ret, frame = cap.read()

    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    ret,thresh1 = cv2.threshold(gray,240,255,cv2.THRESH_BINARY)

    gray = gray - grayFirst

    im2, contours, hierarchy = cv2.findContours(thresh1,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    #print contours

    count = 0
    finalContours = []
    for x in range(0, len(contours)) :
    	cnt = contours[x]
    	if cv2.contourArea(cnt) > minContourSize :
    		finalContours.append(cnt)
    		count = count + 1

    x = 0
    y = 0
    if len(finalContours) > 0 :
    	x,y,w,h = cv2.boundingRect(finalContours[0])

	print 'Contours: ' + str(count) + ' X: ' + str(x) + ' Y: ' + str(y)

	cv2.drawContours(frame, finalContours, -1, (0,255,0), 3)


    #cv2.drawContours(thresh1, contours, -1, 255, 3)

	#detector = cv2.SimpleBlobDetector()
	 
	# Detect blobs.
	#keypoints = detector.detect(thresh1)
	 
	# Draw detected blobs as red circles.
	# cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS ensures the size of the circle corresponds to the size of blob
	#im_with_keypoints = cv2.drawKeypoints(im, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

    # Display the resulting frame
    cv2.imshow('frame',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break



# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()