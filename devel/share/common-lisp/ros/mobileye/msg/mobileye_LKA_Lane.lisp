; Auto-generated. Do not edit!


(cl:in-package mobileye-msg)


;//! \htmlinclude mobileye_LKA_Lane.msg.html

(cl:defclass <mobileye_LKA_Lane> (roslisp-msg-protocol:ros-message)
  ((MType
    :reader MType
    :initarg :MType
    :type cl:fixnum
    :initform 0)
   (Quality
    :reader Quality
    :initarg :Quality
    :type cl:fixnum
    :initform 0)
   (Model_degree
    :reader Model_degree
    :initarg :Model_degree
    :type cl:fixnum
    :initform 0)
   (Position
    :reader Position
    :initarg :Position
    :type cl:float
    :initform 0.0)
   (Curvature
    :reader Curvature
    :initarg :Curvature
    :type cl:float
    :initform 0.0)
   (Heading
    :reader Heading
    :initarg :Heading
    :type cl:float
    :initform 0.0)
   (Curvature_deriv
    :reader Curvature_deriv
    :initarg :Curvature_deriv
    :type cl:float
    :initform 0.0)
   (Width
    :reader Width
    :initarg :Width
    :type cl:float
    :initform 0.0)
   (View_range
    :reader View_range
    :initarg :View_range
    :type cl:float
    :initform 0.0))
)

(cl:defclass mobileye_LKA_Lane (<mobileye_LKA_Lane>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mobileye_LKA_Lane>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mobileye_LKA_Lane)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye-msg:<mobileye_LKA_Lane> is deprecated: use mobileye-msg:mobileye_LKA_Lane instead.")))

(cl:ensure-generic-function 'MType-val :lambda-list '(m))
(cl:defmethod MType-val ((m <mobileye_LKA_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:MType-val is deprecated.  Use mobileye-msg:MType instead.")
  (MType m))

(cl:ensure-generic-function 'Quality-val :lambda-list '(m))
(cl:defmethod Quality-val ((m <mobileye_LKA_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Quality-val is deprecated.  Use mobileye-msg:Quality instead.")
  (Quality m))

(cl:ensure-generic-function 'Model_degree-val :lambda-list '(m))
(cl:defmethod Model_degree-val ((m <mobileye_LKA_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Model_degree-val is deprecated.  Use mobileye-msg:Model_degree instead.")
  (Model_degree m))

(cl:ensure-generic-function 'Position-val :lambda-list '(m))
(cl:defmethod Position-val ((m <mobileye_LKA_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Position-val is deprecated.  Use mobileye-msg:Position instead.")
  (Position m))

(cl:ensure-generic-function 'Curvature-val :lambda-list '(m))
(cl:defmethod Curvature-val ((m <mobileye_LKA_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Curvature-val is deprecated.  Use mobileye-msg:Curvature instead.")
  (Curvature m))

(cl:ensure-generic-function 'Heading-val :lambda-list '(m))
(cl:defmethod Heading-val ((m <mobileye_LKA_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Heading-val is deprecated.  Use mobileye-msg:Heading instead.")
  (Heading m))

(cl:ensure-generic-function 'Curvature_deriv-val :lambda-list '(m))
(cl:defmethod Curvature_deriv-val ((m <mobileye_LKA_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Curvature_deriv-val is deprecated.  Use mobileye-msg:Curvature_deriv instead.")
  (Curvature_deriv m))

(cl:ensure-generic-function 'Width-val :lambda-list '(m))
(cl:defmethod Width-val ((m <mobileye_LKA_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Width-val is deprecated.  Use mobileye-msg:Width instead.")
  (Width m))

(cl:ensure-generic-function 'View_range-val :lambda-list '(m))
(cl:defmethod View_range-val ((m <mobileye_LKA_Lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:View_range-val is deprecated.  Use mobileye-msg:View_range instead.")
  (View_range m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mobileye_LKA_Lane>) ostream)
  "Serializes a message object of type '<mobileye_LKA_Lane>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'MType)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Quality)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Model_degree)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Position))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Curvature_deriv))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Width))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'View_range))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mobileye_LKA_Lane>) istream)
  "Deserializes a message object of type '<mobileye_LKA_Lane>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'MType)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Quality)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Model_degree)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Position) (roslisp-utils:decode-single-float-bits bits)))
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
    (cl:setf (cl:slot-value msg 'Curvature_deriv) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Width) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'View_range) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mobileye_LKA_Lane>)))
  "Returns string type for a message object of type '<mobileye_LKA_Lane>"
  "mobileye/mobileye_LKA_Lane")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mobileye_LKA_Lane)))
  "Returns string type for a message object of type 'mobileye_LKA_Lane"
  "mobileye/mobileye_LKA_Lane")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mobileye_LKA_Lane>)))
  "Returns md5sum for a message object of type '<mobileye_LKA_Lane>"
  "5f536a85eb5e6c93cc0441013010300e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mobileye_LKA_Lane)))
  "Returns md5sum for a message object of type 'mobileye_LKA_Lane"
  "5f536a85eb5e6c93cc0441013010300e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mobileye_LKA_Lane>)))
  "Returns full string definition for message of type '<mobileye_LKA_Lane>"
  (cl:format cl:nil "uint8 MType~%uint8 Quality~%uint8 Model_degree~%float32 Position~%float32 Curvature~%float32 Heading~%float32 Curvature_deriv~%float32 Width~%float32 View_range~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mobileye_LKA_Lane)))
  "Returns full string definition for message of type 'mobileye_LKA_Lane"
  (cl:format cl:nil "uint8 MType~%uint8 Quality~%uint8 Model_degree~%float32 Position~%float32 Curvature~%float32 Heading~%float32 Curvature_deriv~%float32 Width~%float32 View_range~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mobileye_LKA_Lane>))
  (cl:+ 0
     1
     1
     1
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mobileye_LKA_Lane>))
  "Converts a ROS message object to a list"
  (cl:list 'mobileye_LKA_Lane
    (cl:cons ':MType (MType msg))
    (cl:cons ':Quality (Quality msg))
    (cl:cons ':Model_degree (Model_degree msg))
    (cl:cons ':Position (Position msg))
    (cl:cons ':Curvature (Curvature msg))
    (cl:cons ':Heading (Heading msg))
    (cl:cons ':Curvature_deriv (Curvature_deriv msg))
    (cl:cons ':Width (Width msg))
    (cl:cons ':View_range (View_range msg))
))
