; Auto-generated. Do not edit!


(cl:in-package kalman-msg)


;//! \htmlinclude radar_mobileye_data.msg.html

(cl:defclass <radar_mobileye_data> (roslisp-msg-protocol:ros-message)
  ((timestamp
    :reader timestamp
    :initarg :timestamp
    :type cl:integer
    :initform 0)
   (ID
    :reader ID
    :initarg :ID
    :type cl:fixnum
    :initform 0)
   (radar_DistX
    :reader radar_DistX
    :initarg :radar_DistX
    :type cl:float
    :initform 0.0)
   (radar_DistY
    :reader radar_DistY
    :initarg :radar_DistY
    :type cl:float
    :initform 0.0)
   (radar_VrelX
    :reader radar_VrelX
    :initarg :radar_VrelX
    :type cl:float
    :initform 0.0)
   (radar_VrelY
    :reader radar_VrelY
    :initarg :radar_VrelY
    :type cl:float
    :initform 0.0)
   (radar_ArelX
    :reader radar_ArelX
    :initarg :radar_ArelX
    :type cl:float
    :initform 0.0)
   (radar_ArelY
    :reader radar_ArelY
    :initarg :radar_ArelY
    :type cl:float
    :initform 0.0)
   (mobileye_DistX
    :reader mobileye_DistX
    :initarg :mobileye_DistX
    :type cl:float
    :initform 0.0)
   (mobileye_DistY
    :reader mobileye_DistY
    :initarg :mobileye_DistY
    :type cl:float
    :initform 0.0)
   (mobileye_VrelX
    :reader mobileye_VrelX
    :initarg :mobileye_VrelX
    :type cl:float
    :initform 0.0)
   (mobileye_ArelX
    :reader mobileye_ArelX
    :initarg :mobileye_ArelX
    :type cl:float
    :initform 0.0)
   (fusion_DistX
    :reader fusion_DistX
    :initarg :fusion_DistX
    :type cl:float
    :initform 0.0)
   (fusion_DistY
    :reader fusion_DistY
    :initarg :fusion_DistY
    :type cl:float
    :initform 0.0)
   (fusion_VrelX
    :reader fusion_VrelX
    :initarg :fusion_VrelX
    :type cl:float
    :initform 0.0)
   (fusion_VrelY
    :reader fusion_VrelY
    :initarg :fusion_VrelY
    :type cl:float
    :initform 0.0)
   (fusion_ArelX
    :reader fusion_ArelX
    :initarg :fusion_ArelX
    :type cl:float
    :initform 0.0)
   (fusion_ArelY
    :reader fusion_ArelY
    :initarg :fusion_ArelY
    :type cl:float
    :initform 0.0)
   (mobileye_Width
    :reader mobileye_Width
    :initarg :mobileye_Width
    :type cl:float
    :initform 0.0)
   (mobileye_Length
    :reader mobileye_Length
    :initarg :mobileye_Length
    :type cl:float
    :initform 0.0))
)

(cl:defclass radar_mobileye_data (<radar_mobileye_data>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <radar_mobileye_data>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'radar_mobileye_data)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name kalman-msg:<radar_mobileye_data> is deprecated: use kalman-msg:radar_mobileye_data instead.")))

(cl:ensure-generic-function 'timestamp-val :lambda-list '(m))
(cl:defmethod timestamp-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:timestamp-val is deprecated.  Use kalman-msg:timestamp instead.")
  (timestamp m))

(cl:ensure-generic-function 'ID-val :lambda-list '(m))
(cl:defmethod ID-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:ID-val is deprecated.  Use kalman-msg:ID instead.")
  (ID m))

(cl:ensure-generic-function 'radar_DistX-val :lambda-list '(m))
(cl:defmethod radar_DistX-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:radar_DistX-val is deprecated.  Use kalman-msg:radar_DistX instead.")
  (radar_DistX m))

(cl:ensure-generic-function 'radar_DistY-val :lambda-list '(m))
(cl:defmethod radar_DistY-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:radar_DistY-val is deprecated.  Use kalman-msg:radar_DistY instead.")
  (radar_DistY m))

(cl:ensure-generic-function 'radar_VrelX-val :lambda-list '(m))
(cl:defmethod radar_VrelX-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:radar_VrelX-val is deprecated.  Use kalman-msg:radar_VrelX instead.")
  (radar_VrelX m))

(cl:ensure-generic-function 'radar_VrelY-val :lambda-list '(m))
(cl:defmethod radar_VrelY-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:radar_VrelY-val is deprecated.  Use kalman-msg:radar_VrelY instead.")
  (radar_VrelY m))

(cl:ensure-generic-function 'radar_ArelX-val :lambda-list '(m))
(cl:defmethod radar_ArelX-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:radar_ArelX-val is deprecated.  Use kalman-msg:radar_ArelX instead.")
  (radar_ArelX m))

(cl:ensure-generic-function 'radar_ArelY-val :lambda-list '(m))
(cl:defmethod radar_ArelY-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:radar_ArelY-val is deprecated.  Use kalman-msg:radar_ArelY instead.")
  (radar_ArelY m))

(cl:ensure-generic-function 'mobileye_DistX-val :lambda-list '(m))
(cl:defmethod mobileye_DistX-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:mobileye_DistX-val is deprecated.  Use kalman-msg:mobileye_DistX instead.")
  (mobileye_DistX m))

(cl:ensure-generic-function 'mobileye_DistY-val :lambda-list '(m))
(cl:defmethod mobileye_DistY-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:mobileye_DistY-val is deprecated.  Use kalman-msg:mobileye_DistY instead.")
  (mobileye_DistY m))

(cl:ensure-generic-function 'mobileye_VrelX-val :lambda-list '(m))
(cl:defmethod mobileye_VrelX-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:mobileye_VrelX-val is deprecated.  Use kalman-msg:mobileye_VrelX instead.")
  (mobileye_VrelX m))

(cl:ensure-generic-function 'mobileye_ArelX-val :lambda-list '(m))
(cl:defmethod mobileye_ArelX-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:mobileye_ArelX-val is deprecated.  Use kalman-msg:mobileye_ArelX instead.")
  (mobileye_ArelX m))

(cl:ensure-generic-function 'fusion_DistX-val :lambda-list '(m))
(cl:defmethod fusion_DistX-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:fusion_DistX-val is deprecated.  Use kalman-msg:fusion_DistX instead.")
  (fusion_DistX m))

(cl:ensure-generic-function 'fusion_DistY-val :lambda-list '(m))
(cl:defmethod fusion_DistY-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:fusion_DistY-val is deprecated.  Use kalman-msg:fusion_DistY instead.")
  (fusion_DistY m))

(cl:ensure-generic-function 'fusion_VrelX-val :lambda-list '(m))
(cl:defmethod fusion_VrelX-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:fusion_VrelX-val is deprecated.  Use kalman-msg:fusion_VrelX instead.")
  (fusion_VrelX m))

(cl:ensure-generic-function 'fusion_VrelY-val :lambda-list '(m))
(cl:defmethod fusion_VrelY-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:fusion_VrelY-val is deprecated.  Use kalman-msg:fusion_VrelY instead.")
  (fusion_VrelY m))

(cl:ensure-generic-function 'fusion_ArelX-val :lambda-list '(m))
(cl:defmethod fusion_ArelX-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:fusion_ArelX-val is deprecated.  Use kalman-msg:fusion_ArelX instead.")
  (fusion_ArelX m))

(cl:ensure-generic-function 'fusion_ArelY-val :lambda-list '(m))
(cl:defmethod fusion_ArelY-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:fusion_ArelY-val is deprecated.  Use kalman-msg:fusion_ArelY instead.")
  (fusion_ArelY m))

(cl:ensure-generic-function 'mobileye_Width-val :lambda-list '(m))
(cl:defmethod mobileye_Width-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:mobileye_Width-val is deprecated.  Use kalman-msg:mobileye_Width instead.")
  (mobileye_Width m))

(cl:ensure-generic-function 'mobileye_Length-val :lambda-list '(m))
(cl:defmethod mobileye_Length-val ((m <radar_mobileye_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kalman-msg:mobileye_Length-val is deprecated.  Use kalman-msg:mobileye_Length instead.")
  (mobileye_Length m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <radar_mobileye_data>) ostream)
  "Serializes a message object of type '<radar_mobileye_data>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'timestamp)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'timestamp)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'timestamp)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'timestamp)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ID)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'radar_DistX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'radar_DistY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'radar_VrelX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'radar_VrelY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'radar_ArelX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'radar_ArelY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'mobileye_DistX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'mobileye_DistY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'mobileye_VrelX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'mobileye_ArelX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'fusion_DistX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'fusion_DistY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'fusion_VrelX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'fusion_VrelY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'fusion_ArelX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'fusion_ArelY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'mobileye_Width))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'mobileye_Length))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <radar_mobileye_data>) istream)
  "Deserializes a message object of type '<radar_mobileye_data>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'timestamp)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'timestamp)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'timestamp)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'timestamp)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ID)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'radar_DistX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'radar_DistY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'radar_VrelX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'radar_VrelY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'radar_ArelX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'radar_ArelY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'mobileye_DistX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'mobileye_DistY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'mobileye_VrelX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'mobileye_ArelX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fusion_DistX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fusion_DistY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fusion_VrelX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fusion_VrelY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fusion_ArelX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fusion_ArelY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'mobileye_Width) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'mobileye_Length) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<radar_mobileye_data>)))
  "Returns string type for a message object of type '<radar_mobileye_data>"
  "kalman/radar_mobileye_data")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'radar_mobileye_data)))
  "Returns string type for a message object of type 'radar_mobileye_data"
  "kalman/radar_mobileye_data")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<radar_mobileye_data>)))
  "Returns md5sum for a message object of type '<radar_mobileye_data>"
  "4975d13f61a0fd1bd7c6d84c5f81c19b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'radar_mobileye_data)))
  "Returns md5sum for a message object of type 'radar_mobileye_data"
  "4975d13f61a0fd1bd7c6d84c5f81c19b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<radar_mobileye_data>)))
  "Returns full string definition for message of type '<radar_mobileye_data>"
  (cl:format cl:nil "uint32 timestamp~%uint8 ID~%float32 radar_DistX~%float32 radar_DistY~%float32 radar_VrelX~%float32 radar_VrelY~%float32 radar_ArelX~%float32 radar_ArelY~%float32 mobileye_DistX~%float32 mobileye_DistY~%float32 mobileye_VrelX~%float32 mobileye_ArelX~%float32 fusion_DistX~%float32 fusion_DistY~%float32 fusion_VrelX~%float32 fusion_VrelY~%float32 fusion_ArelX~%float32 fusion_ArelY~%float32 mobileye_Width~%float32 mobileye_Length~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'radar_mobileye_data)))
  "Returns full string definition for message of type 'radar_mobileye_data"
  (cl:format cl:nil "uint32 timestamp~%uint8 ID~%float32 radar_DistX~%float32 radar_DistY~%float32 radar_VrelX~%float32 radar_VrelY~%float32 radar_ArelX~%float32 radar_ArelY~%float32 mobileye_DistX~%float32 mobileye_DistY~%float32 mobileye_VrelX~%float32 mobileye_ArelX~%float32 fusion_DistX~%float32 fusion_DistY~%float32 fusion_VrelX~%float32 fusion_VrelY~%float32 fusion_ArelX~%float32 fusion_ArelY~%float32 mobileye_Width~%float32 mobileye_Length~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <radar_mobileye_data>))
  (cl:+ 0
     4
     1
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <radar_mobileye_data>))
  "Converts a ROS message object to a list"
  (cl:list 'radar_mobileye_data
    (cl:cons ':timestamp (timestamp msg))
    (cl:cons ':ID (ID msg))
    (cl:cons ':radar_DistX (radar_DistX msg))
    (cl:cons ':radar_DistY (radar_DistY msg))
    (cl:cons ':radar_VrelX (radar_VrelX msg))
    (cl:cons ':radar_VrelY (radar_VrelY msg))
    (cl:cons ':radar_ArelX (radar_ArelX msg))
    (cl:cons ':radar_ArelY (radar_ArelY msg))
    (cl:cons ':mobileye_DistX (mobileye_DistX msg))
    (cl:cons ':mobileye_DistY (mobileye_DistY msg))
    (cl:cons ':mobileye_VrelX (mobileye_VrelX msg))
    (cl:cons ':mobileye_ArelX (mobileye_ArelX msg))
    (cl:cons ':fusion_DistX (fusion_DistX msg))
    (cl:cons ':fusion_DistY (fusion_DistY msg))
    (cl:cons ':fusion_VrelX (fusion_VrelX msg))
    (cl:cons ':fusion_VrelY (fusion_VrelY msg))
    (cl:cons ':fusion_ArelX (fusion_ArelX msg))
    (cl:cons ':fusion_ArelY (fusion_ArelY msg))
    (cl:cons ':mobileye_Width (mobileye_Width msg))
    (cl:cons ':mobileye_Length (mobileye_Length msg))
))
