; Auto-generated. Do not edit!


(cl:in-package milradar-msg)


;//! \htmlinclude obj208_multi.msg.html

(cl:defclass <obj208_multi> (roslisp-msg-protocol:ros-message)
  ((objs
    :reader objs
    :initarg :objs
    :type (cl:vector milradar-msg:obj208)
   :initform (cl:make-array 0 :element-type 'milradar-msg:obj208 :initial-element (cl:make-instance 'milradar-msg:obj208))))
)

(cl:defclass obj208_multi (<obj208_multi>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <obj208_multi>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'obj208_multi)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name milradar-msg:<obj208_multi> is deprecated: use milradar-msg:obj208_multi instead.")))

(cl:ensure-generic-function 'objs-val :lambda-list '(m))
(cl:defmethod objs-val ((m <obj208_multi>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:objs-val is deprecated.  Use milradar-msg:objs instead.")
  (objs m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <obj208_multi>) ostream)
  "Serializes a message object of type '<obj208_multi>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'objs))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'objs))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <obj208_multi>) istream)
  "Deserializes a message object of type '<obj208_multi>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'objs) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'objs)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'milradar-msg:obj208))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<obj208_multi>)))
  "Returns string type for a message object of type '<obj208_multi>"
  "milradar/obj208_multi")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'obj208_multi)))
  "Returns string type for a message object of type 'obj208_multi"
  "milradar/obj208_multi")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<obj208_multi>)))
  "Returns md5sum for a message object of type '<obj208_multi>"
  "f98d0ef87b339f5337f23f3835cf534b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'obj208_multi)))
  "Returns md5sum for a message object of type 'obj208_multi"
  "f98d0ef87b339f5337f23f3835cf534b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<obj208_multi>)))
  "Returns full string definition for message of type '<obj208_multi>"
  (cl:format cl:nil "obj208[] objs~%~%================================================================================~%MSG: milradar/obj208~%uint16 ID~%uint32 timestamp~%float32 DistX~%float32 DistY~%uint8 index~%float32 VrelX~%float32 VrelY~%float32 RCS~%float32 Lifetime~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'obj208_multi)))
  "Returns full string definition for message of type 'obj208_multi"
  (cl:format cl:nil "obj208[] objs~%~%================================================================================~%MSG: milradar/obj208~%uint16 ID~%uint32 timestamp~%float32 DistX~%float32 DistY~%uint8 index~%float32 VrelX~%float32 VrelY~%float32 RCS~%float32 Lifetime~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <obj208_multi>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'objs) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <obj208_multi>))
  "Converts a ROS message object to a list"
  (cl:list 'obj208_multi
    (cl:cons ':objs (objs msg))
))
