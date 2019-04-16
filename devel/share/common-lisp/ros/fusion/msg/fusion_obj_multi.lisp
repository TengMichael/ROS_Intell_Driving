; Auto-generated. Do not edit!


(cl:in-package fusion-msg)


;//! \htmlinclude fusion_obj_multi.msg.html

(cl:defclass <fusion_obj_multi> (roslisp-msg-protocol:ros-message)
  ((objs
    :reader objs
    :initarg :objs
    :type (cl:vector fusion-msg:fusion_obj)
   :initform (cl:make-array 0 :element-type 'fusion-msg:fusion_obj :initial-element (cl:make-instance 'fusion-msg:fusion_obj))))
)

(cl:defclass fusion_obj_multi (<fusion_obj_multi>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <fusion_obj_multi>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'fusion_obj_multi)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name fusion-msg:<fusion_obj_multi> is deprecated: use fusion-msg:fusion_obj_multi instead.")))

(cl:ensure-generic-function 'objs-val :lambda-list '(m))
(cl:defmethod objs-val ((m <fusion_obj_multi>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader fusion-msg:objs-val is deprecated.  Use fusion-msg:objs instead.")
  (objs m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <fusion_obj_multi>) ostream)
  "Serializes a message object of type '<fusion_obj_multi>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'objs))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'objs))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <fusion_obj_multi>) istream)
  "Deserializes a message object of type '<fusion_obj_multi>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'objs) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'objs)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'fusion-msg:fusion_obj))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<fusion_obj_multi>)))
  "Returns string type for a message object of type '<fusion_obj_multi>"
  "fusion/fusion_obj_multi")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'fusion_obj_multi)))
  "Returns string type for a message object of type 'fusion_obj_multi"
  "fusion/fusion_obj_multi")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<fusion_obj_multi>)))
  "Returns md5sum for a message object of type '<fusion_obj_multi>"
  "5bc9a4420be606c978ba06768536a6fa")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'fusion_obj_multi)))
  "Returns md5sum for a message object of type 'fusion_obj_multi"
  "5bc9a4420be606c978ba06768536a6fa")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<fusion_obj_multi>)))
  "Returns full string definition for message of type '<fusion_obj_multi>"
  (cl:format cl:nil "fusion_obj[] objs~%~%================================================================================~%MSG: fusion/fusion_obj~%uint16 ID~%uint32 timestamp~%float32 DistX~%float32 DistY~%float32 VrelX~%float32 VrelY~%float32 ArelX~%float32 ArelY~%uint8 Class~%float32 Length~%float32 Width~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'fusion_obj_multi)))
  "Returns full string definition for message of type 'fusion_obj_multi"
  (cl:format cl:nil "fusion_obj[] objs~%~%================================================================================~%MSG: fusion/fusion_obj~%uint16 ID~%uint32 timestamp~%float32 DistX~%float32 DistY~%float32 VrelX~%float32 VrelY~%float32 ArelX~%float32 ArelY~%uint8 Class~%float32 Length~%float32 Width~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <fusion_obj_multi>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'objs) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <fusion_obj_multi>))
  "Converts a ROS message object to a list"
  (cl:list 'fusion_obj_multi
    (cl:cons ':objs (objs msg))
))
