; Auto-generated. Do not edit!


(cl:in-package mobileye-msg)


;//! \htmlinclude mobileye_TSR_multi.msg.html

(cl:defclass <mobileye_TSR_multi> (roslisp-msg-protocol:ros-message)
  ((TSRs
    :reader TSRs
    :initarg :TSRs
    :type (cl:vector mobileye-msg:mobileye_TSR)
   :initform (cl:make-array 0 :element-type 'mobileye-msg:mobileye_TSR :initial-element (cl:make-instance 'mobileye-msg:mobileye_TSR))))
)

(cl:defclass mobileye_TSR_multi (<mobileye_TSR_multi>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mobileye_TSR_multi>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mobileye_TSR_multi)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye-msg:<mobileye_TSR_multi> is deprecated: use mobileye-msg:mobileye_TSR_multi instead.")))

(cl:ensure-generic-function 'TSRs-val :lambda-list '(m))
(cl:defmethod TSRs-val ((m <mobileye_TSR_multi>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:TSRs-val is deprecated.  Use mobileye-msg:TSRs instead.")
  (TSRs m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mobileye_TSR_multi>) ostream)
  "Serializes a message object of type '<mobileye_TSR_multi>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'TSRs))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'TSRs))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mobileye_TSR_multi>) istream)
  "Deserializes a message object of type '<mobileye_TSR_multi>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'TSRs) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'TSRs)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'mobileye-msg:mobileye_TSR))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mobileye_TSR_multi>)))
  "Returns string type for a message object of type '<mobileye_TSR_multi>"
  "mobileye/mobileye_TSR_multi")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mobileye_TSR_multi)))
  "Returns string type for a message object of type 'mobileye_TSR_multi"
  "mobileye/mobileye_TSR_multi")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mobileye_TSR_multi>)))
  "Returns md5sum for a message object of type '<mobileye_TSR_multi>"
  "f82b8888a7d5b24d3c3ff243115b7ee5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mobileye_TSR_multi)))
  "Returns md5sum for a message object of type 'mobileye_TSR_multi"
  "f82b8888a7d5b24d3c3ff243115b7ee5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mobileye_TSR_multi>)))
  "Returns full string definition for message of type '<mobileye_TSR_multi>"
  (cl:format cl:nil "mobileye_TSR[] TSRs~%~%================================================================================~%MSG: mobileye/mobileye_TSR~%uint8 MType~%uint8 SupType~%float32 PosX~%float32 PosY~%float32 PosZ~%uint8 FilterType~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mobileye_TSR_multi)))
  "Returns full string definition for message of type 'mobileye_TSR_multi"
  (cl:format cl:nil "mobileye_TSR[] TSRs~%~%================================================================================~%MSG: mobileye/mobileye_TSR~%uint8 MType~%uint8 SupType~%float32 PosX~%float32 PosY~%float32 PosZ~%uint8 FilterType~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mobileye_TSR_multi>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'TSRs) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mobileye_TSR_multi>))
  "Converts a ROS message object to a list"
  (cl:list 'mobileye_TSR_multi
    (cl:cons ':TSRs (TSRs msg))
))
