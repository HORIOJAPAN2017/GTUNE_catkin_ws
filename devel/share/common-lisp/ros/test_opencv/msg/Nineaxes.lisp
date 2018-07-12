; Auto-generated. Do not edit!


(cl:in-package test_opencv-msg)


;//! \htmlinclude Nineaxes.msg.html

(cl:defclass <Nineaxes> (roslisp-msg-protocol:ros-message)
  ((Time
    :reader Time
    :initarg :Time
    :type cl:float
    :initform 0.0)
   (EulerHeading
    :reader EulerHeading
    :initarg :EulerHeading
    :type cl:float
    :initform 0.0)
   (EulerRoll
    :reader EulerRoll
    :initarg :EulerRoll
    :type cl:float
    :initform 0.0)
   (AccelerometerX
    :reader AccelerometerX
    :initarg :AccelerometerX
    :type cl:float
    :initform 0.0)
   (AccelerometerY
    :reader AccelerometerY
    :initarg :AccelerometerY
    :type cl:float
    :initform 0.0)
   (AccelerometerZ
    :reader AccelerometerZ
    :initarg :AccelerometerZ
    :type cl:float
    :initform 0.0)
   (LinearAccelerX
    :reader LinearAccelerX
    :initarg :LinearAccelerX
    :type cl:float
    :initform 0.0)
   (LinearAccelerY
    :reader LinearAccelerY
    :initarg :LinearAccelerY
    :type cl:float
    :initform 0.0)
   (LinearAccelerZ
    :reader LinearAccelerZ
    :initarg :LinearAccelerZ
    :type cl:float
    :initform 0.0)
   (GravAccelerX
    :reader GravAccelerX
    :initarg :GravAccelerX
    :type cl:float
    :initform 0.0)
   (GravAccelerY
    :reader GravAccelerY
    :initarg :GravAccelerY
    :type cl:float
    :initform 0.0)
   (GravAccelerZ
    :reader GravAccelerZ
    :initarg :GravAccelerZ
    :type cl:float
    :initform 0.0)
   (EulerPitch
    :reader EulerPitch
    :initarg :EulerPitch
    :type cl:float
    :initform 0.0))
)

(cl:defclass Nineaxes (<Nineaxes>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Nineaxes>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Nineaxes)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test_opencv-msg:<Nineaxes> is deprecated: use test_opencv-msg:Nineaxes instead.")))

(cl:ensure-generic-function 'Time-val :lambda-list '(m))
(cl:defmethod Time-val ((m <Nineaxes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:Time-val is deprecated.  Use test_opencv-msg:Time instead.")
  (Time m))

(cl:ensure-generic-function 'EulerHeading-val :lambda-list '(m))
(cl:defmethod EulerHeading-val ((m <Nineaxes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:EulerHeading-val is deprecated.  Use test_opencv-msg:EulerHeading instead.")
  (EulerHeading m))

(cl:ensure-generic-function 'EulerRoll-val :lambda-list '(m))
(cl:defmethod EulerRoll-val ((m <Nineaxes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:EulerRoll-val is deprecated.  Use test_opencv-msg:EulerRoll instead.")
  (EulerRoll m))

(cl:ensure-generic-function 'AccelerometerX-val :lambda-list '(m))
(cl:defmethod AccelerometerX-val ((m <Nineaxes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:AccelerometerX-val is deprecated.  Use test_opencv-msg:AccelerometerX instead.")
  (AccelerometerX m))

(cl:ensure-generic-function 'AccelerometerY-val :lambda-list '(m))
(cl:defmethod AccelerometerY-val ((m <Nineaxes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:AccelerometerY-val is deprecated.  Use test_opencv-msg:AccelerometerY instead.")
  (AccelerometerY m))

(cl:ensure-generic-function 'AccelerometerZ-val :lambda-list '(m))
(cl:defmethod AccelerometerZ-val ((m <Nineaxes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:AccelerometerZ-val is deprecated.  Use test_opencv-msg:AccelerometerZ instead.")
  (AccelerometerZ m))

(cl:ensure-generic-function 'LinearAccelerX-val :lambda-list '(m))
(cl:defmethod LinearAccelerX-val ((m <Nineaxes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:LinearAccelerX-val is deprecated.  Use test_opencv-msg:LinearAccelerX instead.")
  (LinearAccelerX m))

(cl:ensure-generic-function 'LinearAccelerY-val :lambda-list '(m))
(cl:defmethod LinearAccelerY-val ((m <Nineaxes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:LinearAccelerY-val is deprecated.  Use test_opencv-msg:LinearAccelerY instead.")
  (LinearAccelerY m))

(cl:ensure-generic-function 'LinearAccelerZ-val :lambda-list '(m))
(cl:defmethod LinearAccelerZ-val ((m <Nineaxes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:LinearAccelerZ-val is deprecated.  Use test_opencv-msg:LinearAccelerZ instead.")
  (LinearAccelerZ m))

(cl:ensure-generic-function 'GravAccelerX-val :lambda-list '(m))
(cl:defmethod GravAccelerX-val ((m <Nineaxes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:GravAccelerX-val is deprecated.  Use test_opencv-msg:GravAccelerX instead.")
  (GravAccelerX m))

(cl:ensure-generic-function 'GravAccelerY-val :lambda-list '(m))
(cl:defmethod GravAccelerY-val ((m <Nineaxes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:GravAccelerY-val is deprecated.  Use test_opencv-msg:GravAccelerY instead.")
  (GravAccelerY m))

(cl:ensure-generic-function 'GravAccelerZ-val :lambda-list '(m))
(cl:defmethod GravAccelerZ-val ((m <Nineaxes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:GravAccelerZ-val is deprecated.  Use test_opencv-msg:GravAccelerZ instead.")
  (GravAccelerZ m))

(cl:ensure-generic-function 'EulerPitch-val :lambda-list '(m))
(cl:defmethod EulerPitch-val ((m <Nineaxes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:EulerPitch-val is deprecated.  Use test_opencv-msg:EulerPitch instead.")
  (EulerPitch m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Nineaxes>) ostream)
  "Serializes a message object of type '<Nineaxes>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Time))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'EulerHeading))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'EulerRoll))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'AccelerometerX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'AccelerometerY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'AccelerometerZ))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'LinearAccelerX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'LinearAccelerY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'LinearAccelerZ))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'GravAccelerX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'GravAccelerY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'GravAccelerZ))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'EulerPitch))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Nineaxes>) istream)
  "Deserializes a message object of type '<Nineaxes>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Time) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'EulerHeading) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'EulerRoll) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'AccelerometerX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'AccelerometerY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'AccelerometerZ) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'LinearAccelerX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'LinearAccelerY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'LinearAccelerZ) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'GravAccelerX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'GravAccelerY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'GravAccelerZ) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'EulerPitch) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Nineaxes>)))
  "Returns string type for a message object of type '<Nineaxes>"
  "test_opencv/Nineaxes")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Nineaxes)))
  "Returns string type for a message object of type 'Nineaxes"
  "test_opencv/Nineaxes")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Nineaxes>)))
  "Returns md5sum for a message object of type '<Nineaxes>"
  "2fcf5021dd14ec1f7c21636820e9d8c9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Nineaxes)))
  "Returns md5sum for a message object of type 'Nineaxes"
  "2fcf5021dd14ec1f7c21636820e9d8c9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Nineaxes>)))
  "Returns full string definition for message of type '<Nineaxes>"
  (cl:format cl:nil "float32 Time~%float32 EulerHeading~%float32 EulerRoll~%float32 AccelerometerX~%float32 AccelerometerY~%float32 AccelerometerZ~%float32 LinearAccelerX~%float32 LinearAccelerY~%float32 LinearAccelerZ~%float32 GravAccelerX~%float32 GravAccelerY~%float32 GravAccelerZ~%float32 EulerPitch~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Nineaxes)))
  "Returns full string definition for message of type 'Nineaxes"
  (cl:format cl:nil "float32 Time~%float32 EulerHeading~%float32 EulerRoll~%float32 AccelerometerX~%float32 AccelerometerY~%float32 AccelerometerZ~%float32 LinearAccelerX~%float32 LinearAccelerY~%float32 LinearAccelerZ~%float32 GravAccelerX~%float32 GravAccelerY~%float32 GravAccelerZ~%float32 EulerPitch~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Nineaxes>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Nineaxes>))
  "Converts a ROS message object to a list"
  (cl:list 'Nineaxes
    (cl:cons ':Time (Time msg))
    (cl:cons ':EulerHeading (EulerHeading msg))
    (cl:cons ':EulerRoll (EulerRoll msg))
    (cl:cons ':AccelerometerX (AccelerometerX msg))
    (cl:cons ':AccelerometerY (AccelerometerY msg))
    (cl:cons ':AccelerometerZ (AccelerometerZ msg))
    (cl:cons ':LinearAccelerX (LinearAccelerX msg))
    (cl:cons ':LinearAccelerY (LinearAccelerY msg))
    (cl:cons ':LinearAccelerZ (LinearAccelerZ msg))
    (cl:cons ':GravAccelerX (GravAccelerX msg))
    (cl:cons ':GravAccelerY (GravAccelerY msg))
    (cl:cons ':GravAccelerZ (GravAccelerZ msg))
    (cl:cons ':EulerPitch (EulerPitch msg))
))
