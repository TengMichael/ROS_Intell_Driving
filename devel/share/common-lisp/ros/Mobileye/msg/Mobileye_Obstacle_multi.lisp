; Auto-generated. Do not edit!


(cl:in-package Mobileye-msg)


;//! \htmlinclude Mobileye_Obstacle_multi.msg.html

(cl:defclass <Mobileye_Obstacle_multi> (roslisp-msg-protocol:ros-message)
  ((Obstacles
    :reader Obstacles
    :initarg :Obstacles
    :type (cl:vector Mobileye-msg:Mobileye_Obstacle)
   :initform (cl:make-array 0 :element-type 'Mobileye-msg:Mobileye_Obstacle :initial-element (cl:make-instance 'Mobileye-msg:Mobileye_Obstacle))))
)

(cl:defclass Mobileye_Obstacle_multi (<Mobileye_Obstacle_multi>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Mobileye_Obstacle_multi>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Mobileye_Obstacle_multi)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name Mobileye-msg:<Mobileye_Obstacle_multi> is deprecated: use Mobileye-msg:Mobileye_Obstacle_multi instead.")))

(cl:ensure-generic-function 'Obstacles-val :lambda-list '(m))
(cl:defmethod Obstacles-val ((m <Mobileye_Obstacle_multi>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader Mobileye-msg:Obstacles-val is deprecated.  Use Mobileye-msg:Obstacles instead.")
  (Obstacles m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Mobileye_Obstacle_multi>) ostream)
  "Serializes a message object of type '<Mobileye_Obstacle_multi>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'Obstacles))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'Obstacles))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Mobileye_Obstacle_multi>) istream)
  "Deserializes a message object of type '<Mobileye_Obstacle_multi>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'Obstacles) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'Obstacles)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'Mobileye-msg:Mobileye_Obstacle))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Mobileye_Obstacle_multi>)))
  "Returns string type for a message object of type '<Mobileye_Obstacle_multi>"
  "Mobileye/Mobileye_Obstacle_multi")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Mobileye_Obstacle_multi)))
  "Returns string type for a message object of type 'Mobileye_Obstacle_multi"
  "Mobileye/Mobileye_Obstacle_multi")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Mobileye_Obstacle_multi>)))
  "Returns md5sum for a message object of type '<Mobileye_Obstacle_multi>"
  "915a530a0724fce732099e5ed869e2b4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Mobileye_Obstacle_multi)))
  "Returns md5sum for a message object of type 'Mobileye_Obstacle_multi"
  "915a530a0724fce732099e5ed869e2b4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Mobileye_Obstacle_multi>)))
  "Returns full string definition for message of type '<Mobileye_Obstacle_multi>"
  (cl:format cl:nil "Mobileye_Obstacle[] Obstacles~%~%================================================================================~%MSG: Mobileye/Mobileye_Obstacle~%uint8 ID~%float32 PosX~%float32 PosY~%uint8 Blinker~%uint8 CutState~%float32 VrelX~%uint8 MType~%uint8 Status~%uint8 Brake~%uint8 Valid~%float32 Length~%float32 Width~%uint8 Age~%uint8 ObsLane~%uint8 CIPV~%float32 AngleRate~%float32 ScaleChange~%float32 AccelX~%float32 Angle~%uint8 Replaced~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Mobileye_Obstacle_multi)))
  "Returns full string definition for message of type 'Mobileye_Obstacle_multi"
  (cl:format cl:nil "Mobileye_Obstacle[] Obstacles~%~%================================================================================~%MSG: Mobileye/Mobileye_Obstacle~%uint8 ID~%float32 PosX~%float32 PosY~%uint8 Blinker~%uint8 CutState~%float32 VrelX~%uint8 MType~%uint8 Status~%uint8 Brake~%uint8 Valid~%float32 Length~%float32 Width~%uint8 Age~%uint8 ObsLane~%uint8 CIPV~%float32 AngleRate~%float32 ScaleChange~%float32 AccelX~%float32 Angle~%uint8 Replaced~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Mobileye_Obstacle_multi>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'Obstacles) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Mobileye_Obstacle_multi>))
  "Converts a ROS message object to a list"
  (cl:list 'Mobileye_Obstacle_multi
    (cl:cons ':Obstacles (Obstacles msg))
))
