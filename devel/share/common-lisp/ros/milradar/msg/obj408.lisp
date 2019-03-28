; Auto-generated. Do not edit!


(cl:in-package milradar-msg)


;//! \htmlinclude obj408.msg.html

(cl:defclass <obj408> (roslisp-msg-protocol:ros-message)
  ((ID
    :reader ID
    :initarg :ID
    :type cl:fixnum
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
   (RCS
    :reader RCS
    :initarg :RCS
    :type cl:float
    :initform 0.0)
   (DynProp
    :reader DynProp
    :initarg :DynProp
    :type cl:fixnum
    :initform 0)
   (Orientation_rms
    :reader Orientation_rms
    :initarg :Orientation_rms
    :type cl:fixnum
    :initform 0)
   (MeasState
    :reader MeasState
    :initarg :MeasState
    :type cl:fixnum
    :initform 0)
   (ProbOfExist
    :reader ProbOfExist
    :initarg :ProbOfExist
    :type cl:fixnum
    :initform 0)
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
   (OrientationAngel
    :reader OrientationAngel
    :initarg :OrientationAngel
    :type cl:float
    :initform 0.0)
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

(cl:defclass obj408 (<obj408>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <obj408>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'obj408)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name milradar-msg:<obj408> is deprecated: use milradar-msg:obj408 instead.")))

(cl:ensure-generic-function 'ID-val :lambda-list '(m))
(cl:defmethod ID-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:ID-val is deprecated.  Use milradar-msg:ID instead.")
  (ID m))

(cl:ensure-generic-function 'DistX-val :lambda-list '(m))
(cl:defmethod DistX-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:DistX-val is deprecated.  Use milradar-msg:DistX instead.")
  (DistX m))

(cl:ensure-generic-function 'DistY-val :lambda-list '(m))
(cl:defmethod DistY-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:DistY-val is deprecated.  Use milradar-msg:DistY instead.")
  (DistY m))

(cl:ensure-generic-function 'VrelX-val :lambda-list '(m))
(cl:defmethod VrelX-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:VrelX-val is deprecated.  Use milradar-msg:VrelX instead.")
  (VrelX m))

(cl:ensure-generic-function 'VrelY-val :lambda-list '(m))
(cl:defmethod VrelY-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:VrelY-val is deprecated.  Use milradar-msg:VrelY instead.")
  (VrelY m))

(cl:ensure-generic-function 'RCS-val :lambda-list '(m))
(cl:defmethod RCS-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:RCS-val is deprecated.  Use milradar-msg:RCS instead.")
  (RCS m))

(cl:ensure-generic-function 'DynProp-val :lambda-list '(m))
(cl:defmethod DynProp-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:DynProp-val is deprecated.  Use milradar-msg:DynProp instead.")
  (DynProp m))

(cl:ensure-generic-function 'Orientation_rms-val :lambda-list '(m))
(cl:defmethod Orientation_rms-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:Orientation_rms-val is deprecated.  Use milradar-msg:Orientation_rms instead.")
  (Orientation_rms m))

(cl:ensure-generic-function 'MeasState-val :lambda-list '(m))
(cl:defmethod MeasState-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:MeasState-val is deprecated.  Use milradar-msg:MeasState instead.")
  (MeasState m))

(cl:ensure-generic-function 'ProbOfExist-val :lambda-list '(m))
(cl:defmethod ProbOfExist-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:ProbOfExist-val is deprecated.  Use milradar-msg:ProbOfExist instead.")
  (ProbOfExist m))

(cl:ensure-generic-function 'ArelX-val :lambda-list '(m))
(cl:defmethod ArelX-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:ArelX-val is deprecated.  Use milradar-msg:ArelX instead.")
  (ArelX m))

(cl:ensure-generic-function 'ArelY-val :lambda-list '(m))
(cl:defmethod ArelY-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:ArelY-val is deprecated.  Use milradar-msg:ArelY instead.")
  (ArelY m))

(cl:ensure-generic-function 'Class-val :lambda-list '(m))
(cl:defmethod Class-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:Class-val is deprecated.  Use milradar-msg:Class instead.")
  (Class m))

(cl:ensure-generic-function 'OrientationAngel-val :lambda-list '(m))
(cl:defmethod OrientationAngel-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:OrientationAngel-val is deprecated.  Use milradar-msg:OrientationAngel instead.")
  (OrientationAngel m))

(cl:ensure-generic-function 'Length-val :lambda-list '(m))
(cl:defmethod Length-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:Length-val is deprecated.  Use milradar-msg:Length instead.")
  (Length m))

(cl:ensure-generic-function 'Width-val :lambda-list '(m))
(cl:defmethod Width-val ((m <obj408>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:Width-val is deprecated.  Use milradar-msg:Width instead.")
  (Width m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <obj408>) ostream)
  "Serializes a message object of type '<obj408>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ID)) ostream)
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'RCS))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'DynProp)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Orientation_rms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'MeasState)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ProbOfExist)) ostream)
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'OrientationAngel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <obj408>) istream)
  "Deserializes a message object of type '<obj408>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ID)) (cl:read-byte istream))
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
    (cl:setf (cl:slot-value msg 'RCS) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'DynProp)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Orientation_rms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'MeasState)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ProbOfExist)) (cl:read-byte istream))
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
    (cl:setf (cl:slot-value msg 'OrientationAngel) (roslisp-utils:decode-single-float-bits bits)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<obj408>)))
  "Returns string type for a message object of type '<obj408>"
  "milradar/obj408")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'obj408)))
  "Returns string type for a message object of type 'obj408"
  "milradar/obj408")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<obj408>)))
  "Returns md5sum for a message object of type '<obj408>"
  "1abcb56f3f65e8d71e8aabff6ec3e1af")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'obj408)))
  "Returns md5sum for a message object of type 'obj408"
  "1abcb56f3f65e8d71e8aabff6ec3e1af")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<obj408>)))
  "Returns full string definition for message of type '<obj408>"
  (cl:format cl:nil "uint8 ID~%float32 DistX~%float32 DistY~%float32 VrelX~%float32 VrelY~%float32 RCS~%uint8 DynProp~%uint8 Orientation_rms~%uint8 MeasState~%uint8 ProbOfExist~%float32 ArelX~%float32 ArelY~%uint8 Class~%float32 OrientationAngel~%float32 Length~%float32 Width~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'obj408)))
  "Returns full string definition for message of type 'obj408"
  (cl:format cl:nil "uint8 ID~%float32 DistX~%float32 DistY~%float32 VrelX~%float32 VrelY~%float32 RCS~%uint8 DynProp~%uint8 Orientation_rms~%uint8 MeasState~%uint8 ProbOfExist~%float32 ArelX~%float32 ArelY~%uint8 Class~%float32 OrientationAngel~%float32 Length~%float32 Width~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <obj408>))
  (cl:+ 0
     1
     4
     4
     4
     4
     4
     1
     1
     1
     1
     4
     4
     1
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <obj408>))
  "Converts a ROS message object to a list"
  (cl:list 'obj408
    (cl:cons ':ID (ID msg))
    (cl:cons ':DistX (DistX msg))
    (cl:cons ':DistY (DistY msg))
    (cl:cons ':VrelX (VrelX msg))
    (cl:cons ':VrelY (VrelY msg))
    (cl:cons ':RCS (RCS msg))
    (cl:cons ':DynProp (DynProp msg))
    (cl:cons ':Orientation_rms (Orientation_rms msg))
    (cl:cons ':MeasState (MeasState msg))
    (cl:cons ':ProbOfExist (ProbOfExist msg))
    (cl:cons ':ArelX (ArelX msg))
    (cl:cons ':ArelY (ArelY msg))
    (cl:cons ':Class (Class msg))
    (cl:cons ':OrientationAngel (OrientationAngel msg))
    (cl:cons ':Length (Length msg))
    (cl:cons ':Width (Width msg))
))
