import cv2
import serial
import time
from datetime import datetime
import io
arduino = serial.Serial('COM13', 115200)

cap= cv2.VideoCapture(0)

width= int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
height= int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
font = cv2.FONT_HERSHEY_SIMPLEX 
writer= cv2.VideoWriter('Pelanggaran/Pelanggaran.mp4', cv2.VideoWriter_fourcc(*'DIVX'), 20, (width,height))
frameTime = 1



while True:
    ret,frame= cap.read()
    writer.write(frame)

    now = datetime.now().time()
    current_time = now.strftime("%H:%M:%S")
    
    cv2.putText(frame, current_time, (7, 70), font, 1, (100, 255, 0), 3, cv2.LINE_AA) 
    writer.write(frame.astype('uint8'))
    cv2.imshow('frame', frame)


    #line = arduino.readline().decode('utf-8').rstrip()
    
    bytesToRead = arduino.inWaiting()
    

    number = arduino.read(bytesToRead).decode('utf-8').rstrip()
    trigger = str(number)
    print(trigger)
    
    if trigger == "1":
        break

    if cv2.waitKey(frameTime) & 0xFF == 27:
        break
    
    #time.sleep(0.2)

cap.release()
writer.release()
cv2.destroyAllWindows()