; Auto-generated. Do not edit!


(cl:in-package Mobileye-msg)


;//! \htmlinclude Mobileye_TSR.msg.html

(cl:defclass <Mobileye_TSR> (roslisp-msg-protocol:ros-message)
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

(cl:defclass Mobileye_TSR (<Mobileye_TSR>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Mobileye_TSR>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Mobileye_TSR)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name Mobileye-msg:<Mobileye_TSR> is deprecated: use Mobileye-msg:Mobileye_TSR instead.")))

(cl:ensure-generic-function 'MType-val :lambda-list '(m))
(cl:defmethod MType-val ((m <Mobileye_TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Mobileye-msg:MType-val is deprecated.  Use Mobileye-msg:MType instead.")
  (MType m))

(cl:ensure-generic-function 'SupType-val :lambda-list '(m))
(cl:defmethod SupType-val ((m <Mobileye_TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Mobileye-msg:SupType-val is deprecated.  Use Mobileye-msg:SupType instead.")
  (SupType m))

(cl:ensure-generic-function 'PosX-val :lambda-list '(m))
(cl:defmethod PosX-val ((m <Mobileye_TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Mobileye-msg:PosX-val is deprecated.  Use Mobileye-msg:PosX instead.")
  (PosX m))

(cl:ensure-generic-function 'PosY-val :lambda-list '(m))
(cl:defmethod PosY-val ((m <Mobileye_TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Mobileye-msg:PosY-val is deprecated.  Use Mobileye-msg:PosY instead.")
  (PosY m))

(cl:ensure-generic-function 'PosZ-val :lambda-list '(m))
(cl:defmethod PosZ-val ((m <Mobileye_TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Mobileye-msg:PosZ-val is deprecated.  Use Mobileye-msg:PosZ instead.")
  (PosZ m))

(cl:ensure-generic-function 'FilterType-val :lambda-list '(m))
(cl:defmethod FilterType-val ((m <Mobileye_TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Mobileye-msg:FilterType-val is deprecated.  Use Mobileye-msg:FilterType instead.")
  (FilterType m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Mobileye_TSR>) ostream)
  "Serializes a message object of type '<Mobileye_TSR>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Mobileye_TSR>) istream)
  "Deserializes a message object of type '<Mobileye_TSR>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Mobileye_TSR>)))
  "Returns string type for a message object of type '<Mobileye_TSR>"
  "Mobileye/Mobileye_TSR")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Mobileye_TSR)))
  "Returns string type for a message object of type 'Mobileye_TSR"
  "Mobileye/Mobileye_TSR")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Mobileye_TSR>)))
  "Returns md5sum for a message object of type '<Mobileye_TSR>"
  "c6519f710ac25fe67cd32cf09bf9fb46")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Mobileye_TSR)))
  "Returns md5sum for a message object of type 'Mobileye_TSR"
  "c6519f710ac25fe67cd32cf09bf9fb46")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Mobileye_TSR>)))
  "Returns full string definition for message of type '<Mobileye_TSR>"
  (cl:format cl:nil "uint8 MType~%uint8 SupType~%float32 PosX~%float32 PosY~%float32 PosZ~%uint8 FilterType~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Mobileye_TSR)))
  "Returns full string definition for message of type 'Mobileye_TSR"
  (cl:format cl:nil "uint8 MType~%uint8 SupType~%float32 PosX~%float32 PosY~%float32 PosZ~%uint8 FilterType~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Mobileye_TSR>))
  (cl:+ 0
     1
     1
     4
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Mobileye_TSR>))
  "Converts a ROS message object to a list"
  (cl:list 'Mobileye_TSR
    (cl:cons ':MType (MType msg))
    (cl:cons ':SupType (SupType msg))
    (cl:cons ':PosX (PosX msg))
    (cl:cons ':PosY (PosY msg))
    (cl:cons ':PosZ (PosZ msg))
    (cl:cons ':FilterType (FilterType msg))
))
