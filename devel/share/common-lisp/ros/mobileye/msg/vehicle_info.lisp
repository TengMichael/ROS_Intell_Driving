; Auto-generated. Do not edit!


(cl:in-package mobileye-msg)


;//! \htmlinclude vehicle_info.msg.html

(cl:defclass <vehicle_info> (roslisp-msg-protocol:ros-message)
  ((Speed
    :reader Speed
    :initarg :Speed
    :type cl:float
    :initform 0.0)
   (YawAngle
    :reader YawAngle
    :initarg :YawAngle
    :type cl:float
    :initform 0.0)
   (PitchAngle
    :reader PitchAngle
    :initarg :PitchAngle
    :type cl:float
    :initform 0.0))
)

(cl:defclass vehicle_info (<vehicle_info>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <vehicle_info>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'vehicle_info)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye-msg:<vehicle_info> is deprecated: use mobileye-msg:vehicle_info instead.")))

(cl:ensure-generic-function 'Speed-val :lambda-list '(m))
(cl:defmethod Speed-val ((m <vehicle_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Speed-val is deprecated.  Use mobileye-msg:Speed instead.")
  (Speed m))

(cl:ensure-generic-function 'YawAngle-val :lambda-list '(m))
(cl:defmethod YawAngle-val ((m <vehicle_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:YawAngle-val is deprecated.  Use mobileye-msg:YawAngle instead.")
  (YawAngle m))

(cl:ensure-generic-function 'PitchAngle-val :lambda-list '(m))
(cl:defmethod PitchAngle-val ((m <vehicle_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:PitchAngle-val is deprecated.  Use mobileye-msg:PitchAngle instead.")
  (PitchAngle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <vehicle_info>) ostream)
  "Serializes a message object of type '<vehicle_info>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'YawAngle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'PitchAngle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <vehicle_info>) istream)
  "Deserializes a message object of type '<vehicle_info>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Speed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'YawAngle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'PitchAngle) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<vehicle_info>)))
  "Returns string type for a message object of type '<vehicle_info>"
  "mobileye/vehicle_info")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'vehicle_info)))
  "Returns string type for a message object of type 'vehicle_info"
  "mobileye/vehicle_info")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<vehicle_info>)))
  "Returns md5sum for a message object of type '<vehicle_info>"
  "4ce4cbfa04d5e948da15a941ff921a8a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'vehicle_info)))
  "Returns md5sum for a message object of type 'vehicle_info"
  "4ce4cbfa04d5e948da15a941ff921a8a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<vehicle_info>)))
  "Returns full string definition for message of type '<vehicle_info>"
  (cl:format cl:nil "float32 Speed~%float32 YawAngle~%float32 PitchAngle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'vehicle_info)))
  "Returns full string definition for message of type 'vehicle_info"
  (cl:format cl:nil "float32 Speed~%float32 YawAngle~%float32 PitchAngle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <vehicle_info>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <vehicle_info>))
  "Converts a ROS message object to a list"
  (cl:list 'vehicle_info
    (cl:cons ':Speed (Speed msg))
    (cl:cons ':YawAngle (YawAngle msg))
    (cl:cons ':PitchAngle (PitchAngle msg))
))
