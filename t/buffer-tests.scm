;; Buffer Smoke tests
(add-to-load-path "..") ; TODO: Learn how to fix this hack

(define-module (buffer-tests)
  #:use-module ((rnrs) :version (6) :select (assert))
  #:use-module (nz buffer))


;; Create a buffer with a name

(define buf (make-buffer "foo"))

;; Read the name
(assert (string=? (buffer-name buf) "foo"))

;; insert a word
(buffer-insert buf "fubar")

;; retrieve the buffer contents

(assert (string=? (buffer-contents buf) "fubar"))

;; move to the middle of the buffer and insert a char
;; retrieve buffer contents
