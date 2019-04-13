; Auto-generated. Do not edit!


(cl:in-package canbus-msg)


;//! \htmlinclude candata.msg.html

(cl:defclass <candata> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (data
    :reader data
    :initarg :data
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 8 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass candata (<candata>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <candata>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'candata)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name canbus-msg:<candata> is deprecated: use canbus-msg:candata instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <candata>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:id-val is deprecated.  Use canbus-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <candata>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:data-val is deprecated.  Use canbus-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <candata>) ostream)
  "Serializes a message object of type '<candata>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'id)) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <candata>) istream)
  "Deserializes a message object of type '<candata>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'id)) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array 8))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i 8)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<candata>)))
  "Returns string type for a message object of type '<candata>"
  "canbus/candata")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'candata)))
  "Returns string type for a message object of type 'candata"
  "canbus/candata")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<candata>)))
  "Returns md5sum for a message object of type '<candata>"
  "2f636bf314749eeb00e7f85696286658")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'candata)))
  "Returns md5sum for a message object of type 'candata"
  "2f636bf314749eeb00e7f85696286658")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<candata>)))
  "Returns full string definition for message of type '<candata>"
  (cl:format cl:nil "uint32 id~%#uint32 timestamp~%uint8[8] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'candata)))
  "Returns full string definition for message of type 'candata"
  (cl:format cl:nil "uint32 id~%#uint32 timestamp~%uint8[8] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <candata>))
  (cl:+ 0
     4
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <candata>))
  "Converts a ROS message object to a list"
  (cl:list 'candata
    (cl:cons ':id (id msg))
    (cl:cons ':data (data msg))
))
