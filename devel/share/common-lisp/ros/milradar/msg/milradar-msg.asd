
(cl:in-package :asdf)

(defsystem "milradar-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "obj208_multi" :depends-on ("_package_obj208_multi"))
    (:file "_package_obj208_multi" :depends-on ("_package"))
    (:file "obj208" :depends-on ("_package_obj208"))
    (:file "_package_obj208" :depends-on ("_package"))
    (:file "obj408_multi" :depends-on ("_package_obj408_multi"))
    (:file "_package_obj408_multi" :depends-on ("_package"))
    (:file "obj408" :depends-on ("_package_obj408"))
    (:file "_package_obj408" :depends-on ("_package"))
  ))