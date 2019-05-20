
(cl:in-package :asdf)

(defsystem "fusion-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "fusion_milradar_obj" :depends-on ("_package_fusion_milradar_obj"))
    (:file "_package_fusion_milradar_obj" :depends-on ("_package"))
    (:file "fusion_obj" :depends-on ("_package_fusion_obj"))
    (:file "_package_fusion_obj" :depends-on ("_package"))
    (:file "fusion_obj_multi" :depends-on ("_package_fusion_obj_multi"))
    (:file "_package_fusion_obj_multi" :depends-on ("_package"))
  ))