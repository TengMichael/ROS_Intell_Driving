; Auto-generated. Do not edit!


(cl:in-package fusion-msg)


;//! \htmlinclude fusion_obj.msg.html

(cl:defclass <fusion_obj> (roslisp-msg-protocol:ros-message)
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
   (ArelX
    :reader ArelX
    :initarg :ArelX
    :type cl:float
    :initform 0.0)
   (ArelY
    :reader ArelY
    :initarg :ArelY
    :type cl:float
    :initform 0.0)
   (Class
    :reader Class
    :initarg :Class
    :type cl:fixnum
    :initform 0)
   (Length
    :reader Length
    :initarg :Length
    :type cl:float
    :initform 0.0)
   (Width
    :reader Width
    :initarg :Width
    :type cl:float
    :initform 0.0))
)

(cl:defclass fusion_obj (<fusion_obj>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <fusion_obj>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'fusion_obj)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name fusion-msg:<fusion_obj> is deprecated: use fusion-msg:fusion_obj instead.")))

(cl:ensure-generic-function 'ID-val :lambda-list '(m))
(cl:defmethod ID-val ((m <fusion_obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fusion-msg:ID-val is deprecated.  Use fusion-msg:ID instead.")
  (ID m))

(cl:ensure-generic-function 'timestamp-val :lambda-list '(m))
(cl:defmethod timestamp-val ((m <fusion_obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fusion-msg:timestamp-val is deprecated.  Use fusion-msg:timestamp instead.")
  (timestamp m))

(cl:ensure-generic-function 'DistX-val :lambda-list '(m))
(cl:defmethod DistX-val ((m <fusion_obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fusion-msg:DistX-val is deprecated.  Use fusion-msg:DistX instead.")
  (DistX m))

(cl:ensure-generic-function 'DistY-val :lambda-list '(m))
(cl:defmethod DistY-val ((m <fusion_obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fusion-msg:DistY-val is deprecated.  Use fusion-msg:DistY instead.")
  (DistY m))

(cl:ensure-generic-function 'VrelX-val :lambda-list '(m))
(cl:defmethod VrelX-val ((m <fusion_obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fusion-msg:VrelX-val is deprecated.  Use fusion-msg:VrelX instead.")
  (VrelX m))

(cl:ensure-generic-function 'VrelY-val :lambda-list '(m))
(cl:defmethod VrelY-val ((m <fusion_obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fusion-msg:VrelY-val is deprecated.  Use fusion-msg:VrelY instead.")
  (VrelY m))

(cl:ensure-generic-function 'ArelX-val :lambda-list '(m))
(cl:defmethod ArelX-val ((m <fusion_obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fusion-msg:ArelX-val is deprecated.  Use fusion-msg:ArelX instead.")
  (ArelX m))

(cl:ensure-generic-function 'ArelY-val :lambda-list '(m))
(cl:defmethod ArelY-val ((m <fusion_obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fusion-msg:ArelY-val is deprecated.  Use fusion-msg:ArelY instead.")
  (ArelY m))

(cl:ensure-generic-function 'Class-val :lambda-list '(m))
(cl:defmethod Class-val ((m <fusion_obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fusion-msg:Class-val is deprecated.  Use fusion-msg:Class instead.")
  (Class m))

(cl:ensure-generic-function 'Length-val :lambda-list '(m))
(cl:defmethod Length-val ((m <fusion_obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fusion-msg:Length-val is deprecated.  Use fusion-msg:Length instead.")
  (Length m))

(cl:ensure-generic-function 'Width-val :lambda-list '(m))
(cl:defmethod Width-val ((m <fusion_obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fusion-msg:Width-val is deprecated.  Use fusion-msg:Width instead.")
  (Width m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <fusion_obj>) ostream)
  "Serializes a message object of type '<fusion_obj>"
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ArelX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ArelY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Class)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Length))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Width))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <fusion_obj>) istream)
  "Deserializes a message object of type '<fusion_obj>"
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
    (cl:setf (cl:slot-value msg 'ArelX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ArelY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Class)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Length) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Width) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<fusion_obj>)))
  "Returns string type for a message object of type '<fusion_obj>"
  "fusion/fusion_obj")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'fusion_obj)))
  "Returns string type for a message object of type 'fusion_obj"
  "fusion/fusion_obj")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<fusion_obj>)))
  "Returns md5sum for a message object of type '<fusion_obj>"
  "f09b42ee033a9e4979d12257c9a761dd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'fusion_obj)))
  "Returns md5sum for a message object of type 'fusion_obj"
  "f09b42ee033a9e4979d12257c9a761dd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<fusion_obj>)))
  "Returns full string definition for message of type '<fusion_obj>"
  (cl:format cl:nil "uint16 ID~%uint32 timestamp~%float32 DistX~%float32 DistY~%float32 VrelX~%float32 VrelY~%float32 ArelX~%float32 ArelY~%uint8 Class~%float32 Length~%float32 Width~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'fusion_obj)))
  "Returns full string definition for message of type 'fusion_obj"
  (cl:format cl:nil "uint16 ID~%uint32 timestamp~%float32 DistX~%float32 DistY~%float32 VrelX~%float32 VrelY~%float32 ArelX~%float32 ArelY~%uint8 Class~%float32 Length~%float32 Width~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <fusion_obj>))
  (cl:+ 0
     2
     4
     4
     4
     4
     4
     4
     4
     1
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <fusion_obj>))
  "Converts a ROS message object to a list"
  (cl:list 'fusion_obj
    (cl:cons ':ID (ID msg))
    (cl:cons ':timestamp (timestamp msg))
    (cl:cons ':DistX (DistX msg))
    (cl:cons ':DistY (DistY msg))
    (cl:cons ':VrelX (VrelX msg))
    (cl:cons ':VrelY (VrelY msg))
    (cl:cons ':ArelX (ArelX msg))
    (cl:cons ':ArelY (ArelY msg))
    (cl:cons ':Class (Class msg))
    (cl:cons ':Length (Length msg))
    (cl:cons ':Width (Width msg))
))
