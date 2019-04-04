; Auto-generated. Do not edit!


(cl:in-package Mobileye-msg)


;//! \htmlinclude Mobileye_Lane.msg.html

(cl:defclass <Mobileye_Lane> (roslisp-msg-protocol:ros-message)
  ((Curvature
    :reader Curvature
    :initarg :Curvature
    :type cl:float
    :initform 0.0)
   (Heading
    :reader Heading
    :initarg :Heading
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

(cl:defclass Mobileye_Lane (<Mobileye_Lane>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Mobileye_Lane>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Mobileye_Lane)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name Mobileye-msg:<Mobileye_Lane> is deprecated: use Mobileye-msg:Mobileye_Lane instead.")))

(cl:ensure-generic-function 'Curvature-val :lambda-list '(m))
(cl:defmethod Curvature-val ((m <Mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Mobileye-msg:Curvature-val is deprecated.  Use Mobileye-msg:Curvature instead.")
  (Curvature m))

(cl:ensure-generic-function 'Heading-val :lambda-list '(m))
(cl:defmethod Heading-val ((m <Mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Mobileye-msg:Heading-val is deprecated.  Use Mobileye-msg:Heading instead.")
  (Heading m))

(cl:ensure-generic-function 'YawAngle-val :lambda-list '(m))
(cl:defmethod YawAngle-val ((m <Mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Mobileye-msg:YawAngle-val is deprecated.  Use Mobileye-msg:YawAngle instead.")
  (YawAngle m))

(cl:ensure-generic-function 'PitchAngle-val :lambda-list '(m))
(cl:defmethod PitchAngle-val ((m <Mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Mobileye-msg:PitchAngle-val is deprecated.  Use Mobileye-msg:PitchAngle instead.")
  (PitchAngle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Mobileye_Lane>) ostream)
  "Serializes a message object of type '<Mobileye_Lane>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Curvature))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Heading))))
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Mobileye_Lane>) istream)
  "Deserializes a message object of type '<Mobileye_Lane>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Curvature) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Heading) (roslisp-utils:decode-single-float-bits bits)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Mobileye_Lane>)))
  "Returns string type for a message object of type '<Mobileye_Lane>"
  "Mobileye/Mobileye_Lane")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Mobileye_Lane)))
  "Returns string type for a message object of type 'Mobileye_Lane"
  "Mobileye/Mobileye_Lane")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Mobileye_Lane>)))
  "Returns md5sum for a message object of type '<Mobileye_Lane>"
  "c114e210f76c61682b6e868c0be18089")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Mobileye_Lane)))
  "Returns md5sum for a message object of type 'Mobileye_Lane"
  "c114e210f76c61682b6e868c0be18089")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Mobileye_Lane>)))
  "Returns full string definition for message of type '<Mobileye_Lane>"
  (cl:format cl:nil "float32 Curvature~%float32 Heading~%float32 YawAngle~%float32 PitchAngle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Mobileye_Lane)))
  "Returns full string definition for message of type 'Mobileye_Lane"
  (cl:format cl:nil "float32 Curvature~%float32 Heading~%float32 YawAngle~%float32 PitchAngle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Mobileye_Lane>))
  (cl:+ 0
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Mobileye_Lane>))
  "Converts a ROS message object to a list"
  (cl:list 'Mobileye_Lane
    (cl:cons ':Curvature (Curvature msg))
    (cl:cons ':Heading (Heading msg))
    (cl:cons ':YawAngle (YawAngle msg))
    (cl:cons ':PitchAngle (PitchAngle msg))
))
