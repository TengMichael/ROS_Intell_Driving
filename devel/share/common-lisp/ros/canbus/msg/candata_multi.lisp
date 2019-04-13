; Auto-generated. Do not edit!


(cl:in-package canbus-msg)


;//! \htmlinclude candata_multi.msg.html

(cl:defclass <candata_multi> (roslisp-msg-protocol:ros-message)
  ((frame
    :reader frame
    :initarg :frame
    :type (cl:vector canbus-msg:candata)
   :initform (cl:make-array 0 :element-type 'canbus-msg:candata :initial-element (cl:make-instance 'canbus-msg:candata))))
)

(cl:defclass candata_multi (<candata_multi>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <candata_multi>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'candata_multi)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name canbus-msg:<candata_multi> is deprecated: use canbus-msg:candata_multi instead.")))

(cl:ensure-generic-function 'frame-val :lambda-list '(m))
(cl:defmethod frame-val ((m <candata_multi>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:frame-val is deprecated.  Use canbus-msg:frame instead.")
  (frame m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <candata_multi>) ostream)
  "Serializes a message object of type '<candata_multi>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'frame))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'frame))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <candata_multi>) istream)
  "Deserializes a message object of type '<candata_multi>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'frame) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'frame)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'canbus-msg:candata))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<candata_multi>)))
  "Returns string type for a message object of type '<candata_multi>"
  "canbus/candata_multi")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'candata_multi)))
  "Returns string type for a message object of type 'candata_multi"
  "canbus/candata_multi")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<candata_multi>)))
  "Returns md5sum for a message object of type '<candata_multi>"
  "7b71a82993b1f36499df06dc83eac42a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'candata_multi)))
  "Returns md5sum for a message object of type 'candata_multi"
  "7b71a82993b1f36499df06dc83eac42a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<candata_multi>)))
  "Returns full string definition for message of type '<candata_multi>"
  (cl:format cl:nil "candata[] frame~%~%================================================================================~%MSG: canbus/candata~%uint32 id~%uint32 timestamp~%uint8[8] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'candata_multi)))
  "Returns full string definition for message of type 'candata_multi"
  (cl:format cl:nil "candata[] frame~%~%================================================================================~%MSG: canbus/candata~%uint32 id~%uint32 timestamp~%uint8[8] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <candata_multi>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'frame) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <candata_multi>))
  "Converts a ROS message object to a list"
  (cl:list 'candata_multi
    (cl:cons ':frame (frame msg))
))
