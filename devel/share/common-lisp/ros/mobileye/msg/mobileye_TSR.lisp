; Auto-generated. Do not edit!


(cl:in-package mobileye-msg)


;//! \htmlinclude mobileye_TSR.msg.html

(cl:defclass <mobileye_TSR> (roslisp-msg-protocol:ros-message)
  ((MType
    :reader MType
    :initarg :MType
    :type cl:fixnum
    :initform 0)
   (SupType
    :reader SupType
    :initarg :SupType
    :type cl:fixnum
    :initform 0)
   (PosX
    :reader PosX
    :initarg :PosX
    :type cl:float
    :initform 0.0)
   (PosY
    :reader PosY
    :initarg :PosY
    :type cl:float
    :initform 0.0)
   (PosZ
    :reader PosZ
    :initarg :PosZ
    :type cl:float
    :initform 0.0)
   (FilterType
    :reader FilterType
    :initarg :FilterType
    :type cl:fixnum
    :initform 0))
)

(cl:defclass mobileye_TSR (<mobileye_TSR>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mobileye_TSR>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mobileye_TSR)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye-msg:<mobileye_TSR> is deprecated: use mobileye-msg:mobileye_TSR instead.")))

(cl:ensure-generic-function 'MType-val :lambda-list '(m))
(cl:defmethod MType-val ((m <mobileye_TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:MType-val is deprecated.  Use mobileye-msg:MType instead.")
  (MType m))

(cl:ensure-generic-function 'SupType-val :lambda-list '(m))
(cl:defmethod SupType-val ((m <mobileye_TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:SupType-val is deprecated.  Use mobileye-msg:SupType instead.")
  (SupType m))

(cl:ensure-generic-function 'PosX-val :lambda-list '(m))
(cl:defmethod PosX-val ((m <mobileye_TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:PosX-val is deprecated.  Use mobileye-msg:PosX instead.")
  (PosX m))

(cl:ensure-generic-function 'PosY-val :lambda-list '(m))
(cl:defmethod PosY-val ((m <mobileye_TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:PosY-val is deprecated.  Use mobileye-msg:PosY instead.")
  (PosY m))

(cl:ensure-generic-function 'PosZ-val :lambda-list '(m))
(cl:defmethod PosZ-val ((m <mobileye_TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:PosZ-val is deprecated.  Use mobileye-msg:PosZ instead.")
  (PosZ m))

(cl:ensure-generic-function 'FilterType-val :lambda-list '(m))
(cl:defmethod FilterType-val ((m <mobileye_TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:FilterType-val is deprecated.  Use mobileye-msg:FilterType instead.")
  (FilterType m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mobileye_TSR>) ostream)
  "Serializes a message object of type '<mobileye_TSR>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'MType)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'SupType)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'PosX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'PosY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'PosZ))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'FilterType)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mobileye_TSR>) istream)
  "Deserializes a message object of type '<mobileye_TSR>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'MType)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'SupType)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'PosX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'PosY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'PosZ) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'FilterType)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mobileye_TSR>)))
  "Returns string type for a message object of type '<mobileye_TSR>"
  "mobileye/mobileye_TSR")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mobileye_TSR)))
  "Returns string type for a message object of type 'mobileye_TSR"
  "mobileye/mobileye_TSR")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mobileye_TSR>)))
  "Returns md5sum for a message object of type '<mobileye_TSR>"
  "c6519f710ac25fe67cd32cf09bf9fb46")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mobileye_TSR)))
  "Returns md5sum for a message object of type 'mobileye_TSR"
  "c6519f710ac25fe67cd32cf09bf9fb46")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mobileye_TSR>)))
  "Returns full string definition for message of type '<mobileye_TSR>"
  (cl:format cl:nil "uint8 MType~%uint8 SupType~%float32 PosX~%float32 PosY~%float32 PosZ~%uint8 FilterType~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mobileye_TSR)))
  "Returns full string definition for message of type 'mobileye_TSR"
  (cl:format cl:nil "uint8 MType~%uint8 SupType~%float32 PosX~%float32 PosY~%float32 PosZ~%uint8 FilterType~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mobileye_TSR>))
  (cl:+ 0
     1
     1
     4
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mobileye_TSR>))
  "Converts a ROS message object to a list"
  (cl:list 'mobileye_TSR
    (cl:cons ':MType (MType msg))
    (cl:cons ':SupType (SupType msg))
    (cl:cons ':PosX (PosX msg))
    (cl:cons ':PosY (PosY msg))
    (cl:cons ':PosZ (PosZ msg))
    (cl:cons ':FilterType (FilterType msg))
))
