; Auto-generated. Do not edit!


(cl:in-package mobileye-msg)


;//! \htmlinclude mobileye_Obstacle.msg.html

(cl:defclass <mobileye_Obstacle> (roslisp-msg-protocol:ros-message)
  ((ID
    :reader ID
    :initarg :ID
    :type cl:fixnum
    :initform 0)
   (PosX
    :reader PosX
    :initarg :PosX
    :type cl:float
    :initform 0.0)
   (PosY
    :reader PosY
    :initarg :PosY
    :type cl:float
    :initform 0.0)
   (Blinker
    :reader Blinker
    :initarg :Blinker
    :type cl:fixnum
    :initform 0)
   (CutState
    :reader CutState
    :initarg :CutState
    :type cl:fixnum
    :initform 0)
   (VrelX
    :reader VrelX
    :initarg :VrelX
    :type cl:float
    :initform 0.0)
   (MType
    :reader MType
    :initarg :MType
    :type cl:fixnum
    :initform 0)
   (Status
    :reader Status
    :initarg :Status
    :type cl:fixnum
    :initform 0)
   (Brake
    :reader Brake
    :initarg :Brake
    :type cl:fixnum
    :initform 0)
   (Valid
    :reader Valid
    :initarg :Valid
    :type cl:fixnum
    :initform 0)
   (Length
    :reader Length
    :initarg :Length
    :type cl:float
    :initform 0.0)
   (Width
    :reader Width
    :initarg :Width
    :type cl:float
    :initform 0.0)
   (Age
    :reader Age
    :initarg :Age
    :type cl:fixnum
    :initform 0)
   (ObsLane
    :reader ObsLane
    :initarg :ObsLane
    :type cl:fixnum
    :initform 0)
   (CIPV
    :reader CIPV
    :initarg :CIPV
    :type cl:fixnum
    :initform 0)
   (AngleRate
    :reader AngleRate
    :initarg :AngleRate
    :type cl:float
    :initform 0.0)
   (ScaleChange
    :reader ScaleChange
    :initarg :ScaleChange
    :type cl:float
    :initform 0.0)
   (ArelX
    :reader ArelX
    :initarg :ArelX
    :type cl:float
    :initform 0.0)
   (Angle
    :reader Angle
    :initarg :Angle
    :type cl:float
    :initform 0.0)
   (Replaced
    :reader Replaced
    :initarg :Replaced
    :type cl:fixnum
    :initform 0))
)

(cl:defclass mobileye_Obstacle (<mobileye_Obstacle>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mobileye_Obstacle>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mobileye_Obstacle)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye-msg:<mobileye_Obstacle> is deprecated: use mobileye-msg:mobileye_Obstacle instead.")))

(cl:ensure-generic-function 'ID-val :lambda-list '(m))
(cl:defmethod ID-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:ID-val is deprecated.  Use mobileye-msg:ID instead.")
  (ID m))

(cl:ensure-generic-function 'PosX-val :lambda-list '(m))
(cl:defmethod PosX-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:PosX-val is deprecated.  Use mobileye-msg:PosX instead.")
  (PosX m))

(cl:ensure-generic-function 'PosY-val :lambda-list '(m))
(cl:defmethod PosY-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:PosY-val is deprecated.  Use mobileye-msg:PosY instead.")
  (PosY m))

(cl:ensure-generic-function 'Blinker-val :lambda-list '(m))
(cl:defmethod Blinker-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Blinker-val is deprecated.  Use mobileye-msg:Blinker instead.")
  (Blinker m))

(cl:ensure-generic-function 'CutState-val :lambda-list '(m))
(cl:defmethod CutState-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:CutState-val is deprecated.  Use mobileye-msg:CutState instead.")
  (CutState m))

(cl:ensure-generic-function 'VrelX-val :lambda-list '(m))
(cl:defmethod VrelX-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:VrelX-val is deprecated.  Use mobileye-msg:VrelX instead.")
  (VrelX m))

(cl:ensure-generic-function 'MType-val :lambda-list '(m))
(cl:defmethod MType-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:MType-val is deprecated.  Use mobileye-msg:MType instead.")
  (MType m))

(cl:ensure-generic-function 'Status-val :lambda-list '(m))
(cl:defmethod Status-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Status-val is deprecated.  Use mobileye-msg:Status instead.")
  (Status m))

(cl:ensure-generic-function 'Brake-val :lambda-list '(m))
(cl:defmethod Brake-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Brake-val is deprecated.  Use mobileye-msg:Brake instead.")
  (Brake m))

(cl:ensure-generic-function 'Valid-val :lambda-list '(m))
(cl:defmethod Valid-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Valid-val is deprecated.  Use mobileye-msg:Valid instead.")
  (Valid m))

(cl:ensure-generic-function 'Length-val :lambda-list '(m))
(cl:defmethod Length-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Length-val is deprecated.  Use mobileye-msg:Length instead.")
  (Length m))

(cl:ensure-generic-function 'Width-val :lambda-list '(m))
(cl:defmethod Width-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Width-val is deprecated.  Use mobileye-msg:Width instead.")
  (Width m))

(cl:ensure-generic-function 'Age-val :lambda-list '(m))
(cl:defmethod Age-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Age-val is deprecated.  Use mobileye-msg:Age instead.")
  (Age m))

(cl:ensure-generic-function 'ObsLane-val :lambda-list '(m))
(cl:defmethod ObsLane-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:ObsLane-val is deprecated.  Use mobileye-msg:ObsLane instead.")
  (ObsLane m))

(cl:ensure-generic-function 'CIPV-val :lambda-list '(m))
(cl:defmethod CIPV-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:CIPV-val is deprecated.  Use mobileye-msg:CIPV instead.")
  (CIPV m))

(cl:ensure-generic-function 'AngleRate-val :lambda-list '(m))
(cl:defmethod AngleRate-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:AngleRate-val is deprecated.  Use mobileye-msg:AngleRate instead.")
  (AngleRate m))

(cl:ensure-generic-function 'ScaleChange-val :lambda-list '(m))
(cl:defmethod ScaleChange-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:ScaleChange-val is deprecated.  Use mobileye-msg:ScaleChange instead.")
  (ScaleChange m))

(cl:ensure-generic-function 'ArelX-val :lambda-list '(m))
(cl:defmethod ArelX-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:ArelX-val is deprecated.  Use mobileye-msg:ArelX instead.")
  (ArelX m))

(cl:ensure-generic-function 'Angle-val :lambda-list '(m))
(cl:defmethod Angle-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Angle-val is deprecated.  Use mobileye-msg:Angle instead.")
  (Angle m))

(cl:ensure-generic-function 'Replaced-val :lambda-list '(m))
(cl:defmethod Replaced-val ((m <mobileye_Obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye-msg:Replaced-val is deprecated.  Use mobileye-msg:Replaced instead.")
  (Replaced m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mobileye_Obstacle>) ostream)
  "Serializes a message object of type '<mobileye_Obstacle>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ID)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'PosX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'PosY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Blinker)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'CutState)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'VrelX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'MType)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Status)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Brake)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Valid)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Length))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Width))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Age)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ObsLane)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'CIPV)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'AngleRate))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ScaleChange))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ArelX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Replaced)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mobileye_Obstacle>) istream)
  "Deserializes a message object of type '<mobileye_Obstacle>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ID)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'PosX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'PosY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Blinker)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'CutState)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'VrelX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'MType)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Status)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Brake)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Valid)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Length) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Width) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Age)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ObsLane)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'CIPV)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'AngleRate) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ScaleChange) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ArelX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Replaced)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mobileye_Obstacle>)))
  "Returns string type for a message object of type '<mobileye_Obstacle>"
  "mobileye/mobileye_Obstacle")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mobileye_Obstacle)))
  "Returns string type for a message object of type 'mobileye_Obstacle"
  "mobileye/mobileye_Obstacle")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mobileye_Obstacle>)))
  "Returns md5sum for a message object of type '<mobileye_Obstacle>"
  "5d3c8bbb55939d00b6248790b776a82f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mobileye_Obstacle)))
  "Returns md5sum for a message object of type 'mobileye_Obstacle"
  "5d3c8bbb55939d00b6248790b776a82f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mobileye_Obstacle>)))
  "Returns full string definition for message of type '<mobileye_Obstacle>"
  (cl:format cl:nil "uint8 ID~%float32 PosX~%float32 PosY~%uint8 Blinker~%uint8 CutState~%float32 VrelX~%uint8 MType~%uint8 Status~%uint8 Brake~%uint8 Valid~%float32 Length~%float32 Width~%uint8 Age~%uint8 ObsLane~%uint8 CIPV~%float32 AngleRate~%float32 ScaleChange~%float32 ArelX~%float32 Angle~%uint8 Replaced~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mobileye_Obstacle)))
  "Returns full string definition for message of type 'mobileye_Obstacle"
  (cl:format cl:nil "uint8 ID~%float32 PosX~%float32 PosY~%uint8 Blinker~%uint8 CutState~%float32 VrelX~%uint8 MType~%uint8 Status~%uint8 Brake~%uint8 Valid~%float32 Length~%float32 Width~%uint8 Age~%uint8 ObsLane~%uint8 CIPV~%float32 AngleRate~%float32 ScaleChange~%float32 ArelX~%float32 Angle~%uint8 Replaced~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mobileye_Obstacle>))
  (cl:+ 0
     1
     4
     4
     1
     1
     4
     1
     1
     1
     1
     4
     4
     1
     1
     1
     4
     4
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mobileye_Obstacle>))
  "Converts a ROS message object to a list"
  (cl:list 'mobileye_Obstacle
    (cl:cons ':ID (ID msg))
    (cl:cons ':PosX (PosX msg))
    (cl:cons ':PosY (PosY msg))
    (cl:cons ':Blinker (Blinker msg))
    (cl:cons ':CutState (CutState msg))
    (cl:cons ':VrelX (VrelX msg))
    (cl:cons ':MType (MType msg))
    (cl:cons ':Status (Status msg))
    (cl:cons ':Brake (Brake msg))
    (cl:cons ':Valid (Valid msg))
    (cl:cons ':Length (Length msg))
    (cl:cons ':Width (Width msg))
    (cl:cons ':Age (Age msg))
    (cl:cons ':ObsLane (ObsLane msg))
    (cl:cons ':CIPV (CIPV msg))
    (cl:cons ':AngleRate (AngleRate msg))
    (cl:cons ':ScaleChange (ScaleChange msg))
    (cl:cons ':ArelX (ArelX msg))
    (cl:cons ':Angle (Angle msg))
    (cl:cons ':Replaced (Replaced msg))
))
