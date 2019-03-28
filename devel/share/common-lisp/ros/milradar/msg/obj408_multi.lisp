; Auto-generated. Do not edit!


(cl:in-package milradar-msg)


;//! \htmlinclude obj408_multi.msg.html

(cl:defclass <obj408_multi> (roslisp-msg-protocol:ros-message)
  ((objs
    :reader objs
    :initarg :objs
    :type (cl:vector milradar-msg:obj408)
   :initform (cl:make-array 0 :element-type 'milradar-msg:obj408 :initial-element (cl:make-instance 'milradar-msg:obj408))))
)

(cl:defclass obj408_multi (<obj408_multi>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <obj408_multi>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'obj408_multi)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name milradar-msg:<obj408_multi> is deprecated: use milradar-msg:obj408_multi instead.")))

(cl:ensure-generic-function 'objs-val :lambda-list '(m))
(cl:defmethod objs-val ((m <obj408_multi>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader milradar-msg:objs-val is deprecated.  Use milradar-msg:objs instead.")
  (objs m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <obj408_multi>) ostream)
  "Serializes a message object of type '<obj408_multi>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'objs))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'objs))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <obj408_multi>) istream)
  "Deserializes a message object of type '<obj408_multi>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'objs) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'objs)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'milradar-msg:obj408))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<obj408_multi>)))
  "Returns string type for a message object of type '<obj408_multi>"
  "milradar/obj408_multi")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'obj408_multi)))
  "Returns string type for a message object of type 'obj408_multi"
  "milradar/obj408_multi")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<obj408_multi>)))
  "Returns md5sum for a message object of type '<obj408_multi>"
  "ce84e7d845ee0f5049aa877fc739f096")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'obj408_multi)))
  "Returns md5sum for a message object of type 'obj408_multi"
  "ce84e7d845ee0f5049aa877fc739f096")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<obj408_multi>)))
  "Returns full string definition for message of type '<obj408_multi>"
  (cl:format cl:nil "obj408[] objs~%~%================================================================================~%MSG: milradar/obj408~%uint8 ID~%float32 DistX~%float32 DistY~%float32 VrelX~%float32 VrelY~%float32 RCS~%uint8 DynProp~%uint8 Orientation_rms~%uint8 MeasState~%uint8 ProbOfExist~%float32 ArelX~%float32 ArelY~%uint8 Class~%float32 OrientationAngel~%float32 Length~%float32 Width~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'obj408_multi)))
  "Returns full string definition for message of type 'obj408_multi"
  (cl:format cl:nil "obj408[] objs~%~%================================================================================~%MSG: milradar/obj408~%uint8 ID~%float32 DistX~%float32 DistY~%float32 VrelX~%float32 VrelY~%float32 RCS~%uint8 DynProp~%uint8 Orientation_rms~%uint8 MeasState~%uint8 ProbOfExist~%float32 ArelX~%float32 ArelY~%uint8 Class~%float32 OrientationAngel~%float32 Length~%float32 Width~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <obj408_multi>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'objs) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <obj408_multi>))
  "Converts a ROS message object to a list"
  (cl:list 'obj408_multi
    (cl:cons ':objs (objs msg))
))
