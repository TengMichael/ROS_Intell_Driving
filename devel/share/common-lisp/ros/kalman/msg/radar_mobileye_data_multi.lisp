; Auto-generated. Do not edit!


(cl:in-package kalman-msg)


;//! \htmlinclude radar_mobileye_data_multi.msg.html

(cl:defclass <radar_mobileye_data_multi> (roslisp-msg-protocol:ros-message)
  ((objs
    :reader objs
    :initarg :objs
    :type (cl:vector kalman-msg:radar_mobileye_data)
   :initform (cl:make-array 0 :element-type 'kalman-msg:radar_mobileye_data :initial-element (cl:make-instance 'kalman-msg:radar_mobileye_data))))
)

(cl:defclass radar_mobileye_data_multi (<radar_mobileye_data_multi>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <radar_mobileye_data_multi>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'radar_mobileye_data_multi)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name kalman-msg:<radar_mobileye_data_multi> is deprecated: use kalman-msg:radar_mobileye_data_multi instead.")))

(cl:ensure-generic-function 'objs-val :lambda-list '(m))
(cl:defmethod objs-val ((m <radar_mobileye_data_multi>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:objs-val is deprecated.  Use kalman-msg:objs instead.")
  (objs m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <radar_mobileye_data_multi>) ostream)
  "Serializes a message object of type '<radar_mobileye_data_multi>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'objs))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'objs))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <radar_mobileye_data_multi>) istream)
  "Deserializes a message object of type '<radar_mobileye_data_multi>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'objs) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'objs)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'kalman-msg:radar_mobileye_data))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<radar_mobileye_data_multi>)))
  "Returns string type for a message object of type '<radar_mobileye_data_multi>"
  "kalman/radar_mobileye_data_multi")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'radar_mobileye_data_multi)))
  "Returns string type for a message object of type 'radar_mobileye_data_multi"
  "kalman/radar_mobileye_data_multi")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<radar_mobileye_data_multi>)))
  "Returns md5sum for a message object of type '<radar_mobileye_data_multi>"
  "d125692124264bb8d5228e34fd2a6d74")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'radar_mobileye_data_multi)))
  "Returns md5sum for a message object of type 'radar_mobileye_data_multi"
  "d125692124264bb8d5228e34fd2a6d74")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<radar_mobileye_data_multi>)))
  "Returns full string definition for message of type '<radar_mobileye_data_multi>"
  (cl:format cl:nil "radar_mobileye_data[] objs~%~%================================================================================~%MSG: kalman/radar_mobileye_data~%uint32 timestamp~%uint8 ID~%float32 radar_DistX~%float32 radar_DistY~%float32 radar_VrelX~%float32 radar_VrelY~%float32 radar_ArelX~%float32 radar_ArelY~%float32 mobileye_DistX~%float32 mobileye_DistY~%float32 mobileye_VrelX~%float32 mobileye_ArelX~%float32 fusion_DistX~%float32 fusion_DistY~%float32 fusion_VrelX~%float32 fusion_VrelY~%float32 fusion_ArelX~%float32 fusion_ArelY~%float32 mobileye_Width~%float32 mobileye_Length~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'radar_mobileye_data_multi)))
  "Returns full string definition for message of type 'radar_mobileye_data_multi"
  (cl:format cl:nil "radar_mobileye_data[] objs~%~%================================================================================~%MSG: kalman/radar_mobileye_data~%uint32 timestamp~%uint8 ID~%float32 radar_DistX~%float32 radar_DistY~%float32 radar_VrelX~%float32 radar_VrelY~%float32 radar_ArelX~%float32 radar_ArelY~%float32 mobileye_DistX~%float32 mobileye_DistY~%float32 mobileye_VrelX~%float32 mobileye_ArelX~%float32 fusion_DistX~%float32 fusion_DistY~%float32 fusion_VrelX~%float32 fusion_VrelY~%float32 fusion_ArelX~%float32 fusion_ArelY~%float32 mobileye_Width~%float32 mobileye_Length~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <radar_mobileye_data_multi>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'objs) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <radar_mobileye_data_multi>))
  "Converts a ROS message object to a list"
  (cl:list 'radar_mobileye_data_multi
    (cl:cons ':objs (objs msg))
))
