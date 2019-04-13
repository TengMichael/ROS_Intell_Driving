; Auto-generated. Do not edit!


(cl:in-package milradar-msg)


;//! \htmlinclude obj208.msg.html

(cl:defclass <obj208> (roslisp-msg-protocol:ros-message)
  ((ID
    :reader ID
    :initarg :ID
    :type cl:fixnum
    :initform 0)
   (timestamp
    :reader timestamp
    :initarg :timestamp
    :type cl:integer
    :initform 0)
   (DistX
    :reader DistX
    :initarg :DistX
    :type cl:float
    :initform 0.0)
   (DistY
    :reader DistY
    :initarg :DistY
    :type cl:float
    :initform 0.0)
   (index
    :reader index
    :initarg :index
    :type cl:fixnum
    :initform 0)
   (VrelX
    :reader VrelX
    :initarg :VrelX
    :type cl:float
    :initform 0.0)
   (VrelY
    :reader VrelY
    :initarg :VrelY
    :type cl:float
    :initform 0.0)
   (RCS
    :reader RCS
    :initarg :RCS
    :type cl:float
    :initform 0.0)
   (Lifetime
    :reader Lifetime
    :initarg :Lifetime
    :type cl:float
    :initform 0.0))
)

(cl:defclass obj208 (<obj208>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <obj208>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'obj208)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name milradar-msg:<obj208> is deprecated: use milradar-msg:obj208 instead.")))

(cl:ensure-generic-function 'ID-val :lambda-list '(m))
(cl:defmethod ID-val ((m <obj208>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:ID-val is deprecated.  Use milradar-msg:ID instead.")
  (ID m))

(cl:ensure-generic-function 'timestamp-val :lambda-list '(m))
(cl:defmethod timestamp-val ((m <obj208>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:timestamp-val is deprecated.  Use milradar-msg:timestamp instead.")
  (timestamp m))

(cl:ensure-generic-function 'DistX-val :lambda-list '(m))
(cl:defmethod DistX-val ((m <obj208>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:DistX-val is deprecated.  Use milradar-msg:DistX instead.")
  (DistX m))

(cl:ensure-generic-function 'DistY-val :lambda-list '(m))
(cl:defmethod DistY-val ((m <obj208>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:DistY-val is deprecated.  Use milradar-msg:DistY instead.")
  (DistY m))

(cl:ensure-generic-function 'index-val :lambda-list '(m))
(cl:defmethod index-val ((m <obj208>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:index-val is deprecated.  Use milradar-msg:index instead.")
  (index m))

(cl:ensure-generic-function 'VrelX-val :lambda-list '(m))
(cl:defmethod VrelX-val ((m <obj208>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:VrelX-val is deprecated.  Use milradar-msg:VrelX instead.")
  (VrelX m))

(cl:ensure-generic-function 'VrelY-val :lambda-list '(m))
(cl:defmethod VrelY-val ((m <obj208>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:VrelY-val is deprecated.  Use milradar-msg:VrelY instead.")
  (VrelY m))

(cl:ensure-generic-function 'RCS-val :lambda-list '(m))
(cl:defmethod RCS-val ((m <obj208>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:RCS-val is deprecated.  Use milradar-msg:RCS instead.")
  (RCS m))

(cl:ensure-generic-function 'Lifetime-val :lambda-list '(m))
(cl:defmethod Lifetime-val ((m <obj208>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:Lifetime-val is deprecated.  Use milradar-msg:Lifetime instead.")
  (Lifetime m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <obj208>) ostream)
  "Serializes a message object of type '<obj208>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ID)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'ID)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'timestamp)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'timestamp)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'timestamp)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'timestamp)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'DistX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'DistY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'index)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'VrelX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'VrelY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'RCS))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Lifetime))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <obj208>) istream)
  "Deserializes a message object of type '<obj208>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ID)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'ID)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'timestamp)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'timestamp)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'timestamp)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'timestamp)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'DistX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'DistY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'index)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'VrelX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'VrelY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'RCS) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Lifetime) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<obj208>)))
  "Returns string type for a message object of type '<obj208>"
  "milradar/obj208")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'obj208)))
  "Returns string type for a message object of type 'obj208"
  "milradar/obj208")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<obj208>)))
  "Returns md5sum for a message object of type '<obj208>"
  "5da0d1fed9b5cee755bd51d6eb5ea908")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'obj208)))
  "Returns md5sum for a message object of type 'obj208"
  "5da0d1fed9b5cee755bd51d6eb5ea908")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<obj208>)))
  "Returns full string definition for message of type '<obj208>"
  (cl:format cl:nil "uint16 ID~%uint32 timestamp~%float32 DistX~%float32 DistY~%uint8 index~%float32 VrelX~%float32 VrelY~%float32 RCS~%float32 Lifetime~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'obj208)))
  "Returns full string definition for message of type 'obj208"
  (cl:format cl:nil "uint16 ID~%uint32 timestamp~%float32 DistX~%float32 DistY~%uint8 index~%float32 VrelX~%float32 VrelY~%float32 RCS~%float32 Lifetime~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <obj208>))
  (cl:+ 0
     2
     4
     4
     4
     1
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <obj208>))
  "Converts a ROS message object to a list"
  (cl:list 'obj208
    (cl:cons ':ID (ID msg))
    (cl:cons ':timestamp (timestamp msg))
    (cl:cons ':DistX (DistX msg))
    (cl:cons ':DistY (DistY msg))
    (cl:cons ':index (index msg))
    (cl:cons ':VrelX (VrelX msg))
    (cl:cons ':VrelY (VrelY msg))
    (cl:cons ':RCS (RCS msg))
    (cl:cons ':Lifetime (Lifetime msg))
))
