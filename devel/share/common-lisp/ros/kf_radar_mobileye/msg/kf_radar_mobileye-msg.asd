
(cl:in-package :asdf)

(defsystem "kf_radar_mobileye-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "radar_mobileye_data" :depends-on ("_package_radar_mobileye_data"))
    (:file "_package_radar_mobileye_data" :depends-on ("_package"))
  ))