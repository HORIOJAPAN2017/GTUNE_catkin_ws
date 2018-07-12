
(cl:in-package :asdf)

(defsystem "test_opencv-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Nineaxes" :depends-on ("_package_Nineaxes"))
    (:file "_package_Nineaxes" :depends-on ("_package"))
    (:file "Num" :depends-on ("_package_Num"))
    (:file "_package_Num" :depends-on ("_package"))
    (:file "coordinate" :depends-on ("_package_coordinate"))
    (:file "_package_coordinate" :depends-on ("_package"))
    (:file "key" :depends-on ("_package_key"))
    (:file "_package_key" :depends-on ("_package"))
    (:file "now_num" :depends-on ("_package_now_num"))
    (:file "_package_now_num" :depends-on ("_package"))
    (:file "path" :depends-on ("_package_path"))
    (:file "_package_path" :depends-on ("_package"))
  ))