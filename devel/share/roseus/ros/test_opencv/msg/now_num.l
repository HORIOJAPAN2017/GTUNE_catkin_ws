;; Auto-generated. Do not edit!


(when (boundp 'test_opencv::now_num)
  (if (not (find-package "TEST_OPENCV"))
    (make-package "TEST_OPENCV"))
  (shadow 'now_num (find-package "TEST_OPENCV")))
(unless (find-package "TEST_OPENCV::NOW_NUM")
  (make-package "TEST_OPENCV::NOW_NUM"))

(in-package "ROS")
;;//! \htmlinclude now_num.msg.html


(defclass test_opencv::now_num
  :super ros::object
  :slots (_num_point _last_point ))

(defmethod test_opencv::now_num
  (:init
   (&key
    ((:num_point __num_point) 0)
    ((:last_point __last_point) 0)
    )
   (send-super :init)
   (setq _num_point (round __num_point))
   (setq _last_point (round __last_point))
   self)
  (:num_point
   (&optional __num_point)
   (if __num_point (setq _num_point __num_point)) _num_point)
  (:last_point
   (&optional __last_point)
   (if __last_point (setq _last_point __last_point)) _last_point)
  (:serialization-length
   ()
   (+
    ;; int16 _num_point
    2
    ;; int16 _last_point
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16 _num_point
       (write-word _num_point s)
     ;; int16 _last_point
       (write-word _last_point s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16 _num_point
     (setq _num_point (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _last_point
     (setq _last_point (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get test_opencv::now_num :md5sum-) "9cb6f0f19d99868baadd61903a6a1bea")
(setf (get test_opencv::now_num :datatype-) "test_opencv/now_num")
(setf (get test_opencv::now_num :definition-)
      "int16 num_point
int16 last_point

")



(provide :test_opencv/now_num "9cb6f0f19d99868baadd61903a6a1bea")


