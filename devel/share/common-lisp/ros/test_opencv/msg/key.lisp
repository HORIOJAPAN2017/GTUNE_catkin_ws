; Auto-generated. Do not edit!


(cl:in-package test_opencv-msg)


;//! \htmlinclude key.msg.html

(cl:defclass <key> (roslisp-msg-protocol:ros-message)
  ((ENTER
    :reader ENTER
    :initarg :ENTER
    :type cl:fixnum
    :initform 0))
)

(cl:defclass key (<key>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <key>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'key)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test_opencv-msg:<key> is deprecated: use test_opencv-msg:key instead.")))

(cl:ensure-generic-function 'ENTER-val :lambda-list '(m))
(cl:defmethod ENTER-val ((m <key>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:ENTER-val is deprecated.  Use test_opencv-msg:ENTER instead.")
  (ENTER m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <key>) ostream)
  "Serializes a message object of type '<key>"
  (cl:let* ((signed (cl:slot-value msg 'ENTER)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <key>) istream)
  "Deserializes a message object of type '<key>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ENTER) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<key>)))
  "Returns string type for a message object of type '<key>"
  "test_opencv/key")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'key)))
  "Returns string type for a message object of type 'key"
  "test_opencv/key")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<key>)))
  "Returns md5sum for a message object of type '<key>"
  "e21e266780e9363474b6e9c1df4da0d9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'key)))
  "Returns md5sum for a message object of type 'key"
  "e21e266780e9363474b6e9c1df4da0d9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<key>)))
  "Returns full string definition for message of type '<key>"
  (cl:format cl:nil "int8 ENTER~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'key)))
  "Returns full string definition for message of type 'key"
  (cl:format cl:nil "int8 ENTER~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <key>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <key>))
  "Converts a ROS message object to a list"
  (cl:list 'key
    (cl:cons ':ENTER (ENTER msg))
))
