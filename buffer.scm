;; Copyright (C) 2017, Javier Olaechea <pirata@gmail.com>

(define-module (nz buffer)
  #:use-module (srfi srfi-9)
  #:use-module (ice-9 gap-buffer)
  #:export (make-buffer
            buffer-name
            buffer-insert
            buffer-contents))

(define-record-type buffer
  (%make-buffer name)
  buffer?
  (name buffer-name)
  ;; XXX: Gap buffers come with the their own point
  ;; (mark buffer-mark set-buffer-mark!)
  (contents %buffer-contents set-buffer-contents!))

(define (make-buffer name)
  (let ((buf (%make-buffer name)))
    (set-buffer-contents! buf (make-gap-buffer))
    buf))

(define (buffer-insert buf string)
  (gb-insert-string! (%buffer-contents buf) string))

(define (buffer-contents buf)
  (gb->string (%buffer-contents buf)))
