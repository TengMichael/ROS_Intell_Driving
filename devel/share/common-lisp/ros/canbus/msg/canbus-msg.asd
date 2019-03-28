
(cl:in-package :asdf)

(defsystem "canbus-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "candata" :depends-on ("_package_candata"))
    (:file "_package_candata" :depends-on ("_package"))
    (:file "candata_multi" :depends-on ("_package_candata_multi"))
    (:file "_package_candata_multi" :depends-on ("_package"))
  ))