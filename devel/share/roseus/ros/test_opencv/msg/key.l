;; Auto-generated. Do not edit!


(when (boundp 'test_opencv::key)
  (if (not (find-package "TEST_OPENCV"))
    (make-package "TEST_OPENCV"))
  (shadow 'key (find-package "TEST_OPENCV")))
(unless (find-package "TEST_OPENCV::KEY")
  (make-package "TEST_OPENCV::KEY"))

(in-package "ROS")
;;//! \htmlinclude key.msg.html


(defclass test_opencv::key
  :super ros::object
  :slots (_ENTER ))

(defmethod test_opencv::key
  (:init
   (&key
    ((:ENTER __ENTER) 0)
    )
   (send-super :init)
   (setq _ENTER (round __ENTER))
   self)
  (:ENTER
   (&optional __ENTER)
   (if __ENTER (setq _ENTER __ENTER)) _ENTER)
  (:serialization-length
   ()
   (+
    ;; int8 _ENTER
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _ENTER
       (write-byte _ENTER s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _ENTER
     (setq _ENTER (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _ENTER 127) (setq _ENTER (- _ENTER 256)))
   ;;
   self)
  )

(setf (get test_opencv::key :md5sum-) "e21e266780e9363474b6e9c1df4da0d9")
(setf (get test_opencv::key :datatype-) "test_opencv/key")
(setf (get test_opencv::key :definition-)
      "int8 ENTER

")



(provide :test_opencv/key "e21e266780e9363474b6e9c1df4da0d9")


