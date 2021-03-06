; Auto-generated. Do not edit!


(cl:in-package test_opencv-msg)


;//! \htmlinclude coordinate.msg.html

(cl:defclass <coordinate> (roslisp-msg-protocol:ros-message)
  ((gridX
    :reader gridX
    :initarg :gridX
    :type cl:fixnum
    :initform 0)
   (gridY
    :reader gridY
    :initarg :gridY
    :type cl:fixnum
    :initform 0)
   (height
    :reader height
    :initarg :height
    :type cl:fixnum
    :initform 0)
   (width
    :reader width
    :initarg :width
    :type cl:fixnum
    :initform 0)
   (theta
    :reader theta
    :initarg :theta
    :type cl:float
    :initform 0.0))
)

(cl:defclass coordinate (<coordinate>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <coordinate>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'coordinate)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test_opencv-msg:<coordinate> is deprecated: use test_opencv-msg:coordinate instead.")))

(cl:ensure-generic-function 'gridX-val :lambda-list '(m))
(cl:defmethod gridX-val ((m <coordinate>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:gridX-val is deprecated.  Use test_opencv-msg:gridX instead.")
  (gridX m))

(cl:ensure-generic-function 'gridY-val :lambda-list '(m))
(cl:defmethod gridY-val ((m <coordinate>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:gridY-val is deprecated.  Use test_opencv-msg:gridY instead.")
  (gridY m))

(cl:ensure-generic-function 'height-val :lambda-list '(m))
(cl:defmethod height-val ((m <coordinate>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:height-val is deprecated.  Use test_opencv-msg:height instead.")
  (height m))

(cl:ensure-generic-function 'width-val :lambda-list '(m))
(cl:defmethod width-val ((m <coordinate>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:width-val is deprecated.  Use test_opencv-msg:width instead.")
  (width m))

(cl:ensure-generic-function 'theta-val :lambda-list '(m))
(cl:defmethod theta-val ((m <coordinate>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:theta-val is deprecated.  Use test_opencv-msg:theta instead.")
  (theta m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <coordinate>) ostream)
  "Serializes a message object of type '<coordinate>"
  (cl:let* ((signed (cl:slot-value msg 'gridX)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'gridY)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'height)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'width)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'theta))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <coordinate>) istream)
  "Deserializes a message object of type '<coordinate>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'gridX) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'gridY) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'height) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'width) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'theta) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<coordinate>)))
  "Returns string type for a message object of type '<coordinate>"
  "test_opencv/coordinate")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'coordinate)))
  "Returns string type for a message object of type 'coordinate"
  "test_opencv/coordinate")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<coordinate>)))
  "Returns md5sum for a message object of type '<coordinate>"
  "fb7916e2ededf5c749b05192bc80a8dd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'coordinate)))
  "Returns md5sum for a message object of type 'coordinate"
  "fb7916e2ededf5c749b05192bc80a8dd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<coordinate>)))
  "Returns full string definition for message of type '<coordinate>"
  (cl:format cl:nil "int8 gridX~%int8 gridY~%int16 height~%int16 width~%float32 theta~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'coordinate)))
  "Returns full string definition for message of type 'coordinate"
  (cl:format cl:nil "int8 gridX~%int8 gridY~%int16 height~%int16 width~%float32 theta~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <coordinate>))
  (cl:+ 0
     1
     1
     2
     2
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <coordinate>))
  "Converts a ROS message object to a list"
  (cl:list 'coordinate
    (cl:cons ':gridX (gridX msg))
    (cl:cons ':gridY (gridY msg))
    (cl:cons ':height (height msg))
    (cl:cons ':width (width msg))
    (cl:cons ':theta (theta msg))
))
