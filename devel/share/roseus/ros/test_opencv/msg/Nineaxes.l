;; Auto-generated. Do not edit!


(when (boundp 'test_opencv::Nineaxes)
  (if (not (find-package "TEST_OPENCV"))
    (make-package "TEST_OPENCV"))
  (shadow 'Nineaxes (find-package "TEST_OPENCV")))
(unless (find-package "TEST_OPENCV::NINEAXES")
  (make-package "TEST_OPENCV::NINEAXES"))

(in-package "ROS")
;;//! \htmlinclude Nineaxes.msg.html


(defclass test_opencv::Nineaxes
  :super ros::object
  :slots (_Time _EulerHeading _EulerRoll _AccelerometerX _AccelerometerY _AccelerometerZ _LinearAccelerX _LinearAccelerY _LinearAccelerZ _GravAccelerX _GravAccelerY _GravAccelerZ _EulerPitch ))

(defmethod test_opencv::Nineaxes
  (:init
   (&key
    ((:Time __Time) 0.0)
    ((:EulerHeading __EulerHeading) 0.0)
    ((:EulerRoll __EulerRoll) 0.0)
    ((:AccelerometerX __AccelerometerX) 0.0)
    ((:AccelerometerY __AccelerometerY) 0.0)
    ((:AccelerometerZ __AccelerometerZ) 0.0)
    ((:LinearAccelerX __LinearAccelerX) 0.0)
    ((:LinearAccelerY __LinearAccelerY) 0.0)
    ((:LinearAccelerZ __LinearAccelerZ) 0.0)
    ((:GravAccelerX __GravAccelerX) 0.0)
    ((:GravAccelerY __GravAccelerY) 0.0)
    ((:GravAccelerZ __GravAccelerZ) 0.0)
    ((:EulerPitch __EulerPitch) 0.0)
    )
   (send-super :init)
   (setq _Time (float __Time))
   (setq _EulerHeading (float __EulerHeading))
   (setq _EulerRoll (float __EulerRoll))
   (setq _AccelerometerX (float __AccelerometerX))
   (setq _AccelerometerY (float __AccelerometerY))
   (setq _AccelerometerZ (float __AccelerometerZ))
   (setq _LinearAccelerX (float __LinearAccelerX))
   (setq _LinearAccelerY (float __LinearAccelerY))
   (setq _LinearAccelerZ (float __LinearAccelerZ))
   (setq _GravAccelerX (float __GravAccelerX))
   (setq _GravAccelerY (float __GravAccelerY))
   (setq _GravAccelerZ (float __GravAccelerZ))
   (setq _EulerPitch (float __EulerPitch))
   self)
  (:Time
   (&optional __Time)
   (if __Time (setq _Time __Time)) _Time)
  (:EulerHeading
   (&optional __EulerHeading)
   (if __EulerHeading (setq _EulerHeading __EulerHeading)) _EulerHeading)
  (:EulerRoll
   (&optional __EulerRoll)
   (if __EulerRoll (setq _EulerRoll __EulerRoll)) _EulerRoll)
  (:AccelerometerX
   (&optional __AccelerometerX)
   (if __AccelerometerX (setq _AccelerometerX __AccelerometerX)) _AccelerometerX)
  (:AccelerometerY
   (&optional __AccelerometerY)
   (if __AccelerometerY (setq _AccelerometerY __AccelerometerY)) _AccelerometerY)
  (:AccelerometerZ
   (&optional __AccelerometerZ)
   (if __AccelerometerZ (setq _AccelerometerZ __AccelerometerZ)) _AccelerometerZ)
  (:LinearAccelerX
   (&optional __LinearAccelerX)
   (if __LinearAccelerX (setq _LinearAccelerX __LinearAccelerX)) _LinearAccelerX)
  (:LinearAccelerY
   (&optional __LinearAccelerY)
   (if __LinearAccelerY (setq _LinearAccelerY __LinearAccelerY)) _LinearAccelerY)
  (:LinearAccelerZ
   (&optional __LinearAccelerZ)
   (if __LinearAccelerZ (setq _LinearAccelerZ __LinearAccelerZ)) _LinearAccelerZ)
  (:GravAccelerX
   (&optional __GravAccelerX)
   (if __GravAccelerX (setq _GravAccelerX __GravAccelerX)) _GravAccelerX)
  (:GravAccelerY
   (&optional __GravAccelerY)
   (if __GravAccelerY (setq _GravAccelerY __GravAccelerY)) _GravAccelerY)
  (:GravAccelerZ
   (&optional __GravAccelerZ)
   (if __GravAccelerZ (setq _GravAccelerZ __GravAccelerZ)) _GravAccelerZ)
  (:EulerPitch
   (&optional __EulerPitch)
   (if __EulerPitch (setq _EulerPitch __EulerPitch)) _EulerPitch)
  (:serialization-length
   ()
   (+
    ;; float32 _Time
    4
    ;; float32 _EulerHeading
    4
    ;; float32 _EulerRoll
    4
    ;; float32 _AccelerometerX
    4
    ;; float32 _AccelerometerY
    4
    ;; float32 _AccelerometerZ
    4
    ;; float32 _LinearAccelerX
    4
    ;; float32 _LinearAccelerY
    4
    ;; float32 _LinearAccelerZ
    4
    ;; float32 _GravAccelerX
    4
    ;; float32 _GravAccelerY
    4
    ;; float32 _GravAccelerZ
    4
    ;; float32 _EulerPitch
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _Time
       (sys::poke _Time (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _EulerHeading
       (sys::poke _EulerHeading (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _EulerRoll
       (sys::poke _EulerRoll (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _AccelerometerX
       (sys::poke _AccelerometerX (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _AccelerometerY
       (sys::poke _AccelerometerY (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _AccelerometerZ
       (sys::poke _AccelerometerZ (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _LinearAccelerX
       (sys::poke _LinearAccelerX (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _LinearAccelerY
       (sys::poke _LinearAccelerY (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _LinearAccelerZ
       (sys::poke _LinearAccelerZ (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _GravAccelerX
       (sys::poke _GravAccelerX (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _GravAccelerY
       (sys::poke _GravAccelerY (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _GravAccelerZ
       (sys::poke _GravAccelerZ (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _EulerPitch
       (sys::poke _EulerPitch (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _Time
     (setq _Time (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _EulerHeading
     (setq _EulerHeading (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _EulerRoll
     (setq _EulerRoll (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _AccelerometerX
     (setq _AccelerometerX (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _AccelerometerY
     (setq _AccelerometerY (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _AccelerometerZ
     (setq _AccelerometerZ (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _LinearAccelerX
     (setq _LinearAccelerX (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _LinearAccelerY
     (setq _LinearAccelerY (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _LinearAccelerZ
     (setq _LinearAccelerZ (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _GravAccelerX
     (setq _GravAccelerX (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _GravAccelerY
     (setq _GravAccelerY (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _GravAccelerZ
     (setq _GravAccelerZ (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _EulerPitch
     (setq _EulerPitch (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get test_opencv::Nineaxes :md5sum-) "2fcf5021dd14ec1f7c21636820e9d8c9")
(setf (get test_opencv::Nineaxes :datatype-) "test_opencv/Nineaxes")
(setf (get test_opencv::Nineaxes :definition-)
      "float32 Time
float32 EulerHeading
float32 EulerRoll
float32 AccelerometerX
float32 AccelerometerY
float32 AccelerometerZ
float32 LinearAccelerX
float32 LinearAccelerY
float32 LinearAccelerZ
float32 GravAccelerX
float32 GravAccelerY
float32 GravAccelerZ
float32 EulerPitch


")



(provide :test_opencv/Nineaxes "2fcf5021dd14ec1f7c21636820e9d8c9")


