; Auto-generated. Do not edit!


(cl:in-package test_opencv-msg)


;//! \htmlinclude now_num.msg.html

(cl:defclass <now_num> (roslisp-msg-protocol:ros-message)
  ((num_point
    :reader num_point
    :initarg :num_point
    :type cl:fixnum
    :initform 0)
   (last_point
    :reader last_point
    :initarg :last_point
    :type cl:fixnum
    :initform 0))
)

(cl:defclass now_num (<now_num>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <now_num>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'now_num)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test_opencv-msg:<now_num> is deprecated: use test_opencv-msg:now_num instead.")))

(cl:ensure-generic-function 'num_point-val :lambda-list '(m))
(cl:defmethod num_point-val ((m <now_num>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:num_point-val is deprecated.  Use test_opencv-msg:num_point instead.")
  (num_point m))

(cl:ensure-generic-function 'last_point-val :lambda-list '(m))
(cl:defmethod last_point-val ((m <now_num>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_opencv-msg:last_point-val is deprecated.  Use test_opencv-msg:last_point instead.")
  (last_point m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <now_num>) ostream)
  "Serializes a message object of type '<now_num>"
  (cl:let* ((signed (cl:slot-value msg 'num_point)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'last_point)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <now_num>) istream)
  "Deserializes a message object of type '<now_num>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'num_point) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'last_point) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<now_num>)))
  "Returns string type for a message object of type '<now_num>"
  "test_opencv/now_num")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'now_num)))
  "Returns string type for a message object of type 'now_num"
  "test_opencv/now_num")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<now_num>)))
  "Returns md5sum for a message object of type '<now_num>"
  "9cb6f0f19d99868baadd61903a6a1bea")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'now_num)))
  "Returns md5sum for a message object of type 'now_num"
  "9cb6f0f19d99868baadd61903a6a1bea")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<now_num>)))
  "Returns full string definition for message of type '<now_num>"
  (cl:format cl:nil "int16 num_point~%int16 last_point~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'now_num)))
  "Returns full string definition for message of type 'now_num"
  (cl:format cl:nil "int16 num_point~%int16 last_point~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <now_num>))
  (cl:+ 0
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <now_num>))
  "Converts a ROS message object to a list"
  (cl:list 'now_num
    (cl:cons ':num_point (num_point msg))
    (cl:cons ':last_point (last_point msg))
))
