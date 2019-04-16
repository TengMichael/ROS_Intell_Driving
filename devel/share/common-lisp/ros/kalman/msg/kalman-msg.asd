
(cl:in-package :asdf)

(defsystem "kalman-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "radar_mobileye_data_multi" :depends-on ("_package_radar_mobileye_data_multi"))
    (:file "_package_radar_mobileye_data_multi" :depends-on ("_package"))
    (:file "radar_mobileye_data" :depends-on ("_package_radar_mobileye_data"))
    (:file "_package_radar_mobileye_data" :depends-on ("_package"))
  ))