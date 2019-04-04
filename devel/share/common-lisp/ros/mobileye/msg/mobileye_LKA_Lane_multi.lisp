; Auto-generated. Do not edit!


(cl:in-package mobileye-msg)


;//! \htmlinclude mobileye_LKA_Lane_multi.msg.html

(cl:defclass <mobileye_LKA_Lane_multi> (roslisp-msg-protocol:ros-message)
  ((Left
    :reader Left
    :initarg :Left
    :type mobileye-msg:mobileye_LKA_Lane
    :initform (cl:make-instance 'mobileye-msg:mobileye_LKA_Lane))
   (Right
    :reader Right
    :initarg :Right
    :type mobileye-msg:mobileye_LKA_Lane
    :initform (cl:make-instance 'mobileye-msg:mobileye_LKA_Lane))
   (Next_Left
    :reader Next_Left
    :initarg :Next_Left
    :type mobileye-msg:mobileye_LKA_Lane
    :initform (cl:make-instance 'mobileye-msg:mobileye_LKA_Lane))
   (Next_Right
    :reader Next_Right
    :initarg :Next_Right
    :type mobileye-msg:mobileye_LKA_Lane
    :initform (cl:make-instance 'mobileye-msg:mobileye_LKA_Lane)))
)

(cl:defclass mobileye_LKA_Lane_multi (<mobileye_LKA_Lane_multi>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mobileye_LKA_Lane_multi>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mobileye_LKA_Lane_multi)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye-msg:<mobileye_LKA_Lane_multi> is deprecated: use mobileye-msg:mobileye_LKA_Lane_multi instead.")))

(cl:ensure-generic-function 'Left-val :lambda-list '(m))
(cl:defmethod Left-val ((m <mobileye_LKA_Lane_multi>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Left-val is deprecated.  Use mobileye-msg:Left instead.")
  (Left m))

(cl:ensure-generic-function 'Right-val :lambda-list '(m))
(cl:defmethod Right-val ((m <mobileye_LKA_Lane_multi>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Right-val is deprecated.  Use mobileye-msg:Right instead.")
  (Right m))

(cl:ensure-generic-function 'Next_Left-val :lambda-list '(m))
(cl:defmethod Next_Left-val ((m <mobileye_LKA_Lane_multi>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Next_Left-val is deprecated.  Use mobileye-msg:Next_Left instead.")
  (Next_Left m))

(cl:ensure-generic-function 'Next_Right-val :lambda-list '(m))
(cl:defmethod Next_Right-val ((m <mobileye_LKA_Lane_multi>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Next_Right-val is deprecated.  Use mobileye-msg:Next_Right instead.")
  (Next_Right m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mobileye_LKA_Lane_multi>) ostream)
  "Serializes a message object of type '<mobileye_LKA_Lane_multi>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'Left) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'Right) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'Next_Left) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'Next_Right) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mobileye_LKA_Lane_multi>) istream)
  "Deserializes a message object of type '<mobileye_LKA_Lane_multi>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'Left) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'Right) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'Next_Left) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'Next_Right) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mobileye_LKA_Lane_multi>)))
  "Returns string type for a message object of type '<mobileye_LKA_Lane_multi>"
  "mobileye/mobileye_LKA_Lane_multi")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mobileye_LKA_Lane_multi)))
  "Returns string type for a message object of type 'mobileye_LKA_Lane_multi"
  "mobileye/mobileye_LKA_Lane_multi")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mobileye_LKA_Lane_multi>)))
  "Returns md5sum for a message object of type '<mobileye_LKA_Lane_multi>"
  "c48a8b814bcf2e7a5ec962b23742a691")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mobileye_LKA_Lane_multi)))
  "Returns md5sum for a message object of type 'mobileye_LKA_Lane_multi"
  "c48a8b814bcf2e7a5ec962b23742a691")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mobileye_LKA_Lane_multi>)))
  "Returns full string definition for message of type '<mobileye_LKA_Lane_multi>"
  (cl:format cl:nil "mobileye_LKA_Lane Left~%mobileye_LKA_Lane Right~%mobileye_LKA_Lane Next_Left~%mobileye_LKA_Lane Next_Right~%~%================================================================================~%MSG: mobileye/mobileye_LKA_Lane~%uint8 MType~%uint8 Quality~%uint8 Model_degree~%float32 Position~%float32 Curvature~%float32 Heading~%float32 Curvature_deriv~%float32 Width~%float32 View_range~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mobileye_LKA_Lane_multi)))
  "Returns full string definition for message of type 'mobileye_LKA_Lane_multi"
  (cl:format cl:nil "mobileye_LKA_Lane Left~%mobileye_LKA_Lane Right~%mobileye_LKA_Lane Next_Left~%mobileye_LKA_Lane Next_Right~%~%================================================================================~%MSG: mobileye/mobileye_LKA_Lane~%uint8 MType~%uint8 Quality~%uint8 Model_degree~%float32 Position~%float32 Curvature~%float32 Heading~%float32 Curvature_deriv~%float32 Width~%float32 View_range~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mobileye_LKA_Lane_multi>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'Left))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'Right))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'Next_Left))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'Next_Right))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mobileye_LKA_Lane_multi>))
  "Converts a ROS message object to a list"
  (cl:list 'mobileye_LKA_Lane_multi
    (cl:cons ':Left (Left msg))
    (cl:cons ':Right (Right msg))
    (cl:cons ':Next_Left (Next_Left msg))
    (cl:cons ':Next_Right (Next_Right msg))
))
