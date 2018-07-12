;; Auto-generated. Do not edit!


(when (boundp 'test_opencv::path)
  (if (not (find-package "TEST_OPENCV"))
    (make-package "TEST_OPENCV"))
  (shadow 'path (find-package "TEST_OPENCV")))
(unless (find-package "TEST_OPENCV::PATH")
  (make-package "TEST_OPENCV::PATH"))

(in-package "ROS")
;;//! \htmlinclude path.msg.html


(defclass test_opencv::path
  :super ros::object
  :slots (_gridX _gridY _height _width _theta _number_of_path ))

(defmethod test_opencv::path
  (:init
   (&key
    ((:gridX __gridX) (make-array 0 :initial-element 0 :element-type :integer))
    ((:gridY __gridY) (make-array 0 :initial-element 0 :element-type :integer))
    ((:height __height) (make-array 0 :initial-element 0 :element-type :integer))
    ((:width __width) (make-array 0 :initial-element 0 :element-type :integer))
    ((:theta __theta) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:number_of_path __number_of_path) 0)
    )
   (send-super :init)
   (setq _gridX __gridX)
   (setq _gridY __gridY)
   (setq _height __height)
   (setq _width __width)
   (setq _theta __theta)
   (setq _number_of_path (round __number_of_path))
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
  (:number_of_path
   (&optional __number_of_path)
   (if __number_of_path (setq _number_of_path __number_of_path)) _number_of_path)
  (:serialization-length
   ()
   (+
    ;; int16[] _gridX
    (* 2    (length _gridX)) 4
    ;; int16[] _gridY
    (* 2    (length _gridY)) 4
    ;; int16[] _height
    (* 2    (length _height)) 4
    ;; int16[] _width
    (* 2    (length _width)) 4
    ;; float32[] _theta
    (* 4    (length _theta)) 4
    ;; int8 _number_of_path
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16[] _gridX
     (write-long (length _gridX) s)
     (dotimes (i (length _gridX))
       (write-word (elt _gridX i) s)
       )
     ;; int16[] _gridY
     (write-long (length _gridY) s)
     (dotimes (i (length _gridY))
       (write-word (elt _gridY i) s)
       )
     ;; int16[] _height
     (write-long (length _height) s)
     (dotimes (i (length _height))
       (write-word (elt _height i) s)
       )
     ;; int16[] _width
     (write-long (length _width) s)
     (dotimes (i (length _width))
       (write-word (elt _width i) s)
       )
     ;; float32[] _theta
     (write-long (length _theta) s)
     (dotimes (i (length _theta))
       (sys::poke (elt _theta i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; int8 _number_of_path
       (write-byte _number_of_path s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16[] _gridX
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _gridX (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _gridX i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     ))
   ;; int16[] _gridY
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _gridY (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _gridY i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     ))
   ;; int16[] _height
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _height (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _height i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     ))
   ;; int16[] _width
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _width (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _width i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     ))
   ;; float32[] _theta
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _theta (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _theta i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; int8 _number_of_path
     (setq _number_of_path (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _number_of_path 127) (setq _number_of_path (- _number_of_path 256)))
   ;;
   self)
  )

(setf (get test_opencv::path :md5sum-) "b267f94d1fa74439d6549ff37a25b875")
(setf (get test_opencv::path :datatype-) "test_opencv/path")
(setf (get test_opencv::path :definition-)
      "int16[] gridX
int16[] gridY
int16[] height
int16[] width
float32[] theta
int8 number_of_path

")



(provide :test_opencv/path "b267f94d1fa74439d6549ff37a25b875")


