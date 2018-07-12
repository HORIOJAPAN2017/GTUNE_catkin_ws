;; Auto-generated. Do not edit!


(when (boundp 'test_opencv::coordinate)
  (if (not (find-package "TEST_OPENCV"))
    (make-package "TEST_OPENCV"))
  (shadow 'coordinate (find-package "TEST_OPENCV")))
(unless (find-package "TEST_OPENCV::COORDINATE")
  (make-package "TEST_OPENCV::COORDINATE"))

(in-package "ROS")
;;//! \htmlinclude coordinate.msg.html


(defclass test_opencv::coordinate
  :super ros::object
  :slots (_gridX _gridY _height _width _theta ))

(defmethod test_opencv::coordinate
  (:init
   (&key
    ((:gridX __gridX) 0)
    ((:gridY __gridY) 0)
    ((:height __height) 0)
    ((:width __width) 0)
    ((:theta __theta) 0.0)
    )
   (send-super :init)
   (setq _gridX (round __gridX))
   (setq _gridY (round __gridY))
   (setq _height (round __height))
   (setq _width (round __width))
   (setq _theta (float __theta))
   self)
  (:gridX
   (&optional __gridX)
   (if __gridX (setq _gridX __gridX)) _gridX)
  (:gridY
   (&optional __gridY)
   (if __gridY (setq _gridY __gridY)) _gridY)
  (:height
   (&optional __height)
   (if __height (setq _height __height)) _height)
  (:width
   (&optional __width)
   (if __width (setq _width __width)) _width)
  (:theta
   (&optional __theta)
   (if __theta (setq _theta __theta)) _theta)
  (:serialization-length
   ()
   (+
    ;; int8 _gridX
    1
    ;; int8 _gridY
    1
    ;; int16 _height
    2
    ;; int16 _width
    2
    ;; float32 _theta
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _gridX
       (write-byte _gridX s)
     ;; int8 _gridY
       (write-byte _gridY s)
     ;; int16 _height
       (write-word _height s)
     ;; int16 _width
       (write-word _width s)
     ;; float32 _theta
       (sys::poke _theta (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _gridX
     (setq _gridX (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _gridX 127) (setq _gridX (- _gridX 256)))
   ;; int8 _gridY
     (setq _gridY (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _gridY 127) (setq _gridY (- _gridY 256)))
   ;; int16 _height
     (setq _height (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _width
     (setq _width (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; float32 _theta
     (setq _theta (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get test_opencv::coordinate :md5sum-) "fb7916e2ededf5c749b05192bc80a8dd")
(setf (get test_opencv::coordinate :datatype-) "test_opencv/coordinate")
(setf (get test_opencv::coordinate :definition-)
      "int8 gridX
int8 gridY
int16 height
int16 width
float32 theta

")



(provide :test_opencv/coordinate "fb7916e2ededf5c749b05192bc80a8dd")


