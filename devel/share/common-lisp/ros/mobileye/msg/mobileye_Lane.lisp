; Auto-generated. Do not edit!


(cl:in-package mobileye-msg)


;//! \htmlinclude mobileye_Lane.msg.html

(cl:defclass <mobileye_Lane> (roslisp-msg-protocol:ros-message)
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
   (Left_Dist
    :reader Left_Dist
    :initarg :Left_Dist
    :type cl:float
    :initform 0.0)
   (Right_Dist
    :reader Right_Dist
    :initarg :Right_Dist
    :type cl:float
    :initform 0.0)
   (Left_Type
    :reader Left_Type
    :initarg :Left_Type
    :type cl:fixnum
    :initform 0)
   (Right_Type
    :reader Right_Type
    :initarg :Right_Type
    :type cl:fixnum
    :initform 0)
   (Left_Conf
    :reader Left_Conf
    :initarg :Left_Conf
    :type cl:fixnum
    :initform 0)
   (Right_Conf
    :reader Right_Conf
    :initarg :Right_Conf
    :type cl:fixnum
    :initform 0)
   (Left_LDW_avai
    :reader Left_LDW_avai
    :initarg :Left_LDW_avai
    :type cl:fixnum
    :initform 0)
   (Right_LDW_avai
    :reader Right_LDW_avai
    :initarg :Right_LDW_avai
    :type cl:fixnum
    :initform 0)
   (Constr_Area
    :reader Constr_Area
    :initarg :Constr_Area
    :type cl:fixnum
    :initform 0)
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

(cl:defclass mobileye_Lane (<mobileye_Lane>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mobileye_Lane>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mobileye_Lane)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye-msg:<mobileye_Lane> is deprecated: use mobileye-msg:mobileye_Lane instead.")))

(cl:ensure-generic-function 'Curvature-val :lambda-list '(m))
(cl:defmethod Curvature-val ((m <mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Curvature-val is deprecated.  Use mobileye-msg:Curvature instead.")
  (Curvature m))

(cl:ensure-generic-function 'Heading-val :lambda-list '(m))
(cl:defmethod Heading-val ((m <mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Heading-val is deprecated.  Use mobileye-msg:Heading instead.")
  (Heading m))

(cl:ensure-generic-function 'Left_Dist-val :lambda-list '(m))
(cl:defmethod Left_Dist-val ((m <mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Left_Dist-val is deprecated.  Use mobileye-msg:Left_Dist instead.")
  (Left_Dist m))

(cl:ensure-generic-function 'Right_Dist-val :lambda-list '(m))
(cl:defmethod Right_Dist-val ((m <mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Right_Dist-val is deprecated.  Use mobileye-msg:Right_Dist instead.")
  (Right_Dist m))

(cl:ensure-generic-function 'Left_Type-val :lambda-list '(m))
(cl:defmethod Left_Type-val ((m <mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Left_Type-val is deprecated.  Use mobileye-msg:Left_Type instead.")
  (Left_Type m))

(cl:ensure-generic-function 'Right_Type-val :lambda-list '(m))
(cl:defmethod Right_Type-val ((m <mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Right_Type-val is deprecated.  Use mobileye-msg:Right_Type instead.")
  (Right_Type m))

(cl:ensure-generic-function 'Left_Conf-val :lambda-list '(m))
(cl:defmethod Left_Conf-val ((m <mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Left_Conf-val is deprecated.  Use mobileye-msg:Left_Conf instead.")
  (Left_Conf m))

(cl:ensure-generic-function 'Right_Conf-val :lambda-list '(m))
(cl:defmethod Right_Conf-val ((m <mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Right_Conf-val is deprecated.  Use mobileye-msg:Right_Conf instead.")
  (Right_Conf m))

(cl:ensure-generic-function 'Left_LDW_avai-val :lambda-list '(m))
(cl:defmethod Left_LDW_avai-val ((m <mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Left_LDW_avai-val is deprecated.  Use mobileye-msg:Left_LDW_avai instead.")
  (Left_LDW_avai m))

(cl:ensure-generic-function 'Right_LDW_avai-val :lambda-list '(m))
(cl:defmethod Right_LDW_avai-val ((m <mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Right_LDW_avai-val is deprecated.  Use mobileye-msg:Right_LDW_avai instead.")
  (Right_LDW_avai m))

(cl:ensure-generic-function 'Constr_Area-val :lambda-list '(m))
(cl:defmethod Constr_Area-val ((m <mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Constr_Area-val is deprecated.  Use mobileye-msg:Constr_Area instead.")
  (Constr_Area m))

(cl:ensure-generic-function 'YawAngle-val :lambda-list '(m))
(cl:defmethod YawAngle-val ((m <mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:YawAngle-val is deprecated.  Use mobileye-msg:YawAngle instead.")
  (YawAngle m))

(cl:ensure-generic-function 'PitchAngle-val :lambda-list '(m))
(cl:defmethod PitchAngle-val ((m <mobileye_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:PitchAngle-val is deprecated.  Use mobileye-msg:PitchAngle instead.")
  (PitchAngle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mobileye_Lane>) ostream)
  "Serializes a message object of type '<mobileye_Lane>"
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Left_Dist))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Right_Dist))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Left_Type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Right_Type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Left_Conf)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Right_Conf)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Left_LDW_avai)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Right_LDW_avai)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Constr_Area)) ostream)
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mobileye_Lane>) istream)
  "Deserializes a message object of type '<mobileye_Lane>"
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
    (cl:setf (cl:slot-value msg 'Left_Dist) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Right_Dist) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Left_Type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Right_Type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Left_Conf)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Right_Conf)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Left_LDW_avai)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Right_LDW_avai)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Constr_Area)) (cl:read-byte istream))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mobileye_Lane>)))
  "Returns string type for a message object of type '<mobileye_Lane>"
  "mobileye/mobileye_Lane")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mobileye_Lane)))
  "Returns string type for a message object of type 'mobileye_Lane"
  "mobileye/mobileye_Lane")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mobileye_Lane>)))
  "Returns md5sum for a message object of type '<mobileye_Lane>"
  "e250089b833df5ee2a8ae64f26afe8d3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mobileye_Lane)))
  "Returns md5sum for a message object of type 'mobileye_Lane"
  "e250089b833df5ee2a8ae64f26afe8d3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mobileye_Lane>)))
  "Returns full string definition for message of type '<mobileye_Lane>"
  (cl:format cl:nil "float32 Curvature~%float32 Heading~%float32 Left_Dist~%float32 Right_Dist~%uint8 Left_Type~%uint8 Right_Type~%uint8 Left_Conf~%uint8 Right_Conf~%uint8 Left_LDW_avai~%uint8 Right_LDW_avai~%uint8 Constr_Area~%float32 YawAngle~%float32 PitchAngle~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mobileye_Lane)))
  "Returns full string definition for message of type 'mobileye_Lane"
  (cl:format cl:nil "float32 Curvature~%float32 Heading~%float32 Left_Dist~%float32 Right_Dist~%uint8 Left_Type~%uint8 Right_Type~%uint8 Left_Conf~%uint8 Right_Conf~%uint8 Left_LDW_avai~%uint8 Right_LDW_avai~%uint8 Constr_Area~%float32 YawAngle~%float32 PitchAngle~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mobileye_Lane>))
  (cl:+ 0
     4
     4
     4
     4
     1
     1
     1
     1
     1
     1
     1
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mobileye_Lane>))
  "Converts a ROS message object to a list"
  (cl:list 'mobileye_Lane
    (cl:cons ':Curvature (Curvature msg))
    (cl:cons ':Heading (Heading msg))
    (cl:cons ':Left_Dist (Left_Dist msg))
    (cl:cons ':Right_Dist (Right_Dist msg))
    (cl:cons ':Left_Type (Left_Type msg))
    (cl:cons ':Right_Type (Right_Type msg))
    (cl:cons ':Left_Conf (Left_Conf msg))
    (cl:cons ':Right_Conf (Right_Conf msg))
    (cl:cons ':Left_LDW_avai (Left_LDW_avai msg))
    (cl:cons ':Right_LDW_avai (Right_LDW_avai msg))
    (cl:cons ':Constr_Area (Constr_Area msg))
    (cl:cons ':YawAngle (YawAngle msg))
    (cl:cons ':PitchAngle (PitchAngle msg))
))
